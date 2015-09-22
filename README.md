# pebble_memory_tools
A few tools to manage memory allocation of Pebble watchapps

One of the big issues when programming for Pebble is the small available memory.
You can do plenty with 64 KB of ram, but you can be easily short if you don't take a few precautions.

Here are a few tools that can make your life easier.

## malloc_low()

The default malloc() function allocates the higher available address block of the requested size.
This can easily cause memory fragmentation, for example if you allocate 2 blocks and free the first one.

You can try to allocate the "long lasting blocks" first, but it's not always possible.

Typical usecase is for example when you want to load a compressed resource into memory to unpack it; if you cannot allocate the uncompressed buffer first (because you won't know the size of uncompressed data before you loaded the compressed resource) you will have to:
- Allocate a block of the size of the compressed resource
- Load the resource into memory
- Do some parsing to find the size of the uncompressed data
- Allocate a block for the uncompressed data
- Uncompress the data
- Free the first block

Now, you have an empty hole that can prevent you to allocate big blocks, even if you have enough ram left.

(One of) the (many) solution(s) is to use malloc_low for your short lasting blocks (the ones that will be freed shortly after use). This function behaves exactly like the default malloc() function, except it allocates the bloc at the very low end of the heap.

Note that if your heap is already frangmented, malloc_low will fail finding low heap and will behave like regular malloc().
