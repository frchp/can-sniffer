#include <stdlib.h>

#include "ring_buffer.h"

#include "bsp.h"

/**
 * Function to initialize a buffer structure with the given size.
 * Returns true if we were able to initialize the buffer and false otherwise.
 */
bool RingBuffer_Init(RingBuffer_t *ps_buff, uint16_t u16_size)
{
  bool b_ret = true;

  if (u16_size > RING_BUFFER_LEN_MAX || ps_buff == NULL) 
  {
    b_ret = false;
  }
  else
  {
    // Atomically initialize the structure
    uint32_t u32_status = bsp_enterCritical();
    ps_buff->u16_size = u16_size;
    ps_buff->u16_head = 0u;
    ps_buff->u16_count = 0u;
    bsp_exitCritical(u32_status);
  }

  return b_ret;
}

/**
 * Add the specified data pointer to the end of the buffer. If the buffer is
 * full, the oldest queued item will be replaced by default.
 * Returns true if the data was stored and false otherwise.
 */
bool RingBuffer_Add(RingBuffer_t *ps_buff, uint8_t arg_u8Data)
{
  bool b_ret = true;

  if (ps_buff == NULL) {
    b_ret = false;
  }
  else
  {
    uint32_t u32_status = bsp_enterCritical();
    if (ps_buff->u16_count < ps_buff->u16_size) {
      uint16_t loc_u16Index = (ps_buff->u16_head + ps_buff->u16_count) % ps_buff->u16_size;

      // Insert this item at the end of the queue
      ps_buff->au8_data[loc_u16Index] = arg_u8Data;
      ps_buff->u16_count++;
    } else {
      // Overwrite what's at the head of the queue since we're out of space
      ps_buff->au8_data[ps_buff->u16_head] = arg_u8Data;
      ps_buff->u16_head = (ps_buff->u16_head + 1) % ps_buff->u16_size;
    }
    bsp_exitCritical(u32_status);
  }

  return b_ret;
}

/**
 * Return a pointer to the head of the buffer without removing that item.
 */
uint8_t RingBuffer_Peek(RingBuffer_t *ps_buff)
{
  uint8_t loc_u8Ret = 0u;

  if (ps_buff == NULL) {
    // Nothing to do
  }
  else
  {
    uint32_t u32_status = bsp_enterCritical();
    if (ps_buff->u16_count > 0) {
      loc_u8Ret = ps_buff->au8_data[ps_buff->u16_head];
    }
    bsp_exitCritical(u32_status);
  }

  return loc_u8Ret;
}

/**
 * Remove an item from the head of the buffer and return its pointer.
 */
uint8_t RingBuffer_Remove(RingBuffer_t *ps_buff)
{
  uint8_t loc_u8Ret = 0u;

  if (ps_buff == NULL) {
    // Nothing to do
  }
  else
  {
    uint32_t u32_status = bsp_enterCritical();
    if (ps_buff->u16_count > 0) {
      loc_u8Ret = ps_buff->au8_data[ps_buff->u16_head];
      ps_buff->u16_head = (ps_buff->u16_head + 1) % ps_buff->u16_size;
      ps_buff->u16_count--;
    }
    bsp_exitCritical(u32_status);
  }

  return loc_u8Ret;
}

/**
 * Determine if the given buffer is empty.
 * Returns true if the buffer is empty and false otherwise.
 */
bool RingBuffer_IsEmpty(RingBuffer_t *ps_buff)
{
  bool b_ret = true;

  if (ps_buff == NULL) {
    // Nothing to do
  }
  else
  {
    uint32_t u32_status = bsp_enterCritical();
    b_ret = (ps_buff->u16_count == 0);
    bsp_exitCritical(u32_status);
  }

  return b_ret;
}

/**
 * Determine if the given buffer is full.
 * Returns true if the buffer is full and false otherwise.
 */
bool RingBuffer_IsFull(RingBuffer_t *ps_buff)
{
  bool b_ret = true;

  if (ps_buff == NULL) {
    // Nothing to do
  }
  else
  {
    uint32_t u32_status = bsp_enterCritical();
    b_ret = (ps_buff->u16_count == ps_buff->u16_size);
    bsp_exitCritical(u32_status);
  }

  return b_ret;
}