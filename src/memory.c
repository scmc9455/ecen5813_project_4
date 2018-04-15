/*********************************************************************************************
@file - memory.c

@brief - Memory.c file is a source file for memory manipulation functions

This is the source file for memory functions "memory.c"
The included functions are
1. memmove
2. memcpy
3. memset
4. memzero
5. reverse
6. reverse_words
7. free_words

@author - Scott McElroy

@date - (February 2, 2018)-Updated March 27th

Created for ECEN5813
**********************************************************************************************/

#include "memory.h"

/*********************************************************************************************/
/****************************my_memmove******************************************************/
/**********************************************************************************************
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
**********************************************************************************************/

uint8_t  *my_memmove(uint8_t *src, uint8_t *dst, uint32_t length)
{
    /* Check to see if pointer were passed properly */
    /* if pointer were not properly passed then the function returns a NULL */
    if((src==NULL) || (dst==NULL))
    {
        return NULL;  
    }
               
    uint8_t *temp_store_loc= (uint8_t *)malloc(length);       
    uint32_t var_len = 0;
  
    /* This section of function copies the source contents to the 
    variable location to avoid corruption */
    while(var_len < length)
    {
        *(temp_store_loc + var_len) = *(src + var_len);
        var_len++;               
    }
    
    var_len = 0;
    /* This section of function copies the variable contents to the destination 
    location to copy even though their might be overlap */
    while(var_len < length)
    {
        *(dst + var_len) = *(temp_store_loc + var_len);
        var_len++;
    }
    	
    /* Check to see if the dst pointer is greater then zero and return NULL if its incorrect */ 
    return ! dst  ? dst : NULL;     
}

/*********************************************************************************************/
/*********************************memcpy******************************************************/
/**********************************************************************************************
@brief - this is a memory coping function from one location to another

The memcpy function is passed a source and destination address,
the contents is directly passed to the destinaion address
This function could be destructive if the dst overrides the source.

@param - *src: source address 
@param - *dst: destination address
@param - length: size of data
@return - dst: destination address
**********************************************************************************************/
uint8_t  *my_memcpy(uint8_t *src, uint8_t *dst, size_t length)
{
    /* Check to see if pointer were passed properly */
    /* if pointer were not properly passed then the function returns a NULL */
    if((src==NULL) || (dst==NULL))
    {
        return NULL;  
    }
	
    uint8_t var_len = 0;

    /* This section takes the contents of the source and move it to the destination address */
    while(var_len < length)
    {
        *(dst + var_len) = *(src + var_len);
        var_len++;
    }
	
    /* Check to see if the dst pointer is not NULL and return NULL if its incorrect */
    return ! dst  ? dst : NULL;
}

/*********************************************************************************************/
/*****************************memset**********************************************************/
/**********************************************************************************************
@brief - This function set a block of memory to a certain value

The memset function is passed a source address and a value,
the value that is passed on a function call is put into the destinaion address

@param - *src: source address 
@param - length: size of data
@param - value: value of data
@return -  src: source address
**********************************************************************************************/
uint8_t  *my_memset(uint8_t *src, uint32_t length, uint8_t value)
{
    /* Check to see if pointer were passed properly */
    /* if pointer were not properly passed then the function returns a NULL */
    if(src == NULL )
    {
        return NULL;  
    }
    
    uint32_t var_len = 0;
    /* Load the value into the memory with the pointer */	
    while(var_len < length)
    {
        *(src + var_len) = value;
        var_len++;
    }

    /* Returns src address*/    
    return src;
}

/*********************************************************************************************/
/******************************memzero********************************************************/
/**********************************************************************************************
@brief- This function zeros out a block of memory

The memzero function is passed a source address and a length,
the function zeros out all of the memory for the specified length.

@param - *src: source address 
@param - length: size of data
@return -  src: source address of zeroed blocks
**********************************************************************************************/
uint8_t  *my_memzero(uint8_t *src, size_t length)
{
    /* Check to see if pointer were passed properly */
    /* if pointer were not properly passed then the function returns a NULL */
    if(src == NULL )
    {
        return NULL;  
    }

    uint8_t var_len = 0;

    while(var_len < length)
    {
        *(src + var_len) = 0;
        var_len++;
    }
	
    /* Returns src address*/    
    return src;
}

/*********************************************************************************************/
/******************************reverse********************************************************/
/**********************************************************************************************
@brief - This function reverse a block of memory by bytes

The reverse function is passed a source address and a length,
the function revereses the order of the memory based on the length.

@param - *src: source address 
@param - length: size of data
@return -  src: source address of versed block
**********************************************************************************************/
uint8_t  *my_reverse(uint8_t *src, size_t length)
{
    /* Check to see if pointer were passed properly */
    /* if pointer were not properly passed then the function returns a NULL */
    if(src == NULL )
    {
        return NULL;  
    }	
	
    uint8_t temp;
    uint8_t var_len = 0;
    uint8_t *var_end = (src + ((uint8_t)length-1));
    /* This section will reverse the order base on half of the length
    since this is an integer, a division by 2 will eliminate the fraction portion of a divion
    this will help determine the function even with odd lengths */
    while(var_len <= (length/2 - 1) )
    {
        temp = *(src + var_len);
        *(src + var_len) = *(var_end - var_len);
        *(var_end - var_len) = temp;
        var_len++;
    }

    /* Returns src address*/    
    return src;    
}

/*********************************************************************************************/
/******************************reserve_words**************************************************/
/**********************************************************************************************
@brief - This function dynamically reserve a block of memory

The reserve function is passed a length,
the function reserves the memory based on the length so memory can be dynamically allocated.
The function returns the location of the newly allocated memory.

@param - length: address of reserved memory
@return - mem_loc: Returns the location address of the reserved memory block
**********************************************************************************************/
void * reserve_words(uint32_t length)
{
    if(length > 0)
    {  
        return (void *) malloc(length);
    }else{
        return NULL; 
    }
}

/*********************************************************************************************/
/******************************free_words*****************************************************/
/**********************************************************************************************
brief - This functions frees a block of memory that was reserved

The free function is passed a source address,
the function frees up the memory that has been dynamically allocated.

@param - *src: source address
@return - Returns a 0 if successful and 1 if it fails
**********************************************************************************************/
uint8_t free_words(void *src)
{
    free(src);   /* deallocates the dynamically allocated memory at the given pointer */	
	
    src = NULL;  /* NULL out the pointer so it doesn't leave a hanging pointer */

    /* Check to see if the src pointer is NULLed (if so return 0). Return 1 if its incorrect*/    
    return ! src  ? 0 : 1; 
}

/*********************************************************************************************/
/*****************************End of File*****************************************************/
/*********************************************************************************************/

