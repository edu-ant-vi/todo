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
void usage(const char *exec)
{
	const char usage_text[] = 
		"usage %s <command>\n\n"
		"List of commands:\n\n"
		"h, help       print this usage text\n"
		"a, add        add new tasks to the todo list\n"
		"r, rm         remove tasks from the todo list\n"
		"c, check      mark tasks as done\n"
		"u, uncheck    mark tasks as todo again\n"
		"w, work-on    mark tasks as work-in-progress\n"
		"\nIf no command is given, the todo list is printed to stdout.\n"
		"Note that there may only be one work-in-progress task at any given moment.\n";
	eprintf(usage_text, exec);
}

// Print help for an specific command
bool help(const char *exec, Command c)
{
	switch(c) {
		case CM_NONE: 
			// Should never happen
			break;
		case CM_HELP: 
			printf("Show how to use a given command.\n\n"
				   "usage: %s help [command]\n\n"
				   "If no command is given, todo's general usage text is shown.\n",
				   exec);
			break;
		case CM_ADD: 
			printf("Add tasks to the todo list.\n\n"
				   "usage: %s add [task-name...]\n",
				   exec);
			break;
		case CM_REMOVE: 
			printf("Remove tasks from the todo list.\n\n"
				   "usage: %s rm [task-index...]\n",
				   exec);
			break;
		case CM_CHECK: 
			printf("Mark tasks as done.\n\n"
				   "usage: %s check [task-index...]\n",
				   exec);
			break;
		case CM_UNCHECK: 
			printf("Mask tasks as todo again.\n\n"
				   "usage: %s uncheck [tasks-index...]\n",
				   exec);
			break;
		case CM_WORK_ON: 
			printf("Mark tasks as work-in-progress.\n\n"
				   "usage: %s work-on [task-index...]\n\n"
				   "Note that there may only be one work-in-progress task per todo"
				   " list. If there is already a work-in-progress task in the "
				   "current todo list when this command is used, it will mark that"
				   " task as done. This means that, if multiple arguments are given"
				   " to it, it will mark all given tasks but the last as complete.\n",
				   exec);
			break;
		default:
			return false;
	}
	return true;
}
