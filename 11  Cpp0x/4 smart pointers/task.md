# Умные указатели
C++ -- язык программирования с ручным управлением памятью.
Главные проблемы:

1. Обращение к непроинициализированной памяти
2. Утечки памяти (висячие ссылки)

## unique_ptr

```c++
Pair * foo() {
    Pair * result = new Pair(23, 42);
    int a;
    std::cin >> a;
    if (a == 5) {
        // утечка памяти, выделенной для result
        throw new std::exception("error");
    }
    return result;
}
```

Теперь `result` -- это smart pointer,
он владеет указателем на новый объект класса `Pair`
```c++
#include <memory>

Pair * foo() {
    std::unique_ptr<Pair> result(new Pair(23, 42));
    int a;
    std::cin >> a;
    if (a == 5) {
        // result -- локальная переменная =>
        // => он будет уничтожен при выбросе исключения =>
        // => память для объекта класса Pair будет очищена автоматически!
        throw new std::exception("error");
    }
    return result.release();
}
```

А лучше так:
```c++
std::unique_ptr<Pair> foo() {
    auto result = std::make_unique<Pair>(23, 42);
    int a;
    std::cin >> a;
    if (a == 5) {
        throw std::logic_error("error");
    }
    return result;
}
```

`unique_ptr` -- "умный" указатель для уникального владения объектом (через указатель на этот объект)

`unique_ptr` очищает память, по указателю, которым владеет когда:
1. Сам `unique_ptr` уничтожается
2. `unique_ptr` начинает владеть новым указателем (`operator =`)
3. Вызван метод `reset()`

Для корректной работы программы только один `unique_ptr` должен владеть объектом в каждый момент времени!

В `unique_ptr` перегружен `operator ->` для доступа к указателю
```c++
auto result = std::make_unique<Pair>(23, 42);
result->print();
```

В `unique_ptr` перегружен move-конструктор и move-`operator =`
```c++
std::unique_ptr<Pair> result = std::unique_ptr<Pair>(new Pair(23, 42));
result->print();
result = std::unique_ptr<Pair>(new Pair(4, 8));
// result теперь владеет другим объектом => 
// память, выделенная под Pair(23, 42), освобождается
```

```c++
Pair * test = new Pair(23, 42);
std::unique_ptr<Pair> result(test);
result->print();
result = std::unique_ptr<Pair>(new Pair(4, 8));
// result теперь владеет другим объектом =>
// память, выделенная под test, освобождается
test->print(); // напечатает мусор или выдаст ошибку
```

```c++
void bar() {
    Pair * test = new Pair(23, 42);
    std::unique_ptr<Pair> result(test);
    std::unique_ptr<Pair> result2(test);
}
// повторное освобождение test через result2
```

Конструктор копирования запрещен, копировать нельзя.

Конструктор перемещения (оператор присваивания с перемещением)
Присутствуют и играют очень важную роль: в них у rvalue забирается владение над объектом.

```c++
unique_ptr(unique_ptr const &) = delete;
unique_ptr & operator=(unique_ptr const &) = delete;
```

## shared_ptr
А что делать, если нужно работать с одним объектом одновременно
в нескольких местах?

Необходимо совместное владение

```c++
#include <memory>

void bar() {
    Pair * test = new Pair(23, 42);
    std::shared_ptr<Pair> result(test);
    // теперь result владеет новым объектом класса Pair
    std::cout << "ptr counted " << result.use_count() << " times";
}
```

Важно: до этого никто не владел test!
Иначе UB


```c++
#include <memory>

void bar() {
    std::shared_ptr<Pair> result = std::make_shared<Pair>(23, 42);
    // теперь result владеет новым объектом класса Pair
    std::cout << "ptr counted " << result.use_count() << " times";
    std::shared_ptr<Pair> result2 = result;
    // теперь еще и result2 владеет этим объектом класса Pair
    baz(result2);
    result2.reset();
    // result2 перестает владеть объектом класса Pair,
    // но объект не удаляется, т.к. result все еще владеет им
    std::cout << "ptr counted " << result.use_count() << " times";
}
// result перестает владеть объектом класса Pair,
// объект удаляется, т.к. больше никто им не владеет
```

*   `shared_ptr` -- "умный" указатель для совместного владения объектом (через указатель на этот объект)
*   `shared_ptr` -- "разделяет" владение объектом, когда создается новый `shared_ptr` с помощью конструктора копирования или оператора присваивания
*   `shared_ptr` перестает владеть объектом, когда уничтожается, либо когда начинает владеть другим объектом
*   Память, выделенная под объект, очищается, когда последний из `shared_ptr` перестает владеть объектом.

Важно: новые владельцы появляются не сами по себе, а из старых.
```c++
void bar() {
    Pair * test = new Pair(23, 42);
    std::shared_ptr<Pair> result(test);
    // теперь result владеет новым объектом класса Pair
    std::cout << "ptr counted " << result.use_count() << " times";
    std::shared_ptr<Pair> result2(test);
    // теперь result2 владеет тем же объектом класса Pair.. Но с result они никак не связаны!
    std::cout << "ptr counted " << result2.use_count() << " times";
}
// выведет два раза "ptr counted 1 times"
// потом kaboom!!
```

