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
#include <string.h>

#include "todo.h"

void usage(const char *name);

int main(int argc, char **argv)
{
	const char todo_filename[] = "TODO";

	Todo_list td;
	todo_init(&td);
	FILE *todo_file = fopen(todo_filename, "a+");
	if(todo_file == NULL) {
		fprintf(stderr, "Could not access or create todo file\n");
		return 2;
	}
	todo_read_file(&td, todo_file);

	if(argc == 1) {
		todo_print(&td);
		todo_free(&td);
		return 0;
	}

	if(strcmp(argv[1], "add") == 0) {
		for(int i = 2; argv[i] != NULL; i++) {
			todo_add(&td, TASK_TODO, argv[i]);
		}
		todo_write_file(&td, todo_file);
		todo_free(&td);
		return 0;
	}

	todo_free(&td);
	return 0;
}

void usage(const char *name)
{
	// TODO update usage text
	fprintf(stderr, "usage: %s\n", name);
}
