/*********************************************************************************************
@file - arch_arm32.h

@brief - arch_arm32 file is the header file for the ARM Architecture functionality

This file is the header for the arch_arm32.c file and includes the functions
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

#ifndef __ARCH_ARM32_H__
#define __ARCH_ARM32_H__

#include <stdint.h>

#define __SCB_ADDRESS               (0xE000ED00)
#define __AIRCR_ADDRESS_OFFSET      (12)
#define __AIRCR              (*((volatile uint32_t *)(__SCB_ADDRESS + __AIRCR_ADDRESS_OFFSET)))
#define __AIRCR_ENDIANNESS_OFFSET   (16)
#define __AIRCR_ENDIANNESS_MASK     (0x00008000)

#define __CPUID_ADDRESS_OFFSET      (0x0)
#define __CPUID              (*((volatile uint32_t *)(__SCB_ADDRESS + __CPUID_ADDRESS_OFFSET)))
#define __CPUID_PART_NO_OFFSET      (4)
#define __CPUID_PART_NO_MASK        (0xFFF0)
#define __CCRID_ADDRESS_OFFSET      (20)
#define __CCR                (*((volatile uint32_t *)(__SCB_ADDRESS + __CCRID_ADDRESS_OFFSET)))
#define __CCR_STK_ALIGNMENT_OFFSET  (9)
#define __CCR_STK_ALIGNMENT_MASK           (1 << __CCR_STK_ALIGNMENT_OFFSET)
#define __CCR_UNALIGNED_ACCESS_TRAP_OFFSET (3)
#define __CCR_UNALIGNED_ACCESS_TRAP_MASK   (1 << __CCR_UNALIGNED_ACCESS_TRAP_OFFSET)
#define __CCR_DIVIDE_BY_ZERO_TRAP_OFFSET   (4)
#define __CCR_DIVIDE_BY_ZERO_TRAP_MASK     (1 << __CCR_DIVIDE_BY_ZERO_TRAP_OFFSET)

/*********************************************************************************************/
/****************ARM32_AIRCR_get_endianness_setting**********************************************/
/**********************************************************************************************
@brief- This function is to read Endianness of the ARM register.

Reports the endianness of the processor from the AIRCR.
This is meant to be an inline function.

@param - none
@return - the endianness of the processor
**********************************************************************************************/

uint32_t ARM32_AIRCR_get_endianness_setting(void);


/*********************************************************************************************/
/******************ARM32_CCR_get_stack_alignment**********************************************/
/**********************************************************************************************
@brief- This function reads the CCR register and returns the stack alignment value

This function is used to get the alignment of the stack value and directly memory
dereferenced. 

@param - void
@return - value of the alignment
**********************************************************************************************/

uint32_t ARM32_CCR_get_stack_alignment(void);

/*********************************************************************************************/
/********************ARM32_CPUID_get_part_number**********************************************/
/**********************************************************************************************
@brief- This function reads the CPU ID register and returns part number and ARM Core

This function is used to get the value of the ARM core type and part number and returns
the direct memory dereferenced value

@param - void
@return - part number of ARM core
**********************************************************************************************/

uint32_t ARM32_CPUID_get_part_number(void);

/*********************************************************************************************/
/********************ARM32_CCR_enable_divide_by_zero******************************************/
/**********************************************************************************************
@brief- This function writes the CCR register to set the divide by zero trap

This function is used to set the value of the divide by zero bit in CCR to 1 (DIV_0_TRP)
This function uses a direct memory dereference

@param - void
@return - 1 if the function ran correctly
**********************************************************************************************/

uint32_t ARM32_CCR_enable_divide_by_zero(void);

/*********************************************************************************************/
/*****************ARM32_CCR_enable_unaligned access_trap**************************************/
/**********************************************************************************************
@brief- This function writes the CCR register to set the unaligned memory access trap

This function is used to set the value of the unaligned memory trap bit in CCR to 1 (UNALIGN_TRP). This function uses a direct memory dereference

@param - void
@return - 1 if the function ran correctly
**********************************************************************************************/

uint32_t ARM32_CCR_enable_unaligned_access_trap(void);

/*********************************************************************************************/
/*********************ARM32_create_unaligned_access_trap**************************************/
/**********************************************************************************************
@brief- This function performs an unaligned memory access that triggers UNALIGN_TRP

This function is used to perform unaligned access so that is triggers the trap from CCR

@param - void
@return - void
**********************************************************************************************/

void ARM32_create_unaligned_access_trap(void);

/*********************************************************************************************/
/*********************ARM32_create_divide_by_zero_trap****************************************/
/**********************************************************************************************
@brief- This function performs a divide by zero that triggers (DIV_0_TRP)

This function is used to perform a divide by zero so that is triggers the trap from CCR
This function should not return and should create a usage fault exception

@param - void
@return - should not return
**********************************************************************************************/

void ARM32_create_divide_by_zero_trap(void);


#endif /*__ARCH_ARM32_H__*/

/*********************************************************************************************/
/**************************************End of File********************************************/

