 /********************
 *  RandomState.h
 *
 * This file is part of EduDS data structure library which is licensed under
 * the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#ifndef EduDS_RANDOMSTATE_H__
#define EduDS_RANDOMSTATE_H__


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"


//I keep the PRNG types and API as opaque as possible, so that if someone
//wants to replace it with their own implementation they won't have to change
//code in the data structures, just the implementations in RandomFunctions.c


EduDS_LOCAL void *RandomState_init(unsigned int seed, EdsErrCode *err);

EduDS_LOCAL unsigned int RandomState_genUInt(void *state, EdsErrCode *err);

EduDS_LOCAL int RandomState_genInt(void *state, EdsErrCode *err);

EduDS_LOCAL void RandomState_destroy(void **state, EdsErrCode *err);

#ifdef __cplusplus
}
#endif

#endif //EduDS_RANDOMSTATE_H__
