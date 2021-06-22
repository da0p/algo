#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct Heap
{
    uint32_t size;
    int *heap;
    uint32_t ne;
} Heap;

Heap* create_heap(uint32_t size)
{
    Heap *h = (Heap *) malloc(sizeof(Heap));

    if (h != NULL) {

        h->heap = (int *) malloc(size * sizeof(int));

        if (h->heap != NULL) {

            h->size  = size;

            h->ne = 0;

            return h;
        }
        else {
            printf("Failed to allocate memory for heap\n");
            free(h);
            return NULL;
        }
    }
    else {
        printf("Failed to allocate memory for heap\n");
        return NULL;
    }
}

void swap(int *a, int *b) {
    int tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

void insert(Heap *h, int key)
{
    uint32_t i, k;
    if (h != NULL) {
        if (h->ne < h->size) {
          if (h->ne == 0)
          {
              h->heap[h->ne] = key;
              h->ne++;
          }
          else {
              h->heap[h->ne] = key;
              i = h->ne;
              while (i > 0 && h->heap[i] > h->heap[(i - 1)/2]) {
                  swap(&h->heap[i], &h->heap[(i - 1) / 2]);
                  k = i;
                  i = (i - 1)/2;
              }
              if (i == 0 && h->heap[k] > h->heap[i])
                  swap(&h->heap[k], &h->heap[i]);
              h->ne++;
          }
        } else {
            printf("Heap is full, can't insert more elements\n");
            return;
        }
    }
}

int delete(Heap *h, int *flag)
{
    int i, j, r;
    *flag = 0;
    if (h != NULL) {
        if (h->ne > 0) {
            r = h->heap[0];
            swap(&h->heap[0], &h->heap[h->ne- 1]);
            h->ne--;
            i = 0;
            j = 2 * i + 1;
            while (j < h->ne) {
                if (j + 1 < h->ne && h->heap[j + 1] > h->heap[j])
                    j = j + 1;
                if (h->heap[i] < h->heap[j]) {
                    swap(&h->heap[i], &h->heap[j]);
                    i = j;
                    j = 2 * i + 1;
                }
                else
                    break;
            }
            *flag = 1;
            return r;
        }
    }
    return -1;
}

Heap* heapify(int *arr, uint32_t arr_size)
{
    Heap *h = create_heap(arr_size);
    uint32_t i, j, k;

    if (h != NULL) {
        /* copy element */
        memcpy(h->heap, arr, arr_size * sizeof(int));
        h->ne = arr_size;
        for (i = (h->ne - 1) / 2; i >= 0; i--) {
            j = 2 * i + 1;
            k = i;
            while (j < h->ne) {
                if (j + 1 < h->ne && arr[j + 1] > arr[j])
                    j = j+ 1;
                if (h->heap[k] < h->heap[j]) {
                    swap(&h->heap[k], &h->heap[j]);
                    k = j;
                    j = 2 * k + 1;
                }
                else break;
            }
            if (i == 0) break;
        }
        return h;
    }

    return NULL;
}

void heap_sort(Heap *h)
{
   uint32_t tmp;
   int flag;
   if (h != NULL) {
       if (h->ne > 0) {
            tmp = h->ne;
            while (h->ne > 0) {
                delete(h, &flag);
            }
            h->ne = tmp;
       }
   }
}

void display(Heap h)
{
    int i;

    for (i = 0; i < h.ne; i++)
        printf("%d ", h.heap[i]);
    printf("\n");
}

void destroy(Heap *h) {
    free(h->heap);
    free(h);
}

int main(int argc, char *argv[])
{
    int flag;

    int arr[7] = {5, 10, 30, 20, 35, 40, 15};

    Heap *h = create_heap(20);

    insert(h, 0);

    insert(h, 2);

    insert(h, 5);

    insert(h, 8);

    insert(h, 9);

    insert(h, 4);

    insert(h, 10);

    insert(h, 7);

    display(*h);

    for (int i = 0; i < 8; i++) {
        printf("delete: %d\n", delete(h, &flag));
        display(*h);
    }

    destroy(h);

    h = heapify(arr, 7);

    display(*h);

    destroy(h);

    return 0;
}
