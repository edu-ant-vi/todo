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

// This module defines how todo is configured.

#ifndef TODO_CONFIG_H
#define TODO_CONFIG_H

#include "common.h"

typedef struct {
	char filename[16];
	bool ascii_only;
	bool quiet;
	bool help;
	bool version;
} Config;

// Generate config from env variables and CLI options
// Return the index of the first non-option argument
int configure(Config *conf, int argc, char *argv[]);

#endif // TODO_CONFIG_H
