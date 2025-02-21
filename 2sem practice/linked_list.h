#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include "node.cpp"

enum _search_result_
{
    price,
    id,
    supplier,
    position
};

class DoublyLinkedList
{
    shared_node_obj head;
    shared_node_obj tail;

public:

    DoublyLinkedList(const DoublyLinkedList& other);

    DoublyLinkedList(const Product& data)
    {
        head = std::make_shared<Node>(data);
        tail.swap(head);
    }

    DoublyLinkedList(const Product& d1, const Product& d2)
    {
        head = std::make_shared<Node>(d1);
        tail = std::make_shared<Node>(d2);

        head->set_next(tail);
        tail->set_prev(head);
    }

    void push(const Product&);
    void push(const Product&, bool);

    void insert(const Product&, int);

    shared_node_obj pop();
    shared_node_obj pop(bool);

    shared_node_obj remove(int);

    void traverse();
    void traverse(bool);

    int length();

    unsigned search(const Product& other);

    const DoublyLinkedList& operator =(const DoublyLinkedList& other);
    const DoublyLinkedList& operator +(const DoublyLinkedList& other);
    const DoublyLinkedList& operator +(const Product& other);
    const DoublyLinkedList& operator -(const Product& other);

};

#endif