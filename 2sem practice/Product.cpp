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
