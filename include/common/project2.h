/*********************************************************************************************
@file - project2.c
@brief - project2.c file is the header file for the project2 testing functionality

@author - Scott McElroy

@date - February 26, 2018

Created for ECEN5813
**********************************************************************************************/
#ifndef __PROJECT2_H__
#define __PROJECT2_H__

#include <stdint.h>

#include <stdio.h>
#include "platform.h"
#include "memory.h"
#include "conversion.h"
#include "debug.h"

#include "data1.h"
#include "uart.h"
#include "circbuf.h"
#include "gpio.h"
#include "arch_arm32.h"
/*Type define for the input character sequence*/
typedef struct {
    uint8_t alpha;
    uint8_t numerial;
    uint8_t punct;
    uint8_t misc;
} input_t;

#define ALPHA(x)      ((uint8_t *)(x))
#define NUMERIAL(x)   ((uint8_t *)(x)+1)
#define PUNCT(x)      ((uint8_t *)(x)+2)
#define MISC(x)       ((uint8_t *)(x)+3)

/*needed global variables for projects2*/
CB_t *UART_RX_buffer;
CB_t *UART_TX_buffer;
uint8_t receive_flag, EOF_flag;
input_t stats;

/****************************************************/
/*********************************************************************************************/
/***********************************Dump Statistics*******************************************/
/**********************************************************************************************
@brief- This function calls ITOA and UART to send statistics to the terminal
@param - void
@return - void
**********************************************************************************************/
void dump_stats(void);

/*********************************************************************************************/
/***********************************Project2**************************************************/
/**********************************************************************************************
@brief- This function test the project functionality
@param - void
@return - void
**********************************************************************************************/
void project2(void);

/*********************************************************************************************/
/***********************************Program2**************************************************/
/**********************************************************************************************
@brief- This function runs to loop for project2
@param - void
@return - void
**********************************************************************************************/
void program2(void);

#endif /*__PROJECT2_H__*/
