/*********************************************************************************************
@file - nordic.c
@brief - nordic.c file is the source file for the nordic functionality

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

#include "nordic.h"

/*********************************************************************************************/
/***********************************nrf_init**************************************************/
/**********************************************************************************************
@brief- This function initializes the NRF DEVICE

@param - void
@return - void
**********************************************************************************************/

void nrf_init(void)
{
    __GPIOD_PSOR |= CHIP_EN_PTD5; /*Set the PTD5 to output to enable the NRF*/
    nrf_write_config(NRF_CONFIG_START); /*Powers up the NRF device*/
    return;
}

/*********************************************************************************************/
/***********************************nrf_read_register*****************************************/
/**********************************************************************************************
@brief- This function reads the contents of the nordic IC register that is passed to it

@param - nordic_reg: register inside the nordic device that 
@return - value: contents of register
**********************************************************************************************/

uint8_t nrf_read_register(uint8_t nordic_reg)
{
    uint8_t reg = nordic_reg | __R_REGISTER; /*This OR's the read command with the address*/
    uint8_t *reg_ptr = &reg;
    uint8_t value;
    uint8_t *value_ptr = &value; 
    uint8_t nop_addr = __NOPER; /*NOP for the read*/
    uint8_t *nop_ptr = &nop_addr; 
    /*Load value to the location */
    NRF_TRANSMIT_ENABLE;
    SPI_write_byte(reg_ptr);
    SPI_read_byte(value_ptr); /*Artifical read to clear the buffer*/
    SPI_write_byte(nop_ptr); /*write a nop so that the read the happens*/
    SPI_read_byte(value_ptr);
    NRF_TRANSMIT_DISABLE;
    /*Since the pointer changes variable value, then value can just be past back*/
    return value;
}

/*********************************************************************************************/
/***********************************nrf_write_register*****************************************/
/**********************************************************************************************
@brief- This function writes to the nordic IC register that is passed to it

@param - nordic_reg: register inside the nordic device that
@param - value: value to pass to the nordic device register
@return - void
**********************************************************************************************/

void nrf_write_register(uint8_t nordic_reg, uint8_t value)
{
    uint8_t reg = nordic_reg | __W_REGISTER; /*This OR's the read command with the address*/
    uint8_t contents = value;
    uint8_t *reg_ptr = &reg;
    uint8_t *contents_ptr = &contents;

    /*Enable the CS to set packet and do a double write for reg then value*/
    NRF_TRANSMIT_ENABLE;
    SPI_write_byte(reg_ptr); /*Register to read from*/
    SPI_write_byte(contents_ptr); /*Value to write in the register*/
    NRF_TRANSMIT_DISABLE; /*Disable CS pin to end transmission to NRF*/
       
    return;
}

/*********************************************************************************************/
/***********************************nrf_read_status*******************************************/
/**********************************************************************************************
@brief- This function reads that status register inside the nordic IC

@param - void
@return - return: contents of the status register
**********************************************************************************************/

uint8_t nrf_read_status(void)
{
    uint8_t status_addr = __STATUS | __R_REGISTER; /*This OR's the read command with the address*/
    uint8_t *status_ptr = &(status_addr);
    uint8_t contents; /*Contents of the status register*/
    uint8_t *contents_ptr = &contents;
    uint8_t nop_addr = __NOPER; /*NOP for the read*/
    uint8_t *nop_ptr = &nop_addr; 
    /*Enable the transmit of the SPI to NRF*/
    NRF_TRANSMIT_ENABLE;
    SPI_write_byte(status_ptr); /*Write the status register out to the NRF*/
    SPI_read_byte(contents_ptr); /*Artifical read to clear the buffer*/
    SPI_write_byte(nop_ptr); /*write a nop so that the read the happens*/
    SPI_read_byte(contents_ptr); /*Read the contents of the status register*/
    NRF_TRANSMIT_DISABLE; /*Relase CS */
    /*Since the pointer changes variable contents, then value can just be past back*/
    return contents;
}

/*********************************************************************************************/
/***********************************nrf_read_config*******************************************/
/**********************************************************************************************
@brief- This function reads that configuration register inside the nordic IC

@param - void
@return - return: contents of the config register
**********************************************************************************************/

uint8_t nrf_read_config(void)
{
    uint8_t config_addr = __CONFIG | __R_REGISTER; /*This OR's the read command with the address*/
    uint8_t *config_ptr = &(config_addr);
    uint8_t contents=0; /*Contents of the status register*/
    uint8_t *contents_ptr = &contents;
    uint8_t nop_addr = __NOPER; /*NOP for the read*/
    uint8_t *nop_ptr = &nop_addr; 
    /*Enable the transmit of the SPI to NRF*/
    NRF_TRANSMIT_ENABLE;
    SPI_write_byte(config_ptr); /*Write the config register out to the NRF*/
    SPI_read_byte(contents_ptr); /*Artifical read to clear the buffer*/
    SPI_write_byte(nop_ptr); /*write a nop so that the read the happens*/
    SPI_read_byte(contents_ptr); /*Read the contents of the config register*/
    NRF_TRANSMIT_DISABLE; /*Relase CS */
    /*Since the pointer changes variable contents, then value can just be past back*/
    return contents;
}

/*********************************************************************************************/
/**********************************nrf_write_config*******************************************/
/**********************************************************************************************
@brief- This function writes the configuration register inside the nordic IC

@param - config: configuration of the NRF
@return - void
**********************************************************************************************/

void nrf_write_config(uint8_t config)
{
    uint8_t config_addr = __CONFIG | __W_REGISTER; /*This OR's the read command with the address*/
    uint8_t *config_ptr = &(config_addr);
    uint8_t contents = config; /*Contents of the config register*/
    uint8_t *contents_ptr = &contents;
    /*Enable the transmit of the SPI to NRF*/
    NRF_TRANSMIT_ENABLE;
    SPI_write_byte(config_ptr); /*Write the config register out to the NRF*/
    SPI_write_byte(contents_ptr); /*Read the contents of the config register*/
    NRF_TRANSMIT_DISABLE; /*Relase CS */

    return;
}

/*********************************************************************************************/
/***********************************nrf_read_rf_setup*****************************************/
/**********************************************************************************************
@brief- This function reads the rf setup register inside the nordic IC

@param - void
@return - return: contents of the rf setup register
**********************************************************************************************/

uint8_t nrf_read_rf_setup(void)
{
    uint8_t rf_setup_addr = __RF_SETUP | __R_REGISTER; /*This OR's the read command with the address*/
    uint8_t *rf_setup_ptr = &(rf_setup_addr);
    uint8_t contents=0; /*Contents of the status register*/
    uint8_t *contents_ptr = &contents;
    uint8_t nop_addr = __NOPER; /*NOP for the read*/
    uint8_t *nop_ptr = &nop_addr; 
    /*Enable the transmit of the SPI to NRF*/
    NRF_TRANSMIT_ENABLE;
    SPI_write_byte(rf_setup_ptr); /*Write the rf_setup register out to the NRF*/
    SPI_read_byte(contents_ptr); /*Artifical read to clear the buffer*/
    SPI_write_byte(nop_ptr); /*write a nop so that the read the happens*/
    SPI_read_byte(contents_ptr); /*Read the contents of the rf_setup register*/
    NRF_TRANSMIT_DISABLE; /*Relase CS */
    /*Since the pointer changes variable contents, then value can just be past back*/
    return contents;
}

/*********************************************************************************************/
/**********************************nrf_write_rf_setup*****************************************/
/**********************************************************************************************
@brief- This function configures the rf setup registers inside the nordic IC

@param - rf_config: configuration value for the RF setup register
@return - void
**********************************************************************************************/

void nrf_write_rf_setup(uint8_t rf_config)
{
    uint8_t rf_setup_addr = __RF_SETUP | __W_REGISTER; /*This OR's the read command with the address*/
    uint8_t *rf_setup_ptr = &(rf_setup_addr);
    uint8_t contents = rf_config; /*Contents of the rf_config register*/
    uint8_t *contents_ptr = &contents;
    /*Enable the transmit of the SPI to NRF*/
    NRF_TRANSMIT_ENABLE;
    SPI_write_byte(rf_setup_ptr); /*Write the rf_config register out to the NRF*/
    SPI_write_byte(contents_ptr); /*Read the contents of the rf_setup register*/
    NRF_TRANSMIT_DISABLE; /*Relase CS */

    return;
}

/*********************************************************************************************/
/***********************************nrf_read_rf_ch********************************************/
/**********************************************************************************************
@brief- This function reads the rf channel register inside the nordic IC

@param - void
@return - return: contents of the rf_ch register
**********************************************************************************************/

uint8_t nrf_read_rf_ch(void)
{
    uint8_t rf_ch_addr = __RF_CH | __R_REGISTER; /*This OR's the read command with the address*/
    uint8_t *rf_ch_ptr = &(rf_ch_addr);
    uint8_t nop_addr = __NOPER; /*NOP for the read*/
    uint8_t *nop_ptr = &nop_addr; 
    uint8_t contents=0; /*Contents of the rf_ch register*/
    uint8_t *contents_ptr = &contents;
    /*Enable the transmit of the SPI to NRF*/
    NRF_TRANSMIT_ENABLE;
    SPI_write_byte(rf_ch_ptr); /*Write the rf_channel register out to the NRF*/
    SPI_read_byte(contents_ptr); /*Artifical read to clear the buffer*/
    SPI_write_byte(nop_ptr); /*write a nop so that the read the happens*/
    SPI_read_byte(contents_ptr); /*Read the contents of the rf_channel register*/
    NRF_TRANSMIT_DISABLE; /*Relase CS */
    /*Since the pointer changes variable contents, then value can just be past back*/
    return contents;
}

/*********************************************************************************************/
/**********************************nrf_write_rf_ch********************************************/
/**********************************************************************************************
@brief- This function write to the rf channel register inside the nordic IC

@param - rf_channel: value to be written to the channel register
@return - void
**********************************************************************************************/

void nrf_write_rf_ch(uint8_t rf_channel)
{
    uint8_t rf_ch_addr = __RF_CH | __W_REGISTER; /*This OR's the read command with the address*/
    uint8_t *rf_ch_ptr = &(rf_ch_addr);
    uint8_t contents = rf_channel; /*Contents of the rf_config register*/
    uint8_t *contents_ptr = &contents;
    /*Enable the transmit of the SPI to NRF*/
    NRF_TRANSMIT_ENABLE;
    SPI_write_byte(rf_ch_ptr); /*Write the rf_channel register out to the NRF*/
    SPI_write_byte(contents_ptr); /*Read the contents of the rf_channel register*/
    NRF_TRANSMIT_DISABLE; /*Relase CS */

    return;
}

/*********************************************************************************************/
/***********************************nrf_read_TX_ADDR******************************************/
/**********************************************************************************************
@brief- This function reads the 5 bytes of the TX_ADDR register 

This will include a write to the passed tx_address + 4 extra bytes beyond that value

@param - *tx_address: location where the byte reads will store the read contents
@return - void
**********************************************************************************************/

void nrf_read_TX_ADDR(uint8_t *tx_address)
{
    uint8_t TX_addr = __TX_ADDR | __R_REGISTER; /*This OR's the read command with the address*/
    uint8_t *TX_addr_ptr = &(TX_addr);
    uint8_t nop_addr = __NOPER; /*NOP for the read*/
    uint8_t *nop_ptr = &nop_addr;
    uint8_t fake = 0;
    uint8_t *fake_ptr = &fake;

    /*Enable the transmit of the SPI to NRF*/
    NRF_TRANSMIT_ENABLE;
    SPI_write_byte(TX_addr_ptr); /*Write the TX_addr register out to the NRF*/
    SPI_read_byte(fake_ptr); /*Artifical read to clear the buffer*/
    for(uint8_t i=0; i<5;i++)
    {
        SPI_write_byte(nop_ptr); /*write a nop so that the read the happens*/
        SPI_read_byte((tx_address + i)); /*Read the contents of the rf_channel register*/
    }
    NRF_TRANSMIT_DISABLE; /*Release CS */

    return;
}

/*********************************************************************************************/
/***********************************nrf_write_TX_ADDR******************************************/
/**********************************************************************************************
@brief- This function writes 5 bytes of data to the TX_ADDR register 

@param - *tx_address: location of the 5 byte values that will be written to the Nordic
@return - void
**********************************************************************************************/

void nrf_write_TX_ADDR(uint8_t *tx_address)
{
    uint8_t TX_addr = __TX_ADDR | __W_REGISTER; /*This OR's the read command with the address*/
    uint8_t *TX_addr_ptr = &(TX_addr);

    /*Enable the transmit of the SPI to NRF*/
    NRF_TRANSMIT_ENABLE;
    SPI_write_byte(TX_addr_ptr); /*Write the TX_addr register out to the NRF*/
    for(uint8_t i=0; i<5;i++)
    {
        SPI_write_byte((tx_address + i)); /*Read the contents of the rf_channel register*/
    }
    NRF_TRANSMIT_DISABLE; /*Relase CS */

    return;
}

/*********************************************************************************************/
/******************************nrf_read_fifo_status*******************************************/
/**********************************************************************************************
@brief- This function reads the status register associated with the fifo inside the nordic IC

@param - void
@return - return: contents of the fifo status register
**********************************************************************************************/

uint8_t nrf_read_fifo_status(void)
{
    /*This OR's the read command with the address*/
    uint8_t fifo_status_addr = __FIFO_STATUS | __R_REGISTER; 
    uint8_t *fifo_status_ptr = &(fifo_status_addr);
    uint8_t contents=0; /*Contents of the fifo_status register*/
    uint8_t *contents_ptr = &contents;
    uint8_t nop_addr = __NOPER; /*NOP for the read*/
    uint8_t *nop_ptr = &nop_addr; 
    /*Enable the transmit of the SPI to NRF*/
    NRF_TRANSMIT_ENABLE;
    SPI_write_byte(fifo_status_ptr); /*Write the fifo_status register out to the NRF*/
    SPI_read_byte(contents_ptr); /*Artifical read to clear the buffer*/
    SPI_write_byte(nop_ptr); /*write a nop so that the read the happens*/
    SPI_read_byte(contents_ptr); /*Read the contents of the fifo_status register*/
    NRF_TRANSMIT_DISABLE; /*Relase CS */
    /*Since the pointer changes variable contents, then value can just be past back*/
    return contents;
}

/*********************************************************************************************/
/******************************nrf_flush_tx_fifo**********************************************/
/**********************************************************************************************
@brief- This function empties the tx fifo inside the nordic IC

@param - void
@return - void
**********************************************************************************************/

void nrf_flush_tx_fifo(void)
{
    uint8_t flush_value = __FLUSH_TX; /*Value of Flush TX command*/
    uint8_t *flush_ptr = &(flush_value);
    /*Enable the transmit of the SPI to NRF*/
    NRF_TRANSMIT_ENABLE;
    SPI_write_byte(flush_ptr); /*Write the rf_channel register out to the NRF*/
    NRF_TRANSMIT_DISABLE; /*Relase CS */

    return;
}

/*********************************************************************************************/
/******************************nrf_flush_rx_fifo**********************************************/
/**********************************************************************************************
@brief- This function empties the rx fifo inside the nordic IC

@param - void
@return - void
**********************************************************************************************/

void nrf_flush_rx_fifo(void)
{
    uint8_t flush_value = __FLUSH_RX; /*Value of Flush RX command*/
    uint8_t *flush_ptr = &(flush_value);
    /*Enable the transmit of the SPI to NRF*/
    NRF_TRANSMIT_ENABLE;
    SPI_write_byte(flush_ptr); /*Write the flush command out to the NRF*/
    NRF_TRANSMIT_DISABLE; /*Relase CS */

    return;
}

/*********************************************************************************************/
/***********************************End of File***********************************************/
/*********************************************************************************************/

