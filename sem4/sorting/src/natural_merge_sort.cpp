#include "../include/natural_merge_sort.h"

template <typename T>
void natural_merge_sort(vector<T> &vec)
{
    size_t n = vec.size();
    if (n <= 1)
        return;

    vector<T> temp(n);

    while (true)
    {
        vector<size_t> runs;
        runs.push_back(0);

        for (size_t i = 1; i < n; i++)
        {
            if (vec[i] < vec[i - 1])
                runs.push_back(i);
        }
        runs.push_back(n);

        if (runs.size() == 2)
            break;

        for (size_t r = 0; r + 2 < runs.size(); r += 2)
        {
            size_t left = runs[r];
            size_t mid = runs[r + 1];
            size_t right = runs[r + 2];

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
        }

        vec = temp;
    }
}

template void natural_merge_sort<int>(vector<int> &vec);
template void natural_merge_sort<double>(vector<double> &vec);
