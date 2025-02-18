# CAN sniffer
Based on [pcb-motor-driver](https://github.com/frchp/pcb-motor-driver) template.

![Build status](https://github.com/frchp/can-sniffer/actions/workflows/actions.yml/badge.svg)

![Sequence diagram](uml/scenario_incoming_can.png)

## Toolchain
- [ARM GNU](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)
- [CMake](https://cmake.org/download/)
- [Ninja](https://github.com/ninja-build/ninja/releases)
- [ST Link](https://www.st.com/en/development-tools/stm32cubeprog.html)
- [OpenOCD](https://packages.msys2.org/packages/mingw-w64-x86_64-openocd)

## VS Code Extensions

- CMake
- CMake Tools
- Cortex-Debug
- Memory View
- RTOS Views

## How to build
 - Have ninja.exe path in your PATH, CMake installed, gcc-arm-none-eabi installed
 - Configure 
```cmake --preset Debug/Release```
 - Build
```cmake --build build```

## MCU specific file

Each MCU has their own ARM compiler flags. Those are defined in a individual module for portability.
> **General rule for settings would be as per table below:**

| STM32 Family | -mcpu           | -mfpu         | -mfloat-abi |
| ------------ | --------------- | ------------- | ----------- |
| STM32F0      | `cortex-m0`     | `Not used`    | `soft`      |
| STM32F1      | `cortex-m3`     | `Not used`    | `soft`      |
| STM32F2      | `cortex-m3`     | `Not used`    | `soft`      |
| STM32F3      | `cortex-m4`     | `fpv4-sp-d16` | `hard`      |
| STM32F4      | `cortex-m4`     | `fpv4-sp-d16` | `hard`      |
| STM32F7 SP   | `cortex-m7`     | `fpv5-sp-d16` | `hard`      |
| STM32F7 DP   | `cortex-m7`     | `fpv5-d16`    | `hard`      |
| STM32G0      | `cortex-m0plus` | `Not used`    | `soft`      |
| STM32C0      | `cortex-m0plus` | `Not used`    | `soft`      |
| STM32G4      | `cortex-m4`     | `fpv4-sp-d16` | `hard`      |
| STM32H7      | `cortex-m7`     | `fpv5-d16`    | `hard`      |
| STM32L0      | `cortex-m0plus` | `Not used`    | `soft`      |
| STM32L1      | `cortex-m3`     | `Not used`    | `soft`      |
| STM32L4      | `cortex-m4`     | `fpv4-sp-d16` | `hard`      |
| STM32L5      | `cortex-m33`    | `fpv5-sp-d16` | `hard`      |
| STM32U5      | `cortex-m33`    | `fpv5-sp-d16` | `hard`      |
| STM32WB      | `cortex-m4`     | `fpv4-sp-d16` | `hard`      |
| STM32WL CM4  | `cortex-m4`     | `Not used`    | `soft`      |
| STM32WL CM0  | `cortex-m0plus` | `Not used`    | `soft`      |

## Documentation
 - [FreeRTOS and Low power](https://www.freertos.org/low-power-ARM-cortex-rtos)
 - [Optimizing low power](https://mcuoneclipse.com/2024/05/22/low-power-optimization-techniques-for-arm-cortex-m0-microcontrollers/)

## HW
See [schematic](hw/can-sniffer.pdf).