#pragma once

#include <stdexcept>

template <class Iterator>
Iterator LocalMax(Iterator first, Iterator last) {
    if (first == last) {
        return last;
    }
    Iterator max_b = first;
    ++first;
    Iterator next_first = first;
    --first;
    Iterator max_a = next_first;
    Iterator max;
    if (next_first == last) {
        return first;
    }
    if (*(next_first) < *first) {
        max = first;
    } else if (*first < *(next_first)) {
        max = next_first;
    } else {
        max = last;
    }
    ++first;
    bool flag = false;
    while (first != last) {
        ++max_a;
        if (max_a == last) {
            flag = true;
        }
        if (flag == true) {
            if (*max_b < *first && *max < *first) {
                max = first;
            } else if (*first < *max_b && *max < *max_b) {
                max = first;
            }
            ++first;
        } else {
            if ((*max_b < *first) && (*max_a < *first)) {
                max = first;
            }
            ++first;
            ++max_b;
        }
    }
    return max;
}
