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

// Introducing command-line options isn't going to be as straightforward
// as I thought it would, because it disrupts one fundamental assumption
// of my current handlers: that they will have full access to the argv
// array. I could give them the full array and also pass them optind, so
// they know where to start. Or I could change the handlers in such a way
// that they don't need to know the full argv array. The second option
// feels more natural, so it's what I'm going to attemp at first.

#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "todo.h"
#include "help.h"
#include "handler.h"
#include "commands.h"
#include "config.h"

Handler handler[] = {
	[CM_NONE]    = none_handler,
	[CM_HELP]    = help_handler,
	[CM_ADD]     = add_handler,
	[CM_REMOVE]  = rm_handler,
	[CM_CHECK]   = check_handler,
	[CM_UNCHECK] = uncheck_handler,
	[CM_WORK_ON] = work_on_handler,
	[CM_ERROR]   = error_handler,
};

void todo_save(Todo_list *td, FILE *todo_fd);

int main(int argc, char *argv[])
{
	// Configuration step
	Config conf;
	configure(&conf);

	// Setup step
	Todo_list td;
	todo_init(&td);

	FILE *todo_fd = fopen(conf.filename, "r");

	if(todo_fd != NULL) {
		// If the file exists, we read it
		todo_read_file(&td, todo_fd);
	} else {
		// Otherwise, we attempt to create it
		todo_fd = fopen(conf.filename, "w");
		if(todo_fd == NULL) {
			eprintf("Could not access nor create file '%s'\n", conf.filename);
			todo_free(&td);
			return 1;
		}
	}

	// Program logic step
	Handler_res hr;
	Command c = parse(argv[1]);
	if(c >= CM_NONE && c <= CM_ERROR) {
		hr = handler[c](&td, argc - 2, &argv[2]);
	} else {
		// Stupid programmer error
		hr = HANDLER_ERROR_PROGRAMMER;
		eprintf("Unhandled command: %s\n", argv[1]);
	}

	// Error handling step
	int exit_code = 0;
	switch(hr) {
		case HANDLER_OK:
			if(!conf.quiet || c == CM_NONE) {
				todo_print(&td, conf.ascii_only);
			}
			break;
		case HANDLER_OK_HELP:
			if(argv[2] != NULL) {
				Command c = parse(argv[2]);
				bool ok = help(argv[0], c);
				if(!ok) {
					eprintf("Unrecognized command: %s\n\n", argv[2]);
					return HANDLER_ERROR_USAGE;
				}
			} else {
				eprintf("Manage todo lists from the command line.\n\n");
				usage(argv[0]);
			}
			break;
		case HANDLER_OK_SAVE_CHANGES:
			todo_save(&td, todo_fd);
			if(!conf.quiet) {
				todo_print(&td, conf.ascii_only);
			}
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

	// Cleanup step
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
