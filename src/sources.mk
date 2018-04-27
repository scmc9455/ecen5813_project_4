#**************************************************************************#
#@file - source.mk
#
#@breif - This is the sources Makefile that will be includede in the make
#
#@author - Scott McElroy
#
#@data - April 3rd, 2018
#
#**************************************************************************#

#Compile time switch for the makefile
ifeq ($(PLATFORM),KL25Z)
SRCS = ./data1.c ./debug.c ./memory.c ./conversion.c \
./arch_arm32.c ./main.c ./gpio.c ./circbuf.c ./uart.c \
./system_MKL25Z4.c ./startup_MKL25Z4.S ./dma.c \
./mem_profiler_kl25z.c ./spi.c ./nordic.c ./uart_circbuf.c \
./logger.c ./timestamp.c

else ifeq ($(PLATFORM),KL25Z_PRO)
SRCS = ./memory.c ./main.c ./dma.c \
./mem_profiler_kl25z.c \
./system_MKL25Z4.c ./startup_MKL25Z4.S ./gpio.c ./spi.c ./nordic.c \
./uart_circbuf.c ./logger.c ./timestamp.c

else ifeq ($(PLATFORM),BBB)
SRCS = ./data1.c ./debug.c ./memory.c ./conversion.c \
./main.c ./circbuf.c ./logger.c ./timestamp.c

else ifeq ($(PLATFORM),BBB_PRO)
SRCS = ./data1.c ./debug.c ./memory.c ./conversion.c \
./main.c ./circbuf.c ./mem_profiler_bbb.c ./logger.c ./timestamp.c

else ifeq ($(PLATFORM),HOST)
SRCS = ./data1.c ./debug.c ./memory.c ./conversion.c \
./main.c ./circbuf.c ./mem_profiler_bbb.c ./logger.c ./timestamp.c
#if no platform is speced, make defaults to native compiler

else ifeq ($(PLATFORM),CMOCKA)
SRCS = ./data1.c ./debug.c ./memory.c ./conversion.c \
./circbuf.c ./unit_tests.c
#if no platform is speced, make defaults to native compiler

else
SRCS = ./main.c \
./data1.c ./debug.c ./memory.c ./conversion.c \
./circbuf.c ./nordic.c
endif

