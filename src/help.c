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

#include <stdio.h>

#include "common.h"
#include "help.h"
#include "commands.h"

// Print usage text for todo
void usage(const char *name)
{
	const char usage_text[] = 
		"usage: %s <command>\n\n"
		"List of commands:\n\n"
		"help: prints this usage text and exits\n"
		"add: adds new tasks to the todo list\n"
		"rm: removes tasks from the todo list\n"
		"check: marks tasks as done\n"
		"uncheck: marks tasks as todo again\n"
		"work-on: marks tasks as work-in-progress\n"
		"\nIf no command is given, the todo list is printed to stdout.\n"
		"Note that there may only be one work-in-progress task at any given moment.\n";
	eprintf(usage_text, name);
}
