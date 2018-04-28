/*********************************************************************************************
@file - timestamp.h

@brief - timestamp.h file is the header file for time capture functions for both BBB and FRDM

This file will be used to timestamp functions like loggers.
The functions that are included are
1. timestamp_BBB
2. timestamp_KL25Z

@author - Scott McElroy

@date - April 23st, 2018

Created for ECEN5813
**********************************************************************************************/

#ifndef __TIMESTAMP_H__
#define __TIMESTAMP_H__

#include <stdint.h>
#include <time.h>

#if defined (KL25Z) || defined (KL25Z_PRO)
#include "rtc.h"
#endif

/*Function MARCOs for code integration*/
#if (defined (BBB) || defined (HOST) || defined (BBB_PRO)) && defined (LOG_ENABLE)
#define TIMESTAMP(x)  timestamp_bbb(x)
#define TIMESTART     timestart_bbb()
#endif

#if (defined (KL25Z) || defined (KL25Z_PRO)) && defined (LOG_ENABLE)
#define TIMESTAMP(x)  timestamp_kl25z(x)
#define TIMESTART     timestart_kl25z()
#endif

#ifdef LOG_OFF
#define TIMESTAMP(x) (x)
#define TIMESTART    (0)
#endif
/*********************************************************************************************/
/***********************************timestamp_bbb*********************************************/
/**********************************************************************************************
@brief - This function passes the value of time back to a structure pointer

@param - time: this is the value that will get changed during an update
@return - nano: nanosecond time 
**********************************************************************************************/
#if defined (BBB) || defined (HOST) || defined (BBB_PRO)
uint32_t timestamp_bbb(uint32_t time);
#endif
/*********************************************************************************************/
/***********************************timestamp_KL25Z*******************************************/
/**********************************************************************************************
@brief - This function passes the value of time back to a structure pointer

@param - time: this is the value that will get changed during an update
@return - nano: nanosecond time 
**********************************************************************************************/
#if defined (KL25Z) || defined (KL25Z_PRO)
uint32_t timestamp_kl25z(uint32_t time);
#endif

/*********************************************************************************************/
/***********************************timestart_BBB*********************************************/
/**********************************************************************************************
@brief - This function will return the value for the start time for timestamps comparisons

@param - void
@return - nano: value to be used for time comparison 
**********************************************************************************************/
#if defined (BBB) || defined (HOST) || defined (BBB_PRO)
uint32_t timestart_bbb(void);
#endif

/*********************************************************************************************/
/***********************************timestart_KL25Z*******************************************/
/**********************************************************************************************
@brief - This function will return the value for the start time for timestamps comparisons

@param - void
@return - nano: value to be used for time comparison
**********************************************************************************************/
#if defined (KL25Z) || defined (KL25Z_PRO)
uint32_t timestart_kl25z(void);
#endif

#endif /*__TIMESTAMP_H__*/
/*********************************************************************************************/
/********************************End of File**************************************************/
/*********************************************************************************************/
