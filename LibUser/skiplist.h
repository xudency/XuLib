#ifndef _SKIP_LIST_H_
#define _SKIP_LIST_H_

#define SKIPLIST_MAXLEVEL 8


typedef struct skiplistNode {
        double score;
        struct skiplistNode *backward;
        struct skiplistLevel {
                struct skiplistNode *forward;
        }level[];
} skiplistNode;

typedef struct skiplist {
        struct skiplistNode *header, *tail;
        unsigned long length;
        int level;
} skiplist;


extern int skiplist_main(int argc, char *argv[]);

#endif
