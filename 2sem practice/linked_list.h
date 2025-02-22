#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include "node.cpp"
#include <cstring>

enum _search_result_
{
    price,
    id,
    supplier,
    position
};

enum _extra_return_values_
{
    _cant_find_object_ = 128128128
};

class DoublyLinkedList
{
    shared_node_obj head;
    shared_node_obj tail;

public:

    DoublyLinkedList(const DoublyLinkedList&);

    DoublyLinkedList(const Product&);

    DoublyLinkedList(const Product&, const Product&);

    DoublyLinkedList(const char*);

    void push(const Product&);
    void push(const Product&, bool);

    void insert(const Product&, int);

    shared_node_obj pop();
    shared_node_obj pop(bool);

    shared_node_obj remove(int);

    void traverse();
    void traverse(bool);
    void traverse(const char*, bool);

    int length();

    unsigned search(const Product&);

    const DoublyLinkedList& operator =(const DoublyLinkedList&);

    const DoublyLinkedList& operator +(const DoublyLinkedList&);
    const DoublyLinkedList& operator +(const Product&);

    const DoublyLinkedList& operator -(const DoublyLinkedList&);
    const DoublyLinkedList& operator -(const Product&);

    const DoublyLinkedList& operator +=(const DoublyLinkedList&);
    const DoublyLinkedList& operator +=(const Product&);

    const DoublyLinkedList& operator -=(const DoublyLinkedList&);
    const DoublyLinkedList& operator -=(const Product&);

    bool save(const char*);
    bool load(const char*);

};

#endif