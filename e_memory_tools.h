#include <pebble.h>
#pragma once

// Allocate a memory block at the bottom of the available heap
// (may fail if the heap is already fragmented; if so it will just behave like regular malloc() )
extern void* malloc_low(size_t s);