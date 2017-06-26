#ifndef _FILE_OPS_H
#define _FILE_OPS_H

void* parse_read_file(char* filename, u32 *file_len);
int parse_write_file(char* filename, void* memaddr, u32 length, int width);

#endif

