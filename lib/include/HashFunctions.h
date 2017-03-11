/***********************************************\
*                HashFunctions.h                *
*           George Koskeridis (C) 2017          *
\***********************************************/

#ifndef __EduDS_HASHFUNCTIONS_H
#define __EduDS_HASHFUNCTIONS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"
#include "AssociationList.h"

EduDS_API size_t HashCode(const void *pKey, size_t key_size);

EduDS_API size_t HashDiv(size_t key_hash, size_t array_len);

EduDS_API size_t HashMult(size_t key_hash, size_t array_len);

#ifdef __cplusplus
}
#endif

#endif //__EduDS_HASHFUNCTIONS_H
