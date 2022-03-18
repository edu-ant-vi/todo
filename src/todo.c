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

#include "todo.h"

void todo_init(Todo_list *td)
{
    td->count = 0;
    td->capacity = 8;
    td->tasks = (Task*) calloc(sizeof(Task), 8);
}

int todo_add(Todo_list *td, Task_state st, const char *name)
{
    if(td->capacity < td->count + 1) {
        td->capacity *= 2;
        td->tasks = 
            realloc(td->tasks, td->capacity * sizeof(Task));
    }
    Task t = { .state = st, .name = name };
    td->tasks[td->count] = t;
    return td->count++;
}

void todo_rm(Todo_list *td, int task_index)
{
    if(task_index < td->count - 1)
        for(int i = td->count - 1; i > task_index; i--)
            td->tasks[i - 1] = td->tasks[i];
    td->count--;
}

void todo_free(Todo_list *td)
{
    free(td->tasks);
    td->count = 0;
    td->capacity = 0;
    td->tasks = NULL;
}
