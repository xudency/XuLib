#ifndef _TYPE_H
#define _TYPE_H

#include <stdio.h>

#define PRINT(format, args...)  \
    printf("[%s:%d]"format "\n", __FUNCTION__, __LINE__, ## args);

typedef unsigned char bool;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef signed long s64;
typedef unsigned long u64;

#define true   1
#define false  0

#endif

