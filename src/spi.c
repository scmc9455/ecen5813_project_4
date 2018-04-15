
/*********************************************************************************************
@file - spi.c
@brief - spi.c file is the source file for the spi functionality

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

#include "spi.h"

/*********************************************************************************************/
/***********************************SPI_Configure*********************************************/
/**********************************************************************************************
@brief- This function configures the SPI module

This function configures the SPI module settings
GPIO must be initiated first before spi_init.

@param - void
@return - void
**********************************************************************************************/

void SPI_configure(void)
{
    /*Enable the clock gate for the SPI0*/
    __SIM_SCGC4 |= SPI0_CG;
    /*initialize the pins for the SPI in GPIO*/
    GPIO_nrf_init();
    /*Enable the SPI controller*/
    __SPI0_C1 |= SPE;

    /*Put the SPI into master mode and slave select pin selected*/
    __SPI0_C1 |= (MSTR + SSOE);
    /*Clear the CPHA to set polarity correctly*/
    __SPI0_C1 &= ~(CPHA + CPOL);
    /*Master_mode fault mode disabled*/
    __SPI0_C2 |= MODFEN;
    /*Divider prescaler*/
    __SPI0_BR &= ~(SPPR + SPR);
}

/*********************************************************************************************/
/***********************************SPI_read_byte*********************************************/
/**********************************************************************************************
@brief- This function is for the SPI to read bytes

This function is the function to read the SPI data register

@param - *spi_read_ptr: pointer of location where byte will be stored
@return - spi_e: status of the SPI
**********************************************************************************************/

spi_e SPI_read_byte(uint8_t *spi_read_ptr)
{
    if(spi_read_ptr == NULL)
    {
        return SPI_PTR_FAILURE;
    }

    /*This function is blocking*/
    /*First read the SPI read buffer flag then read the register*/
    while(((__SPI0_S & SPRF)>>SPRF_SHIFT) != 1);
    *spi_read_ptr = __SPI0_D;

    return SPI_SUCCESS;   
}

/*********************************************************************************************/
/***********************************SPI_write_byte*********************************************/
/**********************************************************************************************
@brief- This function is for the SPI1 to write bytes

This function is to write the SPI1 data register

@param - *spi_write_ptr: pointer of location where byte will be sent to write to the data register
@return - spi_e: status of the SPI
**********************************************************************************************/

spi_e SPI_write_byte(uint8_t *spi_write_ptr)
{
    if(spi_write_ptr == NULL)
    {
        return SPI_PTR_FAILURE;
    }

    /*This function is blocking*/
    /*First read the SPI transmit buffer flag then write to the register*/
    SPI_flush();
    __SPI0_D = *spi_write_ptr;
    SPI_flush();

    return SPI_SUCCESS;   
}


/*********************************************************************************************/
/***********************************SPI_send_packet*******************************************/
/**********************************************************************************************
@brief- This function is for the SPI1 to send packets of a specified length

This function is for the SPI1 to send packets of specific lengths to the data reg

@param - *spi_packet_ptr: pointer of location where byte is located for the send
@param - length: length of the packet to be sent
@return - spi_e: status of the SPI
**********************************************************************************************/

spi_e SPI_send_packet(uint8_t *spi_packet_ptr, uint32_t length)
{
    if(spi_packet_ptr == NULL)
    {
        return SPI_PTR_FAILURE;
    }

    /*For loop so that the whole packet will be sent to the SPI*/
    for(uint32_t i=0; i<length;i++)
    {
        /*SPI flush serves as the blocking function*/
        SPI_flush(); /*Call the flush function to make sure that the transmit buffer is empty*/
        __SPI0_D = *spi_packet_ptr; /*Send the new variable to the transmit buffer when ready*/
    }

    return SPI_SUCCESS;   
}

/*********************************************************************************************/
/***********************************SPI_flush*************************************************/
/**********************************************************************************************
@brief- This function is for the SPI1 blocking function to make sure buffer is empty

@param - void
@return - spi_e: status of the SPI
**********************************************************************************************/

spi_e SPI_flush(void)
{
    /*Blocking function is a while loop until the transmit buffer is empty*/
    while(((__SPI0_S & SPTEF)>>SPTEF_SHIFT) != 1);
    return SPI_SUCCESS;
}

/**************************************************************************************/
/********************************END OF FILE*******************************************/
/**************************************************************************************/

