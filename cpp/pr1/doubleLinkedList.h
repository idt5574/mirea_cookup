#ifndef _D_L_L_H_
#define _D_L_L_H_

#include "Product.cpp"

class Node
{
    Product* data {nullptr};
    Product* prev {nullptr};
    Product* next {nullptr};
    
public:

    Node(Product* d)
    : data(d)
    {}

    void set_next(Node* n)
    {
        if(this == n) return;

        next = n->data;
    }

    void set_prev(Node* p)
    {
        if(this == p) return;

        prev = p->data;
    }

    Product* get_data() { return data; }
    Product* get_next() { return next; }
    Product* get_prev() { return prev; }

};

class DoubleLinkedList
{
    Node* head {nullptr};
    Node* tail {nullptr};

    static unsigned len;

public:

    DoubleLinkedList(Node* head) : head(head)
    { len = 1; }

    DoubleLinkedList(Node* head, Node* tail)
    : head(head), tail(tail)
    { len = 2; }

    Node* get_head() { return head; }
    Node* get_tail() { return tail; }

    void push(Node* new_node)
    {
        tail->set_next(new_node);
        len++;

        new_node->set_prev(tail);
        tail = new_node;
    }

    void pop()
    {
        
    }

};

#endif