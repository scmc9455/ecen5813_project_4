/*********************************************************************************************
@file - main.c

@brief - main program header file

This program only calls functions from project2
This also include all the necessary libraries and headers that are used in each of the files

@author - Scott McElroy

@date - February 25, 2018

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

#ifdef KL25Z
#include "MKL25Z4.h"
#endif

#ifdef KL25Z_PRO
#include "MKL25Z4.h"
#endif

#include <stdint.h>

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

    return 0;
}

/*********************************************************************************************/
/**************************************End of File********************************************/
/*********************************************************************************************/

