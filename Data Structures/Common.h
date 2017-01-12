/***********************************************\
*                   Common.h                    *
*           George Koskeridis (C) 2016          *
\***********************************************/

#ifndef __GiDS_COMMON_H
#define __GiDS_COMMON_H

#ifdef _WIN32
# ifdef EXPORT_API_GiDS_DLL
#  define GiDS_API __declspec(dllexport)
# else
#  define GiDS_API __declspec(dllimport)
# endif
#else
# define GiDS_API
#endif

typedef void (*CustomDataCallback)(void*);


#endif //__GiDS_COMMON_H
