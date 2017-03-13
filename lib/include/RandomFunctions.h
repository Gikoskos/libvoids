 /********************
 *  RandomFunctions.h
 *
 * This file is part of EduDS data structure library which is licensed under
 * the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#ifndef __EduDS_RANDOMFUNCTIONS_H
#define __EduDS_RANDOMFUNCTIONS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"


//I keep the PRNG types and API as opaque as possible, so that if someone
//wants to replace it with their own implementation they won't have to change
//code in the data structures, just the implementations in RandomFunctions.c
typedef void *EdsRandType;


EduDS_API EdsRandType *RandomState_init(unsigned int seed, EdsErrCode *err);

EduDS_API unsigned int RandomState_genUInt(EdsRandType state, EdsErrCode *err);

EduDS_API int RandomState_genInt(EdsRandType state, EdsErrCode *err);

EduDS_API void RandomState_destroy(EdsRandType *state, EdsErrCode *err);

#ifdef __cplusplus
}
#endif

#endif //__EduDS_HASHFUNCTIONS_H
