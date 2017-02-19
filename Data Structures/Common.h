/***********************************************\
*                   Common.h                    *
*           George Koskeridis (C) 2016          *
\***********************************************/
//LIBRARY INTERNAL HEADER. DO NOT INCLUDE THIS ANYWHERE ELSE.

#ifndef __EduDS_COMMON_H
#define __EduDS_COMMON_H

#ifdef _WIN32
# ifdef EXPORT_API_EduDS_DLL
#  define EduDS_API __declspec(dllexport)
# else
#  define EduDS_API __declspec(dllimport)
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

typedef void (*CustomDataCallback)(void*);

typedef enum _TreeTraversalMethod {
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER,
    BREADTH_FIRST, //level-order
    EULER
} TreeTraversalMethod;

typedef unsigned int key_type;

#endif //__EduDS_COMMON_H
