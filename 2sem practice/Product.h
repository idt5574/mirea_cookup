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
    std::string nameplate;
    unsigned cost_price {0};
    _suppliers_ sup {unknown_supplier};

    static unsigned next_id;

public:

    // Constructors

    Product(std::string, unsigned int, _suppliers_, unsigned);
    Product(const Product&);

    // Setters

    void set_price(unsigned);
    void set_supplier(_suppliers_);
    void set_name(const char*);

    // Getters

    unsigned get_id() const;
    const std::string& get_name() const;
    unsigned get_price() const;
    _suppliers_ get_supplier() const;
    
    // Destructor

    ~Product() {}

};

#endif