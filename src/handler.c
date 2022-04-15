/*
   Copyright 2022 Eduardo Antunes

   This file is part of todo.

   todo is free software: you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation,
   either version 3 of the License, or (at your option)
   any later version.

   todo is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied
   warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
   PURPOSE. See the GNU General Public License for more
   details.

   You should have received a copy of the GNU General
   Public License along with todo. If not, see
   <https://www.gnu.org/licenses/>.
*/

#include <stdlib.h>

#include "common.h"
#include "handler.h"
#include "help.h"
#include "todo.h"

// Helpful macros:

// Iterates over the arguments given to the handler as they
// are, binding args[i] to each element on the way.
#define FOR_EACH_ARG() \
	for(int i = 2; args[i] != NULL; i++)

// Iterates over the arguments given to the handler,
// parsing them as indices for the todo list. It binds each
// index to a variable chosen by the user, and deals with
// pasing errors by returning the appropriate Handler_res
// values. 
#define FOR_EACH_ARG_AS_INDEX(num) \
	for(int i = 2; args[i] != NULL; i++)               \
	    if(sscanf(args[i], "%d", &num) == EOF)         \
		    return HANDLER_ERROR_INVALID_NUMERIC_ARGS; \
		else if(num <= 0)                              \
		    return HANDLER_ERROR_INDEX_TOO_LOW;        \
		else if((uint) num > td->count)                \
		    return HANDLER_ERROR_INDEX_TOO_HIGH;       \
		else

// Actual handlers:

Handler_res none_handler(Todo_list *td, char *args[])
{
	todo_print(td);
	return HANDLER_OK;
}

Handler_res help_handler(Todo_list *td, char *args[])
{
	eprintf("Manage todo lists from the command line.\n\n");
	usage(args[0]);
	return HANDLER_OK;
}

Handler_res add_handler(Todo_list *td, char *args[])
{
	FOR_EACH_ARG() {
		todo_add(td, TASK_TODO, args[i]);
	}
	return HANDLER_OK_SAVE_CHANGES;
}

Handler_res rm_handler(Todo_list *td, char *args[])
{
	int index = 0;
	FOR_EACH_ARG_AS_INDEX(index) {
		todo_rm(td, index - 1);
	}
	return HANDLER_OK_SAVE_CHANGES;
}

Handler_res check_handler(Todo_list *td, char *args[])
{
	int index = 0;
	FOR_EACH_ARG_AS_INDEX(index) {
		todo_set_state(td, index - 1, TASK_DONE);
	}
	return HANDLER_OK_SAVE_CHANGES;
}

Handler_res uncheck_handler(Todo_list *td, char *args[])
{
	int index = 0;
	FOR_EACH_ARG_AS_INDEX(index) {
		todo_set_state(td, index - 1, TASK_TODO);
	}
	return HANDLER_OK_SAVE_CHANGES;
}

Handler_res work_on_handler(Todo_list *td, char *args[])
{
	int index = 0;
	FOR_EACH_ARG_AS_INDEX(index) {
		for(int j = 0; j < td->count; j++) {
			if(j == index - 1) {
				td->tasks[j].state = TASK_WIP;
			} else if(td->tasks[j].state == TASK_WIP) {
				td->tasks[j].state = TASK_DONE;
			}
		}
	}
	return HANDLER_OK_SAVE_CHANGES;
}

Handler_res error_handler(Todo_list *td, char *args[])
{
	eprintf("Unrecognized command %s\n\n", args[1]);
	return HANDLER_ERROR_USAGE;
}
