/*********************************************************************************************
@file - debug.c

@brief - debug.c file a source file for the debug function

This is the source file for the debug function
The included function declarations are
1. print_array

@author - Scott McElroy

@date - February 5, 2018

Created for ECEN5813
**********************************************************************************************/
#include "debug.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

/*********************************************************************************************/
/******************************print_array****************************************************/
/**********************************************************************************************
@brief- This function allows for debug using a print array

The print array function is passed a pointer plus a length.
This function takes whatever data is at the memory location and prints the hex output for 
in bytes by the specified number.

@param - start: print destination
@param - length: length of print array
@return - void
**********************************************************************************************/

void print_array(uint8_t *start, uint32_t length)
{
    /* Check to see if pointer were passed properly */
    /* if pointer were not properly passed then the function returns a NULL */
    if(start == NULL)
    {
        return;  
    }
	
    uint8_t *mem_val = start; /*create a pointer that can move*/
    /*printf one byte at a time*/
    while(length > 0)
    {
        printf("%x ", *mem_val);
        length--;
        mem_val++;
    }
	
    printf("\n"); /*print new line character*/
	
    return;
}
