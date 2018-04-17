/*********************************************************************************************
@file - uart_circbuf.c
@brief - uart_circbuf.c file is the source file for the uart connected to the 
circular buffer functionality

This file contains the functions for the uart functions for the KL25z freedom board.
The library contains the method of transmitting and receiving data characters without
the use of printf and debug console. The UART needs to be connnected to the circular
buffer to ensure no incoming or out going data is lost
The freedom board has an on board UART to USB connector to use OpenSDA.

This file uses the following file
1. UART.c
2. CIRCBUF.c

This file header contains functions
1. UART_circbuf_config
2. UART_circbuf_receive
3. UART_circbuf_send
4. UART_circbuf_flush_send

@author - Scott McElroy

@date - April 15, 2018

Created for ECEN5813
**********************************************************************************************/

#include "uart_circbuf.h"

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

CB_t *UART_circbuf_configure(uint32_t baud, uint32_t buf_len)
{
    /*First configure UART with a set baud rate passed into the function*/
    UART_configure(baud);
    /*Setup the pointer to the created circbuf pointer*/
    CB_t *buf_ptr = NULL; /*Creation of a NULLed pointer to be malloc'ed*/
    CB_t **buf_ptr_addr = &buf_ptr; /*Set the double ptr to the buf_ptr (so it can change)*/
    /*Initialize the circular buffer*/
    CB_init(buf_ptr_addr, buf_len); /*buffer of length now created*/
    
    return *buf_ptr_addr;
}

/*********************************************************************************************/
/***********************************UART_Circbuf_receive**************************************/
/**********************************************************************************************
@brief- This function configures the UART to fill the circbuf when item is recieved

This function ties the UART to the circular buffer for recieved items

@param - buf_ptr: pointer ti the buffer that us to send items
@return -status of the UART
**********************************************************************************************/

status_e UART_circbuf_receive(CB_t *buf_ptr)
{
    /*NULL pointer protection*/
    if(buf_ptr == NULL)
    {
        return UART_FAIL;
    }

    /*create varibles and pointer to hold recieved data*/
    uint8_t item;
    uint8_t *item_ptr = &item;   
    /*Take receive UART data and store into local variable*/
    UART_receive(item_ptr);
    /*Store the local variable into the circular buffer*/
    CB_buffer_add_item(buf_ptr,item);

    return UART_SUCCESS;
}

/*********************************************************************************************/
/***********************************UART_Circbuf_send*****************************************/
/**********************************************************************************************
@brief- This function configures the UART to empty the circbuf when item isin the buffer

This function ties the UART to the circular buffer for sending items out of UART
Sends one items from the circular buffer out to the UART

@param - buf_ptr: address of the circular buff that will send data
@return -status of the UART
**********************************************************************************************/

status_e UART_circbuf_send(CB_t *buf_ptr)
{
    /*NULL pointer protection*/
    if(buf_ptr == NULL)
    {
        return UART_FAIL;
    }

    /*create variables and pointer to hold recieved data*/
    uint8_t item;
    uint8_t *item_ptr = &item;   

    /*Store the buffer item into the local variable*/
    CB_buffer_remove_item(buf_ptr,item_ptr);

    /*Send the local variable to the UART to be sent off board*/
    UART_send(item_ptr);

    return UART_SUCCESS;
}
    
/*********************************************************************************************/
/*****************************UART_Circbuf_flush_send*****************************************/
/**********************************************************************************************
@brief- This function configures the UART to empty the circbuf completely

This function empties the circular buffer completely when called
This function is blocking

@param - buf_ptr: address of the circular buff that will send data
@return -status of the UART
**********************************************************************************************/

status_e UART_circbuf_flush_send(CB_t *buf_ptr)
{
    /*NULL pointer protection*/
    if(buf_ptr == NULL)
    {
        return UART_FAIL;
    }

    /*create varibles and pointer to hold recieved data*/
    uint8_t item;
    uint8_t *item_ptr = &item;   

    /*This function will keep running as long as count is >0*/
    while(buf_ptr->count)
    {
        /*Store the circular buffer item into the local variable*/
        CB_buffer_remove_item(buf_ptr,item_ptr);

        /*Wait for the buffer send to happen and the TXbuffer to empty*/
        while((__UART0_S1 & __UART_TDRE) == 0);

        /*Send the local variable to the UART to be sent off board*/
        UART_send(item_ptr);
    }

    return UART_SUCCESS;
}

/*********************************************************************************************/
/*****************************************END of FILE*****************************************/
/*********************************************************************************************/
