/*********************************************************************************************
@file - uart.h
@brief - uart.h file is the header file for the uart functionality

This file contains the functions for the uart functions for the KL25z freedom board.
The library contains the method of transmitting and receiving data characters without
the use of printf and debug console.
The freedom board has an on board UART to USB connector to use OpenSDA.

UART Setup
- LSb first
- 1 Start/1 Stop Bits
- 8-bit data transfers
- No Parity
- The fastest BAUD is 115200/38400/57200 Baud
BAUD Value is not hardcoded

This file header contains functions
1. UART_configure
2. UART_send
3. UART_send_n
4. UART_receive
5. UART_receive_n
6. IRQHandler

@author - Scott McElroy

@date - March 3, 2018

Created for ECEN5813
**********************************************************************************************/
#ifndef __UART_H__
#define __UART_H__

#include <stdint.h>
#include <stdlib.h>
#include "circbuf.h"
#include "project2.h"

typedef enum{
  UART_SUCCESS =0,
  UART_FAIL    =1
}status_e;

/*System Defines*/
#define __SIM_SCGC4 (*((volatile uint32_t *)(0x40048034)))
#define __SIM_SCGC5 (*((volatile uint32_t *)(0x40048038)))
#define __SIM_SOPT2 (*((volatile uint32_t *)(0x40048004)))
#define __SIM_SOPT5 (*((volatile uint32_t *)(0x40048010)))
#define SIM_PORTA_CG    (1 << 9)
#define SIM_PLLFLLSEL   (1 << 16)
#define SIM_UART0_CG    (1 << 10)
#define SIM_UART0SRC_MCGFLLCLK  (0b01 << 26)
#define SIM_UART0ODE    (1 << 16)
#define SIM_UART0RXSRC  (1 << 6)
#define SIM_UART0TXSRC  (0b11)

#define __PORTA_PCR1 (*((volatile uint32_t *)(0x40049004)))
#define __PORTA_PCR2 (*((volatile uint32_t *)(0x40049008)))
#define __ALT0       (0b000 << 8)
#ifndef __ALT2
#define __ALT2       (0b010 << 8)
#endif

/*UART Defines*/
#define __UART0_BDH  (*((volatile uint8_t *)(0x4006A000)))
#define __UART0_BDL  (*((volatile uint8_t *)(0x4006A001)))
#define __UART0_C1   (*((volatile uint8_t *)(0x4006A002)))
#define __UART0_C2   (*((volatile uint8_t *)(0x4006A003)))
#define __UART0_S1   (*((volatile uint8_t *)(0x4006A004)))
#define __UART0_S2   (*((volatile uint8_t *)(0x4006A005)))
#define __UART0_C3   (*((volatile uint8_t *)(0x4006A006)))
#define __UART0_D    (*((volatile uint8_t *)(0x4006A007)))
#define __UART0_C4   (*((volatile uint8_t *)(0x4006A00A)))
#define __UART0_C5   (*((volatile uint8_t *)(0x4006A00B)))

#define __UART_PARITY_EN  (0b1 << 1)
#define __UART_STOP_BIT   (0b1 << 5)
#define __UART_8BIT       (0b1 << 4)
#define __UART_TX_EN      (0b1 << 3)
#define __UART_RX_EN      (0b1 << 2)
#define __UART_RIE        (0b1 << 5)
#define __UART_TIE        (0b1 << 7)
#define __OSR_16          (0b01111)
#define __UART_SBR_BDH    (0b1111)
#define __UART_SBR_BDL    (0xFF)
#define __UART_MSB_FIRST  (0b1 << 5)
#define __UART_TDRE       (0b1 << 7)
#define __UART_RDRF       (0b1 << 5)

#define SYS_CLK      (21000000)
#define OSR_SAMP     (__OSR_16)
#define BAUD_MOD(x)  (SYS_CLK/((OSR_SAMP + 1)*(x)))
#define BDL_MASK     (0xFF)
#define BDH_MASK     (0x1F00)

/*Including CMSIS and device.h info*/
#define __UART0_interrupt     (12)
#define __NVIC_SET_EN_REG     (*((volatile uint32_t *)(0xE000E100)))
#define __NVIC_CLR_EN_REG     (*((volatile uint32_t *)(0xE000E180)))
#define __NVIC_SET_REG        (*((volatile uint32_t *)(0xE000E200)))
#define __disable_NVIC_IRQ(x) (__NVIC_CLR_EN_REG |= (x))
#define __enable_NVIC_IRQ(x)  (__NVIC_SET_EN_REG |= (x))
#define __UART0_IRQ_NUM       (1 << 12)
#define __ALL_IRQ_NUM         (0xFFFF)
/*Define the Macros to turn on and off the global interrupts*/
#define START_CRITICAL(x)     (__enable_NVIC_IRQ(x))
#define END_CRITICAL(x)       (__disable_NVIC_IRQ(x))


extern CB_t *UART_RX_buffer;
extern CB_t *UART_TX_buffer;
extern uint8_t receive_flag;


/*********************************************************************************************/
/***********************************UART_Configure********************************************/
/**********************************************************************************************
@brief- This function configures the UART module

This function configures the UART module settings
This includes port, baud and UART module.

@param - baud: settings to configure speed
@return -status of the UART
**********************************************************************************************/

status_e UART_configure(uint32_t baud);

/*********************************************************************************************/
/***********************************UART_send*************************************************/
/**********************************************************************************************
@brief- This UART function is to send one byte data

This function is for UART module to send out data through this module in one byte
This function blocks on transmitted data.

@param - *data: pointer to the data to send
@return - status of the UART
**********************************************************************************************/

status_e UART_send(uint8_t *data);

/*********************************************************************************************/
/***********************************UART_send_n***********************************************/
/**********************************************************************************************
@brief- This UART function is to send a data block

This function is for UART module to send out data through this module in a block of bytes
This function also takes in the amount of data to be transmitted.
This function blocks on transmitted data.

@param - pointer to the data to send
@param - length of data to be sent
@return - status of the UART
**********************************************************************************************/

status_e UART_send_n(uint8_t *data, size_t length);

/*********************************************************************************************/
/***********************************UART_receive**********************************************/
/**********************************************************************************************
@brief- This UART function is to receive one byte of data

This function is for UART module to recieve data through this module in one byte
This function blocks until receive data is complete.

@param - pointer to the location to put received data
@return - status of the UART
**********************************************************************************************/

status_e UART_receive(uint8_t *data);

/*********************************************************************************************/
/***********************************UART_receive_n********************************************/
/**********************************************************************************************
@brief- This UART function is to receive a block of data

This function is for UART module to recieve data through this module in one block of data
This function also takes in the number of items for the block to receive.
This function blocks until receive data is complete.

@param - pointer to the location to put received data
@param - number of items to be received
@return - status of the UART
**********************************************************************************************/

status_e UART_receive_n(uint8_t *data, size_t length);

/*********************************************************************************************/
/***********************************UART0-IRQHandler******************************************/
/**********************************************************************************************
@brief- This function handles the interrupts of the UART module

This function handles both receive and transmit interrupts.
The interrupt clears the associated flags when complete if they were set.
This is a short function.

@param - void
@return - void
**********************************************************************************************/

void UART0_IRQHandler(void);

#endif /*__UART_H__*/

/*********************************************************************************************/
/***********************************END of FILE***********************************************/
/*********************************************************************************************/
