/*********************************************************************************************
@file - debug.h

@brief - debug.h file a header file for the debug function

This is the header file for the debug function
The included function declarations are
1. print_array

@author - Scott McElroy

@date - February 5, 2018

Created for ECEN5813
**********************************************************************************************/

#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdint.h>

/*********************************************************************************************/
/******************************print_array****************************************************/
/**********************************************************************************************
@brief- This function allows for debug using a print array

The print array function is passed a pointer plus a length.
This function takes whatever data is at the memory location and prints the hex output for 
in bytes by the specified number.

@param - start: print destination
@param - length: length to print
@return - void
**********************************************************************************************/

void print_array(uint8_t *start, uint32_t length);

#endif /* __DEBUG_H__ */
