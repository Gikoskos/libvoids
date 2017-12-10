 /********************
 *  RandomState.c
 *
 * This file is part of libvoids which is licensed under the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#include "MemoryAllocation.h"
#include <math.h>
#include "RandomState.h"

#define SFMT_MEXP 19937
#include "SFMT.h"


void *RandomState_init(unsigned int seed,
                       vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    sfmt_t *sfmt_state;

    sfmt_state = VdsMalloc(sizeof(sfmt_t));

    if (sfmt_state)
        sfmt_init_gen_rand(sfmt_state, (seed) ? seed : VOIDS_SALT);
    else
        tmp_err = VDS_MALLOC_FAIL;

    SAVE_ERR(err, tmp_err);

    return (void*)sfmt_state;
}

unsigned int RandomState_genUInt(void *state,
                                 vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    unsigned int ret = 0;
    sfmt_t *sfmt_state = (state) ? (sfmt_t*)state : NULL;

    if (sfmt_state)
        ret = (unsigned int)sfmt_genrand_uint32(sfmt_state);
    else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return ret;
}

int RandomState_genInt(void *state,
                       vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    int ret = 0;
    sfmt_t *sfmt_state = (state) ? (sfmt_t*)state : NULL;

    if (sfmt_state)
        ret = (int)sfmt_genrand_uint32(sfmt_state);
    else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return ret;
}

void RandomState_destroy(void **state,
                         vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    sfmt_t **sfmt_state = (state) ? (sfmt_t**)state : NULL;

    if (sfmt_state && *sfmt_state) {
        VdsFree(*sfmt_state);
        *sfmt_state = NULL;
    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}
