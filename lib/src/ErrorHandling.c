/***********************************************\
*                ErrorHandling.c                *
*           George Koskeridis (C) 2017          *
\***********************************************/

#include <stdlib.h>
#include "Common.h"

const char *EduDSErrString(EduDSErrCode err)
{
    switch (err) {
    case EduDS_SUCCESS:
        return "Operation was successful";
    case EduDS_MALLOC_FAIL:
        return "Memory allocation failure";
    case EduDS_KEY_EXISTS:
        return "All keys have to be unique, in this data structure";
    case EduDS_INVALID_ARGS:
        return "Invalid parameters given to the function";
    default:
        return "Unknown EduDS error code";
    }
}
