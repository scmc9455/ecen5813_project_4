/*********************************************************************************************
@file - platform.h

@brief - platform.h file a header file for the debug function (compile time switch function)

This is the header file for the compile time switching to enable or disable the printf 
statement on platfors that do not support the function (such as the KL25z)

@author - Scott McElroy

@date - February 10, 2018

Created for ECEN5813
**********************************************************************************************/

#ifndef __PLATFORM_H__
#define __PLATFORM_H__

/*********************************************************************************************/
/******************************compile time switch of printf**********************************/
/*********************************************************************************************/

/*compile time switch for HOST/Beagle Bone Black (enables the function)*/
#ifdef VERBOSE 
#define PRINTF printf
#endif
/*compile time switch for KL25z (disables the function)*/
#ifndef VERBOSE 
#define PRINTF(...)
#endif /*End the compile time switch*/

/******************************************************************************************/

#endif /* __PLATFORM_H__ */
