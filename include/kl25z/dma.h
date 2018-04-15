/*********************************************************************************************
@file - dma.h

@brief - dma.h file is the header file for memory manipulation functions usig DMA

This is the header file for memory functions in "dma.c"
The included function declarations are
1. memmove_dma
2. memset_dma
3. dma_init
4. DMA_IRQHandler

@author - Scott McElroy

@date - March 30th

Created for ECEN5813
**********************************************************************************************/

#ifndef __DMA_H__
#define __DMA_H__

#include <stdlib.h>
#include <stdint.h>

#ifdef KL25Z_PRO
#include "mem_profiler_kl25z.h"
#endif

/*registers direct address MACROs*/
#define __SIM_SCGC6       (*((volatile uint32_t *)(0x4004803C)))
#define __SIM_SCGC7       (*((volatile uint32_t *)(0x40048040)))
#define __DMAMUX0_CHCFG0  (*((volatile uint8_t *)(0x40021000)))
#define __DMA_SAR0        (*((volatile uint32_t *)(0x40008100)))
#define __DMA_DAR0        (*((volatile uint32_t *)(0x40008104)))
#define __DMA_DSR_BCR0    (*((volatile uint32_t *)(0x40008108)))
#define __DMA_DCR0        (*((volatile uint32_t *)(0x4000810C)))
/*MACROs for BIT manipulation*/
#define DMAMUX_CG         (1 << 1)
#define DMA_CG            (1 << 8)
#define DMAMUX0_EN        (1 << 7)
#define DMAMUX0_TRIG      (1 << 6)
#define MAX_BCR           (0xFFFFF)
#define DMA0_SRC63        (0x3F)
#define DMA0_SINC         (1 << 22)
#define DMA0_DINC         (1 << 19)
#define BIT32_SIZE        (0x11) /*must be AND ~ to use*/
#define BIT8_SIZE         (0x01)
#define BIT16_SIZE        (0x10)
#define DMA0_SSIZE(x)     ((x) << 20)
#define DMA0_DSIZE(x)     ((x) << 17)
#define DMA0_START        (1 << 16)
#define DMA0_EINT         (1 << 31)
/*MACROS for IRQ*/
#define __DMA0_IRQ_NUM    (1 << 0)

#define __NVIC_SET_EN_REG     (*((volatile uint32_t *)(0xE000E100)))
#define __NVIC_CLR_EN_REG     (*((volatile uint32_t *)(0xE000E180)))
#define __NVIC_CLR_PEND_REG   (*((volatile uint32_t *)(0xE000E280)))

#define disable_NVIC_IRQ(x) (__NVIC_CLR_EN_REG |= (x))
#define enable_NVIC_IRQ(x)  (__NVIC_SET_EN_REG |= (x))
#define START_CRITICAL(x)     (enable_NVIC_IRQ(x))
#define END_CRITICAL(x)       (disable_NVIC_IRQ(x))

typedef enum{
    DMA_FAILURE = 0,
    DMA_SUCCESS = 1,
    DMA_PTR_NULL = 2
}dma_e;

/*********************************************************************************************/
/****************************memmove_dma******************************************************/
/**********************************************************************************************
@brief - moves memory from one location to another using the DMA

The memmove_dma function is passed a source and destination address,
the contents at the source address get temporarily copied completely 
depending on the length specified when called and then moved to the
destination address. This is done completely with the DMA module.
This function is a non-corruption based moved even if the source and 
destination is overlapping.

@param - *src: source address 
@param - *dst: destination address
@param - length: amount of bytes to be transfered (only excepts 8, 16 or 32)
@param - type: size of data
@return - dma_e: status of function
**********************************************************************************************/

dma_e memmove_dma(uint8_t *src, uint8_t *dst, uint8_t length, uint8_t type);

/*********************************************************************************************/
/*****************************memset_dma******************************************************/
/**********************************************************************************************
@brief - This function set a block of memory to a certain value using the DMA

The memset function is passed a source address and a value,
the value that is passed on a function call is put into the destinaion address using the DMA

@param - *dst: destination address 
@param - length: size of bytes for the blocks
@param - type: type of data
@param - value: value of data
@return -  dma_e: status of function
**********************************************************************************************/

dma_e memset_dma(uint8_t *dst, uint16_t length, uint8_t type, uint8_t value);

/*********************************************************************************************/
/*****************************dma_init********************************************************/
/**********************************************************************************************
@brief - This function will initialize the DMA for usage

@param - void
@return -  void
**********************************************************************************************/

void dma_init(void);

/*********************************************************************************************/
/*****************************DMA_IRQHandler**************************************************/
/**********************************************************************************************
@brief - This function is the handler for the ISR of DMA

@param - void
@return -  void
**********************************************************************************************/

void DMA0_IRQHandler(void);

#endif /*__DMA_H__*/

/*********************************************************************************************/
/*****************************End of File*****************************************************/
/*********************************************************************************************/

