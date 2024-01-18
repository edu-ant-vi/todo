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

// This module defines the valid subcommands for todo,
// along with a parse function to recognize them.

#ifndef TODO_PARSE_H
#define TODO_PARSE_H

typedef enum {
    CM_NONE = 0,
    CM_HELP,
    CM_ADD,
    CM_REMOVE,
    CM_CHECK,
    CM_UNCHECK,
    CM_WORK_ON,

    CM_ERROR,
    NUM_COMMANDS,
} Command;

// Parse subcommand
Command parse(const char *argv1);

#endif // TODO_PARSE_H
