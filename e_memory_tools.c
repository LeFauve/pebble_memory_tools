#include "e_memory_tools.h"

void* malloc_low(size_t s) {
  size_t h = (heap_bytes_free() - s - 8)&~3;
  uint8_t* nofrag = malloc(h);
  nofrag && (*(uint8_t volatile*)nofrag = 0);
  void* ptr = malloc(s);
  if(nofrag) free(nofrag);
  return ptr;
}
