/*********************************************************************************************
@file - timestamp.c

@brief - timestamp.c file is the source file for time capture functions for both BBB and FRDM

This file will be used to timestamp functions like loggers.
The functions that are included are
1. timestamp_bbb
2. timestamp_kl25z
3. timestart_bbb
4. timestart_kl25z

@author - Scott McElroy

@date - April 23st, 2018

Created for ECEN5813
**********************************************************************************************/

#include "timestamp.h"

/*********************************************************************************************/
/***********************************timestamp_bbb*********************************************/
/**********************************************************************************************
@brief - This function passes the value of time back to a structure pointer

@param - time: this is the value that will get changed during an update
@return - nano: nanosecond time 
**********************************************************************************************/
#if defined (BBB) || defined (HOST)
uint32_t timestamp_bbb(uint32_t time)
{
    /*Varibles that will store the values for the time capture*/
    uint32_t nano;
    struct timespec time_var;

    /*Grab time and put into variable*/
    clock_gettime(CLOCK_REALTIME, &time_var);

    /*Adjust the value of time for the return of nano*/
    nano = ((uint32_t)(time_var.tv_nsec)) - time;
    /*Return the value of the time in nanoseconds*/
    return nano;
}
#endif
/*********************************************************************************************/
/***********************************timestamp_KL25Z*******************************************/
/**********************************************************************************************
@brief - This function passes the value of time back to a structure pointer

@param - time: this is the value that will get changed during an update
@return - nano: nanosecond time 
**********************************************************************************************/
#ifdef KL25Z
uint32_t timestamp_kl25z(uint32_t time)
{
    /*Create a variable for the return value*/
    uint32_t nano = time;

    /*Return the value of the time in nanoseconds*/
    return nano;
}
#endif

/*********************************************************************************************/
/***********************************timestart_BBB*********************************************/
/**********************************************************************************************
@brief - This function will return the value for the start time for timestamps comparisons

@param - void
@return - nano: value to be used for time comparison 
**********************************************************************************************/
#if defined (BBB) || defined (HOST)
uint32_t timestart_bbb(void)
{
    /*Setup the variables to be able to use for returns and conversion*/
    uint32_t nano;
    struct timespec time_var;
    /*Grab the time and put it at the time variable structure*/
    clock_gettime(CLOCK_REALTIME,&time_var);
    /*Put the nanosecond time into the nano varaible (casting out of the structure first)*/
    nano = (uint32_t)time_var.tv_nsec;
    /*Return the value of the time in nanoseconds*/
    return nano;
}
#endif

/*********************************************************************************************/
/***********************************timestart_KL25Z*******************************************/
/**********************************************************************************************
@brief - This function will return the value for the start time for timestamps comparisons

@param - void
@return - nano: value to be used for time comparison
**********************************************************************************************/
#ifdef KL25Z
uint32_t timestart_kl25z(void)
{
    /*Setup the variables to be able to use for returns and conversion*/
    uint32_t nano = 0;

    /*Return the value of the time in nanoseconds*/
    return nano;
}
#endif

/*********************************************************************************************/
/********************************End of File**************************************************/
/*********************************************************************************************/
