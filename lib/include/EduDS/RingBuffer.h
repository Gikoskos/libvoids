 /********************
 *  RingBuffer.h
 *
 * This file is part of EduDS data structure library which is licensed under
 * the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#ifndef EduDS_CIRCULAR_BUFF_H__
#define EduDS_CIRCULAR_BUFF_H__


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"


typedef struct _RingBuffer {
	size_t size, write, read, available;
    void **buff;
} RingBuffer;



EduDS_API RingBuffer *RingBuffer_init(size_t buff_size,
                                      EdsErrCode *err);

EduDS_API void RingBuffer_resize(RingBuffer **cBuff,
                                 size_t new_size,
                                 EdsErrCode *err);

EduDS_API void RingBuffer_write(RingBuffer *cBuff,
                                void *pData,
                                EdsErrCode *err);

EduDS_API void *RingBuffer_read(RingBuffer *cBuff,
                                EdsErrCode *err);

EduDS_API void RingBuffer_destroy(RingBuffer **cBuff,
                                  UserDataCallback freeData,
                                  EdsErrCode *err);

#ifdef __cplusplus
}
#endif

#endif //EduDS_CIRCULAR_BUFF_H__
