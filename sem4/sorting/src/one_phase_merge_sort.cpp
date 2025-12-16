#include "../include/one_phase_merge_sort.h"

template <typename T>
void one_phase_merge_sort(vector<T> &vec)
{
    size_t n = vec.size();
    if (n <= 1)
        return;

    size_t mid = n / 2;

    for (size_t i = 1; i < mid; i++)
    {
        T key = vec[i];
        size_t j = i;
        while (j > 0 && vec[j - 1] > key)
        {
            vec[j] = vec[j - 1];
            j--;
        }
        vec[j] = key;
    }

    for (size_t i = mid + 1; i < n; i++)
    {
        T key = vec[i];
        size_t j = i;
        while (j > mid && vec[j - 1] > key)
        {
            vec[j] = vec[j - 1];
            j--;
        }
        vec[j] = key;
    }

    vector<T> temp(n);
    size_t i = 0;
    size_t j = mid;
    size_t k = 0;

    while (i < mid && j < n)
    {
        if (vec[i] <= vec[j])
            temp[k++] = vec[i++];
        else
            temp[k++] = vec[j++];
    }

    while (i < mid)
        temp[k++] = vec[i++];
    while (j < n)
        temp[k++] = vec[j++];

    vec = temp;
}

template void one_phase_merge_sort<int>(vector<int> &vec);
template void one_phase_merge_sort<double>(vector<double> &vec);
