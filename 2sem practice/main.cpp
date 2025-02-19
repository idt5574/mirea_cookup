#include <iostream>

#include "linked_list.cpp"

int main()
{
    DoublyLinkedList lst {(Product){"42 merch", 42000, bratyxi_42}, (Product){"kyrit_kruto", 12000, rnb_club}};

    lst.traverse();

    lst.push((Product){"Goblin", 1000000, rnb_club});
    lst.remove(1);

    lst.traverse();

    return 0;
}