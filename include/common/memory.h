/*********************************************************************************************
@file - memory.h

@brief - Memory.h file is the header file for memory manipulation functions

This is the header file for memory functions in "memory.c"
The included function declarations are
1. memmove
2. memcpy
3. memset
4. memzero
5. reverse
6. reverse_words
7. free_words
***Updated for DMA March 27th***
8. memmove_dma
9. memset_dma

@author - Scott McElroy

@date - (February 5, 2018)-Updated March 27th

Created for ECEN5813
**********************************************************************************************/

#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdlib.h>
#include <stdint.h>

/********************************************************************************************
@brief - moves memory from one location to another

The memmove function is passed a source and destination address,
the contents at the source address get temporarily copied completely 
depending on the length specified when called and then moved to the
destination address.
This function is a non-corruption based moved even if the source and 
destination is overlapping.

@param - *src: source address 
@param - *dst: destination address
@param - length: size of data
@return - dst: destination address
********************************************************************************************/

uint8_t *my_memmove(uint8_t *src, uint8_t *dst, uint32_t length);

/********************************************************************************************
@brief - this is a memory coping function from one location to another

The memcpy function is passed a source and destination address,
the contents is directly passed to the destinaion address
This function could be destructive if the dst overrides the source.

@param - *src: source address 
@param - *dst: destination address
@param - length: size of data
@return - dst: destination address
*********************************************************************************************/

uint8_t *my_memcpy(uint8_t *src, uint8_t *dst, size_t length);

/**********************************************************************************************
@brief - This function set a block of memory to a certain value

The memset function is passed a source address and a value,
the value that is passed on a function call is put into the destinaion address

@param - *src: source address 
@param - length: size of data
@param - value: value of data
@return -  src: source address
**********************************************************************************************/

uint8_t *my_memset(uint8_t *src, uint32_t length, uint8_t value);

/**********************************************************************************************
@brief- This function zeros out a block of memory

The memzero function is passed a source address and a length,
the function zeros out all of the memory for the specified length.

@param - *src: source address 
@param - length: size of data
@return -  src: source address of zeroed blocks
**********************************************************************************************/

uint8_t *my_memzero(uint8_t *src, size_t length);

/**********************************************************************************************
@brief- This function zeros out a block of memory

The memzero function is passed a source address and a length,
the function zeros out all of the memory for the specified length.

@param - *src: source address 
@param - length: size of data
@return -  src: source address of zeroed blocks
**********************************************************************************************/

uint8_t *my_reverse(uint8_t *src, size_t length);

/**********************************************************************************************
@brief - This function dynamically reserve a block of memory

The reserve function is passed a length,
the function reserves the memory based on the length so memory can be dynamically allocated.
The function returns the location of the newly allocated memory.

@param - length: address of reserved memory
@return - mem_loc: Returns the location address of the reserved memory block
**********************************************************************************************/

void *reserve_words(uint32_t length);

/**********************************************************************************************
brief - This functions frees a block of memory that was reserved

The free function is passed a source address,
the function frees up the memory that has been dynamically allocated.

@param - *src: source address
@return - Returns a 0 if successful and 1 if it fails
**********************************************************************************************/

uint8_t free_words(void *src);


#endif /*__MEMORY_H__*/

/*********************************************************************************************/
/*****************************End of File*****************************************************/
/*********************************************************************************************/
