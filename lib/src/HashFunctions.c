 /********************
 *  HashFunctions.c
 *
 * This file is part of EduDS data structure library which is licensed under
 * the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#include <stddef.h>
#include <math.h>
#include "HashFunctions.h"

#define XXH_PRIVATE_API
#include "xxhash.h"


size_t HashCode(const void *pKey, size_t key_size)
{
    return (size_t)XXH32(pKey, key_size, EDUDS_SALT);
}

//Cormen's division method
size_t HashDiv(size_t key_hash, size_t array_len)
{
    return key_hash % array_len;
}

//Cormen's multiplication method
size_t HashMult(size_t key_hash, size_t array_len)
{
   double A = 0.6180339887; //most optimal A as suggested by Knuth
   double hash;

   hash = A*key_hash;
   hash = modf(hash, &A);
   hash = floor(array_len * hash);
   return (size_t)hash;
}
