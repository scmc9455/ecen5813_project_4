/*********************************************************************************************
@file - uart.c
@brief - uart.c file is the source file for the uart functionality

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
BAUD Value is not hard-coded

This file header contains functions
UART Sys_Init_UART
1. UART_configure
2. UART_send
3. UART_send_n
4. UART_receive
5. UART_receive_n
6. IRQHandler

uses the circbuf

@author - Scott McElroy

@date - March 3, 2018

Created for ECEN5813
**********************************************************************************************/

#include "uart.h"

/*********************************************************************************************/
/***********************************UART_Configure********************************************/
/**********************************************************************************************
@brief- This function configures the UART module

This function configures the UART module settings
This includes port, baud and UART module.

@param - baud: settings to configure speed
@return -status of the UART
**********************************************************************************************/

status_e UART_configure(uint32_t baud)
{
    uint16_t prescaler;

    /*PortA clock gate turn on*/
    __SIM_SCGC5 |= SIM_PORTA_CG;
    /*Enable the clock gate for the UART0*/
    __SIM_SCGC4 |=SIM_UART0_CG;
    /*Change the UART0 Clock to MCGFLLCLK*/
    __SIM_SOPT2 |= SIM_UART0SRC_MCGFLLCLK; /*Clock=21MHz is sourcing the UART*/
    __SIM_SOPT2 &= SIM_PLLFLLSEL; /*Selects the FLL for the input*/
    /*UART open drain disabled and TX/RX from pins*/
    __SIM_SOPT5 &= ~(SIM_UART0ODE + SIM_UART0RXSRC + SIM_UART0TXSRC);
    /*Set the port characteristics*/
    /*For PORTA-UART0, pin 1=RX and pin2=TX*/
    __PORTA_PCR1 &= __ALT0; /*ALT0 and the &= resets the bits*/
    __PORTA_PCR1 |= __ALT2; /*ALT2 is UART for this port*/
    __PORTA_PCR2 &= __ALT0; /*ALT0 and the &= resets the bits*/
    __PORTA_PCR2 |= __ALT2; /*ALT2 is UART for this port*/

    /*Setting the UART proper setup*/
    __UART0_BDH &= ~(__UART_STOP_BIT); /*clears the stop bit to get 1 stop bit*/
    /*clears the UART transmission data to 8-bits and disabling the parity*/
    __UART0_C1 &= ~(__UART_8BIT + __UART_PARITY_EN);
    /*Sets the transmission to LSB*/
    __UART0_S2 &= ~(__UART_MSB_FIRST);
    /*Set up the over sampling, default value is *16*/
    __UART0_C4 |= __OSR_16;
    /*The calculation is for the pre-scaler= MCGFLLCLK/((OSR+1)*baud-rate)*/
    __UART0_BDH &= ~(__UART_SBR_BDH); /*Clearing out the pre-scaler*/
    __UART0_BDL &= ~(__UART_SBR_BDL); /*Clearing out the pre-scaler*/
    /*Value is calculated for the pre-scaler and put into a variable to be broken up*/
    prescaler = BAUD_MOD(baud);
    /*put those values into the register*/
    __UART0_BDH |= (uint8_t)((prescaler & BDH_MASK) >> 8);
    __UART0_BDL = (uint8_t)(prescaler & BDL_MASK);
    /*Enable receiver interrupt*/
    /*enable the UART transmit and receive now that the module is configured*/
    __UART0_C2 |= (__UART_RIE + __UART_TX_EN + __UART_RX_EN);
    /*Enables the interrupts in the NVIC*/
    START_CRITICAL(__UART0_IRQ_NUM);

    return UART_SUCCESS;
}

/*********************************************************************************************/
/***********************************UART_send*************************************************/
/**********************************************************************************************
@brief- This UART function is to send one byte data

This function is for UART module to send out data through this module in one byte
This function blocks on transmitted data.
Send and receive requests can be enable through interrupts outside of this filein main.

@param - *data: pointer to the data to send
@return - status of the UART
**********************************************************************************************/

status_e UART_send(uint8_t *data)
{
	if(data==NULL)
    {
        return UART_FAIL;
    }

    /*Performing blocking by doing a while loop*/
    while((__UART0_S1 & __UART_TDRE) == 0){}; /*wait for the buffer to be open, then transmit*/
    /*Load the data into the transmit register once the buffer is emtpy*/
    __UART0_D = *data;
    
    return UART_SUCCESS;
}

/*********************************************************************************************/
/***********************************UART_send_n***********************************************/
/**********************************************************************************************
@brief- This UART function is to send a data block

This function is for UART module to send out data through this module in a block of bytes
This function also takes in the amount of data to be transmitted.
This function blocks on transmitted data.
Send and receive requests can be enable through interrupts outside of this filein main.

@param - *data: pointer to the data to send
@param - length: length of data to be sent
@return - status of the UART
**********************************************************************************************/

status_e UART_send_n(uint8_t *data, size_t length)
{
    if(data == NULL)
    {
       return UART_FAIL;
    } 
    /*create a temporary variable for the block transmit*/
    uint32_t i;
    /*run a loop base on the length of the data to be able to transmit the whole block*/
    for(i=0;i<length;i++)
    {
        while((__UART0_S1 & __UART_TDRE) == 0); /*wait for the buffer to be open, then transmit*/
        __UART0_D = *data;
        data += 1;
    }
     
    return UART_SUCCESS;
}

/*********************************************************************************************/
/***********************************UART_receive**********************************************/
/**********************************************************************************************
@brief- This UART function is to receive one byte of data

This function is for UART module to recieve data through this module in one byte
This function blocks until receive data is complete.
Send and receive requests can be enable through interrupts outside of this file in main.

@param - *data: pointer to the location to put received data
@return - status of the UART
**********************************************************************************************/

status_e UART_receive(uint8_t *data)
{
    if(data == NULL)
    {
       return UART_FAIL;
    } 

    while((__UART0_S1 & __UART_RDRF) == 0){}; /*wait for the buffer to be full receive*/
    *data = __UART0_D; /*Stores the value from the receive buffer into the data pointer*/

    return UART_SUCCESS;
}

/*********************************************************************************************/
/***********************************UART_receive_n********************************************/
/**********************************************************************************************
@brief- This UART function is to receive a block of data

This function is for UART module to recieve data through this module in one block of data
This function also takes in the number of items for the block to receive.
This function blocks until receive data is complete.
Send and receive requests can be enable through interrupts outside of this filein main.

@param - *data: pointer to the location to put received data
@param - length: number of items to be received
@return - status of the UART
**********************************************************************************************/

status_e UART_receive_n(uint8_t *data, size_t length)
{
    if(data == NULL)
    {
       return UART_FAIL;
    } 
    /*create a temporary variable for the block transmit*/
    uint32_t i;
    /*run a loop base on the length of the data to be able to transmit the whole block*/
    for(i=0;i<length;i++)
    {
        while((__UART0_S1 & __UART_RDRF) == 0); /*wait for the buffer to be full receive*/
        *data = __UART0_D; /*Stores the value from the receive buffer into the data pointer*/
        data += 1; /*increase the data pointer*/
    }

    return UART_SUCCESS;
}

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

void UART0_IRQHandler(void)
{
    /*Disables any more UART interrupts from happening*/
    END_CRITICAL(__UART0_IRQ_NUM);
    /*If a transmit interrupt was enabled and the UART TX data register is empty*/
    /*store the global variable into the data register*/
    if((((__UART0_C2 & __UART_TIE))!=0) && ((__UART0_S1 & __UART_TDRE) != 0))
    {
    	__UART0_C2 &= ~(__UART_TIE); /*Clear the transmit interrupt enable*/
    	if((UART_TX_buffer)->count == 0)
    	{
            START_CRITICAL(__UART0_IRQ_NUM);
            return;
    	}
    	/*Check to see if circ_buf is empty*/
    	UART_send((UART_TX_buffer)->head);
        /*Re-enables UART interrupts prior to leaving the handler*/
        START_CRITICAL(__UART0_IRQ_NUM);
        return;
    }

    /*If a receive interrupt was enabled and the UART RX data register is full*/
    /*take the data register and put it into the global variable*/
    if(((__UART0_C2 & __UART_RIE)!=0) && ((__UART0_S1 & __UART_RDRF)!=0) && ((UART_RX_buffer)->count < (UART_RX_buffer)->length))
    {
    	UART_receive((UART_RX_buffer)->head);
    	receive_flag = 1; /*set the global variable for receive flag*/
        /*Re-enables UART interrupts prior to leaving the handler*/
    	START_CRITICAL(__UART0_IRQ_NUM);
        return;
    }

    return;
}

/*********************************************************************************************/
/***********************************END of FILE***********************************************/
/*********************************************************************************************/
