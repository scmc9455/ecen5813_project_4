/*********************************************************************************************
@file - project4.h

@brief - Project4 header file 

This program only calls functions for project4
This also include all the necessary libraries and headers that are used in each of the files

@author - Scott McElroy

@date - April 19, 2018

Created for ECEN5813
**********************************************************************************************/

#ifndef __PROJECT4_H__
#define __PROJECT4_H__

#include "logger.h"

#define BUF_LEN   (75)

#include "circbuf.h"
#include "timestamp.h"

extern CB_t *buf_ptr;

/*********************************************************************************************/
/*****************************Project4********************************************************/
/**********************************************************************************************
@brief - This function is the main code that runs the program for project4

@param - void
@return -  void
**********************************************************************************************/

void project4(void);

#endif /*__PROJECT4_H__*/


/**********************************************************************************************/
/************************************End of File***********************************************/
/**********************************************************************************************/
