/*********************************************************************************************
@file - unit_tests.h
@brief - unit_teste.h file is the header file for the testing functionality of all of the various functions included in this project2

Tests will incude
memory.c
-memmove tests
-memset tests
-memzero tests
-reverse
conversion.c
-atoi
-itoa
data.c
-Endianess conversion
circbuf.c
-various tests

@author - Scott McElroy

@date - March 4, 2018

Created for ECEN5813
**********************************************************************************************/
#ifndef __UNIT_TESTS_H__
#define __UNIT_TESTS_H__

#include <stdio.h>
#include <stdint.h>
#include "platform.h"
#include "project1.h"
#include "memory.h"
#include "conversion.h"
#include "debug.h"
#include "data1.h"
#include "arch_arm32.h"

#include "project2.h"
#include "uart.h"
#include "circbuf.h"

typedef enum{
  TEST_PASS   =0,
  TEST_FAILED =1
}test_type_e;

/*********************************************************************************************/
/**************************************memmove_tests******************************************/
/**********************************************************************************************
@brief- This function tests the memmove features

Tests:
invalid pointers
No overlap
SRC in DST
DST in SRT
DST == SRC

@param - void
@return - test_type: passing of failing
**********************************************************************************************/

test_type_e memmove_tests(void);

/*********************************************************************************************/
/**************************************memset_tests******************************************/
/**********************************************************************************************
@brief- This function tests the memmove features

Tests:
invalid pointers
checks the set

@param - void
@return - test_type: passing of failing
**********************************************************************************************/

test_type_e memset_tests(void);

/*********************************************************************************************/
/**************************************memzero_tests******************************************/
/**********************************************************************************************
@brief- This function tests the memzero features

Tests:
invalid pointers
checks the set

@param - void
@return - test_type: passing of failing
**********************************************************************************************/

test_type_e memzero_tests(void);

/*********************************************************************************************/
/**************************************reverse_tests******************************************/
/**********************************************************************************************
@brief- This function tests the reverse features

Tests:
invalid pointers
checks odd reverses
checks even reverses
checks characters

@param - void
@return - test_type: passing of failing
**********************************************************************************************/

test_type_e reverse_tests(void);

/*********************************************************************************************/
/*****************************************atoi_tests******************************************/
/**********************************************************************************************
@brief- This function tests the atoi function

Tests:
invalid pointers
zero integers
max sized integers

@param - void
@return - test_type: passing of failing
**********************************************************************************************/

test_type_e atoi_tests(void);

/*********************************************************************************************/
/*****************************************itoa_tests******************************************/
/**********************************************************************************************
@brief- This function tests the itoa function

Tests:
invalid pointers
zero integers
max sized integers

@param - void
@return - test_type: passing of failing
**********************************************************************************************/

test_type_e itoa_tests(void);

/*********************************************************************************************/
/***********************************endianness_tests******************************************/
/**********************************************************************************************
@brief- This function tests the endianness function

Tests:
invalid pointers
valid conversions
conversions back

@param - void
@return - test_type: passing of failing
**********************************************************************************************/

test_type_e endianness_tests(void);

/*********************************************************************************************/
/*************************************circbuf_tests*******************************************/
/**********************************************************************************************
@brief- This function tests the circular buffer function

Tests: 
checks to make sure buffer is on the heap
invalid pointers
non-initialized buffers
Add and remove features
buffer full feature
Wrap-add
Wrap remove
Overfill
Over Empty

@param - void
@return - test_type: passing of failing
**********************************************************************************************/

test_type_e circbuf_tests(void);


#endif /*__UNIT_TESTS_H__*/
/*********************************************************************************************/
/*************************************END OF FILE*********************************************/
/*********************************************************************************************/

