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

// This module defines how todo is configured.

#ifndef TODO_CONFIG_H
#define TODO_CONFIG_H

#include "commands.h"
#include "common.h"

typedef struct {
	bool quiet;
	bool help;
	bool version;
	bool ascii_only;
	char filename[16];
	int args_ind;
	Command comm;
} Config;

// Generate config from env variables and CLI options
void read_config(Config *conf, int argc, char *argv[]);

#endif // TODO_CONFIG_H
