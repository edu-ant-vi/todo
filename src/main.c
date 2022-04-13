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
#include "handler.h"
#include "parse.h"

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
	Command cm = parse_command(argv[1]);
	// Call the appropriate handler
	switch(cm) {
		case CM_NONE:
			todo_print(&td);
			hr = HANDLER_OK;
			break;
		case CM_HELP:
			hr = help_handler(&td, &argv[2]);
			break;
		case CM_ADD:
			hr = add_handler(&td, &argv[2]);
			break;
		case CM_REMOVE:
			hr = rm_handler(&td, &argv[2]);
			break;
		case CM_CHECK:
			hr = check_handler(&td, &argv[2]);
			break;
		case CM_ERROR:
			// Stupid user error
			eprintf("Unrecognized command %s\n\n", argv[1]);
			hr = HANDLER_ERROR_USAGE;
			break;
		default:
			// Stupid programmer error
			eprintf("Unhandled command %s\n", argv[1]);
			hr = HANDLER_ERROR_PROGRAMMER;
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
			exit_code = 2;
			break;
		case HANDLER_ERROR_INVALID_NUMERIC_ARGS:
			exit_code = 3;
			eprintf("Arguments to %s must be integers\n", argv[1]);
			break;
		case HANDLER_ERROR_INDEX_TOO_LOW:
			exit_code = 4;
			eprintf("The minimum index is 1\n");
			break;
		case HANDLER_ERROR_INDEX_TOO_HIGH:
			exit_code = 5;
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

