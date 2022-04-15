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

// Handlers are the functions responsible for carrying out
// the individual commands passed to the program. They have
// a uniform signature, accepting a todo list and a list
// of the arguments given to them. They return a handler
// result, which indicates to the main function how the
// execution of the handler went.

// My plan is to put all handlers in an array in the future.

#ifndef TODO_HANDLER_H
#define TODO_HANDLER_H

#include <stdio.h>

#include "common.h"
#include "todo.h"

typedef enum {
	HANDLER_OK,
	HANDLER_OK_SAVE_CHANGES,

	HANDLER_ERROR_USAGE,
	HANDLER_ERROR_PROGRAMMER,
	HANDLER_ERROR_INVALID_NUMERIC_ARGS,
	HANDLER_ERROR_INDEX_TOO_LOW,
	HANDLER_ERROR_INDEX_TOO_HIGH,
} Handler_res;

typedef Handler_res (*Handler)(Todo_list*, char**);

Handler_res none_handler(Todo_list *td, char *args[]);

Handler_res help_handler(Todo_list *td, char *args[]);

Handler_res add_handler(Todo_list *td, char *args[]);

Handler_res rm_handler(Todo_list *td, char *args[]);

Handler_res check_handler(Todo_list *td, char *args[]);

Handler_res uncheck_handler(Todo_list *td, char *args[]);

Handler_res work_on_handler(Todo_list *td, char *args[]);

Handler_res error_handler(Todo_list *td, char *args[]);

#endif // TODO_HANDLER_H
