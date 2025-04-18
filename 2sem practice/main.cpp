#include <iostream>

#include "linked_list.cpp"

template <typename T>
void print_list(const DoublyLinkedList<T>& array, const std::string& name)
{
    std::cout << name << ':' << std::endl;
    for(int i = 0; i < array.get_length(); i++)
        std::cout << array[i].get_raw_data() << std::endl;
    std::cout << std::endl;
}

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
    list_int.push(4, true);
    list_int.remove(2);

    std::cout << "list_int created\n";

    DoublyLinkedList<std::string> list_string;
    list_string.push("one", true);
    list_string.push("two", true);
    list_string.push("three", true);
    list_string.insert("one/two", 1);
    list_string.pop(true);

    std::cout << "list_string created\n";

    DoublyLinkedList<double> list_double;
    list_double.push(1); 
    list_double.push(3); 
    list_double.push(2, true);
    list_double.insert(4, 2);
    list_double.pop();

    std::cout << "list_double created\n";

    DoublyLinkedList list_string_copy = list_string;

    std::cout << "list_string_copy created\n";

    DoublyLinkedList list_one_elem_init {1};

    std::cout << "list_one_elem_init created\n";

    DoublyLinkedList list_two_elem_init {3, 4};

    std::cout << "list_two_elem_init created\n";

    print_list(list_int, "list_int");
    print_list(list_string, "list_string");
    print_list(list_double, "list_double");
    print_list(list_string_copy, "list_string_copy");
    print_list(list_one_elem_init, "list_one_elem_init");
    print_list(list_two_elem_init, "list_two_elem_init");

    return 0;
}