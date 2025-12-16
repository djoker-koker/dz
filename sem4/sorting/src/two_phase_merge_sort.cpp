#include "../include/two_phase_merge_sort.h"

template <typename T>
void two_phase_merge_sort(vector<T> &vec)
{
    size_t n = vec.size();
    if (n <= 1)
        return;

    vector<T> temp(n);

    std::function<void(size_t, size_t)> merge_sort = [&](size_t left, size_t right)
    {
        if (right - left <= 1)
            return;

        size_t mid = left + (right - left) / 2;

        merge_sort(left, mid);
        merge_sort(mid, right);

        size_t i = left;
        size_t j = mid;
        size_t k = left;

        while (i < mid && j < right)
        {
            if (vec[i] <= vec[j])
                temp[k++] = vec[i++];
            else
                temp[k++] = vec[j++];
        }

        while (i < mid)
            temp[k++] = vec[i++];

        while (j < right)
            temp[k++] = vec[j++];

        for (size_t t = left; t < right; ++t)
            vec[t] = temp[t];
    };

    merge_sort(0, n);
}

template void two_phase_merge_sort<int>(vector<int> &vec);
template void two_phase_merge_sort<double>(vector<double> &vec);
