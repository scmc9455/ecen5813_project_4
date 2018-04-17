/*********************************************************************************************
@file - uart_circbuf.h
@brief - uart_circbuf.h file is the header file for the uart connected to the 
circular buffer functionality

This file contains the functions for the uart functions for the KL25z freedom board.
The library contains the method of transmitting and receiving data characters without
the use of printf and debug console. The UART needs to be connnected to the circular
buffer to ensure no incoming or out going data is lost
The freedom board has an on board UART to USB connector to use OpenSDA.

This file uses the following file
1. UART.h
2. CIRCBUF.h

This file header contains functions
1. UART_circbuf_config
2. UART_circbuf_receive
3. UART_circbuf_send
4. UART_circbuf_flush_send

@author - Scott McElroy

@date - April 15, 2018

Created for ECEN5813
**********************************************************************************************/

#ifndef __UART_CIRCBUF_H__
#define __UART_CIRCBUF_H__

#include "circbuf.h"
#include "uart.h"

/*********************************************************************************************/
/***********************************UART_Circbuf_config***************************************/
/**********************************************************************************************
@brief- This function configures the UART module for circbuf

This function configures the UART module settings with the circular buffer
This includes port, baud and UART module.

@param - baud: settings to configure speed
@param - buf_len: length for the buffer setup
@return - buf_ptr: passes back the address location to be able to grab items for buffer
**********************************************************************************************/

CB_t *UART_circbuf_configure(uint32_t baud, uint32_t buf_len);

/*********************************************************************************************/
/***********************************UART_Circbuf_receive**************************************/
/**********************************************************************************************
@brief- This function configures the UART to fill the circbuf when item is recieved

This function ties the UART to the circular buffer for recieved items

@param - buf_ptr: pointer ti the buffer that us to send items
@return -status of the UART
**********************************************************************************************/

status_e UART_circbuf_receive(CB_t *buf_ptr);

/*********************************************************************************************/
/***********************************UART_Circbuf_send*****************************************/
/**********************************************************************************************
@brief- This function configures the UART to empty the circbuf when item isin the buffer

This function ties the UART to the circular buffer for sending items out of UART

@param - buf_ptr: address of the circular buff that will send data
@return -status of the UART
**********************************************************************************************/

status_e UART_circbuf_send(CB_t *buf_ptr);
    
/*********************************************************************************************/
/*****************************UART_Circbuf_flush_send*****************************************/
/**********************************************************************************************
@brief- This function configures the UART to empty the circbuf completely

This function empties the circular buffer completely when called
This function is blocking

@param - buf_ptr: address of the circular buff that will send data
@return -status of the UART
**********************************************************************************************/

status_e UART_circbuf_flush_send(CB_t *buf_ptr);

#endif /*__UART_CIRCBUF_H__*/

/*********************************************************************************************/
/*****************************************END of FILE*****************************************/
/*********************************************************************************************/
