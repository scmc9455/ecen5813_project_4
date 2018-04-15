/*********************************************************************************************
@file - arch_arm32.c

@brief - arch_arm32 file is the source file for the ARM Architecture functionality

This file is the source for the arch_arm32 acrhitecture file and includes the functions
1. ARM32_AIRCR_get_endianness_setting
2. ARM32_CCR_get_stack_alignment
3. ARM32_CPUID_get_part_number
4. ARM32_CCR_enable_divide_by_zero_trap
5. ARM32_CCR_enable_unaligned_access_trap
6. ARM32_create_unaligned_access_trap
7. ARM32_create_divide_by_zero_trap

@author - Scott McElroy

@date - February 25, 2018

Created for ECEN5813
**********************************************************************************************/

#include "arch_arm32.h"
#include <stdint.h>
#include <stdlib.h>

/*********************************************************************************************/
/*************ARM32_AIRCR_get_endianness_setting**********************************************/
/**********************************************************************************************
@brief- This function is to read Endianness of the ARM register.

Reports the endianness of the processor from the AIRCR.
This is meant to be an inline function.

@param - none
@return - the endianness of the processor
**********************************************************************************************/

uint32_t ARM32_AIRCR_get_endianness_setting(void)
{
  /*The below statement will return the value of the endian value*/
  /*and will shift down by the offset to return the value*/
    return (((__AIRCR) & (__AIRCR_ENDIANNESS_MASK)) >> __AIRCR_ENDIANNESS_OFFSET);
}	

/*********************************************************************************************/
/******************ARM32_CCR_get_stack_alignment**********************************************/
/**********************************************************************************************
@brief- This function reads the CCR register and returns the stack alignment value

This function is used to get the alignment of the stack value and directly memory
dereferenced. 

@param - void
@return - value of the alignment
**********************************************************************************************/

uint32_t ARM32_CCR_get_stack_alignment(void)
{
  /*The below statement will return the value of the stack alignment from CCR*/
  /*and will shift down by the offset to return either 1(8-byte aligned) or 0(4-byte aligned)*/
    return (((__CCR) & (__CCR_STK_ALIGNMENT_MASK)) >> __CCR_STK_ALIGNMENT_OFFSET);
}

/*********************************************************************************************/
/********************ARM32_CPUID_get_part_number**********************************************/
/**********************************************************************************************
@brief- This function reads the CPU ID register and returns part number and ARM Core

This function is used to get the value of the ARM core type and part number and returns
the direct memory dereferenced value

@param - void
@return - part number of ARM core
**********************************************************************************************/

uint32_t ARM32_CPUID_get_part_number(void)
{
    /*This line deferences the part number and shift by the offset to return 0xC24*/
    return (((__CPUID) & (__CPUID_PART_NO_MASK)) >> __CPUID_PART_NO_OFFSET);
}

/*********************************************************************************************/
/********************ARM32_CCR_enable_divide_by_zero******************************************/
/**********************************************************************************************
@brief- This function writes the CCR register to set the divide by zero trap

This function is used to set the value of the divide by zero bit in CCR to 1 (DIV_0_TRP)
This function uses a direct memory dereference

@param - void
@return - 1 if the function ran correctly
**********************************************************************************************/

uint32_t ARM32_CCR_enable_divide_by_zero(void)
{
    /*The below value sets the divde by zero trap in the CCR register direct de-ref*/
    __CCR |= __CCR_DIVIDE_BY_ZERO_TRAP_MASK;
    /*The function is supposed to return a uint32_t so it returns 1 if successful*/
    return 1;
}

/*********************************************************************************************/
/*****************ARM32_CCR_enable_unaligned access_trap**************************************/
/**********************************************************************************************
@brief- This function writes the CCR register to set the unaligned memory access trap

This function is used to set the value of the unaligned memory trap bit in CCR to 1 (UNALIGN_TRP). This function uses a direct memory dereference

@param - void
@return - 1 if the function ran correctly
**********************************************************************************************/

uint32_t ARM32_CCR_enable_unaligned_access_trap(void)
{
  /*The below value sets the unaligned access trap in the CCR register direct de-ref*/
    __CCR |= __CCR_UNALIGNED_ACCESS_TRAP_MASK;
    /*The function is supposed to return a uint32_t so it returns 1 if successful*/
    return 1;
}

/*********************************************************************************************/
/*********************ARM32_create_unaligned_access_trap**************************************/
/**********************************************************************************************
@brief- This function performs an unaligned memory access that triggers UNALIGN_TRP

This function is used to perform unaligned access so that is triggers the trap from CCR

@param - void
@return - void
**********************************************************************************************/

void ARM32_create_unaligned_access_trap(void)
{
   #if defined (__GNUC__)
   #pragma GCC diagnostic ignored "-Wunused-but-set-variable"
   #endif
   /*create an 8-bit value that can be stored anywhere unaligned*/
    uint8_t temp;
  /*According to ARM support, casting this 8-bit value to 32 bit will cause unaligned access*/
    uint32_t *unaligned = (uint32_t *)(&temp);
    unaligned = 0;
  /*This will create a hard fault that doesn't return from a hard fault interrupt*/
}

/*********************************************************************************************/
/*********************ARM32_create_divide_by_zero_trap****************************************/
/**********************************************************************************************
@brief- This function performs a divide by zero that triggers (DIV_0_TRP)

This function is used to perform a divide by zero so that is triggers the trap from CCR
This function should not return and should create a usage fault exception

@param - void
@return - should not return
**********************************************************************************************/

void ARM32_create_divide_by_zero_trap(void)
{
  /*The line below is the code for the tigger of a divide by zero event*/
  /*CODE WILL NOT RUN ON KL25Z*/
  /*  uint8_t divide_by_zero = (0x01/0);*/
  /*This will create a hard fault that doesn't return from a hard fault hard fault*/

  return;
}


/*********************************************************************************************/
/**************************************End of File********************************************/
/*********************************************************************************************/
