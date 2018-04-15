/*********************************************************************************************
@file - mem_profiler_kl25z.c

@brief - mem_profiler_kl25z.c file is the source file for memory profiler functions

This file will be used to profile the memory of the KL25Z.
The functions include the generation of a statics file and running of the profiler
Functions included are
1. systick_init
2. systick_start
3. systick_end
4. profiler_memset_dma_kl25z
5. profiler_memmove_dma_kl25z
6. profiler_my_memset_kl25z
7. profiler_my_memmove_kl25z
8. profiler_stdlib_memmove_kl25z
9. profiler_stdlib_memset_kl25z

@author - Scott McElroy

@date - March 31th, 2018

Created for ECEN5813
**********************************************************************************************/

#include "mem_profiler_kl25z.h"

#include <string.h>

uint8_t wait_state = 0;

/*********************************************************************************************/
/*****************************systick_init****************************************************/
/**********************************************************************************************
@brief - This function will initialize the SysTick timer for usage

@param - void
@return -  void
**********************************************************************************************/

void systick_init(void)
{
    /*Configure the SysTick Timer to be from the processor clock*/
    __SYST_CSR |= (TICK_CLKSOURCE);
    /*Set the timer to 0 and compare to max*/
    __SYST_RVR |= TIMER_MAX;
    __SYST_CVR |= 0;

    return;
}

/*********************************************************************************************/
/*****************************systick_start****************************************************/
/**********************************************************************************************
@brief - This function will start the SysTick timer for usage

@param - void
@return -  void
**********************************************************************************************/

void systick_start(void)
{
    __SYST_CSR |= __TICKEN;    

    return;
}

/*********************************************************************************************/
/*****************************systick_end****************************************************/
/**********************************************************************************************
@brief - This function will end the SysTick timer for usage

@param - void
@return -  void
**********************************************************************************************/

void systick_end(void)
{
    __SYST_CSR &= ~(__TICKEN);    

    return;
}


/*********************************************************************************************/
/****************************profiler_memset_kl25z********************************************/
/**********************************************************************************************
@brief - This function is the main code that will analyze the time it take to run mem functions

@param - memset_test_len: length of bytes of the test
@param - memset_type: type of data sent
@return - counter: returned value of the number of cycles
**********************************************************************************************/

uint32_t profiler_memset_dma_kl25z(uint32_t memset_test_len, uint8_t memset_type)
{
    /*necessary variables to run the profiler*/
    uint32_t count_cal = 0, count = 0;
    uint8_t *dst_memset_ptr = NULL;
    /*reverse block of memory to be set*/
    dst_memset_ptr = reserve_words(memset_test_len * (uint32_t)(memset_type/8));
    /*Depending on the input type the pointers will have to be casted differently*/

    /*Calibrate the start and end for timer so it can be subtracted out*/
    systick_init();
    systick_start(); /*start timer*/
    systick_end();  /*stop timer*/
    /*Use the count value to calibrate the timing in and out of the functions*/
    count_cal = (TIMER_MAX - __SYST_CVR); /*Count value of systick timer*/
     
    dma_init(); /*Initialize the DMA*/
    systick_init(); /*Init the systick*/
    /*run the memset function to be tested*/
    memset_dma(dst_memset_ptr, memset_test_len, memset_type, MEMSET_VALUE);
    /*need to wait for DMA to finish*/
    while(wait_state == 0){};
    /*Record the amount that it took to run the memset*/

    if(COUNT_FLAG == 1)
    {
        /*count rolled over so need to add max value times the number of times*/
    	count = ((TIMER_MAX) + (TIMER_MAX - __SYST_CVR));
    }else{
        count = (TIMER_MAX - __SYST_CVR); /*Count value of systick timer*/
    }
    /*Remove the calibration from the calculation to address function push and pop*/
    count -= count_cal; /*give the number of cycles it took to run the DMA testing*/
    /*Free allocated space from running code*/
    free_words(dst_memset_ptr);

    return count;
}

/*********************************************************************************************/
/****************************profiler_memmove_kl25z********************************************/
/**********************************************************************************************
@brief - This function is the main code that will analyze the time it take to run mem functions

@param - memmove_test_len: length of bytes of the test
@param - memmove_type: type of data sent
@return - counter: returned value of the number of cycles
**********************************************************************************************/

uint32_t profiler_memmove_dma_kl25z(uint32_t memmove_test_len, uint8_t memmove_type)
{
    /*necessary variables to run the profiler*/
    uint32_t count_cal = 0, count = 0;
    uint8_t *src_memmove_ptr = NULL;
    uint8_t *dst_memmove_ptr = NULL;
    /*reverse block of memory to be moved*/
    src_memmove_ptr = reserve_words(memmove_test_len * (uint32_t)(memmove_type/8));
    dst_memmove_ptr = reserve_words(memmove_test_len * (uint32_t)(memmove_type/8));
    /*Fill the source address memory using for loop and dependent on the type*/
    for(uint32_t i=0; i<(memmove_test_len) ; i++)
    {
    	/*Load the allocated memory with an arbitrary value to move*/
        *(src_memmove_ptr + i*(memmove_type/8)) = 0x25;
    }

    /*Calibrate the start and end for timer so it can be subtracted out*/
    systick_init();
    systick_start(); /*start timer*/
    systick_end();  /*stop timer*/
    /*Use the count value to calibrate the timing in and out of the functions*/
    count_cal = (TIMER_MAX - __SYST_CVR); /*Count value of systick timer*/

    dma_init(); /*Initialize the DMA*/
    systick_init(); /*Init the systick*/
    memmove_dma(src_memmove_ptr, dst_memmove_ptr, memmove_test_len, memmove_type);
    /*need to wait for DMA to finish*/
    while(wait_state == 0){};
    /*Record the amount that it took to run the memset*/

    if(COUNT_FLAG == 1)
    {
        /*count rolled over so need to add max value times the number of times*/
    	count = ((TIMER_MAX) + (TIMER_MAX - __SYST_CVR));
    }else{
        count = (TIMER_MAX - __SYST_CVR); /*Count value of systick timer*/
    }
    /*Remove the calibration from the calculation to address function push and pop*/
    count -= count_cal; /*give the number of cycles it took to run the DMA testing*/
    /*Free allocated space from running code*/
    free_words(dst_memmove_ptr);
    free_words(src_memmove_ptr);

    return count;
}

/*********************************************************************************************/
/****************************profiler_my_memset_kl25z********************************************/
/**********************************************************************************************
@brief - This function is the main code that will analyze the time it take to run my_mem functions

@param - memset_test_len: length of bytes of the test
@return - counter: returned value of the number of cycles
**********************************************************************************************/

uint32_t profiler_my_memset_kl25z(uint32_t memset_test_len)
{
    /*necessary variables to run the profiler*/
    uint32_t count_cal = 0, count = 0;
    uint8_t *dst_memset_ptr = NULL;
    /*reverse block of memory to be set*/
    dst_memset_ptr = reserve_words(memset_test_len);
    /*Depending on the input type the pointers will have to be casted differently*/

    /*Calibrate the start and end for timer so it can be subtracted out*/
    systick_init();
    systick_start(); /*start timer*/
    systick_end();  /*stop timer*/
    /*Use the count value to calibrate the timing in and out of the functions*/
    count_cal = (TIMER_MAX - __SYST_CVR); /*Count value of systick timer*/

    systick_init(); /*Init the systick*/
    /*Start the systick timer*/
    systick_start();
    /*run the memset function to be tested*/
    my_memset(dst_memset_ptr, memset_test_len, MEMSET_VALUE);
    /*Start the systick timer*/
    systick_end();
    /*Record the amount that it took to run the memset*/
    if(COUNT_FLAG == 1)
    {
        /*count rolled over so need to add max value times the number of times*/
    	count = ((TIMER_MAX) + (TIMER_MAX - __SYST_CVR));
    }else{
        count = (TIMER_MAX - __SYST_CVR); /*Count value of systick timer*/
    }
    /*Remove the calibration from the calculation to address function push and pop*/
    count -= count_cal; /*give the number of cycles it took to run the DMA testing*/
    /*Free allocated space from running code*/
    free_words(dst_memset_ptr);

    return count;
}

/*********************************************************************************************/
/****************************profiler_my_memmove_kl25z****************************************/
/**********************************************************************************************
@brief - This function is the main code that will analyze the time it take to run my_mem functions

@param - memset_test_len: length of bytes of the test
@return - counter: returned value of the number of cycles
**********************************************************************************************/

uint32_t profiler_my_memmove_kl25z(uint32_t memmove_test_len)
{
    /*necessary variables to run the profiler*/
    uint32_t count_cal = 0, count = 0;
    uint8_t *src_memmove_ptr = NULL;
    uint8_t *dst_memmove_ptr = NULL;
    /*reverse block of memory to be moved*/
    src_memmove_ptr = reserve_words(memmove_test_len);
    dst_memmove_ptr = reserve_words(memmove_test_len);
    /*Fill the source address memory using for loop and dependent on the type*/
    for(uint32_t i=0; i<(memmove_test_len) ; i++)
    {
    	/*Load the allocated memory with an arbitrary value to move*/
        *(src_memmove_ptr + i) = 0xA5;
    }

    /*Calibrate the start and end for timer so it can be subtracted out*/
    systick_init();
    systick_start(); /*start timer*/
    systick_end();  /*stop timer*/
    /*Use the count value to calibrate the timing in and out of the functions*/
    count_cal = (TIMER_MAX - __SYST_CVR); /*Count value of systick timer*/

    systick_init(); /*Init the systick*/
    /*Start the systick timer*/
    systick_start();
    my_memmove(src_memmove_ptr, dst_memmove_ptr, memmove_test_len);
    /*Stop the systick timer*/
    systick_end();
    /*Record the amount that it took to run the memset*/
    if(COUNT_FLAG == 1)
    {
        /*count rolled over so need to add max value times the number of times*/
    	count = ((TIMER_MAX) + (TIMER_MAX - __SYST_CVR));
    }else{
        count = (TIMER_MAX - __SYST_CVR); /*Count value of systick timer*/
    }
    /*Remove the calibration from the calculation to address function push and pop*/
    count -= count_cal; /*give the number of cycles it took to run the DMA testing*/
    /*Free allocated space from running code*/
    free_words(dst_memmove_ptr);
    free_words(src_memmove_ptr);

    return count;
}

/*********************************************************************************************/
/****************************profiler_memmove_kl25z_standard**********************************/
/**********************************************************************************************
@brief - This function is the main code that will analyze memmove standard lib functions

@param - memset_test_len: length of bytes of the test
@return - counter: returned value of the number of cycles
**********************************************************************************************/

uint32_t profiler_stdlib_memmove_kl25z(uint32_t memmove_test_len)
{
    /*necessary variables to run the profiler*/
    uint32_t count_cal = 0, count = 0;
    uint8_t *src_memmove_ptr = NULL;
    uint8_t *dst_memmove_ptr = NULL;
    /*reverse block of memory to be moved*/
    src_memmove_ptr = reserve_words(memmove_test_len);
    dst_memmove_ptr = reserve_words(memmove_test_len);
    /*Fill the source address memory using for loop and dependent on the type*/
    for(uint32_t i=0; i<(memmove_test_len) ; i++)
    {
    	/*Load the allocated memory with an arbitrary value to move*/
        *(src_memmove_ptr + i) = 0xA5;
    }

    /*Calibrate the start and end for timer so it can be subtracted out*/
    systick_init();
    systick_start(); /*start timer*/
    systick_end();  /*stop timer*/
    /*Use the count value to calibrate the timing in and out of the functions*/
    count_cal = (TIMER_MAX - __SYST_CVR); /*Count value of systick timer*/

    systick_init(); /*Init the systick*/
    /*Start the systick timer*/
    systick_start();
    /*Run the standard lib memmove functions*/
    memmove(dst_memmove_ptr, src_memmove_ptr, memmove_test_len);
    /*Stop the systick timer*/
    systick_end();
    /*Record the amount that it took to run the memset*/
    if(COUNT_FLAG == 1)
    {
        /*count rolled over so need to add max value times the number of times*/
    	count = ((TIMER_MAX) + (TIMER_MAX - __SYST_CVR));
    }else{
        count = (TIMER_MAX - __SYST_CVR); /*Count value of systick timer*/
    }
    /*Remove the calibration from the calculation to address function push and pop*/
    count -= count_cal; /*give the number of cycles it took to run the DMA testing*/
    /*Free allocated space from running code*/
    free_words(dst_memmove_ptr);
    free_words(src_memmove_ptr);

    return count;
}

/*********************************************************************************************/
/************************profiler_stdlib_memset_kl25z*****************************************/
/**********************************************************************************************
@brief - This function is the main code that will analyze the memset functions in stdlib

@param - memset_test_len: length of bytes of the test
@return - counter: returned value of the number of cycles
**********************************************************************************************/

uint32_t profiler_stdlib_memset_kl25z(uint32_t memset_test_len)
{
    /*necessary variables to run the profiler*/
    uint32_t count_cal = 0, count = 0;
    uint8_t *dst_memset_ptr = NULL;
    /*reverse block of memory to be set*/
    dst_memset_ptr = reserve_words(memset_test_len);
    /*Depending on the input type the pointers will have to be casted differently*/

    /*Calibrate the start and end for timer so it can be subtracted out*/
    systick_init();
    systick_start(); /*start timer*/
    systick_end();  /*stop timer*/
    /*Use the count value to calibrate the timing in and out of the functions*/
    count_cal = (TIMER_MAX - __SYST_CVR); /*Count value of systick timer*/

    systick_init(); /*Init the systick*/
    /*Start the systick timer*/
    systick_start();
    /*run the memset function to be tested*/
    memset(dst_memset_ptr, MEMSET_VALUE, memset_test_len);
    /*Start the systick timer*/
    systick_end();
    /*Record the amount that it took to run the memset*/
    if(COUNT_FLAG == 1)
    {
        /*count rolled over so need to add max value times the number of times*/
    	count = ((TIMER_MAX) + (TIMER_MAX - __SYST_CVR));
    }else{
        count = (TIMER_MAX - __SYST_CVR); /*Count value of systick timer*/
    }
    /*Remove the calibration from the calculation to address function push and pop*/
    count -= count_cal; /*give the number of cycles it took to run the DMA testing*/
    /*Free allocated space from running code*/
    free_words(dst_memset_ptr);

    return count;
}

/*********************************************************************************************/
/*****************************End of File*****************************************************/
/*********************************************************************************************/
