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

#include "type.h"
#include "cli.h"
#include "string.h"
#include "skiplist.h"
#include "../common.h"


int main(int argc, char* argv[])
{
	//cli_main(argc, argv);

	//string_main(argc, argv);

	//string_main(argc, argv);
	
	binary_tree_test(argc, argv);
	
	return 0;
}

