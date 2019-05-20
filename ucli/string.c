#include <string.h>
#include "string.h"
#include "libtype.h"

void strlen_test(void)
{
	char *str = "xudc: 1989";

	// strlen(str) NOT include '\0'	
	PRINTU("string:%s len:%u", str, strlen(str));

	return;
}


int string_main(int argc, char* argv[])
{
	strlen_test();

	return 0;
}

