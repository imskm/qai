#ifndef _HELPERS_H
#define _HELPERS_H
/**
 * Some helpers functions
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

#endif
