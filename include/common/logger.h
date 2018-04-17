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

#ifndef __LOGGER_H__
#define __LOGGER_H__

#ifdef KL25Z
#include "uart_circbuf.h"
#endif

#if defined (BBB) || defined (HOST)
#include <stdio.h>    
#endif

#include "circbuf.h"
#include "conversion.h"
#include <stdint.h>

/*Structure for the logger packet to be sent out*/
typedef struct{
  log_id_e    log_id;
  module_id_e module_id;
  <type32>    timestamp;
  <type32>    log_length;
  *<type8>    payload;
  <type32>    checksum;
} log_item_t;

/*Enumeration of the log id to be included in the packet*/
typedef enum{
  SYSTEM_ID = 0,
  SYSTEM_VERSION = 1,
  LOGGER_INITIALIZED = 2,
  GPIO_INITIALIZED = 3,
  SYSTEM_INITIALIZED = 4,
  SYSTEM_HALTED = 5,
  INFO = 6,
  WARNING = 7,
  ERROR = 8,
  PROFILING_STARTED = 9,
  PROFILING_RESULT = 10,
  PROFILING_COMPLETED = 11,
  DATA_RECEIVED = 12,
  DATA_ANALYSIS_STARTED = 13,
  DATA_ALPHA_COUNT = 14,
  DATA_NUMERIC_COUNT = 15,
  DATA_PUNCTUATION_COUNT = 16,
  DATA_MISC_COUNT = 17,
  DATA_ANALYSIS_COMPLETED = 18,
  HEARTBEAT = 19,
  CORE_DUMP = 20
} log_id_e;


typedef enum{
  PROJECT4,
  TEST
} module_id_e;

/**************************/
/*List of Logger MACROs to be able to enable and disable the logger*/
/*These below MARCOS will actaully be integrated into the program for logging*/
/*************************/
/*****Marcro Functions for the KL25Z**************/
#if defined (KL25Z) && defined (LOG_ENABLE)
#define LOG_RAW_DATA(*data, len); {log_raw_data_kl25z(*data, len);}
#define LOG_RAW_STRING(*string); {log_raw_string_kl25z(*string);}
#define LOG_RAW_INT(number); {log_raw_int_kl25z(number);}
#define LOG_FLUSH(); {log_flush_kl25z();}
#define LOG_RAW_ITEM(log_structure); {log_raw_item_kl25z(log_structure);}
#endif

/*****Marcro Functions for the BBB**************/
#if defined (BBB) && defined (LOG_ENABLE)
#define LOG_RAW_DATA(*data, len); {log_raw_data_bbb(*data, len);}
#define LOG_RAW_STRING(*string); {log_raw_string_bbb(*string);}
#define LOG_RAW_INT(number); {log_raw_int_bbb(number);}
#define LOG_FLUSH(); {log_flush_bbb();}
#define LOG_RAW_ITEM(log_structure); {log_raw_item_bb(log_structure);}
#endif

/*****Marcro Functions for turning the logger off**************/
#ifdef LOG_OFF
#define LOG_RAW_DATA(*data, len); {}
#define LOG_RAW_STRING(string); {}
#define LOG_RAW_INT(number); {}
#define LOG_FLUSH(); {}
#define LOG_RAW_ITEM(log_structure); {}
#endif

#ifdef LOG_ENABLE
CB_t *buf_ptr;
#endif

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

void log_raw_data_kl25z(uint8_t *data, uint32_t len);

void log_raw_data_bbb(uint8_t *data, uint32_t len);

/*********************************************************************************************/
/***********************************log_raw_string********************************************/
/**********************************************************************************************
@brief- This function sends the raw string data out to the terminal

This function send the raw string data to the terminal using the transmission medium 
depending on the platform
This description includes both KL25Z and BBB logger functions
This function assumes that the c-string is null termainated
The string should be in ASCII characters

@param - string: pointer to the string data to be transmitted
@return - void
**********************************************************************************************/

void log_raw_string_kl25z(uint8_t *string);

void log_raw_string_bbb(uint8_t string);

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

void log_raw_int_kl25z(uint8_t number);

void log_raw_int_bbb(uint8_t number);

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

void log_flush_kl25z(void);

void log_flush_bbb(void);

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

void log_raw_item_kl25z(log_item_t log_structure);

void log_raw_item_bbb(log_item_t log_structure);

#endif /*__LOGGER_H__*/

/*********************************************************************************************/
/***********************************END of FILE***********************************************/
/*********************************************************************************************/
