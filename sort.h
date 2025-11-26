#ifndef SORT
#define SORT
#include "stringProcessor.h"
int32_t strcmpp(const char* fStr, const char* sStr);
void swap(char** a, char** b)
{
    char* temp = *a;
    *a = *b;
    *b = temp;
}
void quick_sort(char** arr, size_t length)
{
    if (length < 2) return;
    char* pivot = arr[length / 2];
    long i = 0;
    long j = length - 1;
    while (i <= j)
    {
        while (strcmpp(arr[i], pivot) < 0)
        {
            i++;
        }
        while (strcmpp(arr[j], pivot) > 0)
        {
            j--;
        }

        if (i <= j)
        {
            swap(&arr[i], &arr[j]);
            i++;
            j--;
        }
    }
    if (j > 0)
    {
        quick_sort(arr, (size_t)(j + 1));
    }
    if (i < (long)length)
    {
        quick_sort(arr + i, length - (size_t)i);
    }
}
#endif // !SORT