/**
 * This is an interface for the qai program.
 * You should implement this functions because these functions
 * are called from main qai program.
 * qai program is expecting these functions to be implemented
 * and it should handle the operation as you want and what you
 * want to do with it.
 */
#ifndef _QAI_H
#define _QAI_H

void qai_start();
void qai_stop();
void qai_action(char *line, int type, char *var_name, regmatch_t *match);

#endif
