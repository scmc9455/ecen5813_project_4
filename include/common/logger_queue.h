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

#ifndef __LOGGER_QUEUE_H__
#define __LOGGER_QUEUE_H__

#include <stdint.h>
#include "project4.h"
#include "logger.h"

#if defined (LOG_ENABLE)
#define LOG_ITEM(data, buf_ptr)  (log_item(data,buf_ptr))
#else
#define LOG_ITEM(data,buf_ptr)   {}
#endif
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

void log_item(log_item_t *data, CB_t *buf_ptr);

#endif /*__LOGGER_QUEUE_H__*/

/*********************************************************************************************/
/********************************End of File**************************************************/
/*********************************************************************************************/







