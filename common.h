#ifndef _UK_COMMON_H
#define _UK_COMMON_H

#define OK 0
#define ERROR (-1)

#define PAGE_SIZE 0x1000

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))


#if 0
// Micron
struct physical_address
{
  union
  {
    // ppa format in nand
    struct
    {
      unsigned int ch        : 4;
      unsigned int sec       : 2;
      unsigned int pl        : 1;
      unsigned int lun       : 3;
      unsigned int pg        : 9;
      unsigned int blk       : 12;
      unsigned int resved    : 1;  
    } nand;

    // ppa format in write cache
    struct
    {
      unsigned int ch         : 4;
      unsigned int line       : 3;
      unsigned int lun        : 3;
      unsigned int ver        : 9;
      unsigned int resved     : 12;
      unsigned int in_cache   : 1;
    } cache;

    unsigned int ppa;
  };
};

#else
// Toshiba
struct physical_address
{
  union
  {
    // ppa format in nand
    struct
    {
      unsigned int ch        : 4;  // 16 channels
      unsigned int sec       : 2;  // 4 sectors per page
      unsigned int pl        : 2;  // 4 planes per LUN
      unsigned int lun       : 3;  // 8 LUNs per channel
      unsigned int pg        : 8;  // 256 pages per block
      unsigned int blk       : 12; // 1069 blocks per plane
      unsigned int resved    : 1;  // 1 bit reversed
    } nand;

    // ppa format in write cache
    struct
    {
      unsigned int ch         : 4;
      unsigned int line       : 4;
      unsigned int lun        : 3;
      unsigned int ver        : 8;
      unsigned int resved     : 12; 
      unsigned int in_cache   : 1;  
    } cache;

    unsigned int ppa;
  };
};
#endif

// Ioctl
#define MY_IOCTL_DBG	_IOWR('N', 0x41, unsigned long)

#endif

