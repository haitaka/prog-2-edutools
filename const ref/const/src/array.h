#pragma once

class Array {
public:
    Array();
    Array(int length);
    ~Array();

    int get(int index) const;
    void set(int index, int value);

private:
    static int const DEFAULT_LENGTH = 1024;

    unsigned int const length;
    int * data;
};

