#include "Product.h"
#include <iostream>
#include <cstring>
#include <memory>

unsigned Product::next_id = 0;

using shared_product_obj = std::shared_ptr<Product>;

Product::Product(std::string nameplate, unsigned cost=0, _suppliers_ sup=unknown_supplier, unsigned id=next_id)
: nameplate(nameplate), cost_price(cost), sup(sup), id(id)
{ next_id++; }

Product::Product(const Product& other)
{
    nameplate = other.nameplate;
    cost_price = other.cost_price;
    sup = other.sup;
    id = other.get_id();
}

void Product::set_price(unsigned new_price)
{ cost_price = new_price; }

void Product::set_supplier(_suppliers_ new_sup)
{ sup = new_sup; }

void Product::set_name(const char* new_name)
{ nameplate = new_name; }

unsigned Product::get_id() const
{ return id; }

const std::string& Product::get_name() const
{ return nameplate; }

unsigned Product::get_price() const
{ return cost_price; }

_suppliers_ Product::get_supplier() const
{ return sup; }

