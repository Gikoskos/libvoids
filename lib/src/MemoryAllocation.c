 /********************
 *  MemoryAllocation.c
 *
 * This file is part of libvoids which is licensed under the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#include <stdlib.h>
#include "MemoryAllocation.h"


void *VdsMalloc(size_t size)
{
    return malloc(size);
}

void VdsFree(void *ptr)
{
    free(ptr);
}

void *VdsCalloc(size_t nmemb, size_t size)
{
    return calloc(nmemb, size);
}

void *VdsRealloc(void *ptr, size_t size)
{
    return realloc(ptr, size);
}
