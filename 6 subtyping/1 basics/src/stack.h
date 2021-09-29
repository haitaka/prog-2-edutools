#pragma once

class Stack {
public:
    Stack() = default;
    Stack(Stack const & orig) = delete;
    virtual ~Stack() = default;
    virtual void push(int i) = 0;
    virtual int pop() = 0;
    virtual int peek() const = 0;
    virtual bool isEmpty() const = 0;
    void drainAndPrint();
};

