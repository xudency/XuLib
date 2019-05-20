/*
 *  CLI Main entrance
 *
 *  wxcli -cmd
 *
 */


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

#include "cli.h"

int main(int argc, char* argv[])
{
	cli_main(argc, argv);

	//string_main(argc, argv);

	//string_main(argc, argv);
	
	//BSTree_test(argc, argv);

	//sort_test();

	return 0;
}

