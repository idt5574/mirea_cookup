#include <iostream>

#include "linked_list.cpp"

int main()
{
    DoublyLinkedList lst_1 {(Product){"42 merch", 42000, bratyxi_42}, (Product){"kyrit_kruto", 12000, rnb_club}};
    lst_1.push((Product){"Goblin", 1000000, rnb_club});

    DoublyLinkedList lst_2 {(Product){"Wok", 250, rnb_club}, (Product){"Burger", 250, bratyxi_42}};

    lst_2 = lst_2 + (Product){"Fries", 90, barabulka};

    lst_2.traverse();

    lst_2 = lst_2 - (Product){"Burger", 250, bratyxi_42, 4};

    lst_2.traverse();

    return 0;
}