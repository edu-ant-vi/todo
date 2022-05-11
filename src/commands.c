/*
   Copyright 2022 Eduardo Antunes dos Santos Vieira

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

#include <string.h>

#include "common.h"
#include "commands.h"

char command[NUM_COMMANDS - 1][8] = {
    [CM_HELP]    = "help",
    [CM_ADD]     = "add",
    [CM_REMOVE]  = "rm",
    [CM_CHECK]   = "check",
    [CM_UNCHECK] = "uncheck",
    [CM_WORK_ON] = "work-on",
};

static const char *arg;

// Check if arg is a long command that ends with `rest`
static bool check_long(const char *rest)
{
    return strcmp(&arg[1], rest) == 0;
}

// Check if arg is the command `command`
static bool check_command(const char *command)
{
    if(arg[0] == command[0]) {
        if(arg[1] == '\0') {
            return true;
        } else {
            return check_long(&command[1]);
        }
    }
    return false;
}

// Parse subcommand
Command parse(const char *argv1)
{
    arg = argv1;

    if(arg == NULL) return CM_NONE;

    for(int i = 1; i < NUM_COMMANDS - 1; i++)
        if(check_command(command[i]))
            return i;

    return CM_ERROR;
}
