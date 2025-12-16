#include "../include/shell_sort.h"

template <typename T>
void shell_sort(vector<T> &vec)
{
    size_t n = vec.size();
    if (n <= 1)
        return;

    size_t gap = n / 2;

    while (gap > 0)
    {
        for (size_t i = gap; i < n; i++)
        {
            T temp = vec[i];
            size_t j = i;

            while (j >= gap && temp < vec[j - gap])
            {
                vec[j] = vec[j - gap];
                j -= gap;
            }

            vec[j] = temp;
        }

        gap /= 2;
    }
}

template void shell_sort<int>(vector<int> &vec);
template void shell_sort<double>(vector<double> &vec);
