# Деструкторы

Часто объектам программы требуется доступ к тем системным ресурсам, таким как динамическая память, 
файлы, или сетевые соединения.

Как правило, какой-то один объект становится ответственным одновременно и за выделение и за освобождение 
связанных с ним ресурсов, предоставляя другим объектам лишь ограниченный интерфейс для работы с этими ресурсами.
Такой объект называют *владельцем* ресурса.
Если речь идёт про динамическую память, то указатель, хранящийся во *владельце* этой памяти, 
называют *владеющим указателем*, а все другие указатели на эту память *невладеющими*.

## Resource Acquisition Is Initialization (RAII)

Хорошей практикой управления ресурсами считается привязка времени жизни ресурса ко времени жизни владеющего им объекта.
То есть, захват ресурса при создании (инициализации) объекта и освобождение этого ресурса при разрушении объекта.

## Деструкторы в C++

Для описания действий необходимых перед разрушением объекта в языке C++ используются специальные методы -- *деструкторы*.

Деструктор описывается как метод без возвращаемого типа и без параметров, с именем, состоящем из символа `~` и имени класса.
```c++
class Array {
public:
    Array() : data(new int[42]) {}
    ~Array() {
        delete[] data;
    }
private:
    int * data; // owning pointer
};
```
В примере выше класс `Array` владеет массивом из `42` целых чисел на протяжении всей своей жизни.
Выделение массива динамической памяти происходит в конструкторе `Array()`, а освобождение в деструкторе `~Array()`.o

## Вызов деструкторов

Деструкторы для объектов вызываются автоматически в момент окончания времени жизни объекта.

*   при завершении программы для объектов в статической памяти;
*   при выходе из области видимости для объектов в автоматической памяти;
*   при использовании оператора `delete` для объектов в динамической памяти
    *   при использовании оператора `detlete[]` для *каждого* элемента массива в динамической памяти
*   при завершении потока исполнения для объектов, локальных для этого потока (подробнее позже);
*   при размотке стека при пробросе исключения для объектов в автоматической памяти( подробнее позже).
