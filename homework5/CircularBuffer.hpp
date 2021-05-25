#pragma once
#include <iterator>

template <typename T>
class CircularBuffer;

template <typename T>
class Iter {
private:
    T* cur;
    T* elements;
    int capacity;
    
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = int;
    using pointer = T*;
    using reference = T&;

    Iter(T* cur, T* elements, int capacity) : cur(cur), elements(elements), capacity(capacity) {};

    Iter& operator = (const Iter& other) {
        cur = other.cur;
        elements = other.elements;
        capacity = other.capacity;
        return *this;
    }
    
    bool operator== (Iter const& other) const {
        return cur == other.cur;
    };

    bool operator!= (Iter const& other) const {
        return !(*this == other);
    };

    bool operator< (Iter const& other) const {
        return cur < other.cur;
    };

    reference operator*() const {
        return *cur;
    };

    Iter& operator++() {
        ++cur;
        if (cur == elements + capacity) {
            cur = elements;
        }
        return *this;
    };

    Iter& operator--() {
        if (cur == elements) {
            cur = elements + capacity - 1;
        }
        --cur;
        return *this;
    };

    difference_type operator- (Iter const& other) const {
        if (*this < other)
            return (capacity + cur - other.cur);
        return cur - other.cur;
    }

    Iter& operator+= (int x) {
        x %= capacity;
        if (cur + x < elements + capacity) {
            cur += x;
        }
        else {
            cur += x - capacity;
        }
        return *this;
    }

    Iter& operator-= (int x) {
        x %= capacity;
        if (cur - x < elements) {
            cur += capacity - x;
        }
        else {
            cur -= x;
        }
        return *this;
    }


};
template <typename T>
Iter<T> operator- (const Iter<T>& elem, int x) {
    Iter<T> result = elem;
    result -= x;
    return result;
}


template <typename T>
Iter<T> operator+ (const Iter<T>& elem, int n) {
    Iter<T> result = elem;
    result += n;
    return result;
}

template <typename T>
class CircularBuffer {
    friend class Iter<T>;

private:
    T* elements;
    int capacity;
    int size = 0;
    int _begin = 0;

public:
    explicit CircularBuffer(int new_capacity) : capacity(new_capacity + 1) {
        elements = new T[capacity];
    }

    ~CircularBuffer() {
        delete[] elements;
    }

    CircularBuffer& operator=(const CircularBuffer& other) {
        if (this == &other) {
            return *this;
        }
        delete[] elements;
        size = other.size;
        capacity = other.capacity;
        _begin = other._begin;
        elements = new T[capacity];
        for (int i = 0; i < capacity; i++) {
            elements[i] = other.elements[i];
        }
        return *this;
    }

    T first() {
        return elements[_begin];
    }

    T last() {
        return elements[(_begin + size - 1) % capacity];
    }

    T operator [] (int i) const {
        return elements[(_begin + i) % capacity];
    }

    T& operator [] (int i) {
        if (size == 0 || i >= size) {
            throw std::out_of_range("out of range");
        }
        return elements[(_begin + i) % capacity];
    }

    void addFirst(T value) {
        if (size == 0) {
            elements[0] = value;
        }
        else {
            _begin = (_begin - 1 + capacity) % capacity;
            elements[_begin] = value;
        }
        ++size;
        if (size >= capacity) {
            --size;
        }
    }

    void addLast(T value) {
        if (size == 0) {
            elements[0] = value;
        }
        else {
            elements[(_begin + size) % capacity] = value;
        }
        ++size;
        if (size >= capacity) {
            --size;
        }
    }

    void delFirst() {
        if (size == 1) {
            _begin = 0;
        }
        else {
            _begin = (_begin + 1) % capacity;
        }
        --size;
    }

    void delLast() {
        if (size == 1) {
            _begin = 0;
        }
        --size;
    }

    void changeCapacity(int new_capacity) {
        T* new_elements = new T[new_capacity + 1];
        for (int i = 0; i < capacity; ++i) {
            new_elements[i] = elements[i];
        }
        delete[] elements;
        capacity = new_capacity + 1;
        elements = new_elements;
    }

    Iter<T> begin() const {
        return Iter<T>(elements + _begin, elements, capacity);
    }

    Iter<T> end() const {
        return Iter<T>(elements + (_begin + size) % capacity, elements, capacity);
    }
};