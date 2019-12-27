/*==============================================================================
 Name        : rasplibs/tests/main.c
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
Abstract     : Tests asm routines
==============================================================================*/
#include <precompile.h>
#include <algo.h>
#include <functor.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

#ifndef SIXTEEN
        #define SIXTEEN 16
#endif
#ifndef TEN
        #define TEN     10
#endif

/* assembly declarations */
void gen_sort(genptr array, const size_t count, 
              int (*pred)(const pointer_or_int, const pointer_or_int));

bool is_equal(pointer array1, pointer array2, const size_t count);
void icopy(pointer restrict dest, pointer restrict src, const size_t count); 

int gen_str_less(int_holding_const_char_pointer s1, 
                 int_holding_const_char_pointer s2);

int asm_int_less(int v1, int v2);

/* the test driver */
void test_c();
void print_array(pointer array, const size_t count);

void main(void)
{

    test_c();
    REPORT("asmtest");
}

void test_c()
{
 	TC_BEGIN(__func__);
        printf("\n-----------TEST 1: testing the tests: icopy and is_equal---\n");
        int expected[]= {15,14,13,12,11,10,9,8,7,6,5,4,3,2,1, 0};
        int buf[SIXTEEN];
        icopy(buf, expected, _countof(buf));
        VERIFY(is_equal(expected, buf, _countof(expected)));
        print_array(buf, _countof(buf));

        printf("\n TEST 2:  Sort the Lab assignment array -------------------\n");
        int TheLabRandom[] = {
                -41, 30, -120, 2, 108, 0, 126, 1, 3, 109, -4, 25, 6, -100, 65};
   
        gen_sort(TheLabRandom, _countof(TheLabRandom), asm_int_less);
        printf("ascending\n");
        print_array(TheLabRandom, _countof(TheLabRandom));
           
        printf("\n-----------TEST 3: sort random numbers ascending-----------\n");  
        int test[SIXTEEN];
        int compare[SIXTEEN];
        srand(97);
        
        modify(test, _countof(test), sizeof(int), rand_int);
        icopy(compare, test, _countof(compare));
        
        gen_sort(test, _countof(test), asm_int_less);
        gen_sort(compare, _countof(compare), asm_int_less);
        
        VERIFY(is_equal(test, compare, _countof(test)));
        print_array(test, _countof(test));
     
        printf("\n-----------TEST 5: sort grid of random numbers ascending---\n"); 
        srand(1);
        int grid_test[TEN][TEN];       
        int grid_compare[TEN][TEN];
        int *ptest = (int*)&grid_test;
        int *pcmp = (int*)&grid_compare;
        
        modify(ptest, TEN*TEN, sizeof(int), rand_int);
        icopy(pcmp, ptest, TEN*TEN);
        printf("before\n");
        
        for(size_t row=0; row < TEN; row++) {
                for(size_t col=0; col < TEN; col++)
                        printf("%d ", grid_test[row][col]);
                               
                printf("\n");
        }
     
        gen_sort(grid_test, TEN*TEN, asm_int_less);
        gen_sort(grid_compare, TEN*TEN, asm_int_less);       
        VERIFY(is_equal(ptest, pcmp, _countof(grid_test)));
        printf("after\n");
        for(size_t row=0; row < TEN; row++) {
                for(size_t col=0; col < TEN; col++)
                        printf("%d ", grid_test[row][col]);
                               
                printf("\n");
        }
      
        printf("\n-----------TEST 6: sort string array lexical order---------\n"); 
        const char* strs[] = {
                "zero", "one", "two", "three", "four", "five", "six", "seven",
                "eight", "nine", "ten", "eleven", "twelve", "thirteen",
                "fourteen", "fifteen"
        };
                
        gen_sort(strs, _countof(strs), gen_str_less);
        
        for(size_t i=0; i < _countof(strs); i++)
                printf("%s\n", strs[i]);
        
	PASSED(__func__, __LINE__);
}

/* predicate for sorting strings */
int gen_str_less(int_holding_const_char_pointer s1, 
                 int_holding_const_char_pointer s2)
{
 /* Warning: diabolical code!!  Need to make sure that word size is same 
 as pointer size due toe vil storing of const char* cast into int for the 
 generic sorting predicate so that we can use the same signature for both
 word size and pointer size predicate arguments */
        VERIFY(sizeof(int) == sizeof(const char*));
        VERIFY(sizeof(int) == sizeof(int*));
        VERIFY(s1 && s2);
        const char* left = (const char*)s1;
        const char* right = (const char*)s2;
        return strcmp(left, right) < 0 ? 1 : 0;
}

void print_array(pointer array, const size_t count)
{
        VERIFY(array);
        for(pointer p=array; p < (array + count); p++)
                printf("%d ", *p);
        
        printf("\n");
}

#pragma GCC diagnostic push
