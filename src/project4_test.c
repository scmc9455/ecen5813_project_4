/*********************************************************************************************
@file - project4_test.c

@brief - Project4 source file 

This program only calls functions for project4_test
This also include all the necessary libraries and headers that are used in each of the files

@author - Scott McElroy

@date - April 19, 2018

Created for ECEN5813
**********************************************************************************************/

#include "project4_test.h"

/*********************************************************************************************/
/*****************************Project4_test***************************************************/
/**********************************************************************************************
@brief - This function is the main code that runs the program for project4_test

@param - void
@return -  void
**********************************************************************************************/

void project4_test(void)
{
    /******Test Time function*****/
    uint32_t time_value;
    uint8_t *time_value_ptr = (uint8_t *)&time_value;
    time_value = TIMESTART;

    /***************Data Test****************************/
    /*Create data to be logged out of the logger*/
    uint8_t *data_ptr = NULL;
    data_ptr = (uint8_t *)malloc(BUF_LEN);

    /*Initialize the buffer pointer to point to the global variable address*/
    CB_t **buf_ptr_temp = &buf_ptr;
    /*Call for buffer init of BUF_LEN*/
    CB_init(buf_ptr_temp,BUF_LEN);

    for(uint8_t i=0; i<BUF_LEN; i++)
    {
        *(data_ptr+i) = i;
    }
    
    /*put data out on to the logger (Macro Function)*/
    LOG_RAW_DATA(data_ptr,BUF_LEN);

    /*time stamp print out*/
    time_value = TIMESTAMP(time_value);
    LOG_RAW_DATA(time_value_ptr,4);

    /*Release the allocated memory*/
    free_words(data_ptr);

    /***************String Test****************************/
    /*create a string and string pointer*/
    uint8_t string, len=10;
    uint8_t *string_ptr = &string; 

    /*Fill the string*/
    /*alloc the memory first so nothing happens*/
    string_ptr = (uint8_t *)malloc(len);

    for(uint8_t i=0; i<(len-1); i++)
    {
        *(string_ptr+i) = (0xAA+i);
    }
    /*null terminate the string with \0*/
    *(string_ptr+(len-1)) = 0x00;

    /*Call the log string function macro*/
    LOG_RAW_STRING(string_ptr);

    /*time stamp print out*/
    time_value = TIMESTAMP(time_value);
    LOG_RAW_DATA(time_value_ptr,4);

    /*Release the allocated memory*/
    free_words(string_ptr);

    /*****************Integer Test*************************/
    LOG_RAW_INT(12345);

    /*time stamp print out*/
    time_value = TIMESTAMP(time_value);
    LOG_RAW_DATA(time_value_ptr,4);

    /************Flush buffer Test*************************/
    /*Fill buffer with items that need to be flushed*/
    for(uint8_t i=0; i<10; i++)
    {
        CB_buffer_add_item(buf_ptr, i);
    }

    LOG_FLUSH();

    /*time stamp print out*/
    time_value = TIMESTAMP(time_value);
    LOG_RAW_DATA(time_value_ptr,4);

    /***************Packet Log Test************************/
    /*Initial the data of a packet*/
    uint8_t packet_data, packet_len = 10;
    uint8_t *packet_data_ptr = &packet_data;

    /*Create the memory space for data*/
    packet_data_ptr = (uint8_t *)malloc(packet_len);
    /*Fill the data packet*/
    for(uint8_t i=0; i<packet_len; i++)
    {
        *(packet_data_ptr+i)= 0x50+i;
    }
    /*Initialize a packet to be sent*/
    log_item_t packet;
    log_item_t *packet_ptr = &packet;
    /*fill the packet*/
    packet.log_id = CORE_DUMP;
    packet.module_id = TEST;
    packet.timestamp = TIMESTAMP(time_value);
    packet.log_length = packet_len;
    packet.payload = packet_data_ptr;
    LOG_CHECKSUM(packet_ptr);

    LOG_RAW_ITEM(packet_ptr);

    /*time stamp print out*/
    time_value = TIMESTAMP(time_value);
    LOG_RAW_DATA(time_value_ptr,4);
}

/**********************************************************************************************/
/************************************End of File***********************************************/
/**********************************************************************************************/ imo
