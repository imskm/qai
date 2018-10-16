#ifndef _COLORS_H
	#define _COLORS_H
#endif


/**
 * Attribute Constants
 */

#define _RESET 			0
#define _BRIGHT			1
#define _DIM			2
#define _UNDERLINE		3
#define _BLINK			5
#define _REVERSE		7
#define _HIDDEN			8

/**
 * Color swatches
 */
#define _BLACK			0
#define _RED			1
#define _GREEN			2
#define _YELLOW			3
#define _BLUE			4
#define _MAGENTA		5
#define _CYAN			6
#define _WHITE			7

/**
 * Defining color swatch
 * ONLY for LINUX platform
 *
 * FORMAT
 * --------
 *  [{attr};{fg};{bg}m
 */

#define ANSI_COLOR_RED     	"\x1b[31m"
#define ANSI_COLOR_GREEN   	"\x1b[32m"
#define ANSI_COLOR_YELLOW  	"\x1b[33m"
#define ANSI_COLOR_BLUE    	"\x1b[34m"
#define ANSI_COLOR_MAGENTA 	"\x1b[35m"
#define ANSI_COLOR_CYAN    	"\x1b[36m"
#define ANSI_COLOR_WHITE   	"\x1b[37m"
#define ANSI_RESET   		"\x1b[0m"

#define ANSI_BG_RED     	"\x1b[41m"
#define ANSI_BG_GREEN     	"\x1b[42m"
#define ANSI_BG_YELLOW     	"\x1b[43m"

#define ANSI_BLINK			"\x1b[5m"
#define ANSI_BOLD			"\x1b[1m"


extern void
stdout_color(int fg, ...)
{
}
