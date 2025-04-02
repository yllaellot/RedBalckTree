#include <iostream>
#include <set>

namespace setf
{
    enum Requests
    {
        KEY = 'k',
        QUERY = 'q'
    };

    template <typename C, typename T>
    long range_queries(const C &set, const T& first, const T& second) 
    {
        if (first > second) 
            return 0;

        auto start = set.lower_bound(first);
        auto fin   = set.upper_bound(second);
        return std::distance(start, fin);
    }
}