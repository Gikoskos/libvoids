 /********************
 *  Common.h
 *
 * This file is part of EduDS data structure library which is licensed under
 * the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


//LIBRARY INTERNAL HEADER. DO NOT INCLUDE THIS SEPARATELY.

#ifndef __EduDS_COMMON_H
#define __EduDS_COMMON_H

#ifdef _WIN32
# ifdef _MSC_VER //disable compiler warning bug on MSVC where it warns about
#  pragma warning(disable : 4127) //do{}while(0) macros
# endif
# ifdef EXPORT_API_EduDS_DLL
#  define EduDS_API __declspec(dllexport)
# elif IMPORT_API_EduDS_DLL
#  define EduDS_API __declspec(dllimport)
# else
#  define EduDS_API
# endif
# define EduDS_LOCAL
#else
# ifdef __GNUC__
#  if __GNUC__ >= 4
#   define EduDS_API    __attribute__ ((visibility ("default")))
#   define EduDS_LOCAL  __attribute__ ((visibility ("hidden")))
#  else
#   define EduDS_API
#   define EduDS_LOCAL
#  endif
# else
#  define EduDS_API
#  define EduDS_LOCAL
# endif
#endif

#define EDUDS_SALT 8999 //using a prime number as seed for xxhash and mersenne twister

#define SAVE_ERR(err, tmp_err) \
    if (err) \
        *(err) = tmp_err;

typedef void (*UserDataCallback)(void *pData);
typedef int (*UserCompareCallback)(const void *pKey1, const void *pKey2);
typedef size_t (*UserHashFuncCallback)(size_t key_hash, size_t array_len);

typedef enum _TreeTraversalMethod {
    EDS_PRE_ORDER,
    EDS_IN_ORDER,
    EDS_POST_ORDER,
    EDS_BREADTH_FIRST, //level-order
    EDS_EULER
} TreeTraversalMethod;

//Key-value pair type definition
typedef struct _KeyValuePair {
    void *pData;
    void *pKey;
} KeyValuePair;

//EduDS library error codes
typedef enum _EdsErrCode {
    EDS_SUCCESS = 0x0,
    EDS_MALLOC_FAIL,
    EDS_KEY_EXISTS,
    EDS_INVALID_ARGS
} EdsErrCode;

//ErrorHandling.c functions are declared here instead of using another header file
EduDS_API const char *EdsErrString(EdsErrCode err);

#endif //__EduDS_COMMON_H
