/***********************************************\
*                   Common.h                    *
*           George Koskeridis (C) 2016          *
\***********************************************/
//LIBRARY INTERNAL HEADER. DO NOT INCLUDE THIS ANYWHERE ELSE.

#ifndef __GiDS_COMMON_H
#define __GiDS_COMMON_H

#ifdef _WIN32
# ifdef EXPORT_API_GiDS_DLL
#  define GiDS_API __declspec(dllexport)
# else
#  define GiDS_API __declspec(dllimport)
# endif
# define GiDS_LOCAL
#else
# ifdef __GNUC__
#  if __GNUC__ >= 4
#   define GiDS_API    __attribute__ ((visibility ("default")))
#   define GiDS_LOCAL  __attribute__ ((visibility ("hidden")))
#  else
#   define GiDS_API
#   define GiDS_LOCAL
#  endif
# else
#  define GiDS_API
#  define GiDS_LOCAL
# endif
#endif

typedef void (*CustomDataCallback)(void*);

typedef enum _TreeTraversalMethod {
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER,
    BREADTH_FIRST, //level-order
    EULER
} TreeTraversalMethod;

typedef unsigned int key_type;

#endif //__GiDS_COMMON_H
