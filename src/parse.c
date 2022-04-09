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

#include <string.h>

#include "common.h"
#include "parse.h"

static const char *arg;

// Check if arg is a short command starting with `ch`
static bool check_short(char ch)
{
    // Don't this right now, but I might eventually
    return arg[0] == ch && arg[1] == '\0';
}

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

// Does what it promises
Command parse_command(const char *argv1)
{
    arg = argv1;

    if(arg == NULL)            return CM_NONE;
    if(check_command("help"))  return CM_HELP;
    if(check_command("add"))   return CM_ADD;
    if(check_command("check")) return CM_CHECK;

    return CM_ERROR;
}
