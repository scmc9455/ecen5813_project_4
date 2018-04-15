/*********************************************************************************************
@file - unit_tests.c
@brief - unit_teste.c file is the source file for the testing functionality of all of the various functions included in this project2

Tests will incude
memory.c
-memmove tests
-memset tests
-memzero tests
-reverse
conversion.c
-atoi
-itoa
data.c
-Endianess conversion
circbuf.c
-various tests

@author - Scott McElroy

@date - March 4, 2018

Created for ECEN5813
**********************************************************************************************/

#include "unit_tests.h"

/*********************************************************************************************/
/***********************************main for testing******************************************/
/**********************************************************************************************
@brief- This function is the main loop for the tests

@param - void
@return - void
**********************************************************************************************/

int main()
{
    uint8_t total=0;   
    printf("UNIT TESTS START\n\n");
    printf("total = %d \n",total);
    total += memmove_tests();
    printf("total = %d \n",total);
    total += memset_tests();
    printf("total = %d \n",total);
    total += memzero_tests();
    printf("total = %d \n",total);
    total += reverse_tests();
    printf("total = %d \n",total);
    total += atoi_tests();
    
    printf("total = %d \n",total);
    total += itoa_tests();
    printf("total = %d \n",total);
    total += endianness_tests();
    printf("total = %d \n",total);
    total += circbuf_tests();

    printf("The total number of functions that failed is %d \n",total);
    printf("END UNIT_TESTS\n\n\n");

    return 0;
}

/*********************************************************************************************/
/**************************************memmove_tests******************************************/
/**********************************************************************************************
@brief- This function tests the memmove features

Tests:
invalid pointers
No overlap
SRC in DST
DST in SRT
DST == SRC

@param - void
@return - test_type: passing of failing
**********************************************************************************************/

test_type_e memmove_tests()
{
    /*creating the variables for the test function*/
    uint8_t temp;
    uint8_t *ptr=&temp, *src=NULL, *dst=NULL, length= 10;
    uint8_t VAR1[] = {1,2,3,4,5,6,7,8,9,10};
    uint8_t VAR2[] = {0,0,0,0,0,0,0,0,0,0};
    
    /**************NULL POINTER TEST***********************/
    /*Test code to send in NULL pointers*/
    ptr = (uint8_t *)my_memmove(ptr, dst, length);
    if(ptr != NULL)
    {
        printf("memmove NULL pointer test failed\n");
        return TEST_FAILED;
    }
    
    /***************MEMMOVE TEST**************************/
    /*Testing that the memmove actaully works moving memory*/
    src = &VAR1[0];
    dst = &VAR2[0];
 
    my_memmove(src, dst, length);
    if(VAR1[3] != VAR2[3])
    {
        printf("memmove MEMMOVE test failed\n");
        return TEST_FAILED;
    }

    /***************SRC OVERLAP DST*******************************/
    /*Testing that the memmove works with an SRC in DST region */
    /*The previous line of code should have changed this array already*/
    src = &VAR1[3];
    dst = &VAR1[0]; /*SRC place in the middle of the memory DST with overlap*/

    /*moves the first 5 elements in the array to place them at VAR[3]*/
    my_memmove(src, dst, (uint8_t) 5);
    if((VAR1[0] != VAR2[3])||(VAR1[1] != VAR2[4])||(VAR1[2] != VAR2[5])||(VAR1[3] != VAR2[6]))
    {
        printf("memmove SRC-DST overlap test failed\n");
        return TEST_FAILED; /*if the shift didnt happen the process fails*/
    }

    /***************DST OVERLAP SRC*******************************/
    /*Testing that the memmove works with an DST in SRC region */
    uint8_t VAR3[] = {1,2,3,4,5,6,7,8,9,10}; /*copies the array for comparison*/
    uint8_t VAR4[] = {1,2,3,4,5,6,7,8,9,10}; /*copies the array for comparison*/
    src = &VAR3[0];
    dst = &VAR3[3]; /*DST place in the middle of the memory SRC with overlap*/

    /*moves the first 5 elements in the array to place them at VAR[3]*/
    my_memmove(src, dst, (uint8_t) 5);
    if((VAR3[3] != VAR4[0]) || (VAR3[4] != VAR4[1]) || (VAR3[5] != VAR4[2]) || (VAR3[6] != VAR4[3]))
    {
        printf("memmove DST-SRC overlap test failed\n");
        return TEST_FAILED; /*if the shift didnt happen the process fails*/
    }

    /***************DST==SRC*******************************/
    /*Testing that the memmove works with an DST in SRC region */
    uint8_t VAR5[] = {1,2,3,4,5,6,7,8,9,10}; /*copies the array for comparison*/
    uint8_t VAR6[] = {1,2,3,4,5,6,7,8,9,10}; /*copies the array for comparison*/
    src = &VAR5[0];
    dst = &VAR6[0]; /*DST place in the middle of the memory SRC with overlap*/

    /*moves the first 5 elements in the array to place them at VAR[3]*/
    my_memmove(src, dst, (uint8_t) 5);
    if((VAR5[0] != VAR6[0]) || (VAR5[1] != VAR6[1]) || (VAR5[2] != VAR6[2]) || (VAR5[3] != VAR6[3]))
    {
        printf("memmove DST==SRC overlap test failed\n");
        return TEST_FAILED; /*if the shift didnt happen the process fails*/
    }

    printf("memmove test passed\n");
    /*If all of these functions pass then PASS is returned*/
    return TEST_PASS;
}

/*********************************************************************************************/
/**************************************memset_tests******************************************/
/**********************************************************************************************
@brief- This function tests the memmove features

Tests:
invalid pointers
checks the set

@param - void
@return - test_type: passing or failing
**********************************************************************************************/

test_type_e memset_tests()
{
    /*creating the variables for the test function*/
    uint8_t VAR1[] = {0,0,0,0,0,0,0,0,0,0};
    uint8_t *src=NULL, length=5;
    uint8_t value=5, i=0;
    
    /**************NULL POINTER TEST***********************/
    /*Test code to send in NULL pointers*/
    src = (uint8_t *)my_memset(src, value, length);
    if(src != NULL)
    {
        printf("memset NULL pointer test failed\n");
        return TEST_FAILED;
    }

    /**************MEMSET TEST***********************/
    src = &VAR1[0];
    /*Test code to send in values into the function*/
    src = (uint8_t *)my_memset(src, value, length);
    /*for loop to check the results of the set function*/
    for(i=0;i<length;i++)
    {
        if(*(src+i) != value)
        {
            printf("memset SET test failed\n");
            return TEST_FAILED;
        }
    }
    
    printf("memset test passed\n");
    /*All test passed ad PASS is returned*/
    return TEST_PASS;     
}

/*********************************************************************************************/
/**************************************memzero_tests******************************************/
/**********************************************************************************************
@brief- This function tests the memzero features

Tests:
invalid pointers
checks the set

@param - void
@return - test_type: passing of failing
**********************************************************************************************/

test_type_e memzero_tests()
{
    /*creating the variables for the test function*/
    uint8_t VAR1[] = {1,2,3,4,5,6,7,8,9,10};
    uint8_t *src=NULL, length=5;
    uint8_t i=0;
    
    /**************NULL POINTER TEST***********************/
    /*Test code to send in NULL pointers*/
    src = (uint8_t *)my_memzero(src, length);
    if(src != NULL)
    {
        printf("memzero NULL pointer test failed\n");
        return TEST_FAILED;
    }

    /**************MEMZERO TEST***********************/
    src = &VAR1[0];
    /*Next the values need to be zeroed*/
    src = (uint8_t *)my_memzero(src, length);
    /*for loop to check the results of the set function*/
    for(i=0;i<length;i++)
    {
        if(*(src+i) != 0)
        {
            printf("memzero ZERO test failed\n");
            return TEST_FAILED;
        }
    }
    
    printf("memzero test passed\n");
    /*All test passed ad PASS is returned*/
    return TEST_PASS;     
}

/*********************************************************************************************/
/**************************************reverse_tests******************************************/
/**********************************************************************************************
@brief- This function tests the reverse features

Tests:
invalid pointers
checks odd reverses
checks even reverses
checks characters

@param - void
@return - test_type: passing of failing
**********************************************************************************************/

test_type_e reverse_tests()
{
    /*creating the variables for the test function*/
    uint8_t VAR1[] = {0,1,2,3,4};
    uint8_t VAR2[] = {0,1,2,3,4};
    uint8_t VAR3[] = {0,1,2,3,4,5,6};
    uint8_t VAR4[] = {0,1,2,3,4,5,6};
    uint8_t *src=NULL, length=5, length_even=6;
        
    /**************NULL POINTER TEST***********************/
    /*Test code to send in NULL pointers*/
    src = (uint8_t *)my_reverse(src, length);
    if(src != NULL)
    {
        printf("reverse NULL pointer test failed\n");
        return TEST_FAILED;
    }    

    /**************ODD Reverse test***********************/
    src = &VAR1[0];
    /*Test code to get ODD reversed data*/
    src = (uint8_t *)my_reverse(src,length);
    if(((VAR1[0])!=(VAR2[4]))||((VAR1[1])!=(VAR2[3]))||((VAR1[2])!=(VAR2[2])))
    {
        printf("reverse ODD test failed\n");
        return TEST_FAILED;
    }
    
    /**************EVEN Reverse test***********************/
    src = &VAR3[0];
    /*Test code to get EVEN reversed data*/
    src = (uint8_t *)my_reverse(src,length_even);
    if(((VAR3[0])!=(VAR4[5]))||((VAR3[1])!=(VAR4[4]))||((VAR3[2])!=(VAR4[3])))
    {
        printf("reverse EVEN test failed\n");
        return TEST_FAILED;
    }

    /**************Check Character test***********************/
    /*Test code to get CHAR SET reversed data*/
    src = (uint8_t *)my_reverse(src,length);
    if(src == NULL)
    {
        printf("reverse Character test failed\n");
        return TEST_FAILED;
    }    
        
    printf("reverse test passed\n");
    /*All test passed ad PASS is returned*/
    return TEST_PASS;    
}

/*********************************************************************************************/
/*****************************************atoi_tests******************************************/
/**********************************************************************************************
@brief- This function tests the atoi function

Tests:
invalid pointers
zero integers
max sized integers

@param - void
@return - test_type: passing of failing
**********************************************************************************************/

test_type_e atoi_tests()
{
    /*creating the variables for the test function*/
    uint8_t *ptr=NULL, digits=1, base=10, digits_max=11; /*digits plus null*/
    int32_t temp;
    uint8_t ASCII_char = 0x30; /*this is a zero in ASCII*/
    /*max integer is 2,147,483,647, put in the array with a NULL at the end*/
    uint8_t ASCII_max[] = {0x00,0x37,0x34,0x36,0x33,0x38,0x34,0x37,0x34,0x31,0x32};     
    /**************NULL POINTER TEST***********************/
    /*Test code to send in NULL pointers*/
    temp = my_atoi(ptr, digits, base);
    if(temp != 00)
    {
        printf("atoi NULL pointer test failed\n");
        return TEST_FAILED;
    }
 
    /**************ZERO INTEGER TEST***********************/
    ptr = &ASCII_char;
    /*Test code to send in a zero integer*/
    temp = my_atoi(ptr, digits, base);
    if(temp != 0x0)
    {
        printf("atoi VALUE conversion test failed\n");
        return TEST_FAILED;
    }

    /*************MAX INTEGER TEST***********************/
    ptr = &ASCII_max[0];
    /*Test code to send in a max integer*/
    temp = my_atoi(ptr, digits_max, base);
    if(temp != 2147483647)
    {
        printf("atoi MAX VALUE conversion test failed\n");
        return TEST_FAILED;
    }

    printf("atoi test passed\n");
    /*All test passed ad PASS is returned*/
    return TEST_PASS;    
}

/*********************************************************************************************/
/*****************************************itoa_tests******************************************/
/**********************************************************************************************
@brief- This function tests the itoa function

Tests:
invalid pointers
zero integers
max sized integers

@param - void
@return - test_type: passing of failing
**********************************************************************************************/

test_type_e itoa_tests()
{
    /*creating the variables for the test function*/
    uint8_t *ptr=NULL, base=10;
    uint8_t temp[]={1,2,3,4,5,6,7,8,9,10}, length=0;
    /*max integer is 2,147,483,647*/
    int32_t data = 0;
    int32_t data_max = 2147483647; 
    /**************NULL POINTER TEST***********************/
    /*Test code to send in NULL pointers*/
    length = my_itoa(data, ptr, base);
    if(length != 00)
    {
        printf("itoa NULL pointer test failed\n");
        return TEST_FAILED;
    }

    /**************ZERO INTEGER TEST***********************/
    ptr = &temp[0];
    /*Test code to send in a zero integer*/
    length = my_itoa(data, ptr, base);
    if(temp[1] != 0x30)
    {
        printf("itoa VALUE conversion test failed\n");
        return TEST_FAILED;
    }

   /**************MAX INTEGER TEST***********************/
    ptr = &temp[0];
    /*Test code to send in a max integer*/
    length = my_itoa(data_max, ptr, base);
    if((temp[10] != 0x32) && (temp[9] != 0x31))
    {
        printf("itoa MAX VALUE conversion test failed\n");
        return TEST_FAILED;
    }

    printf("itoa test passed\n");
    /*All test passed ad PASS is returned*/
    return TEST_PASS;    
}

/*********************************************************************************************/
/***********************************endianness_tests******************************************/
/**********************************************************************************************
@brief- This function tests the endianness function

Tests:
invalid pointers
valid conversions
conversions back

@param - void
@return - test_type: passing of failing
**********************************************************************************************/

test_type_e endianness_tests()
{
    /*creating the variables for the test function*/
    uint8_t *ptr=NULL, type_length=2;
    int32_t temp;
    /**************NULL POINTER TEST***********************/
    /*Test code to send in NULL pointers*/
    temp = swap_data_endianness(ptr, type_length);
    if(temp != 00)
    {
        printf("endianness NULL pointer test failed\n");
        return TEST_FAILED;
    }
    
    /**************ENDIANNESS SWAP TEST***********************/
    /*point the pointer towards the variable and load with values*/
    ptr=(uint8_t *)&temp;
    *ptr=0x01;
    *(ptr+1)=0x10;
    /*Test code to swap endianness*/
    swap_data_endianness(ptr, type_length);
    if(temp!=0x0110)
    {
        printf("endianness SWAP big-small test failed\n");
        return TEST_FAILED;
    }     

    /**************ENDIANNESS SWAP back TEST***********************/
    /*Test code to swap back to original endianness*/
    swap_data_endianness(ptr, type_length);
    if(temp!=0x1001)
    {
        printf("endianness SWAP small-big test failed\n");
        return TEST_FAILED;
    }     

    printf("endianness test passed\n");
    /*All test passed ad PASS is returned*/
    return TEST_PASS;    
}

/*********************************************************************************************/
/*************************************circbuf_tests*******************************************/
/**********************************************************************************************
@brief- This function tests the circular buffer function

Tests: 
checks to make sure buffer is on the heap
invalid pointers
non-initialized buffers
Add and remove features
buffer full feature
Wrap-add
Wrap remove
Overfill
Over Empty

@param - void
@return - test_type: passing of failing
**********************************************************************************************/

test_type_e circbuf_tests()
{
    /**************ALLOCATE-FREE TEST***********************/
    /*Test code to make sure the buffer is dynamically allocated*/
    CB_t *temp_buf=NULL; /*dummy variable to avoid compiler error*/
    CB_t **buf_test=&(temp_buf); /*Pointer to the NULLed circ_buf*/
    
    uint8_t status, temp, *temp_ptr=&temp, i=0;
    size_t length=10;

    temp=CB_init(buf_test, length);
    if(temp != CB_SUCCESS)
    {
        printf("buf_test ALLOCATE_FREE test failed\n");
        return TEST_FAILED;
    }

    printf("buf_test ALLOCATE_FREE test passed\n\n");
    /**************NULL pointer TEST***********************/
    /*Test code to make sure the buffer is not NULLing the pointer*/
    if(buf_test == NULL)
    {
        printf("buf_test BUF POINTER test failed\n");
        return TEST_FAILED;
    }

    printf("buf_test NULL POINTER test passed\n\n");
    /**************BUF INIT VALID TEST***********************/
    /*Test code to make sure the buffer is not NULLing the pointer*/
    if((*buf_test)->base == NULL)
    {
        printf("buf_test INITIALIZED test failed\n");
        return TEST_FAILED;
    }

    printf("buf_test BUF INIT VALID test passed\n\n");
    /**************BUF ADD-REMOVE TEST***********************/
    if((*buf_test)->head != (*buf_test)->tail)
    {
        printf("buf_test ADD-REMOVE test failed: head!=tail\n");
        return TEST_FAILED; 
    }

    for(i=0;i<length;i++)
    {
        CB_buffer_add_item(*buf_test, i); 
        CB_buffer_remove_item(*buf_test, temp_ptr);
        if((*buf_test)->head != (*buf_test)->tail)
        {
            printf("buf_test ADD-REMOVE test failed\n");
            return TEST_FAILED;
        }     
    }

    printf("buf_test ADD-REMOVE test passed\n\n");
    /**************BUF FULL TEST***********************/
    for(i=0;i<length;i++)
    {
        CB_buffer_add_item(*buf_test, i); 
    }

    status=CB_is_full(*buf_test);
    if(status == CB_BUFFER_NOT_FULL)
    {
        printf("buf_test BUFF FULL test failed\n");
        return TEST_FAILED;
    }

    printf("buf_test BUF FULL test passed\n\n");
    /**************BUF EMPTY TEST***********************/
    for(i=(length);i>0;i--)
    {
        CB_buffer_remove_item(*buf_test, temp_ptr);
    }

    status=CB_is_empty(*buf_test);
    if(status == CB_BUFFER_NOT_EMPTY)
    {
        printf("buf_test BUFF EMPTY test failed\n");
        return TEST_FAILED;
    }

    printf("buf_test BUF EMPTY test passed\n\n");
    /**************BUF WRAP ADD TEST***********************/
    /*buffer already at the end of the buffer allocation*/
    /*add a few more will cause the wrap around back to the bottom*/
    /*fill buff by 8 and remove*/

    for(i=0;i<8;i++)
    {
       CB_buffer_add_item(*buf_test, i);
       CB_buffer_remove_item(*buf_test, temp_ptr);
    }

    /*load and store 3 more in the buffer so that the buffer wraps around*/
    for(i=0;i<3;i++)
    {
        CB_buffer_add_item(*buf_test, i);
    }
    
    if((*buf_test)->head > (*buf_test)->tail)
    {
        printf("buf_test WRAP ADD test failed\n");
        return TEST_FAILED;
    }

    printf("buf_test BUF WRAP ADD test passed\n\n");
    /**************BUF WRAP REMOVE TEST***********************/
    /*buffer already wrap around the end of the buffer allocation*/
    /*removing items will cause the buffer to continue to wrap around*/
    for(i=0;i<3;i++)
    {
        CB_buffer_remove_item(*buf_test, temp_ptr);
    }
    
    if((*buf_test)->tail > (*buf_test)->tail)
    {
        printf("buf_test WRAP REMOVE test failed\n");
        return TEST_FAILED;
    }

    printf("buf_test BUF WRAP REMOVE test passed\n\n");
    /**************BUF OVERFILL TEST***********************/
    /*buffer already at the end of the buffer allocation*/
    /*add a few more will cause the wrap around back to the bottom*/
    for(i=0;i<(length+1);i++)
    {
        status = CB_buffer_add_item(*buf_test, i);
    }

    if(status != CB_BUFFER_FULL)
    {
        printf("buf_test OVERFILL test failed\n");
        return TEST_FAILED;
    }
    
    printf("buf_test BUF OVERFILL test passed\n\n");
    /**************BUF OVEREMPTY TEST***********************/
    /*buffer already at the end of the buffer allocation*/
    /*add a few more will cause the wrap around back to the bottom*/
    for(i=0;i<(length+1);i++)
    {
        status=CB_buffer_remove_item(*buf_test, temp_ptr);
    }

    if(status != CB_BUFFER_EMPTY)
    {
        printf("buf_test OVEREMPTY test failed\n");
        return TEST_FAILED;
    }

    printf("buf_test BUF OVEREMPTY test passed\n\n");

    printf("circbuf test passed\n");
    /*All test passed ad PASS is returned*/
    return TEST_PASS;    
}

/*********************************************************************************************/
/*************************************circbuf_tests*******************************************/
/*********************************************************************************************/
