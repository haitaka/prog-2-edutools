#pragma once

/**
 * Poor man's linked list implementation.
 */
class List {
public:
    static List * nil();
    static List * copy(List * orig);

    List(int head, List * tail);
    ~List();

    List(List const & that) = delete;
    List & operator=(List const & that) = delete;

    int operator[](int idx);

    int getHead() const;
    List * getTail();

private:
    int const head;
    List * const tail;
};

