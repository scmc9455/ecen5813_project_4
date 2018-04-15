/*********************************************************************************************
@file - spi.h
@brief - spi.h file is the header file for the spi functionality

This file contains the functions for the spi for the KL25z freedom board.
The library contains the method of transmitting and receiving data characters 

This file header contains functions
SPI
1. SPI_configure
2. SPI_read_byte
3. SPI_write_byte
4. SPI_send_packet
5. SPI_flush

@author - Scott McElroy

@date - April 5, 2018

Created for ECEN5813
**********************************************************************************************/

#ifndef __SPI_H__
#define __SPI_H__

#include <stdint.h>
#include <stdlib.h>
#include "gpio.h"

#define __SIM_SCGC4 (*((uint32_t *)(0x40048034)))
#define __SIM_SCGC5 (*((uint32_t *)(0x40048038)))
#define SPI0_CG     (1 << 22)


#define __SPI0_C1     (*((uint8_t *)(0x40076000)))
#define __SPI0_C2     (*((uint8_t *)(0x40076001)))
#define __SPI0_BR     (*((uint8_t *)(0x40076002)))
#define __SPI0_S      (*((uint8_t *)(0x40076003)))
#define __SPI0_D      (*((uint8_t *)(0x40076005)))
#define __SPI0_M      (*((uint8_t *)(0x40076007)))
#define MSTR        (1 << 4)
#define SSOE        (1 << 1)
#define LSBFE       (0x1)
#define SPE         (1 << 6)
#define MODFEN      (1 << 4)
#define SPPR        (0x111 << 4)
#define SPR         (0x1111)
#define SPRF        (1 << 7)
#define SPTEF       (1 << 5)
#define SPRF_SHIFT  (7)
#define SPTEF_SHIFT (5)
#define CPOL        (1 << 3)
#define CPHA        (1 << 2)

typedef enum{
    SPI_PTR_FAILURE=0,
    SPI_SUCCESS=1
}spi_e;

/***************************************************************************************/
/*********************************SPI_Configure*****************************************/
/***************************************************************************************
@brief- This function configures the SPI module

This function configures the SPI module settings
GPIO must be initiated first before spi_init.

@param - void
@return -spi_e: status of the SPI
***************************************************************************************/

void SPI_configure(void);

/****************************************************************************************/
/******************************SPI_read_byte*********************************************/
/*****************************************************************************************
@brief- This function is for the SPI to read bytes

This function is the function to read the SPI data register

@param - *spi_read_ptr: pointer of location where byte will be stored
@return - spi_e: status of the SPI
*****************************************************************************************/

spi_e SPI_read_byte(uint8_t *spi_read_ptr);

/*****************************************************************************************/
/******************************SPI_write_byte*********************************************/
/******************************************************************************************
@brief- This function is for the SPI1 to write bytes

This function is to write the SPI1 data register

@param - *spi_write_ptr: pointer of location where byte will be sent to write to the data register
@return - spi_e: status of the SPI
*******************************************************************************************/

spi_e SPI_write_byte(uint8_t *spi_write_ptr);

/******************************************************************************************/
/********************************SPI_send_packet*******************************************/
/*******************************************************************************************
@brief- This function is for the SPI1 to send packets of a specified length

This function is for the SPI1 to send packets of specific lengths to the data reg

@param - *spi_packet_ptr: pointer of location where byte is located for the send
@param - length: length of the packet to be sent
@return - spi_e: status of the SPI
********************************************************************************************/

spi_e SPI_send_packet(uint8_t *spi_packet_ptr, uint32_t length);

/*******************************************************************************************/
/*********************************SPI_flush*************************************************/
/********************************************************************************************
@brief- This function is for the SPI1 blocking function to make sure buffer is empty

@param - void
@return - spi_e: status of the SPI
********************************************************************************************/

spi_e SPI_flush(void);


#endif /*__SPI_H__*/
/**************************************************************************************/
/********************************END OF FILE*******************************************/
/**************************************************************************************/

