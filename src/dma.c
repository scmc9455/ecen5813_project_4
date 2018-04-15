/*********************************************************************************************
@file - dma.c

@brief - dma.c file is a source file for memory manipulation functions using dma in KL25Z

This is the source file for memory functions "dma.c"
The included functions are
1. memmove_dma
2. memset_dma
3. dma_init
4. DMA_IRQHandler

@author - Scott McElroy

@date - March 30th, 2018

Created for ECEN5813
**********************************************************************************************/

#include "dma.h"

#ifdef KL25Z_PRO
extern uint8_t wait_state;
#endif
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

dma_e memmove_dma(uint8_t *src, uint8_t *dst, uint8_t length, uint8_t type)
{
    if((src == NULL) || (dst == NULL))
    {
        return DMA_PTR_NULL;
    }
    /*Load the value of the source address*/
    __DMA_SAR0 = 0; /*Clear register*/
    __DMA_SAR0 |= (uint32_t)src;
    /*Load the value of the destination address*/
    __DMA_DAR0 = 0; /*Clear register*/
    __DMA_DAR0 |= (uint32_t)dst;
    /*Load the values for the DMA DSR register, makes sure that the max is respected*/
    __DMA_DSR_BCR0 &= ~(MAX_BCR); /*needs a write to clear bcr*/
    __DMA_DSR_BCR0 |= (MAX_BCR & length);
    /*if the length is greater then 1, SINC and DINC are set*/
    if(length > 1)
    {
        __DMA_DCR0 |= (DMA0_SINC + DMA0_DINC); /*Set the Source and Destination increment*/
    }else{
        __DMA_DCR0 &= ~(DMA0_SINC + DMA0_DINC); /*Clear the source and Destination inc*/
    }
    /*Set the type of byte conversion*/
    /*Clear the size bits (also makes it 32-bit conversions)*/
    __DMA_DCR0 &= ~(DMA0_SSIZE(BIT32_SIZE) + DMA0_DSIZE(BIT32_SIZE));    
    /*Sets the byte size to 8-bit*/
    if(type == 8)
    {
        __DMA_DCR0 |= (DMA0_SSIZE(BIT8_SIZE) + DMA0_DSIZE(BIT8_SIZE));
    }else if(type == 16){
        /*Sets the byte size to 16-bit*/
        __DMA_DCR0 |= (DMA0_SSIZE(BIT16_SIZE) + DMA0_DSIZE(BIT16_SIZE));
    }else if(type == 32){
        /*Sets the byte size to 32-bit*/
    	__DMA_DCR0 &= ~(DMA0_SSIZE(BIT32_SIZE) + DMA0_DSIZE(BIT32_SIZE));
    }else{
        return DMA_FAILURE;
    }

    /*Enable DMAMUX*/
    __DMAMUX0_CHCFG0 |= DMAMUX0_EN;

    /*Enable the IRQs in NVIC*/
    START_CRITICAL(__DMA0_IRQ_NUM);

    /*If running the profiler, then systick start*/
    #ifdef KL25Z_PRO
    systick_start();
    #endif

    /*Start conversion and move with DMA*/
    __DMA_DCR0 |= DMA0_START;

    return DMA_SUCCESS;
}

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

dma_e memset_dma(uint8_t *dst, uint16_t length, uint8_t type, uint8_t value)
{
    if(dst == NULL)
    {
        return DMA_PTR_NULL;
    }    
    uint32_t temp = value;
    uint32_t *temp_ptr = &temp;

    /*Load the value of the source address*/
    __DMA_SAR0 = 0; /*Clear register*/
    __DMA_SAR0 |= (uint32_t)temp_ptr;
    /*Load the value of the destination address*/
    __DMA_DAR0 = 0; /*Clear register*/
    __DMA_DAR0 |= (uint32_t)dst;
    /*Load the values for the DMA DSR register, makes sure that the max is respected*/
    __DMA_DSR_BCR0 &= ~(MAX_BCR); /*needs a write to clear bcr*/
    __DMA_DSR_BCR0 |= (MAX_BCR & length);
    /*if the length is greater then 1, SINC and DINC are set*/
    if(length > 1)
    {
        __DMA_DCR0 |= DMA0_DINC; /*Set the Destination increment*/
    }else{
        __DMA_DCR0 &= ~(DMA0_DINC); /*Clear the source and Destination inc*/
    }
    /*Set the type of byte conversion*/
    /*Clear the size bits (also makes it 32-bit conversions)*/
    __DMA_DCR0 &= ~(DMA0_SSIZE(BIT32_SIZE) + DMA0_DSIZE(BIT32_SIZE));    
    /*Sets the byte size to 8-bit*/
    if(type == 8)
    {
        __DMA_DCR0 |= (DMA0_SSIZE(BIT8_SIZE) + DMA0_DSIZE(BIT8_SIZE));
    }else if(type == 16){
        /*Sets the byte size to 16-bit*/
        __DMA_DCR0 |= (DMA0_SSIZE(BIT16_SIZE) + DMA0_DSIZE(BIT16_SIZE));
    }else if(type == 32){
        /*Sets the byte size to 32-bit*/
    	__DMA_DCR0 &= ~(DMA0_SSIZE(BIT32_SIZE) + DMA0_DSIZE(BIT32_SIZE));
    }else{
    	return DMA_FAILURE;
    }

    /*Enable DMAMUX*/
    __DMAMUX0_CHCFG0 |= DMAMUX0_EN;

    /*Enable the IRQs in NVIC*/
    START_CRITICAL(__DMA0_IRQ_NUM);
    /*If running the profiler, then systick start*/
    #ifdef KL25Z_PRO
    systick_start();
    #endif

    /*Start conversion and move with DMA*/
    __DMA_DCR0 |= DMA0_START;

    return DMA_SUCCESS;
}

/*********************************************************************************************/
/*****************************dma_init********************************************************/
/**********************************************************************************************
@brief - This function will initialize the DMA for usage

@param - void
@return -  void
**********************************************************************************************/

void dma_init(void)
{
    /*Clock gate for DMAMUX*/
    __SIM_SCGC6 |= DMAMUX_CG;
    /*Clock gate for DMA*/
    __SIM_SCGC7 |= DMA_CG; 
    /*Make sure the trig and enable for the mux is off*/
    __DMAMUX0_CHCFG0 &= ~(DMAMUX0_EN + DMAMUX0_TRIG);
    /*Load the source mux for the DMA as an always-on pass through*/
    __DMAMUX0_CHCFG0 |= DMA0_SRC63;
    /*Enable the IRQs in DMA*/
   __DMA_DCR0 |= DMA0_EINT;
}

/*********************************************************************************************/
/*****************************DMA_IRQHandler**************************************************/
/**********************************************************************************************
@brief - This function is the handler for the ISR of DMA

@param - void
@return -  void
**********************************************************************************************/

void DMA0_IRQHandler(void)
{
	/*Used for the profiler in the KL25Z testing*/
    #ifdef KL25Z_PRO
	systick_end();
    wait_state = 1;
    #endif
    /*Turn the DMA interrupt off*/

    END_CRITICAL(__DMA0_IRQ_NUM);

    return;
}

/*********************************************************************************************/
/*****************************End of File*****************************************************/
/*********************************************************************************************/

