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
#include "headers/colors.h"

#include "kbase.h"
#include "qai.h"
#include "common.h"

const char *kbase_file_path = "./.qai/kbase";
static struct KBase *kbase;

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

	// Checking question file
	// 2. Read all kbase, compile it, store it
	struct Knowledge *fk;
	char *qfile_name = argv[1];
	FILE *qfile = fopen(qfile_name, "r");
	String line;
	qai_start();
	while(GetString(&line, qfile) > 0)
	{
		fk = kbase_guess(kbase, line);
		// kbase_guess() guessed the line using its knowldege base
		if (fk != NULL)
			qai_action(line, KBASE_KNW, fk->pattern_name);

		// Unkown line: kbase_guess() is not able to guess the line
		else
			qai_action(line, KBASE_UNK, NULL);
	}
	qai_stop();

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
	kbase = kbase_init();
	struct Knowledge *fk;
	char pattern_name[VARNAME_LEN], pattern[PATTER_LEN];

	// 2. Read all kbase, compile it, store it
	String line;
	while(GetString(&line, kbase_h) > 0)
	{
		//printf("%s\n", line);
		extract_pattern_name(line, pattern_name);
		extract_pattern(line, pattern);
		//printf("Pattern name: %s      Pattern: %s\n", pattern_name, pattern);
		if (kbase_add_knowledge(kbase, pattern_name, pattern) != 0)
		{
			die("ERROR: kbase_add_knowledge");
		}

		free(line);
	}

	//printf("Added Knowleges -->\n");
	for (int i = 0; i < kbase->count; ++i)
	{
		fk = kbase_get_knowledge(kbase, kbase->keys[i]);
		//printf("Pattern name: %s      Pattern: %s\n", fk->pattern_name, fk->pattern);
	}


	// Destroying Knowledge base
	kbase_destroy(kbase);

	fclose(kbase_h);

	return 0;
}
