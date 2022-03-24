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

// Abstract data types for the todo app. Those include the
// todo list and task structures.

#ifndef TODO_LIB_H
#define TODO_LIB_H

typedef enum {
    TASK_TODO,
    TASK_DONE,
} Task_state;

typedef struct {
    Task_state state;
    const char *name;
} Task;

// Todo list = dynamic array of tasks
typedef struct {
    int count;
    int capacity;
    Task *tasks;
} Todo_list;

// Initialize todo list
void todo_init(Todo_list *td);

// Add task to todo list and return its index on it
int todo_add(Todo_list *td, Task_state st, const char *name);

// Remove task from todo list by its index
void todo_rm(Todo_list *td, int task_index);

// Free todo list
void todo_free(Todo_list *td);

// Print todo list in readable format
void todo_print(Todo_list *td);

#endif // TODO_LIB_H
