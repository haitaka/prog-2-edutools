# Мотивация

## Тип данных
*   Множество значений
*   Множество операций
 
### Примитивные

`unsigned char`:
* `[0; 255]`
* `-, +, *, /, >, <, ...`
 
`int *` :
* `[0; 2**32)` или `[0; 2**64)`
* `*, +, >, <, ...`

### Составные

```c
struct ReducedFraction {
    int numerator; // числитель
    unsigned int denominator; // знаменатель
};
```

*   Декартово произведение множеств значений отдельных полей
    * `[INT_MIN; INT_MAX] x [0; UINT_MAX]`
*   Чтение и запись полей

__Корректные состояния__ -- _подмножество_ множества значений, определяющееся тем, какой смысл мы вкладываем в тип.

Так знаменатель никакой дроби не должен быть равен `0`.

Более того, в примере выше мы назвали нашу структуру `ReducedFraction`, подразумевая что дробь всегда должна быть _приведённой_.
Язык C никак не позволяет выразить такие свойства (инварианты) множества значений пользовательского типа данных.

```c
struct ReducedFraction f1 = {3, 2};
struct ReducedFraction f2 = {15, 10};
struct ReducedFraction f3 = {42, 0};
```

Для ограничения множества допустимых значений пользовательского типа только корректными состояниями необходимо:
1.  Гарантировать корректность начального состояния
    ```c
    ReducedFraction createCorrect(int num, unsigned int denom) {
        assert(denom != 0);
        ReducedFraction f = {num, denom};
        reduce(&f);
        return f;
    }
    ```
2.  Ограничить множество _допустимых операций_ только такими, которые не нарушают корректность 
    (переводят объект из одного _корректного_ состояния в другое).
    ```c
    ReducedFraction sum(ReducedFraction f1, ReducedFraction f2) {
        ReducedFraction result = {
            f1.numerator * f2.denominator,
            f2.numerator * f1.denominator,
        };
        reduce(&result);
        return result;
    }
    ```

Однако у пользователя (программиста, использующего наш тип данных) всё-равно остаётся возможность испортить состояние:
забыть проинициализировать дробь, проинициализировать в обход `createCorrect`, записывать поля непрямую, 
реализовать свою функцию для сложения дробей вместо `sum` и забыть привести (сократить) результат.

Ошибки неизбежны, важно ограничить пространство возможностей для их совершения.

# Объектно-ориентированный подход (TODO ?)

*   Ограничить прямой доступ к полям структуры;
*   Явно описать множество допустимых операций в виде функций, переводящих объект из одного _корректного_ состояния в другое _корректное_ состояние.

Таким образом внешний код не будет иметь возможности испортить состояние объекта.
А значит, для внешнего наблюдателя множество возможных состояний будет совпадать с множеством корректных состояний.

## C++

Язык C++ позволяет описывать связанные со структурой методы непосредственно в теле структуры.
Такие функции называют __методами__.

А для ограничения внешнего доступа к членам (полям или методам) структуры C++ предоставляет модификаторы области видимости
`public` для членов доступных извне и `private` для членов видимых только изнутри.
```c++
struct ReducedFraction {
public:
    void add(/*ReducedFraction * this,*/ ReducedFraction * that) {
        this->numerator = this->numerator * that->denominator,
        this->denominator = that->numerator * this->denominator,
        this->reduce();
    }
    
private:
    void reduce(/*ReducedFraction * this*/);
    
    int numerator;
    unsigned int denominator;
};
```

Обратите внимание на ключевое слово `this`.
Оно обозначает скрытый параметр типа "указатель на структуру", который неявно подставляется в каждый метод.
При вызове метода в качестве значения параметра `this` передаётся указатель стоящий слева от имени метода.
```c++
f1.add(&f2);
```
В этом примере указатель `&f1` станет значением параметра `this`, а указатель `&f2` будет передан в качестве первого аргумента (`that`).

Для краткости при обращении к членам структуры `this->` можно не писать.

### `class`

В C++ ключевое слово `class` используется для описания структуры, члены которой по-умолчанию считаются `private`.

В дальнейшем пользовательские составные типы данных мы будем называть именно _классами_.

### Конструкторы

Через сокрытие полей и введение методов нам удалось ограничить множество возможных операций так,
что никакая операция не может перевести объект из корректно состояния в некорректное.

Но нам также нужна возможность задавать корректное _начальное состояние_ объекта.
Для этого в C++ используются специальные методы, называемые _конструкторами_.

```c++
class ReducedFraction {
public:
    ReducedFraction(int num, unsigned int denom) : numerator(num), denominator(denom) {
        assert(denominator != 0);
        reduce();
    }
private:
    void reduce();

    int numerator;
    unsigned int denominator;
}
```

У конструкторов не пишется возвращаемый тип, а их имя всегда совпадает с именем класса.

Помимо обычного тела как у других функций, в конструкторах также можно отдельно описать инициализацию полей класса.
Поля и их значения перечисляются через запятую после двоеточия перед основным телом конструктора.
Такой синтаксис называется _списком инициализации_ членов класса.
Списки инициализации членов выполняются _до_ основного тела конструктора.
В дальнейшем мы увидим, почему это может быть полезно.

Важно заметить, что инициализация полей из списка инициализации выполняется _не_ в порядке списка инициализации,
а в том порядке, в котором поля были _объявлены_ в самом классе.

Как и другие методы, конструкторы можно перегружать (overload).
Во избежание дублирования кода из одного перегруженного конструктора можно вызывать другой (делегировать).
Делается это в синтаксисе списков инициализации.
```c++
    ReducedFraction(int num, unsigned int denom) : numerator(num), denominator(denom) {
        assert(denominator != 0);
        reduce();
    }

    ReducedFraction(int integer) : ReducedFraction(integer, 1) {
    }

    ReducedFraction() : ReducedFraction(0) {
    }
```

Конструктор без параметров называется конструктором _по-умолчанию_.
В случае отсутствия у класса других конструкторов, он будет сгенерирован автоматически.


При создании новой переменной соответствующий конструктор будет вызван автоматически.
```c++
int main() {
    ReducedFraction f1(3, 2); // вызывает ReducedFraction(int, unsigned int)
    ReducedFraction f2(42); // вызывает ReducedFraction(int)
    ReducedFraction f3; // вызывает конструктор по-умолчанию ReducedFraction()

    return 0;
}
```

# Операторы `new`/`delete`
В примере выше все три объекта создаются в _автоматической_ (стековой) памяти.
Для создания объектов в _динамической_ памяти C++ предоставляет оператор `new`.
Оператор `delete` используется для освобождения ранее выделенной динамической памяти.
```c++
int main() {
    ReducedFraction * f1 = new ReducedFraction(3, 2); // вызывает ReducedFraction(int, unsigned int)
    ReducedFraction * f2 = new ReducedFraction(42); // вызывает ReducedFraction(int)
    ReducedFraction * f3 = new ReducedFraction(); // вызывает конструктор по-умолчанию ReducedFraction()

    delete f1;
    delete f2;
    delete f3;

    return 0;
}
```

## Массивы в динамической памяти
```c++
int main() {
    ReducedFraction * array = new ReducedFraction[8];
    delete[] array;

    return 0;
}
```
Элементы массива выделяемого с помощью `new` будут проинициализированы с помощью конструктора _по-умолчанию_.

Для освобождения памяти массива следует использовать оператор `delete[]`.

