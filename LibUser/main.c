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
#include "type.h"
#include "string.h"
#include "../common.h"


int main(int argc, char* argv[])
{
	//return cli_main(argc, argv);

	string_main(argc, argv);
	
	return 0;
}

