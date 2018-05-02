/*********************************************************************************************
@file - rtc.c

@brief - rtc is the source file for the rtc function in the FRDM board

This file is the source file for the rtc functionality
This can only be used for the FRDM board

The functions that are contained in the file
1. rtc_init

@author - Scott McElroy

@date - April 27, 2018

Created for ECEN5813
**********************************************************************************************/

#include "rtc.h"

/*********************************************************************************************/
/*****************************rtc_init********************************************************/
/**********************************************************************************************
@brief - This function sets up the rtc functionality for the KL25Z

This function sets up the PTC3 to output the internal RTC clock to use it for the RTC
blocks in the clock distribution portion of the device

@param - void
@return -  void
**********************************************************************************************/

void rtc_init(void)
{
    /*Adjust the clocks for the MCGIRCLK*/
    RTC_MCG_C1 |= (__IRCLKEN + __IREFSTEN);
    RTC_MCG_C2 &= ~(__IRCS);
    /*Enable and PortC*/
    RTC_SIM_SCGC5 |= (RTC_PORTC);
    RTC_PORTC_3 |= PTC3_ALT5; /*Set PTC3 to Clockout*/
    RTC_PORTC_1 |= PTC1_ALT1; /*Set PTC1 to Clockout*/
    /*Output the MCGIRCLK to PTC3*/
    RTC_SIM_SOPT2 |= MCGIRCLKOUT;
    /*Enable RTC*/
    RTC_SIM_SCGC6 |= RTC_ENABLE;
    /*Change the input of RTC to be the RTC pin*/
    RTC_SIM_SOPT1 |= __RTC_CLKIN;
    /*The RTC register now need to be setup*/
    __RTC_TSR = 0x0; /*Write to register to clear*/
    __RTC_TPR = 0x0; /*Write to register to clear*/
    /*Enable clocks and output to peripherials*/
    __RTC_CR |= RTC_CLKO; /*output clock to peripherials*/
    __RTC_SR |= RTC_TCE; /*enable counter*/

    __RTC_IER &= 0x00; /*Turn off interrupts*/

    /*Need to setup for interrupts*/

   return;

}

/*********************************************************************************************/
/*****************************rtc_read********************************************************/
/**********************************************************************************************
@brief - This function is called when a time value needs to be read

This function assumes that the RTC has been initialized already

@param - void
@return -  time_value: 32-bit value of the time register
**********************************************************************************************/

uint32_t rtc_read(void)
{
    uint32_t time_value;

    time_value = (0xFF && __RTC_TPR); /*This value is anded with 0xFF b/c of 16-bit*/
    time_value += (__RTC_TPR << 16); /*Shifts the time value so it can be added to the time value*/

    return time_value;
}

/*********************************************************************************************/
/*****************************End of File********************************************************/
/*********************************************************************************************/
