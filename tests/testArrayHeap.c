#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <EduDS.h>

#define EduDS_ERR_FATAL(func, err) \
    func; \
    if (err != EDS_SUCCESS) { \
        printf("Function call \"%s\" failed with error \"%s\"\n", #func, EdsErrString(err)); \
        return 1; \
    }

#define EduDS_ERR_NON_FATAL(func, err) \
    func; \
    if (err != EDS_SUCCESS) { \
        printf("Function call \"%s\" failed with error \"%s\"\n", #func, EdsErrString(err)); \
    }


int *newRandInt(int range)
{
    int *p = malloc(sizeof(int));

    if (range) {
        *p = rand()%range + 1;
    } else {
        *p = rand();
    }

    return p;
}

int compareInts(const void *key1, const void *key2)
{
    return *(int*)key1 - *(int*)key2;
}

void printInt(void *param)
{
    int x = *(int*)param;

    printf("(%d) ", x);
}

/*EduDS_API ArrayHeap *ArrayHeap_init(UserCompareCallback DataCmp,
                                    HeapPropertyType property,
                                    size_t size,
                                    EdsErrCode *err);

EduDS_API void *ArrayHeap_push(ArrayHeap *arrheap,
                               void *pData,
                               EdsErrCode *err);

EduDS_API void *ArrayHeap_pop(ArrayHeap *arrheap,
                              EdsErrCode *err);

EduDS_API void ArrayHeap_destroy(ArrayHeap **arrheap,
                                 UserDataCallback freeData,
                                 EdsErrCode *err);*/
void printArrayHeap(ArrayHeap *heap, UserDataCallback printData)
{
    if (printData) {
        for (size_t i = 0; i < heap->idx; i++) {
            printData(heap->array[i]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    EdsErrCode err;
    ArrayHeap *heap;

    EduDS_ERR_FATAL(heap = ArrayHeap_init(compareInts, EDS_MAX_HEAP, 13, &err), err);

    srand(time(NULL));

    printf("===PUSHING DATA TO THE HEAP===\n");
    for (int i = 0; i < 20; i++) {
        int *s = newRandInt(50);

        printf("\nTrying to push %d to the heap\n", *s);
        EduDS_ERR_NON_FATAL(ArrayHeap_push(heap, (void*)s, &err), err);
        if (err != EDS_SUCCESS)
            free(s);
        else
            printArrayHeap(heap, printInt);
    }

    printf("\n\n===POPPING DATA FROM THE HEAP===\n");
    for (int i = 0; i < 20; i++) {
        int *s;

        EduDS_ERR_NON_FATAL(s = ArrayHeap_pop(heap, &err), err);
        if (s) {
            printf("\nPopped %d!\n", *s);
            free(s);
            printArrayHeap(heap, printInt);
        }
    }

    printf("\n===Switching heap order to minimum===\n");
    heap->property = EDS_MIN_HEAP;

    printf("===PUSHING DATA TO THE HEAP===\n");
    for (int i = 0; i < 20; i++) {
        int *s = newRandInt(50);

        printf("\nTrying to push %d to the heap\n", *s);
        EduDS_ERR_NON_FATAL(ArrayHeap_push(heap, (void*)s, &err), err);
        if (err != EDS_SUCCESS)
            free(s);
        else
            printArrayHeap(heap, printInt);
    }

    printf("\n\n===POPPING DATA FROM THE HEAP===\n");
    for (int i = 0; i < 20; i++) {
        int *s;

        EduDS_ERR_NON_FATAL(s = ArrayHeap_pop(heap, &err), err);
        if (s) {
            printf("\nPopped %d!\n", *s);
            free(s);
            printArrayHeap(heap, printInt);
        }
    }


    EduDS_ERR_FATAL(ArrayHeap_destroy(&heap, free, &err), err);
    return 0;
}
