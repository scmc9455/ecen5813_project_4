/*********************************************************************************************
@file - data.h

@brief - data.h file a header file for the data conversion functions

This file is the header file for the data.c file and includes the functions
1. print_cstd_type_sizes()
2. print_stdint_type_sizes()
3. print_pointer_sizes()
4. swap_data_endianness
5. determine_endianness

@author - Scott McElroy

@date - February 7, 2018

Created for ECEN5813
**********************************************************************************************/

#ifndef __DATA1_H__
#define __DATA1_H__

#include <stdint.h>
#include <stdlib.h>

#define _LITTLE_ENDIAN (0)
#define _BIG_ENDIAN    (1)
#define SWAP_NO_ERROR (0)
#define SWAP_ERROR    (-1)

/*********************************************************************************************/
/***********************print_cstd_type_sizes*****************************************************/
/**********************************************************************************************
@brief- This function print the standard size types

Reports - Char, short, int, long, double, float, unsigned char, unsigned int, unsigned long

@param - none
@return - void
**********************************************************************************************/

void print_cstd_type_sizes(void);

/*********************************************************************************************/
/******************************print_stdint_type_sizes********************************************/
/**********************************************************************************************
@brief- This function print the standard int type sizes

Reports int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, uint_fast8_t, uint_fast16_t, uint_fast32_t,
uint_least8_t, uint_least16_t, uint_least32_t, size_t, ptrdiff_t

@param - none
@return - void
**********************************************************************************************/

void print_stdint_type_sizes(void);

/*********************************************************************************************/
/******************************print_pointer_sizes************************************************/
/**********************************************************************************************
@brief- This function print the standard pointer type sizes

Reports char *, short *, int *, long *, double *, float *, void *, int8_t *, int16_t *, int32_t *, char **, int **, void **

@param - none
@return - void
**********************************************************************************************/

void print_pointer_sizes(void);

/*********************************************************************************************/
/******************************swap_data_endianness*********************************************/
/**********************************************************************************************
@brief- This function converts endianness of data in memory

Given an address of data and size, this function will flip the data in memory

@param - data: source address of memory to be flipped
@param - type_length: amount of memory to be flipped
@return - SWAP_ERROR/NO_ERROR: successfulness
**********************************************************************************************/

int32_t swap_data_endianness(uint8_t *data, size_t type_length);

/*********************************************************************************************/
/********************determine_endianness*******************************************************/
/**********************************************************************************************
@brief- This function determines the endianness of data in memory

This will report back what the data endianness is so it can be changed if need be

@param - none
@return - value of endianness
**********************************************************************************************/

uint32_t determine_endianness(void);

#endif /*__DATA1_H__*/
