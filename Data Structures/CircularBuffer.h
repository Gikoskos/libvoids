/***********************************************\
*                 CircularBuffer.h              *
*           George Koskeridis (C) 2017          *
\***********************************************/

#ifndef __GiDS_CIRCULAR_BUFF_H
#define __GiDS_CIRCULAR_BUFF_H


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"


typedef struct _CircularBuffer {
	size_t size, write, read, available;
    void **buff;
} CircularBuffer;



GiDS_API CircularBuffer *CircularBuffer_init(size_t buff_size);

GiDS_API void CircularBuffer_resize(CircularBuffer **cBuff, size_t new_size);

GiDS_API void CircularBuffer_write(CircularBuffer *cBuff, void *pData);

GiDS_API void *CircularBuffer_read(CircularBuffer *cBuff);

GiDS_API void CircularBuffer_destroy(CircularBuffer **cBuff, CustomDataCallback freeData);

#ifdef __cplusplus
}
#endif

#endif //__GiDS_CIRCULAR_BUFF_H
