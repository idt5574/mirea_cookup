#include <iostream>

#include "linked_list.cpp"

int main()
{
    DoublyLinkedList lst {{}, {1, "Boots", 20000, bratyxi_42}};

    lst.push({2, "T-Shirt", 5000, bratyxi_42}, true);
    lst.push({3, "Jeans", 7000, bratyxi_42}, true);
    lst.push({4, "Jacket", 15000, bratyxi_42}, true);
    lst.push({5, "Hat", 3000, bratyxi_42}, true);
    lst.push({6, "Gloves", 2500, bratyxi_42}, true);
    lst.push({7, "Scarf", 3000, bratyxi_42}, true);
    lst.push({8, "Socks", 3000, bratyxi_42}, true);
    lst.push({9, "Sweater", 8000, bratyxi_42}, true);
    lst.push({10, "Shorts", 4000, bratyxi_42}, true);
    lst.push({11, "Belt", 3500, bratyxi_42}, true);
    lst.push({12, "Shoes", 12000, bratyxi_42}, true);

    DoublyLinkedList filtered_lst = lst.filter(std::vector<double>{2500, 3000});

    filtered_lst.traverse();
    

    return 0;
}