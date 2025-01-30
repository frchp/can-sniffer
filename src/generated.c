#include "stm32l552xx.h"

void clock_init(void);
void gpio_init(void);
void can1_init(void);
void lpuart1_init(void);
void lpuart1_transmit(char *str);
void can1_rx0_interrupt_handler(void);
void watchdog_init(void);
void watchdog_refresh(void);

int main(void) {
    clock_init();
    gpio_init();
    can1_init();
    lpuart1_init();
    watchdog_init();

    while (1) {
        watchdog_refresh(); // Refresh watchdog to prevent reset
    }
}

void clock_init(void) {
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
    RCC->APB1ENR1 |= RCC_APB1ENR1_CAN1EN;
    RCC->APB1ENR2 |= RCC_APB1ENR2_LPUART1EN;
}

void gpio_init(void) {
    // Configure PB8 as CAN1_RX and PB9 as CAN1_TX (AF9)
    GPIOB->MODER &= ~(GPIO_MODER_MODE8 | GPIO_MODER_MODE9);
    GPIOB->MODER |= (2U << GPIO_MODER_MODE8_Pos) | (2U << GPIO_MODER_MODE9_Pos);
    GPIOB->AFR[1] |= (9U << GPIO_AFRH_AFSEL8_Pos) | (9U << GPIO_AFRH_AFSEL9_Pos);
    
    // Configure PA2 as LPUART1_TX (AF8)
    GPIOA->MODER &= ~GPIO_MODER_MODE2;
    GPIOA->MODER |= (2U << GPIO_MODER_MODE2_Pos);
    GPIOA->AFR[0] |= (8U << GPIO_AFRL_AFSEL2_Pos);
}

void can1_init(void) {
    // Enable clock to FDCAN
    RCC->CCIPR |= (3U << RCC_CCIPR_FDCANSEL_Pos);  // SYSCLK source
    
    // Enter initialization mode
    FDCAN1->CCCR |= FDCAN_CCCR_INIT;
    while (!(FDCAN1->CCCR & FDCAN_CCCR_INIT));
    
    // Configure nominal bit timing (Assuming 40MHz clock, 500 kbps CAN)
    FDCAN1->NBTP = (10U << 16) | (13U << 8) | (3U << 0);
    
    // Enable global filter to accept all messages
    FDCAN1->GFC = 0;
    
    // Enable RX FIFO 0 new message interrupt
    FDCAN1->IE |= FDCAN_IE_RF0NE;
    NVIC_EnableIRQ(FDCAN1_IT0_IRQn);
    
    // Exit initialization mode
    FDCAN1->CCCR &= ~FDCAN_CCCR_INIT;
    while (FDCAN1->CCCR & FDCAN_CCCR_INIT);
}

void lpuart1_init(void) {
    // Configure baud rate (Assuming 80MHz clock, 115200 baud)
    LPUART1->BRR = 6944;
    LPUART1->CR1 |= USART_CR1_TE | USART_CR1_UE;
}

void lpuart1_transmit(char *str) {
    while (*str) {
        while (!(LPUART1->ISR & USART_ISR_TXE));
        LPUART1->TDR = *str++;
    }
}

void FDCAN1_IT0_IRQHandler(void) {
    if (FDCAN1->IR & FDCAN_IR_RF0N) {
        FDCAN1->IR = FDCAN_IR_RF0N;  // Clear interrupt flag
        
        if (FDCAN1->RXF0S & FDCAN_RXF0S_F0FL_Msk) {  // Check if FIFO has data
            uint32_t id = FDCAN1->RXF0A & 0x1FFFFFFF;
            uint32_t data = FDCAN1->RXF0D[0];
            
            char msg[50];
            sprintf(msg, "CAN ID: 0x%08X, Data: 0x%08X\r\n", id, data);
            lpuart1_transmit(msg);
            
            FDCAN1->RXF0A = (FDCAN1->RXF0A & FDCAN_RXF0A_F0AI_Msk);  // Acknowledge message
        }
    }
}

void watchdog_init(void) {
    // Enable independent watchdog (IWDG)
    IWDG->KR = 0xCCCC; // Start the watchdog
    IWDG->KR = 0x5555; // Enable register access
    IWDG->PR = 0x06;   // Set prescaler (4s timeout with 32kHz LSI)
    IWDG->RLR = 0xFFF; // Reload value
    IWDG->KR = 0xAAAA; // Reload counter
}

void watchdog_refresh(void) {
    IWDG->KR = 0xAAAA; // Refresh watchdog counter
}
