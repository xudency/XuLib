#include <string.h>
#include "string.h"
#include "type.h"

void strlen_test(void)
{
	char *str = "xudc: 1989";

	// strlen(str) NOT include '\0'	
	PRINT("string:%s len:%lu", str, strlen(str));

	return;
}


int string_main(int argc, char* argv[])
{
	strlen_test();

	return 0;
}

