# C++11 (C++0x) and beyond

## auto

Автоматический вывод типов переменных:
```c++
auto x = 42; // int
auto y = x * 1.5; // double
````

Возвращаемых типов функций:
```c++
// C++11
auto sum(int x, int y) -> int { 
    return x + y;
}
// C++14
auto sum(int x, int y) {
    return x + y;
}
```

Возвращаемых типов шаблонов:
```c++
// C++11
template<typename T, typename S>
auto sum(T x, S y) -> decltype(t + s) { 
    return x + y;
}
// C++14
template<typename T, typename S>
decltype(auto) sum(T x, S y) {
    return x + y;
}
```

## range-based for
```c++
int a[] = {1, 2, 3, 4, 5};
for (int i : a) {
    std::cout << i << std::endl;
}
```
Работает с
* массивами
* классами, предоставляющими итератор через `begin()` и `end()`
 
Не работает с указателями:
```c++
int * a = new int[10];
for (int i : a) { // ERROR
    std::cout << i << std::endl;
}
```

## initializer_list

```c++
std::initializer_list<int> elems = {1, 2, 3, 4, 5};
for (auto i : elems) {
    std::cout << i << std::endl;
}
```

```c++
class MyArray {
public:
    MyArray(std::initializer_list<int> elems);
    // ...
};

int main() {
    MyArray a = {1, 2, 3, 4, 5};
    return 0;
}
```
