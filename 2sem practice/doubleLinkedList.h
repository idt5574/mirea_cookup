#ifndef _D_L_L_H_
#define _D_L_L_H_

#include "Product.cpp"
#include "Node.cpp"
#include <memory>

using shared_node_obj = std::shared_ptr<Node>;

class DoubleLinkedList
{
    shared_node_obj head {nullptr};
    shared_node_obj tail {nullptr};

    static unsigned len;

public:

    DoubleLinkedList(shared_node_obj head) : head(head)
    { len = 1; }

    DoubleLinkedList(shared_node_obj head, shared_node_obj tail)
    : head(head), tail(tail)
    { len = 2; }

    shared_node_obj get_head() { return head; }
    shared_node_obj get_tail() { return tail; }

    void push(shared_node_obj new_node)
    {
        tail->set_next(new_node);
        len++;

        new_node->set_prev(tail);
        tail = new_node;
    }

    void pop()
    {
        if(tail == head)
    }

};

#endif