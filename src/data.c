/*********************************************************************************************
@file - data.c

@brief - data.c file is the source file for the data conversion functions

This file is the source for the data.c file and includes the functions
1. print_cstd_type_sizes()
2. print_stdint_type_sizes()
3. print_pointer_sizes()
4. swap_data_endianness
5. determine_endianness

@author - Scott McElroy

@date - February 7, 2018

Created for ECEN5813
**********************************************************************************************/

#include "data1.h"
#include "platform.h"
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

/*********************************************************************************************/
/***********************print_cstd_type_sizes*****************************************************/
/**********************************************************************************************
@brief- This function print the standard size types

Reports - Char, short, int, long, double, float, unsigned char, unsigned int, unsigned long

@param - none
@return - void
**********************************************************************************************/

void print_cstd_type_sizes()
{
    /*Compiler directive to ignore the emtpy variable when the KL25z doesnt use printf*/
    #if defined (__GNUC__)
    #pragma GCC diagnostic ignored "-Wunused-but-set-variable"
    #endif
    /*Variable temp configuration below used from project documentation*/
    size_t temp;
    /*below prints the size of respective type based on the project 1 documentation*/
    temp = sizeof(char);
    PRINTF("Char %zd", temp);

    temp = sizeof(short);
    PRINTF("Short %zd", temp);

    temp = sizeof(int);
    PRINTF("Int %zd", temp);

    temp = sizeof(long);
    PRINTF("Long %zd", temp);

    temp = sizeof(double);
    PRINTF("Double %zd", temp);

    temp = sizeof(float);
    PRINTF("Float %zd", temp);

    temp = sizeof(unsigned char);
    PRINTF("Unsigner char %zd", temp);
	
    temp = sizeof(unsigned int);
    PRINTF("Unsigned int %zd", temp);

    temp = sizeof(unsigned long);
    PRINTF("Unsigned long %zd", temp);

    temp = sizeof(signed char);
    PRINTF("Signed char %zd", temp);

    temp = sizeof(signed int);
    PRINTF("Signed int %zd", temp);

    temp = sizeof(signed long);
    PRINTF("Signed long %zd", temp);

    return;
}

/*********************************************************************************************/
/******************************print_stdint_type_sizes********************************************/
/**********************************************************************************************
@brief- This function print the standard int type sizes

Reports int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, uint_fast8_t, uint_fast16_t, uint_fast32_t,
uint_least8_t, uint_least16_t, uint_least32_t, size_t, ptrdiff_t

@param - none
@return - void
**********************************************************************************************/

void print_stdint_type_sizes()
{
    /*Compiler directive to ignore the emtpy variable when the KL25z doesnt use printf*/
    #if defined (__GNUC__)
    #pragma GCC diagnostic ignored "-Wunused-but-set-variable"
    #endif
    /*Variable temp configuration below used from project documentation*/
    size_t temp;
    /*below prints the size of respective type based on the project 1 documentation*/
    temp = sizeof(int8_t);
    PRINTF("int8_t %zd", temp);

    temp = sizeof(uint8_t);
    PRINTF("uint8_t %zd", temp);

    temp = sizeof(int16_t);
    PRINTF("int16_t %zd", temp);

    temp = sizeof(uint16_t);
    PRINTF("uint16_t %zd", temp);

    temp = sizeof(int32_t);
    PRINTF("int32_t %zd", temp);

    temp = sizeof(uint32_t);
    PRINTF("uint32_t %zd", temp);

    temp = sizeof(uint_fast8_t);
    PRINTF("uint_fast8_t %zd", temp);

    temp = sizeof(uint_fast16_t);
    PRINTF("uint_fast16_t %zd", temp);

    temp = sizeof(uint_fast32_t);
    PRINTF("uint_fast32_t %zd", temp);

    temp = sizeof(uint_least8_t);
    PRINTF("uint_least8_t %zd", temp);

    temp = sizeof(uint_least16_t);
    PRINTF("uint_least16_t %zd", temp);

    temp = sizeof(uint_least32_t);
    PRINTF("uint_least32_t %zd", temp);

    temp = sizeof(size_t);
    PRINTF("size_t %zd", temp);

    temp = sizeof(ptrdiff_t);
    PRINTF("ptrdiff_t %zd", temp);	
	
    return;	
}

/*********************************************************************************************/
/******************************print_pointer_sizes************************************************/
/**********************************************************************************************
@brief- This function print the standard pointer type sizes

Reports char *, short *, int *, long *, double *, float *, void *, int8_t *, int16_t *, int32_t *, char **, int **, void **

@param - none
@return - void
**********************************************************************************************/

void print_pointer_sizes()
{
    /*Compiler directive to ignore the emtpy variable when the KL25z doesnt use printf*/
    #if defined (__GNUC__)
    #pragma GCC diagnostic ignored "-Wunused-but-set-variable"
    #endif
    /*Variable temp configuration below used from project documentation*/
    size_t temp;
    /*below prints the size of respective type based on the project 1 documentation*/
    temp = sizeof(char *);
    PRINTF("Char * %zd", temp);

    temp = sizeof(short *);
    PRINTF("Short * %zd", temp);

    temp = sizeof(int *);
    PRINTF("Int * %zd", temp);

    temp = sizeof(long *);
    PRINTF("Long * %zd", temp);

    temp = sizeof(double *);
    PRINTF("Double * %zd", temp);

    temp = sizeof(float *);
    PRINTF("Float * %zd", temp);

    temp = sizeof(void *);
    PRINTF("Void * %zd", temp);

    temp = sizeof(int8_t *);
    PRINTF("Int8_t * %zd", temp);

    temp = sizeof(int16_t *);
    PRINTF("Int16_t * %zd", temp);

    temp = sizeof(int32_t *);
    PRINTF("Int32_t * %zd", temp);

    temp = sizeof(char **);
    PRINTF("Char ** %zd", temp);

    temp = sizeof(int **);
    PRINTF("Int ** %zd", temp);

    temp = sizeof(void **);
    PRINTF("Void ** %zd", temp);

    return;	
}

/*********************************************************************************************/
/******************************swap_data_endianness*********************************************/
/**********************************************************************************************
@brief- This function converts endianness of data in memory

Given an address of data and size, this function will flip the data in memory

@param - data: source address of memory to be flipped
@param - type_length: amount of memory to be flipped
@return - SWAP_ERROR/NO_ERROR: successfulness
**********************************************************************************************/

int32_t swap_data_endianness(uint8_t *data, size_t type_length)
{
    if(data == NULL)
    {
        return NULL; /* returns NULL if the pointer is invalid */
    }
	
    uint32_t temp_len = 0;
    uint32_t data_temp;

    while(temp_len <= (type_length/2))
    {
        data_temp = *((data+type_length)-temp_len);
        *((data+type_length)-temp_len) = *(data+temp_len);
        *(data+temp_len) = data_temp;
        temp_len++;
    }

    if( temp_len == (type_length/2))
    {
        return SWAP_NO_ERROR;
    }else{
        return SWAP_ERROR;
    }	
}

/*********************************************************************************************/
/********************determine_endianness*******************************************************/
/**********************************************************************************************
@brief- This function determines the endianness of data in memory

This will report back what the data endianness is so it can be changed if need be

@param - none
@return - value of endianness
**********************************************************************************************/

uint32_t determine_endianness()
{
    uint16_t temp = 0x8001; /*Temporary 16-bit value to be stored to reference */
    uint16_t *temp_ptr = &temp; /*create a pointer to arbitrary 16-bits of data */

    if( *(uint8_t *)temp_ptr == 0x80)
    {
        /*The value got stored with the high-byte at the low pointer value*/
        return _BIG_ENDIAN;
    }else{
        return _LITTLE_ENDIAN;
    }	
}
