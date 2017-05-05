 /********************
 *  HashFunctions.h
 *
 * This file is part of EduDS data structure library which is licensed under
 * the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#ifndef EduDS_H__ASHFUNCTIONS_H__
#define EduDS_H__ASHFUNCTIONS_H__


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"
#include "AssociationList.h"

EduDS_API size_t HashCode(const void *pKey, size_t key_size);

EduDS_API size_t HashDiv(size_t key_hash, size_t array_len);

EduDS_API size_t HashMult(size_t key_hash, size_t array_len);

#ifdef __cplusplus
}
#endif

#endif //EduDS_H__ASHFUNCTIONS_H__
