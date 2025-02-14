#ifndef _PRODUCT_H_
#define _PRODUCT_H_

#include <string>

enum _suppliers_ {
    bratyxi_42,
    rnb_club,
    barabulka,
    double_r,
    unknown_supplier
};

class Product
{
    unsigned id;
    std::string nameplate {nullptr};
    unsigned cost_price {0};
    _suppliers_ sup {unknown_supplier};

    static unsigned next_id;

public:

    Product(const char*, unsigned int, _suppliers_);

    // Зона геттеров

    unsigned get_id() const { return id; }
    const std::string& get_name() const { return nameplate; }
    unsigned get_price() const { return cost_price; }
    _suppliers_ get_supplier() const { return sup; }

    // Зона сеттеров

    void set_price(unsigned new_price) { cost_price = new_price; }
    void set_supplier(_suppliers_ new_sup) { sup = new_sup; }
    void set_name(const char* new_name) { nameplate = new_name; }
    
    ~Product() { std::cout << nameplate << " deleted\n"; }

};

#endif