/***********************************************\
*                HashFunctions.c                *
*           George Koskeridis (C) 2017          *
\***********************************************/

#include <stdlib.h>
#include <math.h>
#include "HashFunctions.h"

#define XXH_PRIVATE_API
#include "external/xxHash/xxhash.h"


//Cormen's division method
size_t HashDiv(void *pKey, size_t key_size, size_t array_len)
{
    size_t hashcode = XXH32(pKey, key_size, array_len);

    return hashcode % array_len;
}

//Cormen's multiplication method
size_t HashMult(void *pKey, size_t key_size, size_t array_len)
{
   double A = 0.6180339887; //most optimal A as suggested by Knuth
   double hash;

   size_t hashcode = XXH32(pKey, key_size, array_len);

   hash = A*hashcode;
   hash = modf(hash, &A);
   hash = floor(array_len * hash);
   return (size_t)hash;
}
