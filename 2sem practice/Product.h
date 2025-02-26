#ifndef _PRODUCT_H_
#define _PRODUCT_H_

#include <string>

// Перечень имён для поставщиков

enum _suppliers_ {
    bratyxi_42,
    rnb_club,
    barabulka,
    double_r,
    unknown_supplier
};

// Класс продукта

class Product
{
    unsigned id {0};
    std::string nameplate;
    unsigned cost_price {0};
    _suppliers_ sup {unknown_supplier};

    static unsigned next_id;

public:

    // Конструкторы

    Product(); // По умолчанию
    Product(const Product&); // Копирования
    Product(Product&& move); // Перемещения
    Product(std::string, unsigned, _suppliers_, unsigned); // Преобразования

    // Setters

    void set_price(unsigned);
    void set_supplier(_suppliers_);
    void set_name(const char*);

    // Getters

    const unsigned& get_id() const;
    const std::string& get_name() const;
    const unsigned& get_price() const;
    const _suppliers_& get_supplier() const;

    // Refunded operators

    const Product& operator=(const Product&);
    const Product& operator=(Product&&);

    // Destructor

    ~Product() {}

};

#endif