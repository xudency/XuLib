/********************************************************************
* FILE NAME: utest.h
*
*
* PURPOSE: headerfile of this application. 
*
* 
* NOTES:
*
* 
* DEVELOPMENT HISTORY: 
* 
* Date Author Release  Description Of Change 
* ---- ----- ---------------------------- 
*2014.6.27, dxu, initial coding.
*
****************************************************************/
#ifndef _DECLARE_H
#define _DECLARE_H

#include <linux/types.h>
#include <errno.h>
#include <stdio.h>
#include "../../cnex-sw/cfg/flash_cfg.h"

extern char devname[20];

typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef signed long s64;
typedef unsigned long u64;

#define OK 0
#define ERROR (-1)
#define LINE_BYTES 0x10        // how many bytes in one line
#define PAGE_SIZE 0x1000

#define PRINT(format, args...)                      \
    printf("[%s-%d] "format "\n", __FUNCTION__, __LINE__, ## args);

struct cmd_func_stru
{
    char* cmd;
    int (*fn)(int, char**);
};

// Function declare
int usage(int argc, char* argv[]);
void* parse_read_file(char* filename, u32 *file_len);
int parse_write_file(char* filename, void* memaddr, u32 length, int width);

extern int setppa(int argc, char* argv[]);
extern int getppa(int argc, char* argv[]);
extern int kernel_dbg(int argc, char* argv[]);

#endif

