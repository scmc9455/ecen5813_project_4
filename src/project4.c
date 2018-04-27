/*********************************************************************************************
@file - project4.c

@brief - Project4 source file 

This program only calls functions for project4
This also include all the necessary libraries and headers that are used in each of the files

@author - Scott McElroy

@date - April 25, 2018

Created for ECEN5813
**********************************************************************************************/

#include "project4.h"

/*********************************************************************************************/
/*****************************Project4********************************************************/
/**********************************************************************************************
@brief - This function is the main code that runs the program for project4_test

This file integrates that logger functionality into the project2 files

@param - void
@return -  void
**********************************************************************************************/

void project4(void)
{
    uint32_t payload_value;
#if defined LOG_ENABLE
    /*Initialization of the logger variables*/
    /*Start the timer logger*/
    uint32_t time_value;
    /*Allocate the memory for the string*/
    uint8_t *info_string_ptr = (uint8_t *)malloc(25);
    time_value = TIMESTART;
    /*Variables for the circular buffer*/
    CB_t **buf_ptr_temp = &buf_ptr;
    /*Call for buffer init of BUF_LEN*/
    CB_init(buf_ptr_temp,BUF_LEN);
    /*Setup item packet*/
    log_item_t packet;
    log_item_t *packet_ptr = &packet;
    /*Setup the packet*/
    packet.log_id = LOGGER_INITIALIZED;
    packet.module_id = TEST;
    time_value = TIMESTAMP(time_value);
    packet.timestamp = time_value;
    packet.log_length = NO_PAYLOAD;
    packet.payload = (uint8_t *)&payload_value;
    LOG_CHECKSUM(packet_ptr);
    /*Log the logger initialized pointer*/
    LOG_RAW_ITEM(packet_ptr);        
#endif
    /*System initialized*/
    LOG_SYSTEM_INIT;
    /*Profiling has started*/
    LOG_PROFILE_START;
#ifdef KL25Z
    /***********************************/
    /*Variables for reading back outputs*/
    uint8_t status_reg=0, config_reg=0, rf_setup_reg=0, rf_ch_reg=0, fifo_status_reg=0;
    /*To read the NRF device, it needs to be configured*/
    SPI_configure(); /*Writes to the config register and read back from the read config below*/
    nrf_init();
    /****************/
    /*Read Status*/
    status_reg = nrf_read_status();
    /**************/
    /*Read Config*/
    config_reg = nrf_read_config();
    /*************************/
    /*Read and write RF_Setup*/
    nrf_write_rf_setup(0x09); /*write a random value to RF_SETUP*/
    rf_setup_reg = nrf_read_rf_setup();
    /***************************/
    /*Read and write RF_Channel*/
    nrf_write_rf_ch(0x7F); /*write a random value to RF_CH*/
    rf_ch_reg = nrf_read_rf_ch();
    /***********************/
    /*Write the TX_addr reg*/
    uint8_t *tx_add_write_ptr = malloc(5);
    uint8_t *tx_add_read_ptr = malloc(5);
    /*Load the address pointer*/
    for(uint8_t i=0;i<5;i++)
    {
        *(tx_add_write_ptr+i) = (uint8_t)0xA5;
    }
    /*Write to the TX_address*/
    nrf_write_TX_ADDR(tx_add_write_ptr);
    /*Read back the address in the TX register*/
    nrf_read_TX_ADDR(tx_add_read_ptr);
    /*******************/
    /*Read FIFO_Status*/
    fifo_status_reg = nrf_read_fifo_status();
    /*While loops so compiler works*/
    while(status_reg || config_reg || rf_setup_reg || rf_ch_reg || fifo_status_reg);

#endif

#ifdef KL25Z_PRO
    /*********************************************************************/
    /*##########Profiler run for memset using DMA on KL25Z###############*/
    /*********************************************************************/
    /*needed variables for the program*/
    uint32_t memset_dma_kl25z_count_10 = 0;
    uint32_t memset_dma_kl25z_count_10_32bit = 0;
    uint32_t memset_dma_kl25z_count_100 = 0;
    uint32_t memset_dma_kl25z_count_1000 = 0;
    //uint32_t memset_dma_kl25z_count_5000 = 0;

    /*profiler code to run the analysis on the memset_dma using systick timer*/
    /*using 8-bit conversion (the number of conversions are listed as variables)*/
    memset_dma_kl25z_count_10 = profiler_memset_dma_kl25z(MEM_LEN_10, MEM_TYPE8);
    memset_dma_kl25z_count_10_32bit = profiler_memset_dma_kl25z(MEM_LEN_10, MEM_TYPE32);
    memset_dma_kl25z_count_100 = profiler_memset_dma_kl25z(MEM_LEN_100, MEM_TYPE8);
    memset_dma_kl25z_count_1000 = profiler_memset_dma_kl25z(MEM_LEN_1000, MEM_TYPE8);
    /*5000 will not run because linker is not allowing changes*/
    //memset_dma_kl25z_count_5000 = profiler_memset_dma_kl25z(MEM_LEN_5000, MEM_TYPE8);
    /******************************************************************************/
    /*****************End of KL25Z memset_dma test*********************************/
    /******************************************************************************/

    /**********************************************************************/
    /*########Profiler run for memmove using DMA on KL25Z#################*/
    /*********************************************************************/
    /*needed variables for the program*/
    uint32_t memmove_dma_kl25z_count_10 = 0;
    uint32_t memmove_dma_kl25z_count_10_32bit = 0;
    uint32_t memmove_dma_kl25z_count_100 = 0;
    uint32_t memmove_dma_kl25z_count_1000 = 0;
    //uint32_t memmove_dma_kl25z_count_5000 = 0;

    /*profiler code to run the analysis on the memmove_dma using systick timer*/
    /*using 8-bit conversion (the number of conversions are listed as variables)*/
    memmove_dma_kl25z_count_10 = profiler_memmove_dma_kl25z(MEM_LEN_10, MEM_TYPE8);
    memmove_dma_kl25z_count_10_32bit = profiler_memmove_dma_kl25z(MEM_LEN_10, MEM_TYPE32);
    memmove_dma_kl25z_count_100 = profiler_memmove_dma_kl25z(MEM_LEN_100, MEM_TYPE8);
    memmove_dma_kl25z_count_1000 = profiler_memmove_dma_kl25z(MEM_LEN_1000, MEM_TYPE8);
    /*5000 will not run because linker is not allowing changes*/
    //memmove_dma_kl25z_count_5000 = profiler_memmove_dma_kl25z(MEM_LEN_5000);

    /******************************************************************************/
    /*****************End of KL25Z memmove_dma test*********************************/
    /******************************************************************************/

    /*********************************************************************/
    /*#################Profiler run for my_memset on KL25Z###############*/
    /*********************************************************************/
    /*needed variables for the program*/
    uint32_t my_memset_kl25z_count_10 = 0;
    uint32_t my_memset_kl25z_count_100 = 0;
    uint32_t my_memset_kl25z_count_1000 = 0;
    //uint32_t my_memset_kl25z_count_5000 = 0;

    /*profiler code to run the analysis on the memset_dma using systick timer*/
    /*using 8-bit conversion (the number of conversions are listed as variables)*/
    my_memset_kl25z_count_10 = profiler_my_memset_kl25z(MEM_LEN_10);
    my_memset_kl25z_count_100 = profiler_my_memset_kl25z(MEM_LEN_100);
    my_memset_kl25z_count_1000 = profiler_my_memset_kl25z(MEM_LEN_1000);
    /*5000 will not run because linker is not allowing changes*/
    //my_memset_kl25z_count_5000 = profiler_my_memset_kl25z(MEM_LEN_5000);
    /******************************************************************************/
    /*****************End of KL25Z my_memset test*********************************/
    /******************************************************************************/

    /*********************************************************************/
    /*################Profiler run for my_memmove on KL25Z###############*/
    /*********************************************************************/
    /*needed variables for the program*/
    uint32_t my_memmove_kl25z_count_10 = 0;
    uint32_t my_memmove_kl25z_count_100 = 0;
    uint32_t my_memmove_kl25z_count_1000 = 0;
    //uint32_t my_memmove_kl25z_count_5000 = 0;

    /*profiler code to run the analysis on the memset_dma using systick timer*/
    /*using 8-bit conversion (the number of conversions are listed as variables)*/
    my_memmove_kl25z_count_10 = profiler_my_memmove_kl25z(MEM_LEN_10);
    my_memmove_kl25z_count_100 = profiler_my_memmove_kl25z(MEM_LEN_100);
    my_memmove_kl25z_count_1000 = profiler_my_memmove_kl25z(MEM_LEN_1000);
    /*5000 will not run because linker is not allowing changes*/
    //my_memmove_kl25z_count_5000 = profiler_my_memmove_kl25z(MEM_LEN_5000);
    /******************************************************************************/
    /*****************End of KL25Z my_memset test*********************************/
    /******************************************************************************/

    /*********************************************************************/
    /*#############Profiler run for stdlib memmove on KL25Z##############*/
    /*********************************************************************/
    /*needed variables for the program*/
    uint32_t memmove_kl25z_count_10 = 0;
    uint32_t memmove_kl25z_count_100 = 0;
    uint32_t memmove_kl25z_count_1000 = 0;
    //uint32_t memmove_kl25z_count_5000 = 0;

    /*profiler code to run the analysis on the memset_dma using systick timer*/
    /*using 8-bit conversion (the number of conversions are listed as variables)*/
    memmove_kl25z_count_10 = profiler_stdlib_memmove_kl25z(MEM_LEN_10);
    memmove_kl25z_count_100 = profiler_stdlib_memmove_kl25z(MEM_LEN_100);
    memmove_kl25z_count_1000 = profiler_stdlib_memmove_kl25z(MEM_LEN_1000);
    /*5000 will not run because linker is not allowing changes*/
    //memmove_kl25z_count_5000 = profiler_stdlib_memmove_kl25z(MEM_LEN_5000);
    /******************************************************************************/
    /*****************End of KL25Z my_memset test*********************************/
    /******************************************************************************/

    /*********************************************************************/
    /*#############Profiler run for stdlib memset on KL25Z###############*/
    /*********************************************************************/
    /*needed variables for the program*/
    uint32_t memset_kl25z_count_10 = 0;
    uint32_t memset_kl25z_count_100 = 0;
    uint32_t memset_kl25z_count_1000 = 0;
    //uint32_t memset_kl25z_count_5000 = 0;

    /*profiler code to run the analysis on the memset_dma using systick timer*/
    /*using 8-bit conversion (the number of conversions are listed as variables)*/
    memset_kl25z_count_10 = profiler_stdlib_memset_kl25z(MEM_LEN_10);
    memset_kl25z_count_100 = profiler_stdlib_memset_kl25z(MEM_LEN_100);
    memset_kl25z_count_1000 = profiler_stdlib_memset_kl25z(MEM_LEN_1000);
    /*5000 will not run because linker is not allowing changes*/
    //memset_kl25z_count_5000 = profiler_stdlib_memset_kl25z(MEM_LEN_5000);
    /******************************************************************************/
    /*****************End of KL25Z my_memset test*********************************/
    /******************************************************************************/

    /*Variable usage so compiler doesn't output an error*/
    while(memset_dma_kl25z_count_10 || memset_dma_kl25z_count_100 || memset_dma_kl25z_count_1000 );
    while(memset_dma_kl25z_count_10_32bit);
    while(memmove_dma_kl25z_count_10 || memmove_dma_kl25z_count_100 || memmove_dma_kl25z_count_1000 );
    while(memmove_dma_kl25z_count_10_32bit);
    while(my_memset_kl25z_count_10 || my_memset_kl25z_count_100 || my_memset_kl25z_count_1000 );
    while(my_memmove_kl25z_count_10 || my_memmove_kl25z_count_100 || my_memmove_kl25z_count_1000 );
    while(memmove_kl25z_count_10 || memmove_kl25z_count_100 || memmove_kl25z_count_1000 );
    while(memset_kl25z_count_10 || memset_kl25z_count_100 || memset_kl25z_count_1000 );

#endif /*KL25Z_PRO*/

    /******************************************************************************/
    /******************************************************************************/
    /******************************************************************************/

#if defined (HOST) || defined (BBB_PRO) 
    /*Variables to use*/
    uint32_t result = 0;
    /*********************************************************************/
    /*#############Profiler run for my_memset on BBB#####################*/
    /*********************************************************************/
    LOG_MY_MEMSET_INFO10;
    payload_value = profiler_my_memset_bbb(MEM_LEN_10);
    if(payload_value > 1)
    {
        /*Packet to log result*/
        LOG_PROFILE_RESULT;
        result +=1;
    }
    payload_value = 0;
    /*SEND_HEARTBEAT and timestamp*/
    SEND_HEARTBEAT;
    /****************/


    LOG_MY_MEMSET_INFO100;
    payload_value = profiler_my_memset_bbb(MEM_LEN_100);
    if(payload_value > 1)
    {
        /*Packet to log result*/
        LOG_PROFILE_RESULT;
        result +=1;
    }
    payload_value = 0;
    /*SEND_HEARTBEAT and timestamp*/
    SEND_HEARTBEAT;
    /****************/


    LOG_MY_MEMSET_INFO1000;
    payload_value = profiler_my_memset_bbb(MEM_LEN_1000);
    if(payload_value > 1)
    {
        /*Packet to log result*/
        LOG_PROFILE_RESULT;
        result +=1;
    }
    payload_value = 0;
    /*SEND_HEARTBEAT and timestamp*/
    SEND_HEARTBEAT;
    /****************/


    LOG_MY_MEMSET_INFO5000;
    payload_value = profiler_my_memset_bbb(MEM_LEN_5000);
    if(payload_value > 1)
    {
        /*Packet to log result*/
        LOG_PROFILE_RESULT;
        result +=1;
    }
    payload_value = 0;
    /*SEND_HEARTBEAT and timestamp*/
    SEND_HEARTBEAT;
    /****************/

    /******************************************************************************/
    /********************End of BBB my_memset test*********************************/
    /******************************************************************************/

    /*********************************************************************/
    /*#############Profiler run for my_memmove on BBB#####################*/
    /*********************************************************************/
    LOG_MY_MEMMOVE_INFO10;
    payload_value = profiler_my_memmove_bbb(MEM_LEN_10);
    if(payload_value > 1)
    {
        /*Packet to log result*/
        LOG_PROFILE_RESULT;
        result +=1;
    }
    payload_value = 0;
    /*SEND_HEARTBEAT and timestamp*/
    SEND_HEARTBEAT;
    /****************/

    LOG_MY_MEMMOVE_INFO100;
    payload_value = profiler_my_memmove_bbb(MEM_LEN_100);
    if(payload_value > 1)
    {
        /*Packet to log result*/
        LOG_PROFILE_RESULT;
        result +=1;
    }
    payload_value = 0;
    /*SEND_HEARTBEAT and timestamp*/
    SEND_HEARTBEAT;
    /****************/

    LOG_MY_MEMMOVE_INFO1000;
    payload_value = profiler_my_memmove_bbb(MEM_LEN_1000);
    if(payload_value > 1)
    {
        /*Packet to log result*/
        LOG_PROFILE_RESULT;
        result +=1;
    }
    payload_value = 0;
    /*SEND_HEARTBEAT and timestamp*/
    SEND_HEARTBEAT;
    /****************/

    LOG_MY_MEMMOVE_INFO5000;
    payload_value = profiler_my_memmove_bbb(MEM_LEN_5000);
    if(payload_value > 1)
    {
        /*Packet to log result*/
        LOG_PROFILE_RESULT;
        result +=1;
    }
    payload_value = 0;
    /*SEND_HEARTBEAT and timestamp*/
    SEND_HEARTBEAT;
    /****************/
    /******************************************************************************/
    /********************End of BBB my_memmove test********************************/
    /******************************************************************************/

    /*********************************************************************/
    /*#########Profiler run for stlib_memmove on BBB#####################*/
    /*********************************************************************/
    LOG_STDLIB_MEMMOVE_INFO10;
    payload_value = profiler_stdlib_memmove_bbb(MEM_LEN_10);
    if(payload_value > 1)
    {
        /*Packet to log result*/
        LOG_PROFILE_RESULT;
        result +=1;
    }
    payload_value = 0;
    /*SEND_HEARTBEAT and timestamp*/
    SEND_HEARTBEAT;
    /****************/

    LOG_STDLIB_MEMMOVE_INFO100;
    payload_value = profiler_stdlib_memmove_bbb(MEM_LEN_100);
    if(payload_value > 1)
    {
        /*Packet to log result*/
        LOG_PROFILE_RESULT;
        result +=1;
    }
    payload_value = 0;
    /*SEND_HEARTBEAT and timestamp*/
    SEND_HEARTBEAT;
    /****************/

    LOG_STDLIB_MEMMOVE_INFO1000;
    payload_value = profiler_stdlib_memmove_bbb(MEM_LEN_1000);
    if(payload_value > 1)
    {
        /*Packet to log result*/
        LOG_PROFILE_RESULT;
        result +=1;
    }
    payload_value = 0;
    /*SEND_HEARTBEAT and timestamp*/
    SEND_HEARTBEAT;
    /****************/

    LOG_STDLIB_MEMMOVE_INFO5000;
    payload_value = profiler_stdlib_memmove_bbb(MEM_LEN_5000);
    if(payload_value > 1)
    {
        /*Packet to log result*/
        LOG_PROFILE_RESULT;
        result +=1;
    }
    payload_value = 0;
    /*SEND_HEARTBEAT and timestamp*/
    SEND_HEARTBEAT;
    /****************/
    /******************************************************************************/
    /****************End of BBB stdlib_memmove test*******************************/
    /******************************************************************************/

    /*********************************************************************/
    /*#########Profiler run for stlib_memset on BBB#####################*/
    /*********************************************************************/
    LOG_STDLIB_MEMSET_INFO10;
    payload_value = profiler_stdlib_memset_bbb(MEM_LEN_10);
    if(payload_value > 1)
    {
        /*Packet to log result*/
        LOG_PROFILE_RESULT;
        result +=1;
    }
    payload_value = 0;
    /*SEND_HEARTBEAT and timestamp*/
    SEND_HEARTBEAT;
    /****************/

    LOG_STDLIB_MEMSET_INFO100;
    payload_value = profiler_stdlib_memset_bbb(MEM_LEN_100);
    if(payload_value > 1)
    {
        /*Packet to log result*/
        LOG_PROFILE_RESULT;
        result +=1;
    }
    payload_value = 0;
    /*SEND_HEARTBEAT and timestamp*/
    SEND_HEARTBEAT;
    /****************/

    LOG_STDLIB_MEMSET_INFO1000;
    payload_value = profiler_stdlib_memmove_bbb(MEM_LEN_1000);
    if(payload_value > 1)
    {
        /*Packet to log result*/
        LOG_PROFILE_RESULT;
        result +=1;
    }
    payload_value = 0;
    /*SEND_HEARTBEAT and timestamp*/
    SEND_HEARTBEAT;
    /****************/

    LOG_STDLIB_MEMSET_INFO5000;
    payload_value = profiler_stdlib_memset_bbb(MEM_LEN_5000);
    if(payload_value > 1)
    {
        /*Packet to log result*/
        LOG_PROFILE_RESULT;
        result +=1;
    }
    payload_value = 0;
    /*SEND_HEARTBEAT and timestamp*/
    SEND_HEARTBEAT;
    /****************/
    /******************************************************************************/
    /****************End of BBB stdlib_memset test*******************************/
    /******************************************************************************/

#endif /*BBB_PRO || HOST*/

    /*Profiling has completed*/
     LOG_PROFILE_COMPLETED;

    return;
}

/**********************************************************************************************/
/************************************End of File***********************************************/
/**********************************************************************************************/
