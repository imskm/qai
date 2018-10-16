#include<stdio.h>
#include<sys/types.h>
#include<regex.h>
#include<assert.h>

int main(int argc, char *argv[])
{
	assert(argc == 2);

	regex_t regexp;
	//char *pattern = "^[a-zA-Z]{1,}";
	char *pattern = "^([0-9]+)\\) ";
	char *string = (char *)argv[1];
	regmatch_t pregmatch[1];

	assert(regcomp(&regexp, pattern, REG_EXTENDED | REG_NOSUB) == 0);

	assert(regexec(&regexp, string, 1, pregmatch, 0) == 0);

	//if(pregmatch[0].rm_so != -1)
	//{
	//	for(int i = pregmatch[0].rm_so; i <= pregmatch[0].rm_eo; ++i)
	//	{
	//		putchar(string[i]);
	//	}
	//	printf("\n");
	//}

	regfree(&regexp);

	return 0;
}
