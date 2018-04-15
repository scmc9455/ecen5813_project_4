/*********************************************************************************************
@file - project3.h
@brief - project3.h file is the header file for the project3 testing functionality

This file runs that required programs for project 3 including the memory profiler
and the SPI communication commands
Functions Include
1. project3

@author - Scott McElroy

@date - March 31, 2018

Created for ECEN5813
**********************************************************************************************/

#ifndef __PROJECT3_H__
#define __PROJECT3_H__

#ifdef KL25Z_PRO
#include "dma.h"
#include "mem_profiler_kl25z.h"
#endif

#ifdef KL25Z
#include "dma.h"
#include "spi.h"
#include "gpio.h"
#include "nordic.h"
#endif

#if defined (HOST) || defined (BBB_PRO)
#include "mem_profiler_bbb.h"
#include <stdio.h>
#endif

#include <stdint.h>

/*Memset Testing defines*/
#define MEM_LEN_10         (10)
#define MEM_LEN_100        (100)
#define MEM_LEN_1000       (1000)
#define MEM_LEN_5000       (5000)
#define MEM_TYPE8          (8)
#define MEM_TYPE16         (16)
#define MEM_TYPE32         (32)

/*********************************************************************************************/
/*****************************Project3********************************************************/
/**********************************************************************************************
@brief - This function is the main code that runs the program for project3

@param - void
@return -  void
**********************************************************************************************/

void project3(void);

#endif /*__PROJECT3_H__*/

/*********************************************************************************************/
/***********************************END OF FILE***********************************************/
/*********************************************************************************************/

