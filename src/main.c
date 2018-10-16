#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<regex.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdbool.h>

#include "headers/libutil.h"
#include "headers/easyio.h"
#include "headers/hash.h"

#include "qai.h"

const char *kbase_file_path = "./.qai/kbase";

int compile_kbase(void);

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		die("Invalid number of arguments");
	}

	// if fails then print error and exit
	if(compile_kbase() != 0)
	{
		die("Error: compile_kbase");
	}

	return 0;
}

int compile_kbase()
{
	// 1. Open kbase file
	FILE *kbase_h = fopen(kbase_file_path, "r");
	if(!kbase_h)
	{
		// Couldn't open the file
		return 1;
	}

	// Initializing Knowledge Base
	struct KBase *kb = kbase_init();
	char pattern_name[VARNAME_LEN], pattern[PATTER_LEN];

	// 2. Read all kbase, compile it, store it
	String line;
	while(GetString(&line, kbase_h) > 0)
	{
		printf("%s\n", line);
		extract_pattern_name(line, pattern_name);
		extract_pattern(line, pattern);
		printf("Pattern name: %s      Pattern: %s\n", pattern_name, pattern);
		if (kbase_add_knowledge(kb, pattern_name, pattern) != 0)
		{
			die("ERROR: kbase_add_knowledge");
		}

		free(line);
	}

	printf("Added Knowleges -->\n");
	//while (get_next_knowledge(


	// Destroying Knowledge base
	kbase_destroy(kb);

	fclose(kbase_h);

	return 0;
}
