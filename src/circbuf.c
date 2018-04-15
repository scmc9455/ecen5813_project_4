/*********************************************************************************************
@file - circbuf.c
@brief - circbuf.c file is the source file for the circular buffer functionality

This file contains the functions for a circular buffer to place items in memory 
and control/monitor that memory.
The buffer element size is uint8_t and size given at time of allocation.
Pointer should be passed into functions, 
The buffer and structure should be placed on the heap.
The buffer needs to be atomic by enabling/disabling global interrupts 
with (__enable_irq() and __disable_irq()) CMSYS 
functions (not needed on the BBB or HOST: map to nothing).

bufferFull and BufferEmpty needs to be static inline 
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

#include "circbuf.h"

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

CB_e CB_init(CB_t **buf_ptr, uint32_t length)
{
    /*The function needs to be passed a pointer to a pointer so the address change be changed*/
    /*outside of the function, so the malloc structure is given to the address*/
    /*First check to see if the pointer is NULL*/
    if(length > 0)
    {
        /*The line below dynamically allocates the structure for the circular buffer*/
        (*buf_ptr) = (CB_t *)malloc(sizeof(CB_t));
    }else{
    	return CB_NO_LENGTH_ERROR;
    }

    /*If the value is returned as NULL the init returns an Error*/
    if((*buf_ptr) == NULL)
    {
        return CB_NULL_POINTER_ERROR;
    }else{
        /*Second the buffer itself needs to be setup*/
        /*The line below dynamically allocates the structure for the circular buffer*/
        (*buf_ptr)->base = (void *)malloc(sizeof(buf_ptr)*length);
    }
   
    /*These next lines then store the values into the structure*/
    /*The head and tail are at the same location since nothing is in the buffer*/
    (*buf_ptr)->head = (*buf_ptr)->base;
    (*buf_ptr)->tail = (*buf_ptr)->base;
    (*buf_ptr)->length = length;
    (*buf_ptr)->count = 0;

    /*returns SUCCESS if this point is reached*/
    return CB_SUCCESS;
}

/*********************************************************************************************/
/***********************************CB_Destroy************************************************/
/**********************************************************************************************
@brief- This function deallocates the memory of the circular buffer

The function takes in a pointer of the buffer to be destroyed and deallocates the entire buffer
including memory and pointers using FREE. The pointer of the buffer is set to NULL.

@param - **buf_ptr pointer type to the buffer
@return - status of the buffer
**********************************************************************************************/

CB_e CB_destroy(CB_t **buf_ptr)
{
    /*This function cannot be performed if the pointer address is NULL*/
    /*So check to see if the value is NULL*/
    if((*buf_ptr) == NULL)
    {
        return CB_NULL_POINTER_ERROR;
    }

    /*Next the buffer base memory needs to be free (reverse oreder of init)*/
    free((void *)(*buf_ptr)); /*(casted to void to so any type of data is freed)*/
    /*Null the hanging pointer*/
    //*buf_ptr->base = NULL;

    /*Next the buffer struture needs to be free (reverse oreder of init)*/
    free((void *)(*buf_ptr)); /*(casted to void to so any type of data is freed)*/
    /*Null the hanging pointer*/
    (*buf_ptr)->base = NULL;

    return CB_SUCCESS;
}

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

CB_e CB_buffer_add_item(CB_t *buf_ptr, uint8_t data)
{
    /**********pointer check************/
    /*First checks that structure and buffer has valid pointers*/
    if((buf_ptr==NULL)||(buf_ptr->base==NULL)||(buf_ptr->head==NULL)||(buf_ptr->tail==NULL))
    {
        return CB_NULL_POINTER_ERROR;
    }

    /**********buffer full check************/
    /*Check to see if the buffer is full before an item is added*/
    if((buf_ptr->count)==(buf_ptr->length))
    {
        return CB_BUFFER_FULL;
    }

    /**********first value check************/
    /*this is to load the first value and still have the head pointer to the last inputted data*/
    if((buf_ptr->head == buf_ptr->tail) & (buf_ptr->count==0))
    {
        *(buf_ptr->head) = data;
        buf_ptr->count++;
        /*don't increament the head for the first value*/
        return CB_SUCCESS;
    }

    /*check to see if the head is at the end of the buffer*/
    if((buf_ptr->head) == (buf_ptr->base + (buf_ptr->length -1)))
    {
        /*if the head is at the end, it goes back to the base*/
        buf_ptr->head = buf_ptr->base; /*this wraps arounds to the beginning*/
    }else{
        /*the buffer head is increased to one*/
        buf_ptr->head++;
    }
    
    /*the data gets stored into the position of the buffer*/
    *(buf_ptr->head) = data;

    /*increment the count of the buffer structure*/
    buf_ptr->count++;

    return CB_SUCCESS;
}

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

CB_e CB_buffer_remove_item(CB_t *buf_ptr,uint8_t *data)
{
    /*First checks that structure and buffer has valid pointers*/
    if((buf_ptr==NULL)||(buf_ptr->base==NULL)||(buf_ptr->head==NULL)||(buf_ptr->tail==NULL))
    {
        return CB_NULL_POINTER_ERROR;
    }
    
    /*Also checks the storeage variable pointer*/
    if(data == NULL)
    {
        return CB_NULL_POINTER_ERROR;
    }

    /*Check to see if the buffer is empty before an item is added*/
    if(((buf_ptr->count)== 0))
    {
        return CB_BUFFER_EMPTY;       
    }

    if(buf_ptr->head == buf_ptr->tail)
    {
        *data = *buf_ptr->tail;
        buf_ptr->count--;
        return CB_SUCCESS;
    }

    /*Store the oldest item in the buffer into the data variable*/
    *data = *buf_ptr->tail;
    
    /*check to see if the tail is at the beginning of the buffer*/
    if((buf_ptr->tail) == (buf_ptr->base+((buf_ptr)->length-1)))
    {
        /*if the tail is at the beginning, it goes back to the end*/
        /*this wraps arounds to the end*/
        (buf_ptr)->tail = ((buf_ptr)->base); 
    }else{
        /*the buffer tail is decreased by one*/
        buf_ptr->tail++;
    }
  
    buf_ptr->count--;

    return CB_SUCCESS;
}

/*********************************************************************************************/
/************************************CB_is_full***********************************************/
/**********************************************************************************************
@brief- This function will check to see if the buffer is full

The function takes in a pointer to the buffer, and checks to see if the buffer is full.

@param - *buf_ptr: pointer type of the buffer
@return - Full or Not Full
**********************************************************************************************/

CB_e CB_is_full(CB_t *buf_ptr)
{
    /*First checks that structure and buffer has valid pointers*/
    if((buf_ptr==NULL)||(buf_ptr->base==NULL)||(buf_ptr->head==NULL)||(buf_ptr->tail==NULL))
    {
        return CB_NULL_POINTER_ERROR;
    }

    if(((buf_ptr)->count == (buf_ptr)->length))
    {
        return CB_BUFFER_FULL;
    }else{    
        return CB_BUFFER_NOT_FULL;
    }
}

/*********************************************************************************************/
/************************************CB_is_empty**********************************************/
/**********************************************************************************************
@brief- This function will check to see if the buffer is empty

The function takes in a pointer to the buffer, and checks to see if the buffer is empty.

@param - *buf_ptr: pointer type of the buffer
@return - Empty or Not Empty
**********************************************************************************************/

CB_e CB_is_empty(CB_t *buf_ptr)
{
    /*First checks that structure and buffer has valid pointers*/
    if((buf_ptr==NULL)||(buf_ptr->base==NULL)||(buf_ptr->head==NULL)||(buf_ptr->tail==NULL))
    {
        return CB_NULL_POINTER_ERROR;
    }

    if(((buf_ptr)->count == 0)||((buf_ptr)->head == ((buf_ptr)->tail)))
    {
        return CB_BUFFER_EMPTY;
    }else{    
        return CB_BUFFER_NOT_EMPTY;
    }
}

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

CB_e CB_peek(CB_t *buf_ptr, uint8_t position, uint8_t *data)
{
    /*First checks that structure and buffer has valid pointers*/
    if((buf_ptr==NULL)||(buf_ptr->base==NULL)||(buf_ptr->head==NULL)||(buf_ptr->tail==NULL))
    {
        return CB_NULL_POINTER_ERROR;
    }

    /*Also checks the storeage variable pointer*/
    if(data == NULL)
    {
        return CB_NULL_POINTER_ERROR;
    }

    if(((buf_ptr)->head - (buf_ptr)->base) >= position)
    {
        /*Puts the value of the peeked value from the pointer into the data location*/    
        *data = *((buf_ptr)->head - position);
    }else{
        /*decreased the position from the base to account for the wrap around*/
        position -= ((buf_ptr)->head - (buf_ptr)->base);
        /*stores the value from the end of the buffer into data*/
        *data = (*buf_ptr->base + (buf_ptr->length - position));
    }

    return CB_SUCCESS;
}

/*********************************************************************************************/
/**************************************End of File********************************************/
/*********************************************************************************************/
