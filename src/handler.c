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
#include "todo.h"

Handler_res help_handler(Todo_list *td, char **args)
{
	eprintf("Manage todo lists from the command line.\n\n");
	usage(args[0]);
	return HANDLER_OK;
}

Handler_res add_handler(Todo_list *td, char **args)
{
	FOR_EACH(i, args) {
		todo_add(td, TASK_TODO, args[i]);
	}
	return HANDLER_OK_SAVE_CHANGES;
}

Handler_res rm_handler(Todo_list *td, char **args)
{
	int n, index;
	FOR_EACH(i, args) {
		n = sscanf(args[i], "%d", &index);
		if(n == EOF) 
			return HANDLER_ERROR_INVALID_NUMERIC_ARGS;
		if(index <= 0) 
			return HANDLER_ERROR_INDEX_TOO_LOW;
		if((uint) index > td->count) 
			return HANDLER_ERROR_INDEX_TOO_HIGH;
		todo_rm(td, index - 1);
	}
	return HANDLER_OK_SAVE_CHANGES;
}

Handler_res check_handler(Todo_list *td, char **args)
{
	int n, index;
	FOR_EACH(i, args) {
		n = sscanf(args[i], "%d", &index);
		if(n == EOF) 
			return HANDLER_ERROR_INVALID_NUMERIC_ARGS;
		if(index <= 0) 
			return HANDLER_ERROR_INDEX_TOO_LOW;
		if((uint) index > td->count) 
			return HANDLER_ERROR_INDEX_TOO_HIGH;
		todo_set_state(td, index - 1, TASK_DONE);
	}
	return HANDLER_OK_SAVE_CHANGES;
}
