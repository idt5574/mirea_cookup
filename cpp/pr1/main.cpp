#include <iostream>
#include "Product.cpp"

int main()
{
    Product obj {"best product\0", 42, bratyxi_42};
    Product obj_2 {"swag product\0", 300, rnb_club};

    std::cout << obj.get_id() << ' ' << obj.get_name() << ' ' << obj.get_price() << ' ' << obj.get_supplier() << std::endl;
    std::cout << obj_2.get_id() << ' ' << obj_2.get_name() << ' ' << obj_2.get_price() << ' ' << obj_2.get_supplier() << std::endl;

    obj.set_name("42 broduct\0");

    std::cout << std::endl << obj.get_id() << ' ' << obj.get_name() << ' ' << obj.get_price() << ' ' << obj.get_supplier() << std::endl;

    printf("\n");

    return 0;
}