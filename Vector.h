#pragma once
#include <iostream>
#include <string.h>
using namespace std;
#define MAX_STRING 256
#define MAX_NODE 999

template <class T>
class Vector {
private:
    T* array;
    size_t size;
    size_t capacity;

public:
    Vector() {
        array = new T[1];
        size = 0;
        capacity = 1;
    }

    bool Empty() const {
        return this->size == 0;
    }

    void PopFirst() {
        if (size > 0) {
            for (size_t i = 0; i < size - 1; i++) {
                array[i] = array[i + 1];
            }
            size--;
        }
    }

    void PushBack(const T& value) {
        if (size == capacity) {
            capacity += 10;
            T* temp = new T[capacity];
            for (size_t i = 0; i < size; i++) {
                temp[i] = array[i];
            }
            delete[] array;
            array = temp;
        }
        array[size] = value;
        size++;
    }

    const T GetFirst() const{
        return array[0];
    }

    T& operator[](size_t index) {
        return array[index];
    }

    const T& operator[](size_t index) const {
        return array[index];
    }

    ~Vector() {
        delete[] array;
    }
};