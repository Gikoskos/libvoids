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

#ifndef EduDS_COMMON_H__
#define EduDS_COMMON_H__

//if we're compiling on windows
#ifdef _WIN32

//if we're building the library and this header isn't
//just included from someone who uses the library
# ifdef BUILD_EduDS_LIB

#  ifdef _MSC_VER //disable compiler warning bug on MSVC where it warns about
#   pragma warning(disable : 4127) //do{}while(0) macros
#  endif //_MSC_VER

#  ifdef EXPORT_API_EduDS_DLL
#   define EduDS_API __declspec(dllexport)
#  else //EXPORT_API_EduDS_DLL
#   define EduDS_API
#  endif //not EXPORT_API_EduDS_DLL

//if the library is included on a project that uses it
# else //BUILD_EduDS_LIB

#  ifdef IMPORT_API_EduDS_DLL
#   define EduDS_API __declspec(dllimport)
#  else //IMPORT_API_EduDS_DLL
#   define EduDS_API
#  endif //not IMPORT_API_EduDS_DLL

# endif //not BUILD_EduDS_LIB

# define EduDS_LOCAL

#else //_WIN32

# ifdef __GNUC__
#  if __GNUC__ >= 4
#   define EduDS_API    __attribute__ ((visibility ("default")))
#   define EduDS_LOCAL  __attribute__ ((visibility ("hidden")))
#  else
#   define EduDS_API
#   define EduDS_LOCAL
#  endif
# else //__GNUC__
#  define EduDS_API
#  define EduDS_LOCAL
# endif //not __GNUC__

#endif //not _WIN32

//global macros are library internal and shouldn't pollute the user's macro namespace
#ifdef BUILD_EduDS_LIB

#define EDUDS_SALT 8999 //using a prime number as seed for xxhash and mersenne twister

#define SAVE_ERR(err, tmp_err) \
    if (err) \
        *(err) = tmp_err;

#endif //BUILD_EduDS_LIB


#include <stddef.h>

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

#endif //EduDS_COMMON_H__
