/**
 * Include Helper function
 * Required by other functions below
 */
#include "helpers.h"

#ifndef _QAI_H
#define _QAI_H

#define PATTER_LEN   20
#define VARNAME_LEN  20
#define HT_SIZE      HASH_TABLE_SIZE  /* Hash Table size, comes from hash.h */
#define KEYS_SIZE    20

struct Knowledge {
	char *pattern;
	char *pattern_name;
	regex_t compiled;
};

typedef HashMap KHash;
/**
 * Object for holding knowledge
 * KBase Knowledge Base
 */
struct KBase {
	unsigned int count;
	KHash *knowledges;
	unsigned int knowledge_size;
	char **keys;
};

struct KBase *kbase_init();
int kbase_add_knowledge(struct KBase *kb, char *pattern_name, char *pattern);
void kbase_destroy(struct KBase *kb);
struct Knowledge *new_knowledge(char *pattern_name, char *pattern);
struct Knowledge *kbase_get_knowledge(struct KBase *kb, char *pattern);

int extract_pattern_name(char *line, char *pattern_name);
int extract_pattern(char *line, char *pattern);


/**
 * ----------------------------------------------
 * Seperate the code in .c file from here.
 * ----------------------------------------------
 */
struct Knowledge *new_knowledge(char *pattern_name, char *pattern)
{
	regex_t regex;
	struct Knowledge *know = (struct Knowledge *) malloc(sizeof(struct Knowledge));
	if (know)
	{
		know->pattern_name = strdup(pattern_name);
		know->pattern = strdup(pattern);
		if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0)
		{
			free(know);
			return NULL;
		}

		know->compiled = regex;
	}

	return know;
}

struct KBase *kbase_init()
{
	struct KBase *kb = (struct KBase *) malloc(sizeof(struct KBase));
	if (!kb)
		return NULL;

	kb->count = 0;
	kb->knowledge_size = sizeof(struct Knowledge);
	kb->knowledges = hash_create(kb->knowledge_size);
	kb->keys = (char **) malloc(sizeof(char *) * KEYS_SIZE);

	return kb;
}

int kbase_add_knowledge(struct KBase *kb, char *pattern_name, char *pattern)
{
	struct Knowledge *know = new_knowledge(pattern_name, pattern);
	if (know == NULL)
		return 1;

	kb->keys[ kb->count ] = strdup(pattern);
	kb->count++;
	// Check if keys reached its size, if yes then grow the array
	// TODO

	if (!hash_put(kb->knowledges, pattern, know))
		return 2;

	// no need now, since this was copied to hash table
	free(know);

	return 0;
}

struct Knowledge *kbase_get_knowledge(struct KBase *kb, char *pattern)
{
	struct Knowledge *know = (struct Knowledge *)hash_get(kb->knowledges, pattern);
	return know;
}

struct Knowledge *kbase_guess(struct KBase *kbase, char *line)
{
	struct Knowledge *fk;
	regmatch_t pregmatch[1];

	for(int i = 0; i < kbase->count; ++i)
	{
		fk = kbase_get_knowledge(kbase, kbase->keys[i]);
		if (regexec(&fk->compiled, line, 1, pregmatch, 0) == 0)
		{
			//printf("MATCHED[%s / %s]: %s\n", fk->pattern_name, fk->pattern, line);
			return fk;
		}
	}

	return NULL;
}

void kbase_destroy(struct KBase *kb)
{
	// TODO
}

#endif
