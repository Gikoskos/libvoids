 /********************
 *  MemoryAllocation.h
 *
 * This file is part of EduDS data structure library which is licensed under
 * the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#ifndef __EduDS_MEMORYALLOCATION_H
#define __EduDS_MEMORYALLOCATION_H


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"


EduDS_LOCAL void *EdsMalloc(size_t size);

EduDS_LOCAL void EdsFree(void *ptr);

EduDS_LOCAL void *EdsCalloc(size_t nmemb, size_t size);

EduDS_LOCAL void *EdsRealloc(void *ptr, size_t size);

#ifdef __cplusplus
}
#endif

#endif //__EduDS_MEMORYALLOCATION_H
