/*
Kevin_Mazariegos_Diego_Mateos
ECE 154A - Fall 2012
Lab 2 - Mystery Caches
Due: 12/3/12, 11:00 pm

Mystery Cache Geometries:
mystery0:
    block size = 64 bytes
    cache size = 4194304 bytes
    associativity = 16
mystery1:
    block size = 4 bytes
    cache size = 4096 bytes
    associativity = 1
mystery2:
    block size = 32 bytes
    cache size = 4218 bytes
    associativity = 128
*/

#include <stdlib.h>
#include <stdio.h>
#include "mystery-cache.h"

/* 
   Returns the size (in bytes) of the cache
*/
int get_cache_size(int block_size) {
   int access = 0; // var to track

 int exitBlock = block_size; // tracks boundary for next block size
 int numBlocks = 1; // tracks cache blocks


flush_cache();
 access_cache(0);
    //loop until cache misses
 while (access_cache(0)) {
 access = block_size;
 while (access <= exitBlock) {
 access += block_size; 
 access_cache(access);

}

 exitBlock += block_size; // move to next boundary
 numBlocks++;


}


 //
return (numBlocks * block_size);
}

/*
   Returns the associativity of the cache
*/
int get_cache_assoc(int size) {
   flush_cache();
 access_cache(0);


 int block_size = size; // assume block size = cache size
 int access = 0; //tracks address
 int exitBlock = 1;
 int associativity = 0;

//loop until cache miss
 while (access_cache(0)) {

 associativity = 0;
 access = block_size;
// checks for boundary of the associativity level
 while ((access == exitBlock) || (access < exitBlock)) {
 associativity++;
 access += block_size;
 access_cache(access);
 }

 exitBlock += block_size;
 }

 return associativity;
}

/*
   Returns the size (in bytes) of each block in the cache.
*/
int get_block_size() {
   int access = 0;
    int block_size = 0;
    access_cache(0);
    while(access_cache(access)) {
        access+=1;
        block_size++;
    
    return block_size;
}

int main(void) {
    int size;
    int assoc;
    int block_size;
    
    /* The cache needs to be initialized, but the parameters will be
       ignored by the mystery caches, as they are hard coded.
       You can test your geometry parameter discovery routines by 
       calling cache_init() w/ your own size and block size values. */
    cache_init(0,0);
    
    block_size = get_block_size();
    size = get_cache_size(block_size);
    assoc = get_cache_assoc(size);

    printf("Cache size: %d bytes\n", size);
    printf("Cache associativity: %d\n", assoc);
    printf("Cache block size: %d bytes\n", block_size);
    
    return EXIT_SUCCESS;
}

