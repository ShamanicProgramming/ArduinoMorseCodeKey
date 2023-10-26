#ifndef FILL_H
#define FILL_H

template <class ForwardIt, class T>
void fill(ForwardIt first, ForwardIt last, const T &value)
{
    for (; first != last; ++first)
        *first = value;
}

#endif