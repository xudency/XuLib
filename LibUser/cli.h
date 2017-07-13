#ifndef _CLI_H
#define _CLI_H

struct cli_callback_fn
{
    char* cmd;
    int (*fn)(int, char**);
};

extern int cli_main(int argc, char* argv[]);


//////
extern void binary_tree_test(int argc, char* argv[]);

#endif

