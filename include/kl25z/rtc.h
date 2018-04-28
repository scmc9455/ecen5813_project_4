/*********************************************************************************************
@file - rtc.h

@brief - rtc is the header file for the rtc function in the FRDM board

This file is the header file for the rtc functionality
This can only be used for the FRDM board

The functions that are contained in the file
1. rtc_init
2. rtc_read

@author - Scott McElroy

@date - April 27, 2018

Created for ECEN5813
**********************************************************************************************/

#ifndef __RTC_H__
#define __RTC_H__

#include <stdint.h>
/*SIM Regs*/
#define RTC_SIM_SCGC5  (*((volatile uint32_t *)(0x40048038)))
#define RTC_PORTC      (1 << 13)
#define RTC_SIM_SCGC6  (*((volatile uint32_t *)(0x4004803C)))
#define RTC_ENABLE     (1 << 29)
#define RTC_SIM_SOPT2  (*((volatile uint32_t *)(0x40048004)))
#define MCGIRCLKOUT     (0x100 << 5)
#define RTC_SIM_SOPT1  (*((volatile uint32_t *)(0x40047000)))
#define __RTC_CLKIN    (0x10 << 18)


/*MCG Regs*/
#define RTC_MCG_C1     (*((volatile uint8_t *)(0x40064000)))
#define __IRCLKEN      (1 << 1)
#define __IREFSTEN     (1 << 0)
#define RTC_MCG_C2     (*((volatile uint8_t *)(0x40064001)))
#define __IRCS         (1 << 0)
/*Port Settings*/
#define RTC_PORTC_1    (*((volatile uint32_t *)(0x4004B004)))
#define RTC_PORTC_3    (*((volatile uint32_t *)(0x4004B00C)))
#define PTC1_ALT1      (0x001 << 8)
#define PTC3_ALT5      (0x101 << 8)
/*RTC registers*/
#define __RTC_TSR      (*((volatile uint32_t *)(0x4003D000)))
#define __RTC_TPR      (*((volatile uint32_t *)(0x4003D004)))
#define __RTC_TAR      (*((volatile uint32_t *)(0x4003D008)))
#define __RTC_TCR      (*((volatile uint32_t *)(0x4003D00C)))
#define __RTC_CR       (*((volatile uint32_t *)(0x4003D010)))
#define RTC_CLKO        (1 << 9)
#define __RTC_SR       (*((volatile uint32_t *)(0x4003D014)))
#define RTC_TCE        (1 << 4)
#define __RTC_LR       (*((volatile uint32_t *)(0x4003D018)))
#define __RTC_IER      (*((volatile uint32_t *)(0x4003D01C)))

/*********************************************************************************************/
/*****************************rtc_init********************************************************/
/**********************************************************************************************
@brief - This function sets up the rtc functionality for the KL25Z

This function sets up the PTC3 to output the internal RTC clock to use it for the RTC
blocks in the clock distribution portion of the device

@param - void
@return -  void
**********************************************************************************************/

void rtc_init(void);

/*********************************************************************************************/
/*****************************rtc_read********************************************************/
/**********************************************************************************************
@brief - This function is called when a time value needs to be read

This function assumes that the RTC has been initialized already

@param - void
@return -  time_value: 32-bit value of the time register
**********************************************************************************************/

uint32_t rtc_read(void);

#endif /*__RTC_H__*/

/*********************************************************************************************/
/*****************************Project4********************************************************/
/*********************************************************************************************/
