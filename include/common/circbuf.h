/*********************************************************************************************
@file - circbuf.h
@brief - circbuf.h file is the header file for the circular buffer functionality

This file contains the functions for a circular buffer to place items in memory 
and control/monitor that memory.
The buffer element size is uint8_t and size given at time of allocation.
Pointer should be passed into functions, 
The buffer and structure should be placed on the heap.
The buffer needs to be atomic by enabling/disabling global interrupts 
with (__enable_irq() and __disable_irq()) CMSYS 
functions (not needed on the BBB or HOST: map to nothing).

bufferFull and BufferEmpty needs to be inline 
(These need to be accounted for on the C89 compiler)???

This file is the source for the circular buffer functions
1. CB_init
2. CB_destroy
3. CB_buffer_add_item
4. CB_buffer_remove_item
5. CB_is_full
6. CB_is_empty
7. CB_peek

@author - Scott McElroy

@date - March 3, 2018

Created for ECEN5813
**********************************************************************************************/
#ifndef __CIRCBUF_H__
#define __CIRCBUF_H__

#include <stdint.h>
#include <stdlib.h>

typedef struct {
  uint8_t *base; /*allocated size of memory*/
  uint8_t *head; /*pointer to the newest item in the buffer*/
  uint8_t *tail; /*pointer to the oldest item in the buffer*/
  size_t length; /*set dynamically and is the number of items allocated*/
  size_t count;  /*current number of items in the buffer*/
}CB_t;

typedef enum {
  CB_SUCCESS            =0,
  CB_NULL_POINTER_ERROR =1,
  CB_NO_LENGTH_ERROR    =2,
  CB_BUFFER_FULL        =3,
  CB_BUFFER_NOT_FULL    =4,
  CB_BUFFER_EMPTY       =5,
  CB_BUFFER_NOT_EMPTY   =6
} CB_e;

/*********************************************************************************************/
/***********************************CB_INIT***************************************************/
/**********************************************************************************************
@brief- This function is initializes the circular buffer

This function initializes a circular buffer with length and the pointer to the buffer
The function returns error codes on success of failure
The buffer allocates Head,Tail, and count

@param - **buf_ptr: pointer type of the buffer
@param - length: buffer length
@return - status of the buffer
**********************************************************************************************/

CB_e CB_init(CB_t **buf_ptr,uint32_t length);

/*********************************************************************************************/
/***********************************CB_Destroy************************************************/
/**********************************************************************************************
@brief- This function deallocates the memory of the circular buffer

The function takes in a pointer of the buffer to be destroyed and deallocates the entire buffer
including memory and pointers using FREE. The pointer of the buffer is set to NULL.

@param - **buf_ptr: pointer type to the buffer
@return - status of the buffer
**********************************************************************************************/

CB_e CB_destroy(CB_t **buf_ptr);

/*********************************************************************************************/
/******************************CB_buffer_add_item*********************************************/
/**********************************************************************************************
@brief- This function adds an item to the buffer

The function takes in a pointer to the buffer, and data to be added.
The function returns the success or failure of the buffer function.

@param - buf_ptr: pointer to the buffer
@param - data: data to add to the buffer
@return - status of the buffer
**********************************************************************************************/

CB_e CB_buffer_add_item(CB_t *buf_ptr, uint8_t data);

/*********************************************************************************************/
/******************************CB_buffer_remove_item******************************************/
/**********************************************************************************************
@brief- This function removes an item to the buffer

The function takes in a pointer to the buffer, and variable to store/remove item from the bufer
The function returns the success or failure of the buffer function.

@param - *buf_ptr: pointer type of the buffer
@param - *data: variable to store the removed data
@return - status of the buffer
**********************************************************************************************/

CB_e CB_buffer_remove_item(CB_t *buf_ptr, uint8_t *data);

/*********************************************************************************************/
/************************************CB_is_full***********************************************/
/**********************************************************************************************
@brief- This function will check to see if the buffer is full

The function takes in a pointer to the buffer, and checks to see if the buffer is full.

@param - *buf_ptr: pointer type of the buffer
@return - Full or Not Full (1 or 0)
**********************************************************************************************/

CB_e CB_is_full(CB_t *buf_ptr);

/*********************************************************************************************/
/************************************CB_is_empty**********************************************/
/**********************************************************************************************
@brief- This function will check to see if the buffer is empty

The function takes in a pointer to the buffer, and checks to see if the buffer is empty.

@param - *buf_ptr: pointer type of the buffer
@return - Empty or Not Empty (1 or 0)
**********************************************************************************************/

CB_e CB_is_empty(CB_t *buf_ptr); 

/*********************************************************************************************/
/****************************************CB_peek**********************************************/
/**********************************************************************************************
@brief- This function will check to see if the buffer is empty

The function takes in a pointer to the buffer, and checks to see if the buffer is empty.

@param - *buf_ptr: pointer type of the buffer
@param - position: position from the head of the buffer to peek
@param - *data: pointer to hold the data peeked at
@return - Status of the operation
**********************************************************************************************/

CB_e CB_peek(CB_t *buf_ptr, uint8_t position, uint8_t *data);


#endif /*__CIRCBUF_H__*/

/*********************************************************************************************/
/**************************************End of File********************************************/
/*********************************************************************************************/
