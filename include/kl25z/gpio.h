/*********************************************************************************************
@file - gpio.h

@brief - gpio.h file the header file for the manipulation of port registers

This is the header file for port manipulation functions
The included function declarations are
1. GPIO_Configure
2. Toggle_Red_LED
3. PORTB_set
4. PORTD_Set
5. PORTB_Clear
6. PORTD_Clear
7. PORTB_Toggle
8. PORTD_Toggle
9. GPIO_nrf_init (Updated April 5th, 2018)

@author - Scott McElroy

@date - February 25, 2018 (Updated April 5th, 2018)

Created for ECEN5813
**********************************************************************************************/
#ifndef __GPIO_H__
#define __GPIO_H__

#include <stdint.h>
#include <stdlib.h>

/*BITS corresponding to the pins of the register*/
#define __SIM_SCGC5_ADDR     (*((volatile uint32_t *)(0x40048038)))

#define __SIM_SCGC5_PORTB    ((uint32_t)1 << 10)
#define __SIM_SCGC5_PORTD    ((uint32_t)1 << 12)
#define PORTD_CG    (1 << 12)

/*BITS corresponding to the pins of the register*/
#define PIN18              ((uint8_t)18)
#define PIN19              ((uint8_t)19)
#define PIN1               ((uint8_t)1)

/*direct dereferencing to PORTB PTB18 crtl*/
#define __PORTB_PCR18        (*((volatile uint32_t *)(0x4004A048))) 
/*direct dereferencing to PORTB PTB18 crtl*/
#define __PORTB_PCR19        (*((volatile uint32_t *)(0x4004A04C))) 
/*direct dereferencing to PORTD PTD1 crtl*/
#define __PORTD_PCR1         (*((volatile uint32_t *)(0x4004C004)))
/*Register define associated for the SPI port with PORTD*/
#define __PORTD_PCR0  (*((volatile uint32_t *)(0x4004C000)))
#define __PORTD_PCR1  (*((volatile uint32_t *)(0x4004C004)))
#define __PORTD_PCR2  (*((volatile uint32_t *)(0x4004C008)))
#define __PORTD_PCR3  (*((volatile uint32_t *)(0x4004C00C)))
/*Chip enable and chip select defines*/
#define __PORTD_PCR5  (*((volatile uint32_t *)(0x4004C014)))
#define __PORTD_PCR6  (*((volatile uint32_t *)(0x4004C018)))

/*Value specified for the PCR functions*/
#define __ALT1               (0b001 << 8)
#ifndef __ALT2 
#define __ALT2               (0b010 << 8) 
#endif
/*Value used for the SPI0 CS pin*/
#define PSC0_PTD0     (0x1)
#define CHIP_EN_PTD5  (1 << 5)
#define CHIP_SEL_PTD6 (1 << 6)

/*direct dereferencing to GPIOB direction crtl register*/
#define __GPIOB_PDDR         (*((volatile uint32_t *)(0x400FF054))) 
/*direct dereferencing to GPIOD direction crtl register*/
#define __GPIOD_PDDR         (*((volatile uint32_t *)(0x400FF0D4))) 

/*direct dereferencing to GPIOB SET crtl register*/
#define __GPIOB_PSOR         (*((volatile uint32_t *)(0x400FF044)))
/*direct dereferencing to GPIOD SET crtl register*/
#define __GPIOD_PSOR         (*((volatile uint32_t *)(0x400FF0C4)))

/*direct dereferencing to GPIOB CLEAR crtl register*/
#define __GPIOB_PCOR         (*((volatile uint32_t *)(0x400FF048)))
/*direct dereferencing to GPIOD CLEAR crtl register*/
#define __GPIOD_PCOR         (*((volatile uint32_t *)(0x400FF0C8)))
 
/*direct dereferencing to GPIOB TOGGLE crtl register*/
#define __GPIOB_PTOR         (*((volatile uint32_t *)(0x400FF04C)))
/*direct dereferencing to GPIOD TOGGLE crtl register*/
#define __GPIOD_PTOR         (*((volatile uint32_t *)(0x400FF0CC)))

#define __RGB_RED_PIN        (PIN18)
#define __RGB_GREEN_PIN      (PIN19)
#define __RGB_BLUE_PIN       (PIN1)

#define RGB_RED_ON()       (PORTB_Set( RGB_RED_PIN ))
#define RGB_RED_OFF()      (PORTB_Clear( RGB_RED_PIN ))
#define RGB_RED_TOGGLE()   (PORTB_Toggle( RGB_RED_PIN ))

#define RGB_GREEN_ON()     (PORTB_Set( RGB_GREEN_PIN ))
#define RGB_GREEN_OFF()    (PORTB_Clear( RGB_GREEN_PIN ))
#define RGB_GREEN_TOGGLE() (PORTB_Toggle( RGB_GREEN_PIN ))

#define RGB_BLUE_ON()      (PORTD_Set( RGB_BLUE_PIN ))
#define RGB_BLUE_OFF()     (PORTD_Clear( RGB_BLUE_PIN ))
#define RGB_BLUE_TOGGLE()  (PORTD_Toggle( RGB_BLUE_PIN ))

/*********************************************************************************************/
/******************************GPIO_Configure*************************************************/
/**********************************************************************************************
@brief- This function configures the RGB LEDs to output their intial values

RGB LED constants are configured in the header files.
Red LED is PORTB-Pin18 initial state off
Green LED is PORTB-Pin19 initial state off
Blue LED is PORTD-Pin1 initial state off

@param - void
@return - void
**********************************************************************************************/

void GPIO_Configure(void);

/*********************************************************************************************/
/******************************Toggle_RED_LED*************************************************/
/**********************************************************************************************
@brief- This function toggles the Red LEDs

@param - void
@return - void
**********************************************************************************************/

void Toggle_Red_LED(void);

/*********************************************************************************************/
/******************************PORTB_Set******************************************************/
/**********************************************************************************************
@brief- This function sets the portB register output bit field

@param - bit_num: The bit to be changed in the port register
@return - void
**********************************************************************************************/

void PORTB_Set(uint8_t bit_num);

/*********************************************************************************************/
/******************************PORTD_Set******************************************************/
/**********************************************************************************************
@brief- This function set the portD register output bit field

@param - bit_num: The bit to be changed in the port register
@return - void
**********************************************************************************************/

void PORTD_Set(uint8_t bit_num);

/*********************************************************************************************/
/******************************PORTB_Clear****************************************************/
/**********************************************************************************************
@brief- This function clears the portB register output bit field

@param - bit_num: The bit to be changed in the port register
@return - void
**********************************************************************************************/

void PORTB_Clear(uint8_t bit_num);

/*********************************************************************************************/
/******************************PORTD_Clear****************************************************/
/**********************************************************************************************
@brief- This function clears the portD register output bit field

@param - bit_num: The bit to be changed in the port register
@return - void
**********************************************************************************************/

void PORTD_Clear(uint8_t bit_num);

/*********************************************************************************************/
/******************************PORTB_Toggle**************************************************/
/**********************************************************************************************
@brief- This function toggles the portB register output bit field

@param - bit_num: The bit to be changed in the port register
@return - void
**********************************************************************************************/

void PORTB_Toggle(uint8_t bit_num);

/*********************************************************************************************/
/******************************PORTD_Toggle***************************************************/
/**********************************************************************************************
@brief- This function toggles the portD register output bit field

@param - bit_num: The bit to be changed in the port register
@return - void
**********************************************************************************************/

void PORTD_Toggle(uint8_t bit_num);

/*********************************************************************************************/
/******************************GPIO_nrf_init***************************************************/
/**********************************************************************************************
@brief- This function initializes the SPI port for the NRF device

@param - void
@return - void
**********************************************************************************************/

void GPIO_nrf_init(void);

#endif /*__GPIO_H__*/

/*********************************************************************************************/
/******************************END of file****************************************************/

