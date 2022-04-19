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
#include <getopt.h>

#include "common.h"
#include "config.h"

// Get default config
static void default_config(Config *conf)
{
    strcpy(conf->filename, "TODO");
    conf->ascii_only = false;
    conf->quiet = false;
    conf->help = false;
    conf->version = false;
}

// Generate config from env variables and CLI options
// Return the index of the first non-option argument
int configure(Config *conf, int argc, char *argv[])
{
    default_config(conf);
    
    // Look up the environment variables
    const char *filename = getenv("TODO_FILENAME");
    if(filename != NULL && strlen(filename) <= 15)
        strncpy(conf->filename, filename, 16);

    if(getenv("TODO_ASCII_ONLY") != NULL)
        conf->ascii_only = true;

    if(getenv("TODO_QUIET") != NULL)
        conf->quiet = true;

    // Look up the CLI options
    int opt = 0, longindex;
    const char short_opts[] = "qhf:";
    struct option long_opts[] = {
        { "quiet",     no_argument,       0, 'q' },
        { "file-name", required_argument, 0, 'f' },
        { "help",      no_argument,       0, 'h' },
        { "version",   no_argument,       0, 'v' },
        { 0,           0,                 0,  0  },
    };

    while(true) {
        opt = getopt_long(argc, argv, short_opts, long_opts, &longindex);
        if(opt == -1) break;

        switch(opt) {
            case 'q':
                conf->quiet = true;
                break;
            case 'f':
                strncpy(conf->filename, optarg, 16);
                break;
            case 'h':
                conf->help = true;
                break;
            case 'v':
                conf->version = true;
                break;
            case '?':
                return -1;
        }
    }

    return optind;
}
