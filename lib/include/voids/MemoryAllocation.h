 /********************
 *  MemoryAllocation.h
 *
 * This file is part of libvoids which is licensed under the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#ifndef VOIDS_MEMORYALLOCATION_H__
#define VOIDS_MEMORYALLOCATION_H__


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"


VOIDS_LOCAL void *VdsMalloc(size_t size);

VOIDS_LOCAL void VdsFree(void *ptr);

VOIDS_LOCAL void *VdsCalloc(size_t nmemb, size_t size);

VOIDS_LOCAL void *VdsRealloc(void *ptr, size_t size);

#ifdef __cplusplus
}
#endif

#endif //VOIDS_MEMORYALLOCATION_H__
