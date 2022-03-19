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

#include "parse.h"

static Cm_type parse_keyword(const char *text, int i, const char *rest, Cm_type ct)
{
    if(text[i + 1] == '\0') return ct;
    else if(strcmp(&text[i + 1], rest) == 0) return ct;
    else return CM_ERROR;
}

// Parse a string as a todo command
Cm_type parse(const char *text)
{
    for(int i = 0; text[i] != '\0'; i++) {
        switch(text[i]) {
            case 'h': return parse_keyword(text, i, "elp", CM_HELP);
            case 'e': return parse_keyword(text, i, "xit", CM_EXIT);
            default:  return CM_ERROR;
        }
    }

    return CM_ERROR;
}
