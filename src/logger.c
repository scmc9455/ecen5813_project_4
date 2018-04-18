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
    /**Variables to be used***/
    uint32_t length = len;

    /*null pointer protection from a global buffer pointer*/
    if(buf_ptr == NULL)
    {
        return LOG_BUF_PTR_NULL;
    }
    
    /*fill the circular buffer until the length is finished*/
    while(length > 0)
    {
        /*add this data piece to the circular buffer*/
        CB_buffer_add_item(buf_ptr, *data);
        length--;
    }
    
    /*flush the circular buffer to the terminal*/
    UART_circbuf_flush_send(buf_ptr);

    return;
}
/****************log_data function for the BBB****************8**/
void log_raw_data_bbb(uint8_t *data, uint32_t len)
{
    /**Variables to be used***/
    uint32_t length = len;

    /*null pointer protection from a global buffer pointer*/
    if(buf_ptr == NULL)
    {
        return LOG_BUF_PTR_NULL;
    }
    
    /*fill the circular buffer until the length is finished*/
    while(length > 0)
    {
        /*add this data piece to the circular buffer*/
        CB_buffer_add_item(buf_ptr, *data);
        length--;
    }
    
    /*flush the circular buffer to the terminal*/
    BBB_circbuf_flush_send(buf_ptr);

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
    /*Store address so it can be incremented*/
    uint8_t i=0; /*This will be used to increment the address pointer*/

    /*statement checks for the null pointer*/
    if(string == NULL)
    {
        return;
    }
    /*While the string is not outputing a NULL termainator*/
    /*The circular buffer continues to be loaded*/
    while(*(string+i) != 0x0) /*Compares the value at the pointer +i*/
    {
        /*Add the items to the circular buffer*/
        CB_buffer_add_item(buf_ptr,*(string+i));

        if(buf_ptr->count == buf_ptr->length)
        {
            /*flush the circular buffer to the terminal*/
            UART_circbuf_flush_send(buf_ptr);
        }

        i += 1; /*Increment i by i*/
    }

    /*flush the circular buffer to the terminal*/
    UART_circbuf_flush_send(buf_ptr);
  
    return;
}
/******log_string for bbb**********/
void log_raw_string_bbb(uint8_t string)
{
    /*Store address so it can be incremented*/
    uint8_t i=0; /*This will be used to increment the address pointer*/

    /*statement checks for the null pointer*/
    if(string == NULL)
    {
        return;
    }
    /*While the string is not outputing a NULL termainator*/
    /*The circular buffer continues to be loaded*/
    while(*(string+i) != 0x0) /*Compares the value at the pointer +i*/
    {
        /*Add the items to the circular buffer*/
        CB_buffer_add_item(buf_ptr,*(string+i));

        if(buf_ptr->count == buf_ptr->length)
        {
            /*flush the circular buffer to the terminal*/
            BBB_circbuf_flush_send(buf_ptr);
        }

        i += 1; /*Increment i by i*/
    }

    /*flush the circular buffer to the terminal*/
    BBB_circbuf_flush_send(buf_ptr);

    return;
}

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

void log_raw_int_kl25z(uint32_t number)
{
    /*Convert the number to an ASCII value before transmitting*/
    uint8_t *number_ptr;
    number_ptr = (uint8_t *)malloc(10); /*The maximum number of digits for 32 bit is 10*/

    /*store the converted data directly into the buffer*/

    uint8_t bytes; /*Variable to store size of converted data in bytes*/
    /*This will be used for the loop to send out data*/
    bytes = my_itoa(number, number_ptr,10); /*Convert the hex value into and ASCII value*/
    /*The base is to be converted to base 10 ASCII*/
    
    /*Below adds the items from the converted function to the buffer*/
    for(uint8_t i=0; i<bytes; i++)
    {
        CB_buffer_add_item(buf_ptr, *(number_ptr+i));
    }
    
    /*Flush the buffer to the terminal*/
    UART_circbuf_flush_send(buf_ptr);

    return;
}
/****log_int for bbb******/
void log_raw_int_bbb(uint8_t number)
{
    /*Convert the number to an ASCII value before transmitting*/
    uint8_t *number_ptr;
    number_ptr = (uint8_t *)malloc(10); /*The maximum number of digits for 32 bit is 10*/

    /*store the converted data directly into the buffer*/

    uint8_t bytes; /*Variable to store size of converted data in bytes*/
    /*This will be used for the loop to send out data*/
    bytes = my_itoa(number, number_ptr,10); /*Convert the hex value into and ASCII value*/
    /*The base is to be converted to base 10 ASCII*/
    
    /*Below adds the items from the converted function to the buffer*/
    for(uint8_t i=0; i<bytes; i++)
    {
        CB_buffer_add_item(buf_ptr, *(number_ptr+i));
    }
    
    /*Flush the buffer to the terminal*/
    BBB_circbuf_flush_send(buf_ptr);

    return;
}

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
    /*Flush the buffer to the terminal*/
    UART_circbuf_flush_send(buf_ptr);

    return;
};

void log_flush_bbb(void)
{
    /*Flush the buffer to the terminal*/
    BBB_circbuf_flush_send(buf_ptr);

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
/*********************************BBB_circbuf_flush_send**************************************/
/**********************************************************************************************
@brief- This function configures the BBB to empty the circbuf completely

This function empties the circular buffer completely when called
This function is blocking
This function specifically is used to printf to the terminal for the BBB

@param - buf_ptr: address of the circular buff that will send data
@return -void
**********************************************************************************************/

void BBB_circbuf_flush_send(CB_t *buf_ptr)
{
    /*NULL pointer protection*/
    if(buf_ptr == NULL)
    {
        return;
    }

    /*create varibles and pointer to hold received data*/
    uint8_t item;
    uint8_t *item_ptr = &item;   

    /*This function will keep running as long as count is >0*/
    while(buf_ptr->count)
    {
        /*Store the circular buffer item into the local variable*/
        CB_buffer_remove_item(buf_ptr,item_ptr);

        /*Send the local variable to the UART to be sent off board*/
        LOG_PRINTF("%d ",item)
    }

    return;
}

/*********************************************************************************************/
/***********************************END of FILE***********************************************/
/*********************************************************************************************/
