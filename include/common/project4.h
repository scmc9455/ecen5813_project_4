/*********************************************************************************************
@file - project4.h

@brief - Project4 header file 

This program only calls functions for project4_test
This also include all the necessary libraries and headers that are used in each of the files

@author - Scott McElroy

@date - April 25, 2018

Created for ECEN5813
**********************************************************************************************/

#ifndef __PROJECT4_H__
#define __PROJECT4_H__

#include "logger.h"

#define BUF_LEN   (50)
#define NO_PAYLOAD (0)

#include "circbuf.h"
#include "timestamp.h"

extern CB_t *buf_ptr;

#ifdef KL25Z_PRO
#include "dma.h"
#include "mem_profiler_kl25z.h"
#endif

#ifdef KL25Z
#include "dma.h"
#include "spi.h"
#include "gpio.h"
#include "nordic.h"
#endif

#if defined (HOST) || defined (BBB_PRO)
#include "mem_profiler_bbb.h"
#include <stdio.h>
#endif

#include <stdint.h>

/*Memset Testing defines*/
#define MEM_LEN_10         (10)
#define MEM_LEN_100        (100)
#define MEM_LEN_1000       (1000)
#define MEM_LEN_5000       (5000)
#define MEM_TYPE8          (8)
#define MEM_TYPE16         (16)
#define MEM_TYPE32         (32)

/*MARCO function for implementing logger*/
/*Include logger functions for each sendable packet*/
/*************PACKET CREATORS**********/
#ifdef LOG_ENABLE
#define SEND_HEARTBEAT   {\
    packet.log_id = HEARTBEAT;\
    time_value = TIMESTAMP(time_value);\
    packet.timestamp = time_value;\
    LOG_CHECKSUM(packet_ptr);\
    LOG_RAW_ITEM(packet_ptr);}
#define LOG_SYSTEM_INIT  {\
    packet.log_id = SYSTEM_INITIALIZED;\
    time_value = TIMESTAMP(time_value);\
    packet.timestamp = time_value;\
    LOG_CHECKSUM(packet_ptr);\
    LOG_RAW_ITEM(packet_ptr);}
#define LOG_PROFILE_START   {\
    packet.log_id = PROFILING_STARTED;\
    time_value = TIMESTAMP(time_value);\
    packet.timestamp = time_value;\
    LOG_CHECKSUM(packet_ptr);\
    LOG_RAW_ITEM(packet_ptr);}  
#define LOG_PROFILE_RESULT   {\
    packet.log_id = PROFILING_RESULT;\
    packet.log_length = 4;\
    packet.payload = (uint8_t *)&payload_value;\
    time_value = TIMESTAMP(time_value);\
    packet.timestamp = time_value;\
    LOG_CHECKSUM(packet_ptr);\
    LOG_RAW_ITEM(packet_ptr);}  
#define LOG_PROFILE_COMPLETED   {\
    packet.log_id = PROFILING_COMPLETED;\
    time_value = TIMESTAMP(time_value);\
    packet.timestamp = time_value;\
    LOG_CHECKSUM(packet_ptr);\
    LOG_RAW_ITEM(packet_ptr);}  
/*Memset Packet creation*/
#define LOG_MY_MEMSET_INFO10  {\
    packet.log_id = INFO;\
    packet.log_length = 16;\
    *(info_string_ptr) = 0x6D;\
    *(info_string_ptr+1) = 0x79;\
    *(info_string_ptr+2) = 0x5F;\
    *(info_string_ptr+3) = 0x6D;\
    *(info_string_ptr+4) = 0x65;\
    *(info_string_ptr+5) = 0x6D;\
    *(info_string_ptr+6) = 0x73;\
    *(info_string_ptr+7) = 0x65;\
    *(info_string_ptr+8) = 0x74;\
    *(info_string_ptr+9) = 0x20;\
    *(info_string_ptr+10) = 0x6C;\
    *(info_string_ptr+11) = 0x65;\
    *(info_string_ptr+12) = 0x6E;\
    *(info_string_ptr+13) = 0x20;\
    *(info_string_ptr+14) = 0x31;\
    *(info_string_ptr+15) = 0x30;\
    packet.payload = info_string_ptr; \
    time_value = TIMESTAMP(time_value);\
    packet.timestamp = time_value;\
    LOG_CHECKSUM(packet_ptr);\
    LOG_RAW_ITEM(packet_ptr);}  
#define LOG_MY_MEMSET_INFO100  {\
    packet.log_id = INFO;\
    packet.log_length = 17;\
    *(info_string_ptr) = 0x6D;\
    *(info_string_ptr+1) = 0x79;\
    *(info_string_ptr+2) = 0x5F;\
    *(info_string_ptr+3) = 0x6D;\
    *(info_string_ptr+4) = 0x65;\
    *(info_string_ptr+5) = 0x6D;\
    *(info_string_ptr+6) = 0x73;\
    *(info_string_ptr+7) = 0x65;\
    *(info_string_ptr+8) = 0x74;\
    *(info_string_ptr+9) = 0x20;\
    *(info_string_ptr+10) = 0x6C;\
    *(info_string_ptr+11) = 0x65;\
    *(info_string_ptr+12) = 0x6E;\
    *(info_string_ptr+13) = 0x20;\
    *(info_string_ptr+14) = 0x31;\
    *(info_string_ptr+15) = 0x30;\
    *(info_string_ptr+16) = 0x30;\
    packet.payload = info_string_ptr; \
    time_value = TIMESTAMP(time_value);\
    packet.timestamp = time_value;\
    LOG_CHECKSUM(packet_ptr);\
    LOG_RAW_ITEM(packet_ptr);} 
#define LOG_MY_MEMSET_INFO1000  {\
    packet.log_id = INFO;\
    packet.log_length = 18;\
    *(info_string_ptr) = 0x6D;\
    *(info_string_ptr+1) = 0x79;\
    *(info_string_ptr+2) = 0x5F;\
    *(info_string_ptr+3) = 0x6D;\
    *(info_string_ptr+4) = 0x65;\
    *(info_string_ptr+5) = 0x6D;\
    *(info_string_ptr+6) = 0x73;\
    *(info_string_ptr+7) = 0x65;\
    *(info_string_ptr+8) = 0x74;\
    *(info_string_ptr+9) = 0x20;\
    *(info_string_ptr+10) = 0x6C;\
    *(info_string_ptr+11) = 0x65;\
    *(info_string_ptr+12) = 0x6E;\
    *(info_string_ptr+13) = 0x20;\
    *(info_string_ptr+14) = 0x31;\
    *(info_string_ptr+15) = 0x30;\
    *(info_string_ptr+16) = 0x30;\
    *(info_string_ptr+17) = 0x30;\
    packet.payload = info_string_ptr; \
    time_value = TIMESTAMP(time_value);\
    packet.timestamp = time_value;\
    LOG_CHECKSUM(packet_ptr);\
    LOG_RAW_ITEM(packet_ptr);}     
#define LOG_MY_MEMSET_INFO5000  {\
    packet.log_id = INFO;\
    packet.log_length = 18;\
    *(info_string_ptr) = 0x6D;\
    *(info_string_ptr+1) = 0x79;\
    *(info_string_ptr+2) = 0x5F;\
    *(info_string_ptr+3) = 0x6D;\
    *(info_string_ptr+4) = 0x65;\
    *(info_string_ptr+5) = 0x6D;\
    *(info_string_ptr+6) = 0x73;\
    *(info_string_ptr+7) = 0x65;\
    *(info_string_ptr+8) = 0x74;\
    *(info_string_ptr+9) = 0x20;\
    *(info_string_ptr+10) = 0x6C;\
    *(info_string_ptr+11) = 0x65;\
    *(info_string_ptr+12) = 0x6E;\
    *(info_string_ptr+13) = 0x20;\
    *(info_string_ptr+14) = 0x35;\
    *(info_string_ptr+15) = 0x30;\
    *(info_string_ptr+16) = 0x30;\
    *(info_string_ptr+17) = 0x30;\
    packet.payload = info_string_ptr; \
    time_value = TIMESTAMP(time_value);\
    packet.timestamp = time_value;\
    LOG_CHECKSUM(packet_ptr);\
    LOG_RAW_ITEM(packet_ptr);}  
/*Memmove Packet Creation*/
#define LOG_MY_MEMMOVE_INFO10  {\
    packet.log_id = INFO;\
    packet.log_length = 17;\
    *(info_string_ptr) = 0x6D;\
    *(info_string_ptr+1) = 0x79;\
    *(info_string_ptr+2) = 0x5F;\
    *(info_string_ptr+3) = 0x6D;\
    *(info_string_ptr+4) = 0x65;\
    *(info_string_ptr+5) = 0x6D;\
    *(info_string_ptr+6) = 0x6D;\
    *(info_string_ptr+7) = 0x6F;\
    *(info_string_ptr+8) = 0x76;\
    *(info_string_ptr+9) = 0x65;\
    *(info_string_ptr+10) = 0x20;\
    *(info_string_ptr+11) = 0x6C;\
    *(info_string_ptr+12) = 0x65;\
    *(info_string_ptr+13) = 0x6E;\
    *(info_string_ptr+14) = 0x20;\
    *(info_string_ptr+15) = 0x31;\
    *(info_string_ptr+16) = 0x30;\
    packet.payload = info_string_ptr; \
    time_value = TIMESTAMP(time_value);\
    packet.timestamp = time_value;\
    LOG_CHECKSUM(packet_ptr);\
    LOG_RAW_ITEM(packet_ptr);}  
#define LOG_MY_MEMMOVE_INFO100  {\
    packet.log_id = INFO;\
    packet.log_length = 18;\
    *(info_string_ptr) = 0x6D;\
    *(info_string_ptr+1) = 0x79;\
    *(info_string_ptr+2) = 0x5F;\
    *(info_string_ptr+3) = 0x6D;\
    *(info_string_ptr+4) = 0x65;\
    *(info_string_ptr+5) = 0x6D;\
    *(info_string_ptr+6) = 0x6D;\
    *(info_string_ptr+7) = 0x6F;\
    *(info_string_ptr+8) = 0x76;\
    *(info_string_ptr+9) = 0x65;\
    *(info_string_ptr+10) = 0x20;\
    *(info_string_ptr+11) = 0x6C;\
    *(info_string_ptr+12) = 0x65;\
    *(info_string_ptr+13) = 0x6E;\
    *(info_string_ptr+14) = 0x20;\
    *(info_string_ptr+15) = 0x31;\
    *(info_string_ptr+16) = 0x30;\
    *(info_string_ptr+17) = 0x30;\
    packet.payload = info_string_ptr; \
    time_value = TIMESTAMP(time_value);\
    packet.timestamp = time_value;\
    LOG_CHECKSUM(packet_ptr);\
    LOG_RAW_ITEM(packet_ptr);} 
#define LOG_MY_MEMMOVE_INFO1000  {\
    packet.log_id = INFO;\
    packet.log_length = 19;\
    *(info_string_ptr) = 0x6D;\
    *(info_string_ptr+1) = 0x79;\
    *(info_string_ptr+2) = 0x5F;\
    *(info_string_ptr+3) = 0x6D;\
    *(info_string_ptr+4) = 0x65;\
    *(info_string_ptr+5) = 0x6D;\
    *(info_string_ptr+6) = 0x6D;\
    *(info_string_ptr+7) = 0x6F;\
    *(info_string_ptr+8) = 0x76;\
    *(info_string_ptr+9) = 0x65;\
    *(info_string_ptr+10) = 0x20;\
    *(info_string_ptr+11) = 0x6C;\
    *(info_string_ptr+12) = 0x65;\
    *(info_string_ptr+13) = 0x6E;\
    *(info_string_ptr+14) = 0x20;\
    *(info_string_ptr+15) = 0x31;\
    *(info_string_ptr+16) = 0x30;\
    *(info_string_ptr+17) = 0x30;\
    *(info_string_ptr+18) = 0x30;\
    packet.payload = info_string_ptr; \
    time_value = TIMESTAMP(time_value);\
    packet.timestamp = time_value;\
    LOG_CHECKSUM(packet_ptr);\
    LOG_RAW_ITEM(packet_ptr);}     
#define LOG_MY_MEMMOVE_INFO5000  {\
    packet.log_id = INFO;\
    packet.log_length = 19;\
    *(info_string_ptr) = 0x6D;\
    *(info_string_ptr+1) = 0x79;\
    *(info_string_ptr+2) = 0x5F;\
    *(info_string_ptr+3) = 0x6D;\
    *(info_string_ptr+4) = 0x65;\
    *(info_string_ptr+5) = 0x6D;\
    *(info_string_ptr+6) = 0x6D;\
    *(info_string_ptr+7) = 0x6F;\
    *(info_string_ptr+8) = 0x76;\
    *(info_string_ptr+9) = 0x65;\
    *(info_string_ptr+10) = 0x20;\
    *(info_string_ptr+11) = 0x6C;\
    *(info_string_ptr+12) = 0x65;\
    *(info_string_ptr+13) = 0x6E;\
    *(info_string_ptr+14) = 0x20;\
    *(info_string_ptr+15) = 0x35;\
    *(info_string_ptr+16) = 0x30;\
    *(info_string_ptr+17) = 0x30;\
    *(info_string_ptr+18) = 0x30;\
    packet.payload = info_string_ptr; \
    time_value = TIMESTAMP(time_value);\
    packet.timestamp = time_value;\
    LOG_CHECKSUM(packet_ptr);\
    LOG_RAW_ITEM(packet_ptr);}  
/*Macro functions for Stdlib_memset*/
#define LOG_STDLIB_MEMSET_INFO10  {\
    packet.log_id = INFO;\
    packet.log_length = 20;\
    *(info_string_ptr) = 0x73;\
    *(info_string_ptr+1) = 0x74;\
    *(info_string_ptr+2) = 0x64;\
    *(info_string_ptr+3) = 0x6C;\
    *(info_string_ptr+4) = 0x69;\
    *(info_string_ptr+5) = 0x62;\
    *(info_string_ptr+6) = 0x5F;\
    *(info_string_ptr+7) = 0x6D;\
    *(info_string_ptr+8) = 0x65;\
    *(info_string_ptr+9) = 0x6D;\
    *(info_string_ptr+10) = 0x73;\
    *(info_string_ptr+11) = 0x65;\
    *(info_string_ptr+12) = 0x74;\
    *(info_string_ptr+13) = 0x20;\
    *(info_string_ptr+14) = 0x6C;\
    *(info_string_ptr+15) = 0x65;\
    *(info_string_ptr+16) = 0x6E;\
    *(info_string_ptr+17) = 0x20;\
    *(info_string_ptr+18) = 0x31;\
    *(info_string_ptr+19) = 0x30;\
    packet.payload = info_string_ptr; \
    time_value = TIMESTAMP(time_value);\
    packet.timestamp = time_value;\
    LOG_CHECKSUM(packet_ptr);\
    LOG_RAW_ITEM(packet_ptr);}  
#define LOG_STDLIB_MEMSET_INFO100  {\
    packet.log_id = INFO;\
    packet.log_length = 21;\
    *(info_string_ptr) = 0x73;\
    *(info_string_ptr+1) = 0x74;\
    *(info_string_ptr+2) = 0x64;\
    *(info_string_ptr+3) = 0x6C;\
    *(info_string_ptr+4) = 0x69;\
    *(info_string_ptr+5) = 0x62;\
    *(info_string_ptr+6) = 0x5F;\
    *(info_string_ptr+7) = 0x6D;\
    *(info_string_ptr+8) = 0x65;\
    *(info_string_ptr+9) = 0x6D;\
    *(info_string_ptr+10) = 0x73;\
    *(info_string_ptr+11) = 0x65;\
    *(info_string_ptr+12) = 0x74;\
    *(info_string_ptr+13) = 0x20;\
    *(info_string_ptr+14) = 0x6C;\
    *(info_string_ptr+15) = 0x65;\
    *(info_string_ptr+16) = 0x6E;\
    *(info_string_ptr+17) = 0x20;\
    *(info_string_ptr+18) = 0x31;\
    *(info_string_ptr+19) = 0x30;\
    *(info_string_ptr+20) = 0x30;\
    packet.payload = info_string_ptr; \
    time_value = TIMESTAMP(time_value);\
    packet.timestamp = time_value;\
    LOG_CHECKSUM(packet_ptr);\
    LOG_RAW_ITEM(packet_ptr);}  
#define LOG_STDLIB_MEMSET_INFO1000  {\
    packet.log_id = INFO;\
    packet.log_length = 22;\
    *(info_string_ptr) = 0x73;\
    *(info_string_ptr+1) = 0x74;\
    *(info_string_ptr+2) = 0x64;\
    *(info_string_ptr+3) = 0x6C;\
    *(info_string_ptr+4) = 0x69;\
    *(info_string_ptr+5) = 0x62;\
    *(info_string_ptr+6) = 0x5F;\
    *(info_string_ptr+7) = 0x6D;\
    *(info_string_ptr+8) = 0x65;\
    *(info_string_ptr+9) = 0x6D;\
    *(info_string_ptr+10) = 0x73;\
    *(info_string_ptr+11) = 0x65;\
    *(info_string_ptr+12) = 0x74;\
    *(info_string_ptr+13) = 0x20;\
    *(info_string_ptr+14) = 0x6C;\
    *(info_string_ptr+15) = 0x65;\
    *(info_string_ptr+16) = 0x6E;\
    *(info_string_ptr+17) = 0x20;\
    *(info_string_ptr+18) = 0x31;\
    *(info_string_ptr+19) = 0x30;\
    *(info_string_ptr+20) = 0x30;\
    *(info_string_ptr+21) = 0x30;\
    packet.payload = info_string_ptr; \
    time_value = TIMESTAMP(time_value);\
    packet.timestamp = time_value;\
    LOG_CHECKSUM(packet_ptr);\
    LOG_RAW_ITEM(packet_ptr);}  
#define LOG_STDLIB_MEMSET_INFO5000  {\
    packet.log_id = INFO;\
    packet.log_length = 22;\
    *(info_string_ptr) = 0x73;\
    *(info_string_ptr+1) = 0x74;\
    *(info_string_ptr+2) = 0x64;\
    *(info_string_ptr+3) = 0x6C;\
    *(info_string_ptr+4) = 0x69;\
    *(info_string_ptr+5) = 0x62;\
    *(info_string_ptr+6) = 0x5F;\
    *(info_string_ptr+7) = 0x6D;\
    *(info_string_ptr+8) = 0x65;\
    *(info_string_ptr+9) = 0x6D;\
    *(info_string_ptr+10) = 0x73;\
    *(info_string_ptr+11) = 0x65;\
    *(info_string_ptr+12) = 0x74;\
    *(info_string_ptr+13) = 0x20;\
    *(info_string_ptr+14) = 0x6C;\
    *(info_string_ptr+15) = 0x65;\
    *(info_string_ptr+16) = 0x6E;\
    *(info_string_ptr+17) = 0x20;\
    *(info_string_ptr+18) = 0x35;\
    *(info_string_ptr+19) = 0x30;\
    *(info_string_ptr+20) = 0x30;\
    *(info_string_ptr+21) = 0x30;\
    packet.payload = info_string_ptr; \
    time_value = TIMESTAMP(time_value);\
    packet.timestamp = time_value;\
    LOG_CHECKSUM(packet_ptr);\
    LOG_RAW_ITEM(packet_ptr);} 
/*Macro functions for Stdlib_memmove*/
#define LOG_STDLIB_MEMMOVE_INFO10  {\
    packet.log_id = INFO;\
    packet.log_length = 21;\
    *(info_string_ptr) = 0x73;\
    *(info_string_ptr+1) = 0x74;\
    *(info_string_ptr+2) = 0x64;\
    *(info_string_ptr+3) = 0x6C;\
    *(info_string_ptr+4) = 0x69;\
    *(info_string_ptr+5) = 0x62;\
    *(info_string_ptr+6) = 0x5F;\
    *(info_string_ptr+7) = 0x6D;\
    *(info_string_ptr+8) = 0x65;\
    *(info_string_ptr+9) = 0x6D;\
    *(info_string_ptr+10) = 0x6D;\
    *(info_string_ptr+11) = 0x6F;\
    *(info_string_ptr+12) = 0x76;\
    *(info_string_ptr+13) = 0x65;\
    *(info_string_ptr+14) = 0x20;\
    *(info_string_ptr+15) = 0x6C;\
    *(info_string_ptr+16) = 0x65;\
    *(info_string_ptr+17) = 0x6E;\
    *(info_string_ptr+18) = 0x20;\
    *(info_string_ptr+19) = 0x31;\
    *(info_string_ptr+20) = 0x30;\
    packet.payload = info_string_ptr; \
    time_value = TIMESTAMP(time_value);\
    packet.timestamp = time_value;\
    LOG_CHECKSUM(packet_ptr);\
    LOG_RAW_ITEM(packet_ptr);}
#define LOG_STDLIB_MEMMOVE_INFO100  {\
    packet.log_id = INFO;\
    packet.log_length = 22;\
    *(info_string_ptr) = 0x73;\
    *(info_string_ptr+1) = 0x74;\
    *(info_string_ptr+2) = 0x64;\
    *(info_string_ptr+3) = 0x6C;\
    *(info_string_ptr+4) = 0x69;\
    *(info_string_ptr+5) = 0x62;\
    *(info_string_ptr+6) = 0x5F;\
    *(info_string_ptr+7) = 0x6D;\
    *(info_string_ptr+8) = 0x65;\
    *(info_string_ptr+9) = 0x6D;\
    *(info_string_ptr+10) = 0x6D;\
    *(info_string_ptr+11) = 0x6F;\
    *(info_string_ptr+12) = 0x76;\
    *(info_string_ptr+13) = 0x65;\
    *(info_string_ptr+14) = 0x20;\
    *(info_string_ptr+15) = 0x6C;\
    *(info_string_ptr+16) = 0x65;\
    *(info_string_ptr+17) = 0x6E;\
    *(info_string_ptr+18) = 0x20;\
    *(info_string_ptr+19) = 0x31;\
    *(info_string_ptr+20) = 0x30;\
    *(info_string_ptr+21) = 0x30;\
    packet.payload = info_string_ptr; \
    time_value = TIMESTAMP(time_value);\
    packet.timestamp = time_value;\
    LOG_CHECKSUM(packet_ptr);\
    LOG_RAW_ITEM(packet_ptr);}
#define LOG_STDLIB_MEMMOVE_INFO1000  {\
    packet.log_id = INFO;\
    packet.log_length = 23;\
    *(info_string_ptr) = 0x73;\
    *(info_string_ptr+1) = 0x74;\
    *(info_string_ptr+2) = 0x64;\
    *(info_string_ptr+3) = 0x6C;\
    *(info_string_ptr+4) = 0x69;\
    *(info_string_ptr+5) = 0x62;\
    *(info_string_ptr+6) = 0x5F;\
    *(info_string_ptr+7) = 0x6D;\
    *(info_string_ptr+8) = 0x65;\
    *(info_string_ptr+9) = 0x6D;\
    *(info_string_ptr+10) = 0x6D;\
    *(info_string_ptr+11) = 0x6F;\
    *(info_string_ptr+12) = 0x76;\
    *(info_string_ptr+13) = 0x65;\
    *(info_string_ptr+14) = 0x20;\
    *(info_string_ptr+15) = 0x6C;\
    *(info_string_ptr+16) = 0x65;\
    *(info_string_ptr+17) = 0x6E;\
    *(info_string_ptr+18) = 0x20;\
    *(info_string_ptr+19) = 0x31;\
    *(info_string_ptr+20) = 0x30;\
    *(info_string_ptr+21) = 0x30;\
    *(info_string_ptr+22) = 0x30;\
    packet.payload = info_string_ptr; \
    time_value = TIMESTAMP(time_value);\
    packet.timestamp = time_value;\
    LOG_CHECKSUM(packet_ptr);\
    LOG_RAW_ITEM(packet_ptr);}
#define LOG_STDLIB_MEMMOVE_INFO5000  {\
    packet.log_id = INFO;\
    packet.log_length = 23;\
    *(info_string_ptr) = 0x73;\
    *(info_string_ptr+1) = 0x74;\
    *(info_string_ptr+2) = 0x64;\
    *(info_string_ptr+3) = 0x6C;\
    *(info_string_ptr+4) = 0x69;\
    *(info_string_ptr+5) = 0x62;\
    *(info_string_ptr+6) = 0x5F;\
    *(info_string_ptr+7) = 0x6D;\
    *(info_string_ptr+8) = 0x65;\
    *(info_string_ptr+9) = 0x6D;\
    *(info_string_ptr+10) = 0x6D;\
    *(info_string_ptr+11) = 0x6F;\
    *(info_string_ptr+12) = 0x76;\
    *(info_string_ptr+13) = 0x65;\
    *(info_string_ptr+14) = 0x20;\
    *(info_string_ptr+15) = 0x6C;\
    *(info_string_ptr+16) = 0x65;\
    *(info_string_ptr+17) = 0x6E;\
    *(info_string_ptr+18) = 0x20;\
    *(info_string_ptr+19) = 0x35;\
    *(info_string_ptr+20) = 0x30;\
    *(info_string_ptr+21) = 0x30;\
    *(info_string_ptr+22) = 0x30;\
    packet.payload = info_string_ptr; \
    time_value = TIMESTAMP(time_value);\
    packet.timestamp = time_value;\
    LOG_CHECKSUM(packet_ptr);\
    LOG_RAW_ITEM(packet_ptr);}
#else
#define SEND_HEARTBEAT   {}
#define LOG_SYSTEM_INIT  {}
#define LOG_PROFILE_START {}
#define LOG_PROFILE_COMPLETED {}
#define LOG_PROFILE_RESULT {}
#define LOG_MY_MEMSET_INFO10  {}
#define LOG_MY_MEMSET_INFO100  {}
#define LOG_MY_MEMSET_INFO1000  {}
#define LOG_MY_MEMSET_INFO5000  {}
#define LOG_MY_MEMMOVE_INFO10  {}
#define LOG_MY_MEMMOVE_INFO100  {}
#define LOG_MY_MEMMOVE_INFO1000  {}
#define LOG_MY_MEMMOVE_INFO5000  {}
#define LOG_STDLIB_MEMSET_INFO10 {}
#define LOG_STDLIB_MEMSET_INFO100 {}
#define LOG_STDLIB_MEMSET_INFO1000 {}
#define LOG_STDLIB_MEMSET_INFO5000 {}
#define LOG_STDLIB_MEMMOVE_INFO10 {}
#define LOG_STDLIB_MEMMOVE_INFO100 {}
#define LOG_STDLIB_MEMMOVE_INFO1000 {}
#define LOG_STDLIB_MEMMOVE_INFO5000 {}
#endif

/*********************************************************************************************/
/*****************************Project4********************************************************/
/**********************************************************************************************
@brief - This function is the main code that runs the program for project4

This file integrates that logger functionality into the project2 files

@param - void
@return -  void
**********************************************************************************************/

void project4(void);

#endif /*__PROJECT4_H__*/

/**********************************************************************************************/
/************************************End of File***********************************************/
/**********************************************************************************************/
