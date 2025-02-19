#ifndef _NODE_H_
#define _NODE_H_

#include "Product.cpp"

#include <memory>

class Node
{
    shared_product_obj data;

    std::shared_ptr<Node> prev {nullptr};
    std::shared_ptr<Node> next {nullptr};

public:

    Node(const Product& other)
    {
        data = std::make_shared<Product>(other);
    }

    void set_nameplate(const char* n) { data->set_name(n); }
    void set_price(unsigned p) { data->set_price(p); }
    void set_supplier(_suppliers_ s) { data->set_supplier(s); }

    void set_next(std::shared_ptr<Node> n) { next.swap(n); }
    void set_prev(std::shared_ptr<Node> n) { prev.swap(n); };

    unsigned get_id() { return data->get_id(); }
    const std::string& get_name() { return data->get_name(); }
    unsigned get_price() { return data->get_price(); }
    _suppliers_ get_supplier() { return data->get_supplier(); }

    std::shared_ptr<Node> get_prev() { return prev; }
    std::shared_ptr<Node> get_next() { return next; }

    ~Node()
    {
        data.reset();
        prev.reset();
        next.reset();
    }
    
};

#endif