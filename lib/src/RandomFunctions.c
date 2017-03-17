 /********************
 *  RandomFunctions.c
 *
 * This file is part of EduDS data structure library which is licensed under
 * the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#include <stdlib.h>
#include <math.h>
#include "RandomFunctions.h"

#define SFMT_MEXP 19937
#include "SFMT.h"


void *RandomState_init(unsigned int seed,
                       EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;
    sfmt_t *sfmt_state;

    sfmt_state = malloc(sizeof(sfmt_t));

    if (sfmt_state)
        sfmt_init_gen_rand(sfmt_state, (seed) ? seed : EDUDS_SALT);
    else
        tmp_err = EDS_MALLOC_FAIL;

    SAVE_ERR(err, tmp_err);

    return (void*)sfmt_state;
}

unsigned int RandomState_genUInt(void *state,
                                 EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;
    unsigned int ret = 0;
    sfmt_t *sfmt_state = (state) ? (sfmt_t*)state : NULL;

    if (sfmt_state)
        ret = (unsigned int)sfmt_genrand_uint32(sfmt_state);
    else
        tmp_err = EDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return ret;
}

int RandomState_genInt(void *state,
                       EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;
    int ret = 0;
    sfmt_t *sfmt_state = (state) ? (sfmt_t*)state : NULL;

    if (sfmt_state)
        ret = (int)sfmt_genrand_uint32(sfmt_state);
    else
        tmp_err = EDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return ret;
}

void RandomState_destroy(void **state,
                         EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;
    sfmt_t **sfmt_state = (state) ? (sfmt_t**)state : NULL;

    if (sfmt_state && *sfmt_state) {
        free(*sfmt_state);
        *sfmt_state = NULL;
    } else
        tmp_err = EDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}
