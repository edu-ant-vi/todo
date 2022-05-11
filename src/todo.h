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

// Abstract data types for the todo app. Those include the
// todo list and task structures.

#ifndef TODO_LIB_H
#define TODO_LIB_H

#include <stdio.h>

#include "common.h"

typedef enum {
    TASK_TODO,
    TASK_WIP,
    TASK_DONE,
    TASK_HOLE,  // makes the remove operation simpler
} Task_state;

typedef struct {
    Task_state state;
    char name[256];
} Task;

// Todo list = dynamic array of tasks
typedef struct {
    uint count;
    uint capacity;
    Task *tasks;
} Todo_list;

// Initialize todo list
void todo_init(Todo_list *td);

// Add task to todo list and return its index on it
uint todo_add(Todo_list *td, Task_state ts, const char *name);

// Set the state of a task by its index
void todo_set_state(Todo_list *td, uint task_index, Task_state ts);

// Remove task from todo list by its index
#define todo_rm(td, task_index) \
    todo_set_state(td, task_index, TASK_HOLE)

// Free todo list
void todo_free(Todo_list *td);

// Print todo list in readable format
void todo_print(Todo_list *td, bool ascii_only);

// Write todo list to file
void todo_write_file(Todo_list *td, FILE *file);

// Read todo list from file
void todo_read_file(Todo_list *td, FILE *file);

#endif // TODO_LIB_H
