#include <iostream>

#include "linked_list.cpp"

int main()
{
    Node<int> dflt_node_init;
    
    Node trans_node_init_1 {-5};

    Node copy_node_init {trans_node_init_1};
    
    Node move_node_init {(Node<int>){-10}};

    std::cout << "Node variables: " << std::endl;
    std::cout << dflt_node_init.get_raw_data() << ' ' << trans_node_init_1.get_raw_data() << 
            ' ' << copy_node_init.get_raw_data() << ' ' << move_node_init.get_raw_data() << std::endl;
    std::cout << std::endl;

    DoublyLinkedList<int> list_int;
    list_int.push(1);
    list_int.push(2);
    list_int.push(3);

    std::cout << "list_int created\n";

    DoublyLinkedList<std::string> list_string;
    list_string.push("one");
    list_string.push("two");
    list_string.push("three");

    std::cout << "list_string created\n";

    DoublyLinkedList<double> list_double; std::cout << "init\n";
    list_double.push(1); std::cout << "push 1\ns";
    list_double.push(2); std::cout << "push 2\n";
    list_double.push(3, true); std::cout << "push 3 in end\n";

    std::cout << "list_double created\n";

    std::cout << "list_int:" << std::endl;
    for(int i = 0; i < list_int.get_length(); i++)
        std::cout << list_int[i].get_raw_data() << std::endl;
    std::cout << std::endl;

    std::cout << "list_string:" << std::endl;
    for(int i = 0; i < list_string.get_length(); i++)
        std::cout << list_string[i].get_raw_data() << std::endl;
    std::cout << std::endl;

    std::cout << "list_double:" << std::endl;
    for(int i = 0; i < list_double.get_length(); i++)
        std::cout << list_double[i].get_raw_data() << std::endl;
    std::cout << std::endl;

    return 0;
}