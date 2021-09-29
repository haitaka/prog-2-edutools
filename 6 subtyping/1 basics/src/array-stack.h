#pragma once

#include "stack.h"

class ArrayStack : public Stack {
public:
    static const int defaultCapacity = 42;
    static const int growthFactor = 2;

    ArrayStack();
    explicit ArrayStack(int capacity);
    ArrayStack(ArrayStack const & orig);
    ~ArrayStack() override;

    void push(int val) override;
    int pop() override;
    int peek() const override;
    bool isEmpty() const override;

    ArrayStack & operator=(ArrayStack that);

    friend void swap(ArrayStack & s1, ArrayStack & s2);

private:
    void grow();

    int count;
    int capacity;
    int * data;
};

