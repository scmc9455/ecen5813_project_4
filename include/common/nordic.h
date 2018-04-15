/*********************************************************************************************
@file - nordic.h
@brief - nordic.h file is the header file for the nordic functionality

This file contains the functions for the nordic communciations.
This file contains functions definitions for the following
**Nordic Functions****
1. nrf_read_register
2. nrf_write_register
3. nrf_read_status
4. nrf_write_config
5. nrf_read_config
6. nrf_read_rf_setup
7. nrf_write_rf_setup
8. nrf_read_rf_ch
9. nrf_write_rf_ch
10. nrf_read_TX_ADDR
11. nrf_write_TX_ADDR
12. nrf_read_fifo_status
13. nrf_flush_tx_fifo
14. nrf_flush_rx_fifo
15. nrf_init

******NOTE: To use these functions the SPI_configure function must have previously been called
The nordic device will be connected to SPI0 Pins: PTD1, PTD2, PTD3, PTD5, PTD6

@author - Scott McElroy

@date - April 6, 2018

Created for ECEN5813
**********************************************************************************************/

#ifndef __NORDIC_H__
#define __NORDIC_H__

#include <stdint.h>
#include <stdlib.h>
#include "gpio.h"
#include "spi.h"

/*Using PIN5 as the Chip enable PTD5, these MACRO can only be used after SPI_CONFIG has run*/
/*To be used in the main program functions to enable and disable the NRF chip*/
#define NRF_CHIP_ENABLE       (__GPIOD_PSOR |= CHIP_EN_PTD5)
#define NRF_CHIP_DISABLE      (__GPIOD_PCOR |= CHIP_EN_PTD5)
/*Chip select PTD6 (active low), these MACRO can only be used after SPI_CONFIG has run*/
/*MARCO used to handle the /CS pin functionality and go around the built in SPI CS pin*/
#define NRF_TRANSMIT_ENABLE   (__GPIOD_PCOR |= CHIP_SEL_PTD6)
#define NRF_TRANSMIT_DISABLE  (__GPIOD_PSOR |= CHIP_SEL_PTD6)

/*Commands for NRF*/
#define __R_REGISTER           (0x00) /*ORed with*/
#define __W_REGISTER           (0x20) /*ORed with*/
#define __R_RX_PAYLOAD         (0x61)
#define __W_TX_PAYLOAD         (0xA0)
#define __FLUSH_TX             (0xE1)
#define __FLUSH_RX             (0xE2)
#define __REUSE_TX_PL          (0xE3)
#define __ACTIVATE             (0x50)
#define __R_RX_PL_WID          (0x60)
#define __W_ACK_PAYLOAD        (0xAF) /*ANDed with*/
#define __W_TX_PAYLOAD_NO_ACK  (0xB0)
#define __NOPER                (0xFF)

/*Register definitions*/
#define __CONFIG        (0x00)
#define __RF_SETUP      (0x06)
#define __RF_CH         (0x05)
#define __STATUS        (0x07)
#define __TX_ADDR       (0x10)
#define __FIFO_STATUS   (0x17)

/*Defines for power on and off*/
#define NRF_POWER_ON      (1)
#define NRF_POWER_OFF     (0)
#define NRF_POWER_UP_MASK (0x02)
#define NRF_CONFIG_START  (0b01111010) /*Mask Interrupts and enable CRC POWER_UP and TX*/

/*********************************************************************************************/
/***********************************nrf_init**************************************************/
/**********************************************************************************************
@brief- This function initializes the NRF DEVICE

@param - void
@return - void
**********************************************************************************************/

void nrf_init(void);

/*********************************************************************************************/
/***********************************nrf_read_register*****************************************/
/**********************************************************************************************
@brief- This function reads the contents of the nordic IC register that is passed to it

@param - nordic_reg: register inside the nordic device that 
@return - value: contents of register
**********************************************************************************************/

uint8_t nrf_read_register(uint8_t nordic_reg);

/*********************************************************************************************/
/***********************************nrf_write_register*****************************************/
/**********************************************************************************************
@brief- This function writes to the nordic IC register that is passed to it

@param - nordic_reg: register inside the nordic device that
@param - value: value to pass to the nordic device register
@return - void
**********************************************************************************************/

void nrf_write_register(uint8_t nordic_reg, uint8_t value);

/*********************************************************************************************/
/***********************************nrf_read_status*******************************************/
/**********************************************************************************************
@brief- This function reads that status register inside the nordic IC

@param - void
@return - return: contents of the status register
**********************************************************************************************/

uint8_t nrf_read_status(void);

/*********************************************************************************************/
/***********************************nrf_read_config*******************************************/
/**********************************************************************************************
@brief- This function reads that configuration register inside the nordic IC

@param - void
@return - return: contents of the config register
**********************************************************************************************/

uint8_t nrf_read_config(void);

/*********************************************************************************************/
/**********************************nrf_write_config*******************************************/
/**********************************************************************************************
@brief- This function writes the configuration register inside the nordic IC

@param - config: configuration of the NRF
@return - void
**********************************************************************************************/

void nrf_write_config(uint8_t config);

/*********************************************************************************************/
/***********************************nrf_read_rf_setup*****************************************/
/**********************************************************************************************
@brief- This function reads the rf setup register inside the nordic IC

@param - void
@return - return: contents of the rf setup register
**********************************************************************************************/

uint8_t nrf_read_rf_setup(void);

/*********************************************************************************************/
/**********************************nrf_write_rf_setup*****************************************/
/**********************************************************************************************
@brief- This function configures the rf setup registers inside the nordic IC

@param - rf_config: configuration value for the RF setup register
@return - void
**********************************************************************************************/

void nrf_write_rf_setup(uint8_t rf_config);

/*********************************************************************************************/
/***********************************nrf_read_rf_ch********************************************/
/**********************************************************************************************
@brief- This function reads the rf channel register inside the nordic IC

@param - void
@return - return: contents of the rf_ch register
**********************************************************************************************/

uint8_t nrf_read_rf_ch(void);

/*********************************************************************************************/
/**********************************nrf_write_rf_ch********************************************/
/**********************************************************************************************
@brief- This function write to the rf channel register inside the nordic IC

@param - rf_channel: value to be written to the channel register
@return - void
**********************************************************************************************/

void nrf_write_rf_ch(uint8_t rf_channel);

/*********************************************************************************************/
/***********************************nrf_read_TX_ADDR******************************************/
/**********************************************************************************************
@brief- This function reads the 5 bytes of the TX_ADDR register 

@param - *tx_address: location where the byte reads will store the read contents
@return - void
**********************************************************************************************/

void nrf_read_TX_ADDR(uint8_t *tx_address);

/*********************************************************************************************/
/***********************************nrf_write_TX_ADDR******************************************/
/**********************************************************************************************
@brief- This function writes 5 bytes of data to the TX_ADDR register 

@param - *tx_address: location of the 5 byte values that will be written to the Nordic
@return - void
**********************************************************************************************/

void nrf_write_TX_ADDR(uint8_t *tx_address);

/*********************************************************************************************/
/******************************nrf_read_fifo_status*******************************************/
/**********************************************************************************************
@brief- This function reads the status register associated with the fifo inside the nordic IC

@param - void
@return - return: contents of the fifo status register
**********************************************************************************************/

uint8_t nrf_read_fifo_status(void);

/*********************************************************************************************/
/******************************nrf_flush_tx_fifo**********************************************/
/**********************************************************************************************
@brief- This function empties the tx fifo inside the nordic IC

@param - void
@return - void
**********************************************************************************************/

void nrf_flush_tx_fifo(void);

/*********************************************************************************************/
/******************************nrf_flush_rx_fifo**********************************************/
/**********************************************************************************************
@brief- This function empties the rx fifo inside the nordic IC

@param - void
@return - void
**********************************************************************************************/

void nrf_flush_rx_fifo(void);

#endif /*__NORDIC_H__*/

/*********************************************************************************************/
/***********************************End of File***********************************************/
/*********************************************************************************************/

