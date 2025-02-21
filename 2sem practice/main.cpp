#include <iostream>

#include "linked_list.cpp"

int main()
{
    DoublyLinkedList lst_1 {(Product){"42 merch", 42000, bratyxi_42, 1}, (Product){"kyrit_kruto", 12000, rnb_club, 2}};
    lst_1.push((Product){"Goblin", 1000000, rnb_club, 3});

    std::cout << std::endl << "lst_1 init" << std::endl;
    lst_1.traverse();

    DoublyLinkedList lst_2 {(Product){"Wok", 250, rnb_club, 4}, (Product){"Burger", 250, bratyxi_42, 5}};

    std::cout << std::endl << "lst_2 init" << std::endl;
    lst_2.traverse();

    lst_1 += lst_2;

    std::cout << std::endl << "lst_1 += lst_2" << std::endl;
    lst_1.traverse();

    lst_2 -= lst_1;

    std::cout << std::endl << "lst_2 -= lst_1" << std::endl;
    lst_2.traverse();
    
    return 0;
}