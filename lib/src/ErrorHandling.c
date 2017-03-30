 /********************
 *  ErrorHandling.c
 *
 * This file is part of EduDS data structure library which is licensed under
 * the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#include "Common.h"


const char *EdsErrString(EdsErrCode err)
{
    switch (err) {
    case EDS_SUCCESS:
        return "Operation was successful";
    case EDS_MALLOC_FAIL:
        return "Memory allocation failure";
    case EDS_KEY_EXISTS:
        return "All keys have to be unique, in this data structure";
    case EDS_INVALID_ARGS:
        return "Invalid parameters given to the function";
    default:
        return "Unknown EduDS error code";
    }
}
