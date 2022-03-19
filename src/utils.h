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

// Small utility functions

#ifndef TODO_UTILS_H
#define TODO_UTILS_H

#include <stdbool.h>

// A yes-or-no prompt
bool yorn(const char* prompt);

// Get a line of input from stdin
void get_line(char *buf, int buf_size);

#endif // TODO_UTILS_H
