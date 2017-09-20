#include <memory.h>

template <class T>
arrlist<T>::arrlist(int capacity)
    : _data(new T[capacity])
    , _prev(new int[capacity])
    , _next(new int[capacity])
    , _size(0)
    , _capacity(capacity)
    , _head(-1)
    , _tail(-1)
{
    _free_head = 0;
    for (int i=0; i<capacity-1; ++i) {
        _next[i] = i+1;
        _prev[i] = -1;
    }

    _next[capacity-1] = -1;
    _prev[capacity-1] = -1;
}

template <class T>
arrlist<T>::~arrlist()
{
}

template <class T>
arrlist<T>::arrlist(const arrlist & al)
{
    _head = al._head;
    _tail = al._tail;
    _size = al._size;
    _capacity = al._capacity;
    _free_head = al._free_head;
    _data.reset(new T[al._capacity]);
    memcpy(_data.get(), al._data.get(), al._capacity * sizeof(T));
    _prev.reset(new int[al._capacity]);
    memcpy(_prev.get(), al._prev.get(), al._capacity * sizeof(int));
    _next.reset(new int[al._capacity]);
    memcpy(_next.get(), al._next.get(), al._capacity * sizeof(int));
}

template <class T>
arrlist<T>::arrlist(arrlist && al)
{
    _head = al._head;
    _tail = al._tail;
    _size = al._size;
    _capacity = al._capacity;
    _free_head = al._free_head;
    _data = std::move(al._data);
    _prev = std::move(al._prev);
    _next = std::move(al._next);

    al._size = 0;
    al._capacity = 0;
    al._free_head = -1;
}

template <class T>
arrlist<T> & arrlist<T>::operator=(arrlist && al)
{
    _head = al._head;
    _tail = al._tail;
    _size = al._size;
    _capacity = al._capacity;
    _free_head = al._free_head;
    _data = std::move(al._data);
    _prev = std::move(al._prev);
    _next = std::move(al._next);

    al._size = 0;
    al._capacity = 0;
    al._free_head = -1;

    return *this;
}

template <class T>
arrlist<T> & arrlist<T>::operator=(const arrlist & al)
{
    _head = al._head;
    _tail = al._tail;
    _size = al._size;
    _capacity = al._capacity;
    _free_head = al._free_head;
    _data.reset(new T[al._capacity]);
    memcpy(_data.get(), al._data.get(), al._capacity * sizeof(T));
    _prev.reset(new int[al._capacity]);
    memcpy(_prev.get(), al._prev.get(), al._capacity * sizeof(int));
    _next.reset(new int[al._capacity]);
    memcpy(_next.get(), al._next.get(), al._capacity * sizeof(int));
    return *this;
}

template <class T>
int arrlist<T>::push_back()
{
    if (_free_head == -1)
        return -1;

    int idx = _free_head;
    _free_head = _next[_free_head];
    ++_size;

    int old_tail= _tail;
    _tail = idx;
    _prev[_tail] = old_tail;
    if (old_tail >= 0) {
        _next[old_tail] = _tail;
    }

    if (_head == -1) {
        _head = idx;
    }

    return idx;
}

template <class T>
int arrlist<T>::push_back(const T & t)
{
    int idx = push_back();
    if (idx >= 0) {
        _data[idx] = t;
    }

    return idx;
}

template <class T>
int arrlist<T>::push_front()
{
    if (_free_head == -1)
        return -1;

    int idx = _free_head;
    _free_head = _next[_free_head];
    ++_size;

    int old_head = _head;
    _head = idx;
    if (old_head >= 0) {
        _prev[old_head] = _head;
    }
    _next[_head] = old_head;

    if (_tail == -1) {
        _tail = idx;
    }

    return idx;
}

template <class T>
int arrlist<T>::push_front(const T & t)
{
    int idx = push_front();
    if (idx >= 0) {
        _data[idx] = t;
    }

    return idx;
}

template <class T>
void arrlist<T>::pop(int i)
{
    int old_free_head = _free_head;
    _free_head = i;
    _data[i].~T();
    --_size;

    int prev = _prev[i];
    int next = _next[i];

    if (prev == -1) {
        _head = next;
    } else {
        _next[prev] = next;
    }

    if (next == -1) {
        _tail = prev;
    } else {
        _prev[next] = prev;
    }

    _next[_free_head] = old_free_head;
}

template <class T>
void arrlist<T>::pop_front()
{
    pop(_head);
}

template <class T>
void arrlist<T>::pop_back()
{
    pop(_tail);
}

template <class T>
void arrlist<T>::move_tail(int idx)
{
    if (idx == _tail) {
        return;
    }

    int prev = _prev[idx];
    int next = _next[idx];

    _prev[next] = prev;
    if (prev == -1) {
        _head = next;
    } else {
        _next[prev] = next;
    }

    int old_tail = _tail;
    _tail = idx;

    _next[old_tail] = _tail;
    _prev[_tail] = old_tail;
    _next[_tail] = -1;
}

template <class T>
void arrlist<T>::move_head(int idx)
{
    if (idx == _head) {
        return;
    }

    int prev = _prev[idx];
    int next = _next[idx];

    if (next == -1) {
        _tail = prev;
    } else {
        _prev[next] = prev;
    }
    _next[prev] = next;

    int old_head = _head;
    _head = idx;

    _prev[old_head] = _head;
    _next[_head] = old_head;
    _prev[_head] = -1;
}

template <class T>
int arrlist<T>::head() const
{
    return _head;
}

template <class T>
int arrlist<T>::tail() const
{
    return _tail;
}

template <class T>
int arrlist<T>::next(int i) const
{
    return _next[i];
}

template <class T>
int arrlist<T>::prev(int i) const
{
    return _prev[i];
}

template <class T>
T & arrlist<T>::operator[](int i)
{
    return _data[i];
}

template <class T>
int arrlist<T>::capacity() const
{
    return _capacity;
}

template <class T>
int arrlist<T>::size() const
{
    return _size;
}
