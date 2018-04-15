/*********************************************************************************************
@file - conversion.h

@brief - conversion.h file is a header file for conversions

This is the header file for conversion functions
The included function declarations are
1. itoa (integer to ASCII)
2. atoi (ASCII to integer)

@author - Scott McElroy

@date - February 5, 2018

Created for ECEN5813
**********************************************************************************************/

#ifndef __CONVERSION_H__
#define __CONVERSION_H__

#include <stdint.h>

#define NEG_CHECK_INT32 (0x80000000)
/*********************************************************************************************/
/******************************itoa***********************************************************/
/**********************************************************************************************
@brief- This function changes an integer to an ASCII number

The ITOA function is passed 32 bit data and a pointer plus a base type.
It will convert the base type value to an ASCII number and it returns the length.
The function can handle signed values.

@param - data: value to be converted
@param - *ptr: storage destination
@param - base: numerical base to be converted to
@return - length: size of converted ASCII
**********************************************************************************************/

uint8_t my_itoa(int32_t data, uint8_t *ptr, uint32_t base);

/*********************************************************************************************/
/******************************atoi***********************************************************/
/**********************************************************************************************
@brief- This function changes an ASCII number to an integer number

The ATOI function is passed a pointer plus a base type and the number of digits in the ASCII
It will convert the base type value to an ASCII number and it returns the length.
value. The function returns a 32-bit value of the converted data.

@param - *ptr: location of stored data
@param - digits: number of ASCII characters
@param - base: numerical base type of ASCII
@return - Returns the converted value
**********************************************************************************************/

int32_t my_atoi(uint8_t *ptr, uint8_t digits, uint32_t base);

#endif /* __CONVERSION_H__ */
