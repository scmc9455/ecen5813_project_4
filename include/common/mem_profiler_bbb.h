/*********************************************************************************************
@file - mem_profiler_bbb.h

@brief - mem_profiler_bbb.h file is the header file for memory profiler functions for BBB

This file will be used to profile the memory of the BBB.
The functions include the generation of a statics file and running of the profiler
The functions that are included are
1. profiler_my_memset_bbb
2. profiler_my_memmove_bbb
3. profiler_stdlib_memset_bbb
4. profiler_stdlib_memmove_bbb

@author - Scott McElroy

@date - April 1st, 2018

Created for ECEN5813
**********************************************************************************************/

#ifndef __MEM_PROFILER_BBB_H__
#define __MEM_PROFILER_BBB_H__

#include "memory.h"
#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

/*Profiler settings*/
#define MEMSET_VALUE       (0xA5)

/*********************************************************************************************/
/****************************profiler_my_memset_bbb********************************************/
/**********************************************************************************************
@brief - This function is the main code that will analyze the time it take to run my_mem functions

@param - memset_test_len: length of bytes of the test
@return - counter: returned value of the number of cycles
**********************************************************************************************/

void profiler_my_memset_bbb(uint32_t memset_test_len);

/*********************************************************************************************/
/****************************profiler_my_memmove_bbb****************************************/
/**********************************************************************************************
@brief - This function is the main code that will analyze the time it take to run my_mem functions

@param - memset_test_len: length of bytes of the test
@return - counter: returned value of the number of cycles
**********************************************************************************************/

void profiler_my_memmove_bbb(uint32_t memmove_test_len);

/*********************************************************************************************/
/****************************profiler_stdlib_memmove_bbb**************************************/
/**********************************************************************************************
@brief - This function is the main code that will analyze the time it take to run mem functions

@param - memset_test_len: length of bytes of the test
@return - counter: returned value of the number of cycles
**********************************************************************************************/

void profiler_stdlib_memmove_bbb(uint32_t memmove_test_len);

/*********************************************************************************************/
/*************************profiler_stdlib_memset_bbb****************************************/
/**********************************************************************************************
@brief - This function is the main code that will analyze the time it take to run mem functions

@param - memset_test_len: length of bytes of the test
@return - counter: returned value of the number of cycles
**********************************************************************************************/

void profiler_stdlib_memset_bbb(uint32_t memset_test_len);


#endif /*__MEM_PROFILER_BBB_H__*/

/*********************************************************************************************/
/*****************************End of File*****************************************************/
/*********************************************************************************************/

