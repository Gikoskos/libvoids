/***********************************************\
*                  RingBuffer.h                 *
*           George Koskeridis (C) 2017          *
\***********************************************/

#ifndef __EduDS_CIRCULAR_BUFF_H
#define __EduDS_CIRCULAR_BUFF_H


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"


typedef struct _RingBuffer {
	size_t size, write, read, available;
    void **buff;
} RingBuffer;



EduDS_API RingBuffer *RingBuffer_init(size_t buff_size,
                                      EduDSErrCode *err);

EduDS_API void RingBuffer_resize(RingBuffer **cBuff,
                                 size_t new_size,
                                 EduDSErrCode *err);

EduDS_API void RingBuffer_write(RingBuffer *cBuff,
                                void *pData,
                                EduDSErrCode *err);

EduDS_API void *RingBuffer_read(RingBuffer *cBuff,
                                EduDSErrCode *err);

EduDS_API void RingBuffer_destroy(RingBuffer **cBuff,
                                  UserDataCallback freeData,
                                  EduDSErrCode *err);

#ifdef __cplusplus
}
#endif

#endif //__EduDS_CIRCULAR_BUFF_H
