/*********************************************************************************************
@file - logger_queue.c
@brief - logger_queue.c file is the source file for transmission of non-blocking functions

This file contains the functions that will be used to send log items to the terminal.
This file is universal across platforms

This file uses the following files
1. logger.c file

This file header contains functions
1. log_item

@author - Scott McElroy

@date - April 30, 2018

Created for ECEN5813
**********************************************************************************************/

#include "logger_queue.h"

/*********************************************************************************************/
/***********************************log_item**********************************************/
/**********************************************************************************************
@brief- This function is the non-blocking function for the logger

This function send the item to the terminal using the transmission medium depending on
the platform.

@param - data: log_type and logger data to be sent
@param - buf_ptr: pointer to the buffer that the data gets sent to
@return - void
**********************************************************************************************/

void log_item(log_item_t *data, CB_t *buf_ptr)
{
    /*This functions calls the log_raw item for the*/
    /*KL25Z to output the given structure to the */
    log_raw_item_kl25z(data);    
    /*Interrupts need to be implemented to use non-blocking functions*/
    return;
}

/*********************************************************************************************/
/********************************End of File**************************************************/
/*********************************************************************************************/








