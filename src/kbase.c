struct Knowledge *new_knode(char *pattern_name, char *pattern)
{
	regex_t regex;
	struct Knowledge *knode = (struct KNode *) malloc(sizeof(struct KNode));
	if (knode)
	{
		knode->pattern_name = strdup(patter_name);
		knode->pattern = strdup(pattern);
		if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0)
		{
			free(knode);
			return NULL;
		}

		knode->compiled = regex;
	}

	return knode;
}

struct KBase *kbase_init()
{
	struct KBase *kb = (struct KBase *) malloc(sizeof(struct KBase));
	if (!kb)
		return NULL;

	kb->count = 0;
	kb->knowledges = hash_create(sizeof(struct Knowledge));
	kb->knode_size = knode_size;

	return kb;
}

int kbase_add(struct KBase *kb, char *pattern_name, char *pattern)
{
	Knowledge *knode = new_Knode(pattern_name, pattern);
	if (knode == NULL)
		return 1;

	if (!hash_put(pattern, knode))
		return 2;

	// no need now, since this was copied to hash table
	free(knode);

	return 0;
}

void kbase_destroy(struct KBase *kb)
{
	// TODO
}

/**
 * Some utility functions
 */
int extract_pattern_name(char *line, char *storage)
{
	const int started = 1, nstarted = 0;
	const char begin_tag = '<';
	const char end_tag   = '>';

	int state = nstarted;
	int c, i, k;

	i = k = 0;
	// skipping any leading spaces
	while ((c = line[i++]) == ' ' || c == '\t')
		; /* skipping spaces */

	--i; /* syncing cursor position from previous +1 offset */
	while ((c = line[i++]) != end_tag && c != '\0')
	{
		if (c == begin_tag)
		{
			state = started;
			continue;
		}

		if (state == started)
			storage[k++] = c;
	}

	storage[k] = 0;

	return k;
}

int extract_pattern(char *line, char *storage)
{
	int c, i, k;
	const int started = 1;
	int state;

	i = k = state = 0;
	while ((c = line[i++]) != '\0')
	{
		if (state != started && c == ' ')
		{
			state = started;
			continue;
		}

		if (state == started)
			storage[k++] = c;
	}

	storage[k] = 0;

	return k;
}
