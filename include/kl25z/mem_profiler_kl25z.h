/*********************************************************************************************
@file - mem_profiler_kl25z.h

@brief - mem_profiler_kl25z.h file is the header file for memory profiler functions

This file will be used to profile the memory of the KL25Z.
The functions include the generation of a statics file and running of the profiler
Functions included are
1. systick_init
2. systick_start
3. systick_end
4. profiler_memset_dma_kl25z
5. profiler_memmove_dma_kl25z
6. profiler_my_memset_kl25z
7. profiler_my_memmove_kl25z
8. profiler_stdlib_memmove_kl25z
9. profiler_stdlib_memset_kl25z

@author - Scott McElroy

@date - March 31th, 2018

Created for ECEN5813
**********************************************************************************************/

#ifndef __MEM_PROFILER_KL25Z_H__
#define __MEM_PROFILER__KL25Z_H__

#include <stdint.h>
#include <stdlib.h>
#include "dma.h"
#include "memory.h"

#define __SYST_CSR         (*((volatile uint32_t *)(0xE000E010)))
#define __SYST_RVR         (*((volatile uint32_t *)(0xE000E014)))
#define __SYST_CVR         (*((volatile uint32_t *)(0xE000E018)))
#define TICK_CLKSOURCE     (1 << 2)
#define __TICKINT          (1 << 1)
#define __TICKEN           (0x1)
#define TIMER_MAX          (0xFFFFFF)
#define COUNT_FLAG         ((__SYST_CSR & (1<<16)) >> 16)

/*Profiler settings*/
#define MEMSET_VALUE       (0xA5)

/*********************************************************************************************/
/***********************systick_init**********************************************************/
/*********************************************************************************************
@brief - This function will initialize the SysTick Timer for usage

@param - void
@return -  void
**********************************************************************************************/

void systick_init(void);

/*********************************************************************************************/
/*****************************systick_start****************************************************/
/**********************************************************************************************
@brief - This function will start the SysTick timer for usage

@param - void
@return -  void
**********************************************************************************************/

void systick_start(void);

/*********************************************************************************************/
/*****************************systick_end****************************************************/
/**********************************************************************************************
@brief - This function will end the SysTick timer for usage

@param - void
@return -  void
**********************************************************************************************/

void systick_end(void);

/*********************************************************************************************/
/****************************profiler_memset_kl25z********************************************/
/**********************************************************************************************
@brief - This function is the main code that will analyze the time it take to run mem functions

@param - memset_test_len: length of bytes of the test
@param - memset_type: type of data sent
@return - counter: returned value of the number of cycles
**********************************************************************************************/

uint32_t profiler_memset_dma_kl25z(uint32_t memset_test_len, uint8_t memset_type);

/*********************************************************************************************/
/****************************profiler_memmove_kl25z********************************************/
/**********************************************************************************************
@brief - This function is the main code that will analyze the time it take to run mem functions

@param - memmove_test_len: length of bytes of the test
@param - memmove_type: type of data sent
@return - counter: returned value of the number of cycles
**********************************************************************************************/

uint32_t profiler_memmove_dma_kl25z(uint32_t memmove_test_len, uint8_t memmove_type);

/*********************************************************************************************/
/****************************profiler_my_memset_kl25z********************************************/
/**********************************************************************************************
@brief - This function is the main code that will analyze the time it take to run my_mem functions

@param - memset_test_len: length of bytes of the test
@return - counter: returned value of the number of cycles
**********************************************************************************************/

uint32_t profiler_my_memset_kl25z(uint32_t memset_test_len);

/*********************************************************************************************/
/****************************profiler_my_memmove_kl25z****************************************/
/**********************************************************************************************
@brief - This function is the main code that will analyze the time it take to run my_mem functions

@param - memset_test_len: length of bytes of the test
@return - counter: returned value of the number of cycles
**********************************************************************************************/

uint32_t profiler_my_memmove_kl25z(uint32_t memmove_test_len);

/*********************************************************************************************/
/****************************profiler_memmove_kl25z_standard**********************************/
/**********************************************************************************************
@brief - This function is the main code that will analyze the time it take to run my_mem functions

@param - memset_test_len: length of bytes of the test
@return - counter: returned value of the number of cycles
**********************************************************************************************/

uint32_t profiler_stdlib_memmove_kl25z(uint32_t memmove_test_len);

/*********************************************************************************************/
/*************************profiler_stdlib_memset_kl25z****************************************/
/**********************************************************************************************
@brief - This function is the main code that will analyze the time it take to run my_mem functions

@param - memset_test_len: length of bytes of the test
@return - counter: returned value of the number of cycles
**********************************************************************************************/

uint32_t profiler_stdlib_memset_kl25z(uint32_t memset_test_len);

#endif /*__MEM_PROFILER__KL25Z_H__*/

/********************************************************************************************/
/*****************************End of File****************************************************/
/********************************************************************************************/

