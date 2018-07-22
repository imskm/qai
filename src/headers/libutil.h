#ifndef LIB_UTIL
	#define LIB_UTIL
#endif

void print_error(char* msg)
{
	fputs(msg, stderr);
}

void die(char* msg)
{
	fputs(msg, stderr);
	printf("\n");
	exit(0);
}
