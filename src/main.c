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
#include "parse.h"

// Exit like a gentleman
#define politely_exit(code) \
	todo_free(&td);         \
	fclose(todo_file);      \
	exit(code);

void usage(const char *name);
void todo_save(Todo_list *td, FILE *todo_file);

int main(int argc, char **argv)
{
	const char todo_filename[] = "TODO";

	Todo_list td;
	todo_init(&td);

	FILE *todo_file = fopen(todo_filename, "r");

	if(todo_file != NULL) {
		// If the file exists, we read it
		todo_read_file(&td, todo_file);
	} else {
		// Otherwise, we attempt to create it
		todo_file = fopen(todo_filename, "w");
		if(todo_file == NULL) {
			eprintf("Could not access nor create file '%s'\n", todo_filename);
			todo_free(&td);
			return 1;
		}
	}

	Command cm = parse_command(argv[1]);
	switch(cm) {
		case CM_NONE:
			// No command was given: prints todo list
			todo_print(&td);
			politely_exit(0);
		case CM_HELP:
			// help command: prints usage
			eprintf("Manage todo lists from the command line.\n\n");
			usage(argv[0]);
			politely_exit(0);
		case CM_ADD:
			// add command: iterates over its arguments, using them
			// as names for new tasks for the todo list.
			for(int i = 2; argv[i] != NULL; i++) {
				todo_add(&td, TASK_TODO, argv[i]);
			}
			todo_save(&td, todo_file);
			politely_exit(0);
		case CM_REMOVE:
			// rm command: iterates over its arguments, using them as
			// indexes for tasks to remove.
			for(int i = 2; argv[i] != NULL; i++) {
				int n;
				int index;
				n = sscanf(argv[i], "%d", &index);
				if(n == EOF) {
					eprintf("Arguments to rm must be numeric\n");
					politely_exit(65);
				}
				if(index <= 0) {
					eprintf("Task indexes start from 1\n");
					politely_exit(65);
				}
				if((uint) index > td.count) {
					eprintf("The maximum task index at the moment is %d\n", td.count);
					politely_exit(65);
				}
				todo_rm(&td, index - 1);
			}
			todo_save(&td, todo_file);
			politely_exit(0);
		case CM_CHECK:
			// check command: iterates over its arguments, using them
			// as indexes for tasks to mark as done.
			for(int i = 2; argv[i] != NULL; i++) {
				int n;
				int index;
				n = sscanf(argv[i], "%d", &index);
				if(n == EOF) {
					eprintf("Arguments to check must be numeric\n");
					politely_exit(65);
				}
				if(index <= 0) {
					eprintf("Task indexes start from 1\n");
					politely_exit(65);
				}
				if((uint) index > td.count) {
					eprintf("The maximum task index at the moment is %d\n", td.count);
					politely_exit(65);
				}
				todo_set_state(&td, index - 1, TASK_DONE);
			}
			todo_save(&td, todo_file);
			politely_exit(0);
		case CM_ERROR:
			// Stupid user error
			eprintf("Unrecognized command\n\n");
			usage(argv[0]);
			politely_exit(64);
		default:
			// Stupid programmer error
			eprintf("Unhandled command: %d\n", cm);
			politely_exit(1024);
	}

	todo_save(&td, todo_file);
	politely_exit(0);
}

void todo_save(Todo_list *td, FILE *todo_file)
{
	todo_file = freopen(NULL, "w", todo_file);
	if(todo_file == NULL) {
		eprintf("Could not save changes to the TODO file\n"
				"Perhaps you don't have write permissions on it?\n");
		todo_free(td);
		exit(1);
	}
	todo_write_file(td, todo_file);
}

// Prints usage text
void usage(const char *name)
{
	const char usage_text[] = 
		"usage: %s <command>\n\n"
		"List of commands:\n\n"
		"help:  prints this usage text and exits\n"
		"add:   adds new tasks to the todo list\n"
		"rm:    removes tasks from the todo list\n"
		"check: marks tasks as done\n"
		"\nIf no command is given, the todo list is printed to stdout.\n";
	eprintf(usage_text, name);
}
