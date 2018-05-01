/*********************************************************************************************
@file - main.c

@brief - main program header file

This program only calls functions from project4
This also include all the necessary libraries and headers that are used in each of the files

@author - Scott McElroy

@date - April 19, 2018

Created for ECEN5813
**********************************************************************************************/

#ifdef PROJECT1
#include "project1.h"
#endif

#ifdef PROJECT2
#include "project2.h"
#endif

#ifdef PROJECT3
#include "project3.h"
#include <stdio.h>
#endif

#ifdef PROJECT4
#include "project4.h"
#endif

#ifdef PROJECT4_TEST
#include "project4_test.h"
#endif

#ifdef KL25Z
#include "MKL25Z4.h"
#endif

#ifdef KL25Z_PRO
#include "MKL25Z4.h"
#endif

#include <stdint.h>

#if defined (PROJECT4) || defined (PROJECT4_TEST)
/*Adding a global variable for the circular buffer pointer*/
CB_t *buf_ptr;
#endif

int main(void)
{
    #ifdef PROJECT1
        project1();
    #endif
    
    #ifdef PROJECT2
        program2();
    #endif

    #ifdef PROJECT3
        project3();
    #endif   

    #ifdef PROJECT4_TEST
        project4_test();
    #endif

    #if defined (PROJECT4)
        project4();
    #endif

    while(1);

    return 0;
}

/*********************************************************************************************/
/**************************************End of File********************************************/
/*********************************************************************************************/


