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

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "parse.h"

static Parser parser;

static bool is_whitespace(char ch)
{
    return ch == ' ' || ch == '\t';
}

static bool is_digit(char ch)
{
    return ch >= '0' && ch <= '9';
}

static char advance()
{
    return parser.text[parser.offset++];
}

static char peek()
{
    return parser.text[parser.offset];
}

static bool at_end()
{
    return parser.text[parser.offset] == '\0';
}

static const char *remaining_text()
{
    return &parser.text[parser.offset];
}

static Cm_type parse_keyword(const char *expected, Cm_type ct)
{
    if(is_whitespace(peek()) || at_end()) {
        advance();
        return ct;
    }
    else if(strncmp(remaining_text(), expected, strlen(expected)) == 0) {
        for(unsigned long i = 0; i < strlen(expected); i++) advance();
        advance();
        return ct;
    }
    else return CM_ERROR;
}

// Surprisingly, this works. It just needs some refactoring and polishment now.

Command parse(const char *text)
{
    parser.text = text;
    parser.offset = 0;

    Command cm;

    while(is_whitespace(peek())) {
        advance();
    }

    switch(advance()) {
        case 'h': cm.type = parse_keyword("elp", CM_HELP); break;
        case 'q': cm.type = parse_keyword("uit", CM_QUIT); break;
        default:  cm.type = CM_ERROR;
    }

    if(cm.type == CM_ERROR) {
        strcpy(cm.arg.string, "Parsing error");
        return cm;
    }

    char ch = advance();
    if(ch == '"') {
        int size;
        for(size = 0; parser.text[parser.offset + size] != '"'; size++) {
            if(at_end()) {
                cm.type = CM_ERROR;
                strcpy(cm.arg.string, "Unterminated string");
            }
        }
        strncpy(cm.arg.string, remaining_text(), size - 1);
    } else if(is_digit(ch)) {
        cm.arg.number = strtoul(remaining_text(), NULL, 10);
    }

    return cm;
}
