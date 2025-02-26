#include "Product.h" // Копируем информацию из заголовочного файла
#include <iostream> 
#include <cstring> // Для стандартных функций работы со стоками языка Си (аналог string.h) 

unsigned Product::next_id = 0; // Инициализируем статическую переменную

using shared_product_obj = std::shared_ptr<Product>; // Объявляем новое имя для типа shared_ptr<Product>

/* shared_ptr - один из видов умных указателей в языке с++.
    Указатель типа shared_ptr берёт на себя ответственность за то, чтоб
    у вас в программе не было утечек памяти, и когда уже ни один объект не ссылается
    на shared_ptr, то указатель сам удаляется. */

// Констуктор по умолчанию (позволяет создавать объект без передачи каких-либо параметров)

Product::Product()
{
    nameplate = "unnamed";
}

// Конструктор копирования (позволяет инициализировать новый объект с копией данных другого объекта)

Product::Product(const Product& other) 
: nameplate(other.nameplate), id(other.id), cost_price(other.cost_price), sup(other.sup) {}

// Конструктор копирования перещемением (позволяет инициализировать новый объект перемещением данных из другого объекта, данные другого объекта обнуляются)

Product::Product(Product&& move)
{
    id = move.id;
    nameplate = move.nameplate;
    sup = move.sup;
    cost_price = move.cost_price;

    // Так как конструктор "перемещает" данные из одного объекта в другой - нам нужно обнулить данные переданного в конструктор объекта
    id = 0;
    nameplate = "unnamed";
    sup = unknown_supplier;
    cost_price = 0;
}

// Конструктор преобразования (данные разных типов преобразует в наш класс)

Product::Product(std::string nameplate, unsigned cost=0, _suppliers_ sup=unknown_supplier, unsigned id=next_id)
: nameplate(nameplate), cost_price(cost), sup(sup), id(id)
{ next_id++; }

void Product::set_price(unsigned new_price) // Установка цены
{ cost_price = new_price; }

void Product::set_supplier(_suppliers_ new_sup) // Установка поставщика
{ sup = new_sup; }

void Product::set_name(const char* new_name) // Установка имени
{ nameplate = new_name; }

const unsigned& Product::get_id() const // Получение айдишника
{ return id; }

const std::string& Product::get_name() const // Получение имени
{ return nameplate; }

const unsigned& Product::get_price() const // Получение цены
{ return cost_price; }

const _suppliers_& Product::get_supplier() const // Получение поставщика (тк enum - возвращаемое значение - число)
{ return sup; }

const Product& Product::operator=(const Product& other) // Переопределённый оператор присваивания продукта копированием, чтоб копирование не происходило побайтно
{
    if(this == &other) return *this;

    id = other.id;
    nameplate = other.nameplate;
    cost_price = other.cost_price;
    sup = other.sup;

    return *this;
}

const Product& Product::operator=(Product&& move) // Переопределённый оператор присваивания продукта перемещением
{
    if(this == &move) return *this;

    id = move.id;
    nameplate = move.nameplate;
    sup = move.sup;
    cost_price = move.cost_price;

    // Так как конструктор "перемещает" данные из одного объекта в другой - нам нужно обнулить данные переданного в конструктор объекта
    id = 0;
    nameplate = "unnamed";
    sup = unknown_supplier;
    cost_price = 0;

    return *this;
}
