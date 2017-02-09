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



GiDS_API CircularBuffer *newCircularBuffer(size_t buff_size);

GiDS_API void resizeCircularBuffer(CircularBuffer **cBuff, size_t new_size);

GiDS_API void pushCircularBuffer(CircularBuffer *cBuff, void *pData);

GiDS_API void *popCircularBuffer(CircularBuffer *cBuff);

GiDS_API void deleteCircularBuffer(CircularBuffer **cBuff, CustomDataCallback freeData);

#ifdef __cplusplus
}
#endif

#endif //__GiDS_CIRCULAR_BUFF_H
