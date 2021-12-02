# Итераторы

## Мотивация
Часто при разработке программы с использованием коллекций (массивов, списков, ассоциативных словарей и т.д.) появляются следующие задачи:
* перебрать все элементы коллекции
* поискать элемент получить доступ к нему *или специальное значение, если элемент не был найден*
* получить идентификатор какой-то позиции в коллекции для быстрого доступа к ней (например, для создания нового элемента на этой позиции)
 
Для решения всех этих задач бывает удобно использовать указатели: на элементы массива, или на внутренние структуры, представляющие узлы связного списка.

К примеру перебор элементов массива может выглядеть так:
```c++
int array[N];
int * begin = array;
int * end = array + N;
for (int * ptr = begin; ptr != end; ++ptr) {
    std::cout << *ptr << std::endl;
}
```

А поиск первого вхождения заданного значения в связном списке так:
```c++
Node * findFirst(int value) {
    Node * elem = this->head;
    while (elem != nullptr) {
        if (elem->value == value) {
            return elem;
        }
        elem = elem->next;
    }
    return nullptr; // no such element
}
```

Однако в таком случае внешнему коду необходимо предоставлять доступ ко внутреннему устройству коллекции:
внутренним структурам, представляющим узлы списка; внутренней логике расположения элементов и т.д.
Это нарушает инкапсуляцию.

Вместо этого при объектно-ориентированном подходе используются специальные объекты, схожие по функционалу с указателями,
но скрывающие внутри все детали реализации и сложную логику доступа к элементам.
Такие объекты называются __итераторами__.

## Итераторы в C++

```c++
MyArray<int> myIntArray;
for (MyArray<int>::Iterator iter = myIntArray.begin(); iter != myIntArray.end(); ++iter) {
    std::cout << *iter << std::endl;
}
```

В примере выше `MyArray<T>::Iterator` -- это класс, описанный внутри шаблонного класса `MyArray<T>`.
В нём переопределены операторы `++` (для перемещения итератора на следующий по порядку элемент), `*` (для доступа к элементу, на который сейчас указывает итератор), и `!=` (для сравнения).
Метод `begin()` класса `MyArray<T>` возвращает итератор, указывающий на первый элемент массива.
Метод `end()` возвращает специальное значение, которое получается если выполнить `++` с итератором на последний элемент.

Также итераторы могут предоставлять операторы `--` для движения в обратном направлении, и оператор `->` лд доступа к членам элемента, на который указывает итератор.

### Операторы * и ->
На перегрузку оператора` `*` не специальных ограничений
```c++
T & operator*() {
    return this->pointedValue;
}
T const & operator*() const {
    return this->pointedValue;
}
```

Перегруженный оператор `->` должен всегда возвращать указатель, или другой объект (по ссылке), для которого оператор `->` уже реализован.
```c++
T * operator->() {
    return &this->pointedValue;
}
T const * operator->() const {
    return &this->pointedValue;
}
// ERROR: T must have -> operator
// T operator->() {
//     return this->pointedValue;
// }
```

### Range-based for

Громоздкий цикл для перебора элементов с помощью итератора часто бывает неудобен в написании.
```c++
for (auto iter = myIntArray.begin(); iter != myIntArray.end(); ++iter) {
    std::cout << *iter << std::endl;
}
```

В C++11 появилась возможность краткой записи такого цикла:
```c++
for (int & iter : myIntArray) {
    std::cout << it << std::endl;
}
for (int x : myIntArray) {
    std::cout << x << std::endl;
}
```

### Пример
Шаблон связного списка с итератором мог бы выглядеть так:
```c++
#include <iostream>
#include <iterator>
#include <cassert>

template<typename T>
class List {
private:
    struct Node {
        T value;
        Node * next;
    };
    
    Node * head;
public:
    List();
    List(List const & orig);
    ~List();
    List & operator=(List const & that);
    bool isEmpty() const;
    T & getHead();
    void append(T const & val);

    class Iterator : public std::iterator<std::input_iterator_tag, T> {
    public:
        explicit Iterator(Node * node) : node(node) {}
        T & operator*() {
            return node->value;
        }
        T * operator->() {
            return &node->value;
        }
        Iterator & operator++() {
            node = node->next;
            return *this;
        }
        bool operator==(Iterator const & that) const {
            return node == that.node;
        }
        bool operator!=(Iterator const & that) const {
            return !(*this == that);
        }
    private:
        Node * node;
    };

    Iterator begin() {
        return Iterator(head);
    }
    Iterator end() {
        return Iterator(nullptr);
    }
};

int main() {
    List<int> l;
    l.append(4);
    l.append(8);
    l.append(15);
    l.append(16);
    l.append(23);
    l.append(42);

    for (int & it : l) {
        std::cout << it << std::endl;
    }
    for (int x : l) {
        std::cout << x << std::endl;
    }

    return 0;
}
```
