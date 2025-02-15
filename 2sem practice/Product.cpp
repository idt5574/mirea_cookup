#include "Product.h"
#include <iostream>
#include <cstring>
#include <memory>

unsigned Product::next_id = 0;
using shared_product_obj = std::shared_ptr<Product>;

Product::Product(const char* nameplate, unsigned cost=0, _suppliers_ sup=unknown_supplier)
: nameplate(nameplate), cost_price(cost), sup(sup)
{ id = next_id++; }

