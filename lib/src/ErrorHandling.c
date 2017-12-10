 /********************
 *  ErrorHandling.c
 *
 * This file is part of libvoids which is licensed under the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#include "Common.h"


const char *VdsErrString(vdsErrCode err)
{
    switch (err) {
    case VDS_SUCCESS:
        return "Operation was successful";
    case VDS_MALLOC_FAIL:
        return "Memory allocation failure";
    case VDS_KEY_EXISTS:
        return "Key already exists; no duplicate keys allowed in this data structure";
    case VDS_BUFFER_FULL:
        return "Buffer has reached capacity; pop elements in order to push again";
    case VDS_BUFFER_EMPTY:
        return "Buffer is empty";
    case VDS_INVALID_ARGS:
        return "Invalid parameters given to the function";
    default:
        return "Unknown libvoids error code";
    }
}
