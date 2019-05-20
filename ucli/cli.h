#ifndef _CLI_H
#define _CLI_H


extern char devname[20];

struct cli_callback_fn
{
    char* cmd;
    int (*fn)(int, char**);
};

extern int cli_main(int argc, char* argv[]);


//////
extern void BSTree_test(int argc, char* argv[]);
extern void sort_test(void);






/////////////////////
int scan_bb_cli_parse(int argc, char* argv[]);
int scan_rdraw_cli_parse(int argc, char* argv[]);


#endif

