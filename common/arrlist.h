#ifndef RALPH_COMMON_H
#define RALPH_COMMON_H

#include <memory>

namespace ralph
{

template <class T>
class arrlist {
public:
    arrlist(int size);
    ~arrlist();
    arrlist(const arrlist & arrlist);
    arrlist(arrlist && arrlist);
    arrlist & operator=(const arrlist & arrlist);
    arrlist & operator=(arrlist && arrlist);

    int push_front();
    int push_front(const T & t);
    int push_back();
    int push_back(const T & t);

    void pop(int idx);
    void pop_front();
    void pop_back();

    void move_tail(int idx);
    void move_head(int idx);

    int head() const;
    int tail() const;
    int next(int idx) const;
    int prev(int idx) const;
    T & operator[](int i);

    int capacity() const;
    int size() const;

private:
    std::unique_ptr<T[]> _data;
    std::unique_ptr<int[]> _prev;
    std::unique_ptr<int[]> _next;
    int _size;
    int _capacity;
    int _free_head;
    int _head;
    int _tail;
};

#include "arrlist-inc.h"

} /* namespace ralph */

#endif // RALPH_COMMON_H
