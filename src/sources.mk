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
./project1.c ./arch_arm32.c ./main.c ./gpio.c ./circbuf.c ./uart.c \
./system_MKL25Z4.c ./startup_MKL25Z4.S ./project2.c ./dma.c \
./project3.c ./mem_profiler_kl25z.c ./spi.c ./nordic.c ./uart_circbuf.c

else ifeq ($(PLATFORM),KL25Z_PRO)
SRCS = ./memory.c ./main.c ./dma.c \
./mem_profiler_kl25z.c ./project3.c \
./system_MKL25Z4.c ./startup_MKL25Z4.S ./gpio.c ./spi.c ./nordic.c \
./uart_circbuf.c

else ifeq ($(PLATFORM),BBB)
SRCS = ./data1.c ./debug.c ./memory.c ./conversion.c \
./project1.c ./main.c ./circbuf.c ./project3.c

else ifeq ($(PLATFORM),BBB_PRO)
SRCS = ./data1.c ./debug.c ./memory.c ./conversion.c \
./main.c ./circbuf.c ./project3.c ./mem_profiler_bbb.c 

else ifeq ($(PLATFORM),HOST)
SRCS = ./data1.c ./debug.c ./memory.c ./conversion.c \
./project1.c ./main.c ./circbuf.c ./project3.c ./mem_profiler_bbb.c
#if no platform is speced, make defaults to native compiler

else ifeq ($(PLATFORM),CMOCKA)
SRCS = ./data1.c ./debug.c ./memory.c ./conversion.c \
./project1.c ./circbuf.c ./unit_tests.c
#if no platform is speced, make defaults to native compiler

else
SRCS = ./main.c \
./data1.c ./debug.c ./memory.c ./conversion.c \
./project1.c ./circbuf.c ./project2.c ./project3.c ./nordic.c
endif

