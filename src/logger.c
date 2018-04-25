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
6. checksum

@author - Scott McElroy

@date - April 15, 2018

Created for ECEN5813
**********************************************************************************************/

#include "logger.h"

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

void log_raw_data_kl25z(uint8_t *data, uint32_t len)
{
    /*null pointer protection from a global buffer pointer*/
    if(buf_ptr == NULL)
    {
        return;
    }
    
    /*fill the circular buffer until the length is finished*/
    for(uint32_t i=0; i<len ;i++)
    {
        /*add this data piece to the circular buffer*/
        CB_buffer_add_item(buf_ptr, *(data+i));
    }
    
    /*flush the circular buffer to the terminal*/
    UART_SEND(buf_ptr);

    return;
}
/****************log_data function for the BBB****************8**/
void log_raw_data_bbb(uint8_t *data, uint32_t len)
{
    /*null pointer protection from a global buffer pointer*/
    if(buf_ptr == NULL)
    {
        return;
    }

    /*fill the circular buffer until the length is finished*/
    for(uint32_t i=0; i<len ;i++)
    {
        /*add this data piece to the circular buffer*/
        CB_buffer_add_item(buf_ptr, *(data+i));
    }
    
    /*flush the circular buffer to the terminal*/
    BBB_circbuf_flush_send(buf_ptr);

    /*Add a newline character to clean script*/
    PRINT_NL;

    return;
}

/*********************************************************************************************/
/***********************************log_raw_string********************************************/
/**********************************************************************************************
@brief- This function sends the raw string data out to the terminal

This function send the raw string data to the terminal using the transmission medium 
depending on the platform
This description includes both KL25Z and BBB logger functions
This function also assumes the c-string is null terminated
The string should be in ASCII characters

@param - string: pointer to the string data to be transmitted
@return - void
**********************************************************************************************/

void log_raw_string_kl25z(uint8_t *string)
{
    /*null pointer protection from a global buffer pointer*/
    if(buf_ptr == NULL)
    {
        return;
    }
 
    /*Store address so it can be incremented*/
    uint32_t i=0; /*This will be used to increment the address pointer*/

    /*statement checks for the null pointer*/
    if(string == NULL)
    {
        return;
    }
    /*While the string is not outputing a NULL termainator*/
    /*The circular buffer continues to be loaded*/
    while(*(string+i) != 0x0) /*Compares the value at the pointer +i*/
    {
        /*Add the items to the circular buffer*/
        CB_buffer_add_item(buf_ptr,*(string+i));

        if(buf_ptr->count == buf_ptr->length)
        {
            /*flush the circular buffer to the terminal*/
            UART_SEND(buf_ptr);
        }

        i += 1; /*Increment i by i*/
    }

    /*Null terminal the string so logger can determine the end*/
    CB_buffer_add_item(buf_ptr,*(string+i));

    /*flush the circular buffer to the terminal*/
    UART_SEND(buf_ptr);
  
    return;
}
/******log_string for bbb**********/
void log_raw_string_bbb(uint8_t *string)
{
    /*null pointer protection from a global buffer pointer*/
    if(buf_ptr == NULL)
    {
        return;
    }

    /*Store address so it can be incremented*/
    uint32_t i=0; /*This will be used to increment the address pointer*/

    /*statement checks for the null pointer*/
    if(string == NULL)
    {
        return;
    }
    /*While the string is not outputing a NULL termainator*/
    /*The circular buffer continues to be loaded*/
    while(*(string+i) != 0x0) /*Compares the value at the pointer +i*/
    {
        /*Add the items to the circular buffer*/
        CB_buffer_add_item(buf_ptr,*(string+i));

        if(buf_ptr->count == buf_ptr->length)
        {
            /*flush the circular buffer to the terminal*/
            BBB_circbuf_flush_send(buf_ptr);
        }

        i += 1; /*Increment i by i*/
    }

    /*Null terminal the string so logger can determine the end*/
    CB_buffer_add_item(buf_ptr,*(string+i));

    /*flush the circular buffer to the terminal*/
    BBB_circbuf_flush_send(buf_ptr);

    /*Adding a new line to clean up file*/
    PRINT_NL;

    return;
}

/*********************************************************************************************/
/***********************************log_raw_int***********************************************/
/**********************************************************************************************
@brief- This function sends the raw integer data out to the terminal

This function send the raw integer data to the terminal using the transmission medium 
depending on the platform.Before sending this integer it converts the data using ITOA
This description includes both KL25Z and BBB logger functions
*Circular Buffer must be at least 10 bytes long

@param - number: number data to be transmitted
@return - void
**********************************************************************************************/

void log_raw_int_kl25z(uint32_t number)
{
    /*null pointer protection from a global buffer pointer*/
    if(buf_ptr == NULL)
    {
        return;
    }

    /*Convert the number to an ASCII value before transmitting*/
    uint8_t *number_ptr;
    number_ptr = (uint8_t *)malloc(10); /*The maximum number of digits for 32 bit is 10*/

    /*store the converted data directly into the buffer*/

    uint8_t bytes; /*Variable to store size of converted data in bytes*/
    /*This will be used for the loop to send out data*/
    bytes = my_itoa(number, number_ptr,10); /*Convert the hex value into and ASCII value*/
    /*The base is to be converted to base 10 ASCII*/
    
    /*Below adds the items from the converted function to the buffer*/
    for(uint8_t i=0; i<bytes; i++)
    {
        CB_buffer_add_item(buf_ptr, *(number_ptr+i));
    }
    
    /*Flush the buffer to the terminal*/
    UART_SEND(buf_ptr);

    /*Free the reserved memory*/
    free_words(number_ptr);

    return;
}
/****log_int for bbb******/
void log_raw_int_bbb(uint32_t number)
{
    /*null pointer protection from a global buffer pointer*/
    if(buf_ptr == NULL)
    {
        return;
    }

    /*Convert the number to an ASCII value before transmitting*/
    uint8_t *number_ptr;
    number_ptr = (uint8_t *)malloc(10); /*The maximum number of digits for 32 bit is 10*/

    /*store the converted data directly into the buffer*/

    uint8_t bytes; /*Variable to store size of converted data in bytes*/
    /*This will be used for the loop to send out data*/
    bytes = my_itoa(number, number_ptr,10); /*Convert the hex value into and ASCII value*/
    /*The base is to be converted to base 10 ASCII*/
    
    /*Below adds the items from the converted function to the buffer*/
    for(uint8_t i=bytes; i>0; i--)
    {
        CB_buffer_add_item(buf_ptr, *(number_ptr+(i-1)));
    }
    
    /*Flush the buffer to the terminal*/
    BBB_circbuf_flush_send(buf_ptr);

    /*Free the reserved memory*/
    free_words(number_ptr);

    /*Add a new line for clean log file*/
    PRINT_NL;

    return;
}

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

void log_flush_kl25z(void)
{
    /*null pointer protection from a global buffer pointer*/
    if(buf_ptr == NULL)
    {
        return;
    }

    /*Flush the buffer to the terminal*/
    UART_SEND(buf_ptr);

    return;
}
/***********BBB_buffer flush**********/
void log_flush_bbb(void)
{
    /*null pointer protection from a global buffer pointer*/
    if(buf_ptr == NULL)
    {
        return;
    }

    /*Flush the buffer to the terminal*/
    BBB_circbuf_flush_send(buf_ptr);

    /*Add a new line for a clean log*/
    PRINT_NL;

    return;
}

/*********************************************************************************************/
/***********************************log_raw_item**********************************************/
/**********************************************************************************************
@brief- This function sends an item to the transmission medium

This function sends the log structure item to the terminal using the transmission medium 
depending on the platform
This description includes both KL25Z and BBB logger functions
***The circular buffer needs to be large enough to make sure that the structure over head 
can be handled

**Structure looks like the following****
Header - Payload - Footer

@param - log_structure: log item structure that contains all the log details
@rerturn - void
**********************************************************************************************/

void log_raw_item_kl25z(log_item_t *log_structure)
{
    /*null pointer protection from a global buffer pointer*/
    if(buf_ptr == NULL)
    {
        return;
    }

    /*First flush the buffer to make sure their is room for the structure items*/
    UART_SEND(buf_ptr);

    /***Start loading the circular buffer with the structure elements**/
    /*Load the *LOG ID* to buffer*/
    CB_buffer_add_item(buf_ptr, log_structure->log_id);
    /*Load the *MODULE ID* to buffer*/
    CB_buffer_add_item(buf_ptr, log_structure->module_id);
    /*Load the *TIMESTAMP* to buffer, needs to run 4 times because it 32 bits (4 bytes)*/
    for(uint8_t i=0; i<4; i++)
    {
        CB_buffer_add_item(buf_ptr, log_structure->timestamp);
    }

    /*Load the *log_length* to buffer, needs to run 4 times because it 32 bits (4 bytes)*/
    for(uint8_t i=0; i<4; i++)
    {
        CB_buffer_add_item(buf_ptr, log_structure->log_length);
    }

    /*flush the buffer to make sure their is room for the payload*/
    UART_SEND(buf_ptr);

    /*Load the payload into the buffer to be sent*/
    for(uint8_t i=0; i<log_structure->log_length; i++)
    {
        /*If the payload reaches a full buffer is will flush the buffer*/
        if(buf_ptr->count == buf_ptr->length)
        {
            UART_SEND(buf_ptr);
        }

        /*Send the payload to the circular buffer until the payload is fully loaded*/      
        CB_buffer_add_item(buf_ptr, *(log_structure->payload+i));
    }

    /*Load the *CHECKSUM* to buffer*/
    CB_buffer_add_item(buf_ptr, log_structure->checksum);

    /*flush the buffer to complete the packets transmission*/
    UART_SEND(buf_ptr);

    return;
}
/**********BBB_structure print**********/
void log_raw_item_bbb(log_item_t *log_structure)
{
    /*null pointer protection from a global buffer pointer*/
    if(buf_ptr == NULL)
    {
        return;
    }

    /*First flush the buffer to make sure their is room for the structure items*/
    BBB_circbuf_flush_send(buf_ptr);

    /***Start loading the circular buffer with the structure elements**/
    /*Load the *LOG ID* to buffer*/
    CB_buffer_add_item(buf_ptr, log_structure->log_id);

    /*Load the *MODULE ID* to buffer*/
    CB_buffer_add_item(buf_ptr, log_structure->module_id);

    /*Load the *TIMESTAMP* to buffer, needs to run 4 times because it 32 bits (4 bytes)*/
    uint32_t timestamp = log_structure->timestamp;
    uint8_t *timestamp_ptr = (uint8_t *)(&timestamp);
    for(uint8_t i=0; i<4; i++)
    {
        CB_buffer_add_item(buf_ptr, *(timestamp_ptr+i));
    }
    /*Load the *log_length* to buffer, needs to run 4 times because it 32 bits (4 bytes)*/
    uint32_t log_length = log_structure->log_length;
    uint8_t *log_length_ptr = (uint8_t *)(&log_length);
    for(uint8_t i=0; i<4; i++)
    {
        CB_buffer_add_item(buf_ptr, *(log_length_ptr+i));
    }
    /*flush the buffer to make sure their is room for the payload*/
    BBB_circbuf_flush_send(buf_ptr);

    /*Load the payload into the buffer to be sent*/
    for(uint8_t i=0; i<log_structure->log_length; i++)
    {
        /*If the payload reaches a full buffer is will flush the buffer*/
        if(buf_ptr->count == buf_ptr->length)
        {
            BBB_circbuf_flush_send(buf_ptr);
        }

        /*Send the payload to the circular buffer until the payload is fully loaded*/      
        CB_buffer_add_item(buf_ptr, *(log_structure->payload+i));
    }

    /*Load the *CHECKSUM* to buffer*/
    uint32_t checksum = log_structure->checksum;
    uint8_t *checksum_ptr = (uint8_t *)(&checksum);
    for(uint8_t i=0; i<4; i++)
    {
        CB_buffer_add_item(buf_ptr, *(checksum_ptr+i));
    }
    /*flush the buffer to complete the packets transmission*/
    BBB_circbuf_flush_send(buf_ptr);

    /*Add a new line for a clean log*/
    PRINT_NL;

    return;
}

/*********************************************************************************************/
/*********************************BBB_circbuf_flush_send**************************************/
/**********************************************************************************************
@brief- This function configures the BBB to empty the circbuf completely

This function empties the circular buffer completely when called
This function is blocking
This function specifically is used to printf to the terminal for the BBB

@param - buf_ptr: address of the circular buff that will send data
@return -void
**********************************************************************************************/

void BBB_circbuf_flush_send(CB_t *buf_ptr)
{
    /*NULL pointer protection*/
    if(buf_ptr == NULL)
    {
        return;
    }

    /*create varibles and pointer to hold received data*/
    uint8_t item;
    uint8_t *item_ptr = &item;   

    /*This function will keep running as long as count is >0*/
    while(buf_ptr->count)
    {
        /*Store the circular buffer item into the local variable*/
        CB_buffer_remove_item(buf_ptr,item_ptr);

        /*Send the local variable to the UART to be sent off board*/
        LOG_PRINTF(("%X "),item);
    }

    return;
}

/*********************************************************************************************/
/*********************************checksum_add************************************************/
/**********************************************************************************************
@brief- This function calculates the checksum for the log packet

A packet is passed into the function and the checksum is calculated by adding
all the binary "1" and returning a 32 bit value
This will update the checksum value in the log_structure

@param - log_structure: pointer to packet structure to be calculated
@return - void
**********************************************************************************************/

void checksum_add(log_item_t *log_structure)
{
    /*Need the variable for the return checksum*/
    uint32_t checksum = 0;
    uint32_t log_id = (uint32_t)log_structure->log_id;
    uint32_t module_id = (uint32_t)log_structure->module_id;
    uint32_t timestamp = (log_structure->timestamp);
    uint32_t log_length = (log_structure->log_length);

    /*Count the number of binary one in the log_id and put them into count*/
    while(log_id > 0)
    {
        if((log_id & 0x1) == 0x1)
        {
            checksum +=1;
        }
        log_id = log_id >> 1; /*binary shift left to capture the next value*/
    }

    /*Count the number of binary one in the module_id and put them into count*/
    while(module_id > 0)
    {
        if((module_id & 0x1) == 0x1)
        {
            checksum +=1;
        }
        module_id = module_id >> 1; /*binary shift left to capture the next value*/
    }

    /*Count the number of binary one in the timestamp and put them into count*/
    while(timestamp > 0)
    {
        if((timestamp & 0x1) == 0x1)
        {
            checksum +=1;
        }
        timestamp = timestamp >> 1; /*binary shift left to capture the next value*/
    }

    /*Count the number of binary one in the log length and put them into count*/
    while(log_length > 0)
    {
        if((log_length & 0x1) == 0x1)
        {
            checksum +=1;
        }
        log_length = log_length >> 1; /*binary shift left to capture the next value*/
    }

    for(uint32_t i=0; i<(log_structure->log_length); i++)
    {
        /*Load a value from the payload pointer into the variable to be used*/
        uint8_t payload_value = *((log_structure->payload)+i);
        while(payload_value > 0)
        {
            if((payload_value & 0x1) == 0x1)
            {
                checksum +=1;
            }
            payload_value = payload_value >> 1; /*binary shift left to capture the next value*/
        }
    }
    
    /*Add the value to the checksum in the log_structure*/
    (log_structure->checksum) = checksum;

    return;

}

/*********************************************************************************************/
/***********************************END of FILE***********************************************/
/*********************************************************************************************/
