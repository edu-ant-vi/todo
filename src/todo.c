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

// Necessary for strndup function
#define _POSIX_C_SOURCE 200810L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "todo.h"

// Initialize todo list
void todo_init(Todo_list *td)
{
    td->count = 0;
    td->capacity = 8;
    td->tasks = (Task*) calloc(8, sizeof(Task));
}

// Add task to todo list and return its index on it
int todo_add(Todo_list *td, Task_state ts, const char *name)
{
    if(td->capacity < td->count + 1) {
        td->capacity *= 2;
        td->tasks = 
            realloc(td->tasks, td->capacity * sizeof(Task));
    }
    Task t;
    t.state = ts;
    t.name = strndup(name, 256);
    td->tasks[td->count] = t;
    return td->count++;
}

// Remove task from todo list by its index
void todo_rm(Todo_list *td, int task_index)
{
    if(task_index < td->count - 1)
        for(int i = td->count - 1; i > task_index; i--)
            td->tasks[i - 1] = td->tasks[i];
    td->count--;
}

// Free todo list
void todo_free(Todo_list *td)
{
    for(int i = 0; i < td->count; i++) {
        free(td->tasks[td->count].name);
    }
    free(td->tasks);
    td->count = 0;
    td->capacity = 0;
    td->tasks = NULL;
}

// Print todo list in readable format
void todo_print(Todo_list *td)
{
    printf("=== TODO ===\n");

    if(td->count == 0) {
        printf("No tasks. Rejoice!\n");
        return;
    }

    for(int i = 0; i < td->count; i++) {
        switch(td->tasks[i].state) {
            case TASK_TODO:
                printf("[ ] ");
                break;
            case TASK_DONE:
                printf("[✓] ");
                break;
            default:
                // Should never happen
                fprintf(stderr, "Unrecognized task state\n");
                exit(16);
        }
        printf("%s\n", td->tasks[i].name);
    }
    printf("\n");
}

// Write todo list to file
void todo_write_file(Todo_list *td, FILE *file)
{
    for(int i = 0; i < td->count; i++) {
        switch(td->tasks[i].state) {
            case TASK_TODO:
                fprintf(file, "t,");
                break;
            case TASK_DONE:
                fprintf(file, "d,");
                break;
            default:
                fprintf(file, "?,");
        }
        fprintf(file, "%s\n", td->tasks[i].name);
    }
}

// Read todo list from file
void todo_read_file(Todo_list *td, FILE *file)
{
    int i;
    Task_state ts;
    char ch, name[256];
    do {
        i = fscanf(file, "%c,%[^\n]\n", &ch, name);
        switch(ch) {
            case 't': ts = TASK_TODO; break;
            case 'd': ts = TASK_DONE; break;
            default:
                // Should never happen
                fprintf(stderr, "Malformed TODO file!\n");
                exit(33);
        }
        todo_add(td, ts, name);
    } while(i != EOF);
}
