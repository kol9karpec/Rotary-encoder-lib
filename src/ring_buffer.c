#include "../headers/ring_buffer.h"

uint8_t push(uint8_t data, ring_buffer_t * ring_buffer) {
  uint8_t result = 1;
  
  if(ring_buffer->start == ring_buffer->end) { //check for buffer is full
      result = 0;
  } else {
    if(is_empty(ring_buffer)) {
        ring_buffer->data[ring_buffer->start] = data;
    } else {
        ring_buffer->data[ring_buffer->end] = data;
        if(ring_buffer->end == DEF_SIZE-1) {
          ring_buffer->end = 0;
        } else {
          ring_buffer->end++;
        }
    } 
  }

  return result;
}

uint8_t pop(volatile uint8_t * dest, ring_buffer_t * ring_buffer) {
  uint8_t result = 1;

  if(is_empty(ring_buffer)) {
    result = 0;
    *dest = ring_buffer->data[ring_buffer->start];
  } else {
    *dest = ring_buffer->data[ring_buffer->start++];
  }

  return result;
}

uint8_t is_empty(ring_buffer_t * ring_buffer) {
  uint8_t result = 0;

  if((ring_buffer->start+1 == ring_buffer->end) || \
      ((ring_buffer->start==DEF_SIZE-1) && \
        (ring_buffer->end==0))) {
    result = 1;
  }
  return result;
}

void clean(ring_buffer_t * ring_buffer) {
  ring_buffer->start = 0;
  ring_buffer->end = 1;
}