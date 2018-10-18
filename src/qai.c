#include <stdio.h>
#include <string.h>
#include <regex.h>

#include "qai.h"
#include "common.h"
#include "headers/colors.h"

static unsigned int nque, nans, nunk;

void qai_start()
{
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
