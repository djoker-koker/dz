#include "../include/quick_sort.h"

template <typename T>
void quick_sort(vector<T> &vec, int left, int right)
{
    if (left >= right)
        return;

    T pivot = vec[(left + right) / 2];
    int i = left;
    int j = right;

    while (i <= j)
    {
        while (vec[i] < pivot)
            i++;
        while (vec[j] > pivot)
            j--;

        if (i <= j)
        {
            std::swap(vec[i], vec[j]);
            i++;
            j--;
        }
    }

    if (left < j)
        quick_sort(vec, left, j);
    if (i < right)
        quick_sort(vec, i, right);
}

template <typename T>
void quick_sort(vector<T> &vec)
{
    if (vec.size() <= 1)
        return;
    quick_sort(vec, 0, vec.size() - 1);
}

template void quick_sort<int>(vector<int> &vec);
template void quick_sort<double>(vector<double> &vec);
