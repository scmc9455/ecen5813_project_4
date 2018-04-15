/*********************************************************************************************
@file - project2.c
@brief - project2.c file is the header file for the project2 testing functionality

@author - Scott McElroy

@date - February 26, 2018

Created for ECEN5813
**********************************************************************************************/

#include "project2.h"

/********************************************************************************************/

/*********************************************************************************************/
/***********************************Dump Statistics*******************************************/
/**********************************************************************************************
@brief- This function calls ITOA and UART to send statistics to the terminal
@param - void
@return - void
**********************************************************************************************/
void dump_stats(void)
{
    /*create pointers to the struct so itoa can convert the values*/
    input_t *stats_ptr = &stats;

    /*Code data to send out stats to console*/
    my_itoa(stats.alpha,ALPHA(stats_ptr),10);
    my_itoa(stats.numerial,NUMERIAL(stats_ptr),10);
    my_itoa(stats.punct,PUNCT(stats_ptr),10);
    my_itoa(stats.misc,MISC(stats_ptr),10);

    /*send out stats*/
    UART_send(ALPHA(stats_ptr));
    UART_send(NUMERIAL(stats_ptr));
    UART_send(PUNCT(stats_ptr));
    UART_send(MISC(stats_ptr));

    /*zero out the stats for the send stuff*/
    stats.alpha = 0;
    stats.numerial = 0;
    stats.punct = 0;
    stats.misc = 0;
}

/*********************************************************************************************/
/***********************************Project2**************************************************/
/**********************************************************************************************
@brief- This function test the project functionality
@param - void
@return - void
**********************************************************************************************/
void project2(void)
{
    uint8_t variable;
	/*code data for running the statics structure*/
    variable = *((UART_RX_buffer)->tail);
    /*case statement to input stats*/
    if(((variable>0x20) && (variable<0x30)) || ((variable>0x39) && (variable<0x61)) || ((variable>0x5A) && (variable<0x7F)))
    {
        /*punctuation received from UART*/
    	stats.punct += 1;
    }else if((variable > 0x2F) && (variable < 0x3A))
    {
        /*numerial received from UART*/
    	stats.numerial += 1;
    }else if(((variable>0x40) && (variable<0x5B)) || ((variable<0x60) && (variable<0x7B)))
    {
        /*alpha received from UART*/
    	stats.alpha += 1;
    }else if(variable != 0x00)
    {
        /*misc received from UART*/
    	stats.misc += 1;
    }else if(variable == 0x00)
    {
        /*EOF received from UART*/
    	EOF_flag = 1;
    }

    /*take the receive buffer tail pointer data*/
}

/*********************************************************************************************/
/***********************************Project2_code*********************************************/
/**********************************************************************************************
@brief- This function will run the main loops for the coding
@param - void
@return - void
**********************************************************************************************/
void program2(void)
{
    uint8_t run = 1, status;
    /*Configure UART for transmit and receive*/
    status = UART_configure(57200);

    status = CB_init(&UART_RX_buffer, 10);
    if(status == CB_NULL_POINTER_ERROR)
    {
        return;
    }
    status = CB_init(&UART_TX_buffer, 10);
    if(status == CB_NULL_POINTER_ERROR)
    {
        return;
    }
    /*zero out the stats for the send stuff*/
    stats.alpha = 0;
    stats.numerial = 0;
    stats.punct = 0;
    stats.misc = 0;

    while(run){
        if(EOF_flag == 1)
        {
            EOF_flag = 0;
            dump_stats();
        }
        if(receive_flag == 1)
        {
    	    project2();
        }
    }
}
/*********************************************************************************************/
/***********************************END OF FILE***********************************************/
/*********************************************************************************************/
