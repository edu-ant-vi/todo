/*
   Copyright 2022-2024 Eduardo Antunes dos Santos Vieira

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

#include <assert.h>
#include <string.h>
#define TODO_VERSION "1.1.0"

#include <stdio.h>
#include <stdlib.h>

#include "todo.h"
#include "common.h"
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
};

void todo_save(Todo_list *td, FILE *todo_fd);

int main(int argc, char *argv[])
{
	// Configuration step
	Config conf;
	read_config(&conf, argc, argv);

	// Setup step
	Todo_list td;
	todo_init(&td);
	assert(strcmp(conf.filename, "TODO") == 0);

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
	Command c = conf.comm;
	if(c >= CM_NONE && c <= CM_ERROR) {
		if(conf.help) {
			hr = HANDLER_OK_HELP;
		} else if(conf.version) {
			hr = HANDLER_OK_VERSION;
		} else {
			hr = handler[c](&td, &argv[conf.args_ind]);
		}
	} else {
		// Stupid programmer error
		hr = HANDLER_ERROR_PROGRAMMER;
		/* eprintf("Unhandled command: %s\n", argv[optind]); */
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
			/* if(!conf.help) optind++; */
			if(conf.args_ind < argc) {
				Command c = parse(argv[conf.args_ind]);
				bool ok = help(argv[0], c);
				if(!ok) {
					eprintf("Unrecognized command: %s\n", argv[conf.args_ind]);
					usage(argv[0]);
					exit_code = 1; // usage error
				}
			} else {
				printf("Manage todo lists from the command line.\n");
				usage(argv[0]);
			}
			break;
		case HANDLER_OK_VERSION:
			printf("%s\n", TODO_VERSION);
			printf("Copyright 2022-2024 Eduardo Antunes dos Santos Vieira\n");
			printf("Licensed under GNU GPL v3\n");
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
			eprintf("Arguments to %s must be integers\n", argv[conf.args_ind - 1]);
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
