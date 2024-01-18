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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "config.h"
#include "commands.h"
#include "common.h"
#include "help.h"

// Get default config
static void default_config(Config *conf)
{
    conf->quiet = false;
    conf->help = false;
    conf->version = false;
    conf->ascii_only = false;
    strcpy(conf->filename, "TODO");
    conf->comm = CM_NONE;
}

// Generate config from env variables and CLI options
void read_config(Config *conf, int argc, char *argv[])
{
    default_config(conf);

    // Look up the environment variables
    const char *filename = getenv("TODO_FILENAME");
    if(filename != NULL) {
        strncpy(conf->filename, filename, 15);
        conf->filename[15] = '\0';
    }

    if(getenv("TODO_ASCII_ONLY") != NULL)
        conf->ascii_only = true;

    if(getenv("TODO_QUIET") != NULL)
        conf->quiet = true;

    // Look up the CLI options
    int opt = 0, longindex;
    const char short_opts[] = ":qhf:";
    struct option long_opts[] = {
        { "quiet",     no_argument,       0, 'q' },
        { "file-name", required_argument, 0, 'f' },
        { "help",      no_argument,       0, 'h' },
        { "version",   no_argument,       0, 'v' },
        { 0,           0,                 0,  0  },
    };

    while(1) {
        opt = getopt_long(argc, argv, short_opts, long_opts, &longindex);
        if(opt == -1) break;
        switch(opt) {
            case 'q':
                conf->quiet = true;
                break;
            case 'f':
                strncpy(conf->filename, optarg, 15);
                conf->filename[15] = '\0';
                break;
            case 'h':
                conf->help = true;
                break;
            case 'v':
                conf->version = true;
                break;
            case '?':
                eprintf("Unrecognized option %s\n", argv[optind - 1]);
                usage(argv[0]);
                exit(1);
                break;
            case ':':
                eprintf("Option %s requires an argument\n", argv[optind - 1]);
                usage(argv[0]);
                exit(2);
                break;
        }
    }
    // Parse subcommands
    conf->comm = parse(argv[optind]);
    if(conf->comm == CM_ERROR) {
        eprintf("Unrecognized command %s\n", argv[optind]);
        usage(argv[0]);
        exit(3);
    }
    conf->args_ind = optind + 1;
}
