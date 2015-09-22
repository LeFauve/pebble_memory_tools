#include "e_memory_tools.h"

void* malloc_low(size_t s) {
  size_t h = (heap_bytes_free() - s - 8)&~3;
  uint8_t* nofrag = malloc(h);
  *(uint8_t volatile*)nofrag = 0;
  void* ptr = malloc(s);
  free(nofrag);
  return ptr;
}