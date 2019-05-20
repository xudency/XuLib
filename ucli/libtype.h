#ifndef _LIB_TYPES_H_H
#define _LIB_TYPES_H_H

#include <stdio.h>

// User Print
#define PRINTU(fmt, args...)  \
    printf("USER[%s:%d]"fmt "\n", __FUNCTION__, __LINE__, ## args);

typedef unsigned char bool;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef signed long s64;
typedef unsigned long u64;


#define OK 0
#define ERROR (-1)

#define PAGE_SIZE 0x1000

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#endif
