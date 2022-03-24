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
#include <stdbool.h>

#include "todo.h"
#include "utils.h"

void usage(const char *name);

int main(int argc, char **argv)
{
	if(argc != 1) usage(argv[0]);

	bool create = yorn("No todo list found. Create one?");

	if(create) {
		Todo_list td;
		todo_init(&td);
		todo_print(&td);
	}

	printf("Ok, exiting...\n");
	return 0;
}

void usage(const char *name)
{
	fprintf(stderr, "usage: %s\n", name);
	exit(1);
}
