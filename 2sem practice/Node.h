#ifndef _NODE_H_
#define _NODE_H_

#include "Product.cpp"
#include <memory>

class Node
{
    shared_product_obj data {nullptr};
    shared_product_obj prev {nullptr};
    shared_product_obj next {nullptr};
    
public:

    Node(Product* d)
    : data(d)
    {}

    void set_next(std::shared_ptr<Node> n)
    {
        if(this == n.get()) return;

        next = n->data;
    }

    void set_prev(std::shared_ptr<Node> p)
    {
        if(this == p.get()) return;

        prev = p->data;
    }

    shared_product_obj get_data() { return data; }
    shared_product_obj get_next() { return next; }
    shared_product_obj get_prev() { return prev; }

};

#endif