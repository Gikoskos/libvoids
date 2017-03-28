 /********************
 *  MemoryAllocation.c
 *
 * This file is part of EduDS data structure library which is licensed under
 * the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#include <stdlib.h>
#include "MemoryAllocation.h"


void *EdsMalloc(size_t size)
{
    return malloc(size);
}

void EdsFree(void *ptr)
{
    free(ptr);
}

void *EdsCalloc(size_t nmemb, size_t size)
{
    return calloc(nmemb, size);
}

void *EdsRealloc(void *ptr, size_t size)
{
    return realloc(ptr, size);
}
