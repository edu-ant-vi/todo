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
#include <string.h>

#include "common.h"
#include "config.h"

// Get default config
static void default_config(Config *conf)
{
    strcpy(conf->filename, "TODO");
    conf->ascii_only = false;
    conf->quiet = false;
}

// Generate config from env variables
void configure(Config *conf)
{
    default_config(conf);
    
    const char *filename = getenv("TODO_FILENAME");
    if(filename != NULL && strlen(filename) <= 15)
        strncpy(conf->filename, filename, 16);

    if(getenv("TODO_ASCII_ONLY") != NULL)
        conf->ascii_only = true;

    if(getenv("TODO_QUIET") != NULL)
        conf->quiet = true;
}
