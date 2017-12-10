 /********************
 *  RingBuffer.c
 *
 * This file is part of libvoids which is licensed under the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#include "MemoryAllocation.h"
#include "RingBuffer.h"


RingBuffer *RingBuffer_init(size_t buff_size,
                            vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    RingBuffer *cBuffNew = NULL;

    if (buff_size) {

        cBuffNew = EdsCalloc(1, sizeof(RingBuffer));

        if (cBuffNew) {

            cBuffNew->buff = VdsMalloc(sizeof(void*) * buff_size);

            if (cBuffNew->buff) {
                cBuffNew->size = buff_size;
            } else {
                VdsFree(cBuffNew);
                cBuffNew = NULL;
                tmp_err = VDS_MALLOC_FAIL;
            }

        } else
            tmp_err = VDS_MALLOC_FAIL;

    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return cBuffNew;
}

void RingBuffer_resize(RingBuffer **cBuff,
                       size_t new_size,
                       vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;

    if (new_size) {

        if (cBuff) {

            if (*cBuff) {

                //can only resize to a bigger buffer for now
                if ((*cBuff)->size < new_size) {
                    void **tmp_buff = VdsRealloc((*cBuff)->buff, sizeof(void*) * new_size);

                    if (tmp_buff) {
                        (*cBuff)->buff = tmp_buff;
                        (*cBuff)->size = new_size;
                    } else {
                        tmp_err = VDS_MALLOC_FAIL;
                    }
                }

            } else {
                *cBuff = RingBuffer_init(new_size, err);
            }

        } else
            tmp_err = VDS_INVALID_ARGS;

    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}

void RingBuffer_write(RingBuffer *cBuff,
                      void *pData,
                      vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;

    if (cBuff) {

        if (cBuff->available < cBuff->size) {
            cBuff->buff[cBuff->write] = pData;

            cBuff->write++;
            if (cBuff->write >= cBuff->size)
                cBuff->write = 0;

            cBuff->available++;
        } else
            tmp_err = VDS_BUFFER_FULL;

    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}

void *RingBuffer_read(RingBuffer *cBuff,
                      vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    void *pData = NULL;

    if (cBuff) {

        if (cBuff->available) {
            pData = cBuff->buff[cBuff->read];

            cBuff->available--;
            cBuff->read++;
            if (cBuff->read >= cBuff->size)
                cBuff->read = 0;
        }

    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return pData;
}

void RingBuffer_destroy(RingBuffer **cBuff,
                        vdsUserDataFunc freeData,
                        vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;

    if (cBuff) {

        if (*cBuff) {

            if (freeData) {
                for (size_t i = 0; i <= (*cBuff)->size; i++)
                    freeData((*cBuff)->buff[i]);
            }

            VdsFree((*cBuff)->buff);
            VdsFree(*cBuff);

            *cBuff = NULL;

        } else
            tmp_err = VDS_INVALID_ARGS;
    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}
