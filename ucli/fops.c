/********************************************************************
* FILE NAME: parser.c
*
*
* PURPOSE: parsing for each cmd name.
*
* 
* NOTES:
*
* 
* DEVELOPMENT HISTORY: 
* 
* Date Author Release  Description Of Change 
* ---- ----- ---------------------------- 
*2016.11.27, XuDency, initial coding.
*
********************************************************************/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <math.h>
#include "libtype.h"

#define LINE_BYTES 0x10        // how many bytes in one line

void pr(void *adrs, int n, int width )
{
    int i;
    void *tmpadrs = (void *)((u64) adrs & ~(width - 1));
    u8 *pbyte;        
    u16 *pshort;    
    u32 *pint;    
    u64 *plong;        

    /* print column sign */
    printf("        ");
    switch (width)
    {
        case 1:
            for(i = 0; i < LINE_BYTES; i+=width)
            {
                printf("%-2x ", i);
            }
            break;
        case 2:
            for(i = 0; i < LINE_BYTES; i+=width)
            {
                printf("%-4x ", i);
            }
            break;
        case 4:
            for(i = 0; i < LINE_BYTES; i+=width)
            {
                printf("%-8x ", i);
            }
            break;
        case 8:
            for(i = 0; i < LINE_BYTES; i+=width)
            {
                printf("%-16x ", i);
            }
            break;

        default:
            for(i = 0; i < LINE_BYTES; i+=width)
            {
                printf("%-2x ", i);
            }
            break;
            
    }
    printf("\n---------");
    for(i = 0; i < LINE_BYTES; i++)
    {
        printf("---");
    }

    /* print out */
    while (n-- > 0)
    {
        if (LINE_BYTES/width == i) {
            i = 0;
            printf ("\n0x%04x: ", (u16)((u64) tmpadrs - (u64)adrs));
        }

    switch (width)
    {
        case 1:
            pbyte = (u8*)tmpadrs;
            printf ("%02x ", *pbyte);
            break;
        case 2:
            pshort = (u16*)tmpadrs;
            printf ("%04x ", *pshort);
            break;
        case 4:
            pint = (u32*)tmpadrs;
            printf ("%08x ", *pint);
            break;
        case 8:
            plong = (u64*)tmpadrs;
            printf ("%08lx%08lx ", *(plong+1), *plong);
            break;
        
        default:
            pbyte = (u8 *)tmpadrs;
            printf ("%02x ", *pbyte);
            break;
        }

        tmpadrs = (void *)((u64)tmpadrs + width);
        i++;
    }

    printf ("\n");
}

int parse_write_file(char* filename, void* memaddr, u32 length, int width)
{
    int fd = ERROR;
    int ret = 0;

    if(0 == strlen(filename)){
        pr(memaddr, length, width);
    } else {
        /* creating file */
        fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0777);
        if (0 > fd) {
            perror("open fd");
            return ERROR;
        }

        /* write file */
        if (0 > write(fd, memaddr, length)) {
            perror("write fd");
            ret = ERROR;
            goto close_fd;
        }
    }
    
close_fd:
    close(fd);
    return ret;
}

void* parse_read_file(char* filename, u32 *file_len)
{
    int fd = ERROR;
    struct stat filestat;
    void* memaddr = NULL;
    u32 MAX_SIZE = PAGE_SIZE*1024;

    /*get file length, now for data within 4k, larger data is under verifing and to be continued... */
    if ((0 > stat(filename, &filestat) || (MAX_SIZE < filestat.st_size))) {
        perror("stat");
        return (void*)ERROR;
    } else {
        *file_len = filestat.st_size;
    }

    memaddr = malloc(*file_len);
    if (NULL == memaddr) {
        perror("malloc");
        return (void*)ERROR;
    }
    
    /* open file */
    fd = open(filename, O_RDONLY);
    if (0 > fd) {
        perror("open fd");
        free(memaddr);
        return (void*)ERROR;
    }

    /* read file */
    if (*file_len != read(fd, memaddr, *file_len)) {
        perror("read fd");
        free(memaddr);
        close(fd);
        return (void*)ERROR;
    }
    
    close(fd);
    return memaddr;
}
