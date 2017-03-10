/***********************************************\
*                  RingBuffer.c                 *
*           George Koskeridis (C) 2017          *
\***********************************************/

#include <stdlib.h>
#include <stdint.h> //for SIZE_MAX
#include "RingBuffer.h"


RingBuffer *RingBuffer_init(size_t buff_size,
                            EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;
    RingBuffer *cBuffNew = NULL;

    if (buff_size) {

        cBuffNew = calloc(1, sizeof(RingBuffer));

        if (cBuffNew) {

            cBuffNew->buff = malloc(sizeof(void*) * buff_size);

            if (cBuffNew->buff) {
                cBuffNew->size = buff_size;
            } else {
                free(cBuffNew);
                cBuffNew = NULL;
                tmp_err = EduDS_MALLOC_FAIL;
            }

        } else
            tmp_err = EduDS_MALLOC_FAIL;

    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return cBuffNew;
}

void RingBuffer_resize(RingBuffer **cBuff,
                       size_t new_size,
                       EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;

    if (new_size) {

        if (cBuff) {

            if (*cBuff) {

                //@FIXME: can only resize to a bigger buffer for now
                if ((*cBuff)->size < new_size) {
                    void **tmp_buff = realloc((*cBuff)->buff, sizeof(void*) * new_size);

                    if (tmp_buff) {
                        (*cBuff)->buff = tmp_buff;
                        (*cBuff)->size = new_size;
                    } else {
                        tmp_err = EduDS_MALLOC_FAIL;
                    }
                }

            } else {
                *cBuff = RingBuffer_init(new_size, err);
            }

        } else
            tmp_err = EduDS_INVALID_ARGS;

    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}

void RingBuffer_write(RingBuffer *cBuff,
                      void *pData,
                      EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;

    if (cBuff) {

        cBuff->buff[cBuff->write] = pData;

        cBuff->write++;
        if (cBuff->write >= cBuff->size)
            cBuff->write = 0;

        //prevent overflow
        if (cBuff->available < SIZE_MAX)
            cBuff->available++;
    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}

void *RingBuffer_read(RingBuffer *cBuff,
                      EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;
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
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return pData;
}

void RingBuffer_destroy(RingBuffer **cBuff,
                        UserDataCallback freeData,
                        EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;

    if (cBuff) {

        if (*cBuff) {

            if (freeData) {
                for (size_t i = 0; i <= (*cBuff)->size; i++)
                    freeData((*cBuff)->buff[i]);
            }

            free((*cBuff)->buff);
            free(*cBuff);

            *cBuff = NULL;

        } else
            tmp_err = EduDS_INVALID_ARGS;
    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}
