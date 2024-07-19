/*==============================================================================
 Name        : precompile.h
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
==============================================================================*/
#pragma once
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

/* array size macros */
#ifndef _countof
#define _countof(x) sizeof(x) / sizeof(x[0])
#endif

#ifndef _gridcountof
#define _gridcountof(x) sizeof(x) / sizeof(x[0][0])
#endif

typedef int IntType;
typedef IntType value_type;
typedef value_type *pointer;
typedef pointer iterator;
typedef const iterator const_iterator;
typedef void* genptr;
typedef int   pointer_or_int;
typedef int   int_holding_const_char_pointer;

/* TEST HARNESS*/
extern int passed;
extern int failed;
extern int tcs;
#define TC_BEGIN(func) \
	printf("--------------------TEST GROUP BEGIN %s ---------------------\n", func); \
	tcs++;
#define VERIFY(x) \
	(x) ? passed++ : failed++; \
	assert(x)
#define PASSED(func, line) \
	printf("--------------------PASSED %s Line: %d --------------------\n", func, line); \
	passed++;
#define REPORT(msg) \
	printf("--%s VALIDATIONS PASSED=%d VALIDATIONS FAILED=%d-------\n", msg, passed, failed);




