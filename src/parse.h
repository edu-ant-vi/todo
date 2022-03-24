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

#ifndef TODO_PARSE_H
#define TODO_PARSE_H

typedef enum {
    CM_HELP,
    CM_QUIT,
    CM_ERROR,
} Cm_type;

typedef struct {
    Cm_type type;
    union {
        char string[256];
        unsigned long number;
    } arg;
} Command;

typedef struct {
    const char *text;
    int offset;
} Parser;

// Parse a string as a command
Command parse(const char *text);

#endif // TODO_PARSE_H
