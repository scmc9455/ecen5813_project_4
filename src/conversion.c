/*********************************************************************************************
@file - conversion.c

@brief - conversion.c file a source file for conversions

This is the source file for conversion functions
The included function declarations are
1. itoa (integer to ASCII)
2. atoi (ASCII to integer)

@author - Scott McElroy

@date - February 5, 2018

Created for ECEN5813
**********************************************************************************************/

#include "conversion.h"

#include <stdint.h>
#include <stdlib.h>

/*********************************************************************************************/
/******************************itoa************************************************************/
/**********************************************************************************************
@brief- This function changes an integer to an ASCII number

The ITOA function is passed 32 bit data and a pointer plus a base type.
It will convert the base type value to an ASCII number and it returns the length.
The function can handle signed values.

@param - data: value to be converted
@param - *ptr: storage destination
@param - base: numerical base to be converted to
@return - length: size of converted ASCII
**********************************************************************************************/

uint8_t my_itoa(int32_t data, uint8_t * ptr, uint32_t base)
{
    /* Check to see if pointer were passed properly */
    /* if pointer were not properly passed then the function returns a NULL */
    if(! ptr)
    {
        return 00;  
    }
    /* create a dummy pointer store data and see what comes back from it. 
       Will determine endianness */
    uint16_t temp = 0x8001; /*Temporary 16-bit value to be stored to reference */
    uint16_t *temp_ptr = &temp; /*create a pointer to arbitrary 16-bits of data */
    uint8_t temp_len, length = 0;
    uint8_t divide_temp;
    uint32_t modulus_var, remainder;
    int32_t data_neg=0;

    /* Start of Conversion function, architecture independent*/
    *ptr = 0x0; /* NULL character at the end of the low byte*/
    length++;
    /********Base conversion sequence and pointer storage*******/
    if(data < 0)
    {
        data_neg = data;
        data = -data;
    } 

    modulus_var = (uint32_t) data; /*type cast data to unsigned type*/ 
    if(modulus_var == 0)
    {
        *(ptr+length) = ((uint32_t)0x30);
        length++;
        return length;
    }
    /****************NEW CODE FOR CONVERSION**********************************/
    while(modulus_var > 0)
    {
        remainder = modulus_var % base;
        modulus_var = modulus_var / base;
        if((modulus_var <= 0) && (remainder <= 0))
	{
            break;
        }
        /*load ASCII value from the remainder*/
        *(ptr+length) = (remainder + ((uint32_t)0x30));
        length++;
    }
    /****************NEW CODE FOR CONVERSION**********************************/
/******************************************************************************************/
    /* Adds a negative sign to the ASCII characters */
    if( (data_neg & NEG_CHECK_INT32) )
    {
        /*First bit is a 1 = negative number */
        *(ptr+length) = 0x2D; /* adds a negative sign to the final MSB */
        length++;
    }

    /*CHECKING ENDIANNESS - little endian assumed and nothing needs to be done */
    if( *((uint8_t *)temp_ptr) == 0x80)
    {
        /*ARCH is big-endian and data needs to be flipped in memory */
	
        /* Swap order in memory function */
        temp_len = 0;
        while(temp_len <= (length >> 1))
        {
            divide_temp = *((ptr+length)-temp_len);
            *((ptr+length)-temp_len) = *(ptr+temp_len);
            *(ptr+temp_len) = divide_temp;
            temp_len++;
        }	
    } 

    return length;
}

/*********************************************************************************************/
/******************************atoi************************************************************/
/**********************************************************************************************
@brief- This function changes an ASCII number to an integer number

The ATOI function is passed a pointer plus a base type and the number of digits in the ASCII
It will convert the base type value to an ASCII number and it returns the length.
value. The function returns a 32-bit value of the converted data.

@param - *ptr: location of stored data
@param - digits: number of ASCII characters
@param - base: numerical base type of ASCII
@return - Returns the converted value
**********************************************************************************************/

int32_t my_atoi(uint8_t *ptr, uint8_t digits, uint32_t base)
{
    /* Check to see if pointer were passed properly */
    /* if pointer were not properly passed then the function returns a NULL */
    if( !ptr )
    {
        return 00;  
    }

    uint16_t temp = 0x8001; /*Temporary 16-bit value to be stored to reference */
    uint16_t *temp_ptr = &temp; /*create a pointer to arbitrary 16-bits of data */
    uint8_t data_temp, temp_len, position;
    int32_t sign_temp, data=0;
    uint32_t base_temp, results;

    digits = digits-1; /*Removes one value so it can be used with the pointer*/
    /*******CHECKING ENDIANNESS - little endian assumed and nothing needs to be done ***************/
    if( *((uint8_t *)temp_ptr) == 0x80)
    {
        /*ARCH is big-endian and data needs to be flipped in memory */
        /* Swap order in memory function */
        temp_len = 0;
        while(temp_len <= (digits >> 1))
        {
            data_temp = *((ptr+digits)-temp_len);
            *((ptr+digits)-temp_len) = *(ptr+temp_len);
            *(ptr+temp_len) = data_temp;
            temp_len++;
        }	
    }
    /***********************************************************************************/
    /* check for signed data */
    data_temp = *(ptr+digits);
    sign_temp = 1;
    if(data_temp == 0x2D)
    {
        /*First = negative number */
        sign_temp=-1;
        digits--;
    }
    /*******Function section that will convert the incoming number ***/
		
    while((digits) > 0)
    {
        base_temp = 1;
        position = digits - 1;
        data_temp = *(ptr+digits); /* take data from pointer */
        data_temp -= (uint8_t)48; /* down shifts the ASCII table */	
        /* exponent calculator based on position */
        if(position <= 0)
        {
            base_temp = 1;
            position=0;
        }
	
        while(position > 0)
        {
            base_temp *= base;
            position--;            
        }

        results = (base_temp * data_temp); 
        data += results;
        digits--;
    }	
	
    data *= sign_temp; /* add the sign back to the data int32 */
    return data;
}
