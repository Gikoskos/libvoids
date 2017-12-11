#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <voids.h>

#define VDS_EC(func, err) \
do { \
    func; \
    if (err != VDS_SUCCESS) { \
        fprintf(stderr, "Function call \"%s\" failed with error \"%s\"\n", #func, VdsErrString(err)); \
        assert(err != VDS_MALLOC_FAIL && err != VDS_INVALID_ARGS); \
    } \
} while (0)


#define MAX_ARRAY_SIZE 1000

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

void check_data_integrity(ArrayHeap *heap, int *data, size_t data_len)
{
    assert(heap);
    assert(data);
    for (size_t i = 0; i < heap->idx; i++) {
        size_t j;
        for (j = 0; j < data_len; j++) {
            if ((*(int*)heap->array[i]) == data[j])
                break;
        }
        assert(j < data_len);
    }
}

void mix_array(int *array, size_t len)
{
    assert(array);

    int *mixed, tmp;
    size_t idx;

    assert(NULL != (mixed = malloc(sizeof(int) * len)));

    for (int i = 0; i < len; i++) {
        mixed[i] = i;
    }

    for (int i = 0; i < len; i++) {
        idx = ((size_t)rand())%len;

        tmp = mixed[i];
        mixed[i] = mixed[idx];
        mixed[idx] = tmp;
    }
}

void testarrheap(vdsHeapProperty property)
{
    assert(property == VDS_MAX_HEAP || property == VDS_MIN_HEAP);

    vdsErrCode err;
    ArrayHeap *heap;
    size_t dat_len = ((size_t)rand())%MAX_ARRAY_SIZE + 1;
    int *data, *built;

    assert(NULL != (data = malloc(sizeof(int) * dat_len)));
    assert(NULL != (built = malloc(sizeof(int) * dat_len)));

    for (int i = 0; i < dat_len; i++) {
        do {
            data[i] = rand();
        } while (!data[i]);
        built[i] = data[i];
    }

    VDS_EC(heap = ArrayHeap_init(compareInts, property, dat_len, &err), err);

    for (int i = 0; i < dat_len; i++) {
        VDS_EC(ArrayHeap_push(heap, (void*)&data[i], &err), err);
        assert(heap->idx == i + 1);
        check_data_integrity(heap, data, dat_len);
    }

    int prev = 0;
    for (int i = dat_len; i != 0; i--) {
        int *p;
        VDS_EC(p = ArrayHeap_pop(heap, &err), err);
        if (prev) {
            if (property == VDS_MAX_HEAP)
                assert(prev >= *p);
            else
                assert(prev <= *p);
        }

        assert(heap->idx == i - 1);
        check_data_integrity(heap, data, dat_len);

        prev = *p;
    }

    VDS_EC(ArrayHeap_destroy(&heap, NULL, &err), err);
    free(data);
    free(built);
}

int main(int argc, char *argv[])
{
    testarrheap(VDS_MAX_HEAP);
    testarrheap(VDS_MIN_HEAP);
    return 0;
}
