/*********************************************************************************************
@file - logger.c
@brief - logger.c file is the source file for transmission of blocking functions

This file contains the functions that will be used to send log items to the terminal.
This file is universal across platforms

This file uses the following files
1. UART_circbuf.c (only on the KL25Z)

This file header contains functions
1. log_data
2. log_string
3. log_integer
4. log_flush
5. log_item

@author - Scott McElroy

@date - April 15, 2018

Created for ECEN5813
**********************************************************************************************/

#include "logger.h"

/*********************************************************************************************/
/***********************************log_raw_data**********************************************/
/**********************************************************************************************
@brief- This function sends the raw data out to the terminal

This function send the raw data to the terminal using the transmission medium depending on
the platform.
This description includes both KL25Z and BBB logger functions

@param - data: pointer to the data to be transmitted
@param - len: length for the amount of data to be transmitted
@return - void
**********************************************************************************************/

void log_raw_data_kl25z(uint8_t *data, uint32_t len)
{
    /*null pointer protection from a global buffer pointer*/
    if(buf_ptr == NULL)
    {
        return LOG_BUF_PTR_NULL;
    }
    
    /*fill the circular buffer until the length is finished*/
    while(len > 0)
    {
        /*add this data piece to the circular buffer*/
        CB_buffer_add_item(buf_ptr,*data);
    }

    /*flush the circular buffer to the terminal*/
    UART_circbuf_flush_send(buf_ptr);

    return;
}
/****log_data function for the BBB*****/
void log_raw_data_bbb(uint8_t *data, uint32_t len)
{
    return;
}

/*********************************************************************************************/
/***********************************log_raw_string********************************************/
/**********************************************************************************************
@brief- This function sends the raw string data out to the terminal

This function send the raw string data to the terminal using the transmission medium 
depending on the platform
This description includes both KL25Z and BBB logger functions
This function also assumes the c-string is null terminated
The string should be in ASCII characters

@param - string: pointer to the string data to be transmitted
@return - void
**********************************************************************************************/

void log_raw_string_kl25z(uint8_t *string)
{
    /*statement checks for the null pointer*/
    if(string == NULL)
    {
        return;
    }
    /*While the string is not outputing a NULL termainator*/
    /*The circular buffer continues to load the buffer*/
    while(*string != 0x0)
    {
        /*Add the items to the circular buffer*/
        CB_buffer_add_item(buf_ptr,*string);

        if(buf_ptr->count == buf_ptr->length)
        {
            /*flush the circular buffer to the terminal*/
            UART_circbuf_flush_send(buf_ptr);
        }
    }

    /*flush the circular buffer to the terminal*/
    UART_circbuf_flush_send(buf_ptr);
  
    return;
};
/******log_string for bbb**********/
void log_raw_string_bbb(uint8_t string)
{
    return;
};

/*********************************************************************************************/
/***********************************log_raw_int***********************************************/
/**********************************************************************************************
@brief- This function sends the raw integer data out to the terminal

This function send the raw integer data to the terminal using the transmission medium 
depending on the platform.Before sending this integer it converts the data using ITOA
This description includes both KL25Z and BBB logger functions

@param - number: number data to be transmitted
@return - void
**********************************************************************************************/

void log_raw_int_kl25z(uint8_t number)
{
    

    return;
};
/****log_int for bbb******/
void log_raw_int_bbb(uint8_t number)
{
    return;
};

/*********************************************************************************************/
/***********************************log_flush*************************************************/
/**********************************************************************************************
@brief- This function blocks until the current buffer is empty

This function blocks until the logger is finished sending transmissions until the 
buffer is empty
This description includes both KL25Z and BBB logger functions

@param - void
@return - void
**********************************************************************************************/

void log_flush_kl25z(void)
{
    return;
};

void log_flush_bbb(void)
{
    return;
};

/*********************************************************************************************/
/***********************************log_raw_item**********************************************/
/**********************************************************************************************
@brief- This function sends an item to the transmission medium

This function sends the log structure item to the terminal using the transmission medium 
depending on the platform
This description includes both KL25Z and BBB logger functions

@param - log_structure: log item structure that contains all the log details
@rerturn - void
**********************************************************************************************/

void log_raw_item_kl25z(log_item_t log_structure)
{
    return;
};

void log_raw_item_bbb(log_item_t log_structure)
{
    return;
};

/*********************************************************************************************/
/***********************************END of FILE***********************************************/
/*********************************************************************************************/
