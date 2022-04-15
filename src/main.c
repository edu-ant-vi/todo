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

// A cli todo app. Because creativity was never an option.

#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "todo.h"
#include "help.h"
#include "handler.h"
#include "commands.h"

Handler handler[] = {
	[CM_NONE]    = none_handler,
	[CM_HELP]    = help_handler,
	[CM_ADD]     = add_handler,
	[CM_REMOVE]  = rm_handler,
	[CM_CHECK]   = check_handler,
	[CM_UNCHECK] = uncheck_handler,
	[CM_ERROR]   = error_handler,
};

void todo_save(Todo_list *td, FILE *todo_fd);

int main(int argc, char **argv)
{
	const char todo_filename[] = "TODO";

	Todo_list td;
	todo_init(&td);

	FILE *todo_fd = fopen(todo_filename, "r");

	if(todo_fd != NULL) {
		// If the file exists, we read it
		todo_read_file(&td, todo_fd);
	} else {
		// Otherwise, we attempt to create it
		todo_fd = fopen(todo_filename, "w");
		if(todo_fd == NULL) {
			eprintf("Could not access nor create file '%s'\n", todo_filename);
			todo_free(&td);
			return 1;
		}
	}

	Handler_res hr;
	Command c = parse(argv[1]);
	if(c < CM_NONE || c > CM_ERROR) {
		// Stupid programmer error
		hr = HANDLER_ERROR_PROGRAMMER;
		eprintf("Unhandled command: %s\n", argv[1]);
	} else {
		hr = handler[c](&td, argv);
	}

	int exit_code = 0;
	switch(hr) {
		case HANDLER_OK:
			break;
		case HANDLER_OK_SAVE_CHANGES:
			todo_save(&td, todo_fd);
			break;
		case HANDLER_ERROR_USAGE:
			exit_code = 1;
			usage(argv[0]);
			break;
		case HANDLER_ERROR_PROGRAMMER:
			exit_code = 0xDEAD;
			break;
		case HANDLER_ERROR_INVALID_NUMERIC_ARGS:
			exit_code = 2;
			eprintf("Arguments to %s must be integers\n", argv[1]);
			break;
		case HANDLER_ERROR_INDEX_TOO_LOW:
			exit_code = 3;
			eprintf("The minimum index is 1\n");
			break;
		case HANDLER_ERROR_INDEX_TOO_HIGH:
			exit_code = 4;
			eprintf("The maximum index right now is %d\n", td.count);
			break;
		default:
			// Stupid programmer strikes again
			exit_code = 0xDEAD;
			eprintf("Unhandled handler result\n");
	}

	todo_free(&td);
	fclose(todo_fd);
	return exit_code;
}

void todo_save(Todo_list *td, FILE *todo_fd)
{
	todo_fd = freopen(NULL, "w", todo_fd);
	if(todo_fd == NULL) {
		eprintf("Could not save changes to the TODO file\n"
				"Perhaps you don't have write permissions on it?\n");
		todo_free(td);
		exit(1);
	}
	todo_write_file(td, todo_fd);
}
