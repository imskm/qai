#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

#include "qai.h"
#include "common.h"
#include "headers/colors.h"

#define STORAGE "storage.qa"

static unsigned int nque, nans, nunk;
static FILE *qa_file;
static char current_file[64] = STORAGE;
static int is_running = 0;
static int file_exist(char *filename)
{
	if (access(filename, R_OK) == 0)
		return 1;

	return 0;
}

static int file_writable(char *filename)
{
	if (access(filename, W_OK) == 0)
		return 1;

	return 0;
}

static void write_line(FILE *file, char *line)
{
	// Do clean up firs
	// then write
	fprintf(file, "%s\n", line);
}

static void clean_line(char *line)
{

	return;
}

static FILE *file_init(char *filename)
{

	return NULL;
}

void qai_action(char *line, int type, char *var_name, regmatch_t *match)
{
	switch(type)
	{
		case KBASE_KNW :
			fprintf(stderr, ANSI_COLOR_GREEN"%12s: "ANSI_RESET"%s\n", var_name, (char *)&line[match->rm_eo]);
			//fprintf(stderr, "Start: %d   End: %d", match.rm_so, match.rm_eo);
			if (strcmp(var_name, "question") == 0)
				nque++;
			else if (strcmp(var_name, "answer") == 0)
				nans++;

			// writing line to storage
			write_line(qa_file, (char *)&line[match->rm_eo]);
			break;
			
		case KBASE_UNK :
			fprintf(stderr, ANSI_COLOR_RED"%s: "ANSI_RESET"%s\n", "UNKNOWN", line);
			nunk++;
			break;

		default :
			//
			break;
	}
}

void qai_start()
{
	if (file_exist(STORAGE))
	{
		if (!file_writable(STORAGE))
		{
			sprintf(current_file, "%s-%d", STORAGE, 1);
			fprintf(stderr, "File %s is not writable\n", STORAGE);
			fprintf(stderr, "Creating new file %s\n", current_file);
		}
	}

	// Opening anc caching file
	if (is_running == 0)
	{
		qa_file = fopen(current_file, "w");
		if (qa_file == NULL)
		{
			fprintf(stderr, "qai_start: failed to create storage file\n");
			exit(1);
		}
		is_running = 1;
	}

	nque = 0, nans = 0, nunk = 0;
	fprintf(stderr, ANSI_BOLD ANSI_COLOR_YELLOW"QAI Started\n"ANSI_RESET);
}

void qai_stop()
{
	fprintf(stderr, ANSI_BOLD ANSI_COLOR_YELLOW"\n\nQAI Stopping\n"ANSI_RESET);
	fprintf(stderr, "    Questions: %3d\n", nque);
	fprintf(stderr, "    Answers  : %3d\n", nans);
	fprintf(stderr, "    Unknowns : %3d\n", nunk);
	fprintf(stderr, ANSI_BOLD ANSI_COLOR_YELLOW"QAI Stoped\n"ANSI_RESET);

	// Do the cleanup
	is_running = 0;
}

