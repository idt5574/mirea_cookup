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

    // Constructors

    Node(const Product&);

    // Setters

    void set_nameplate(const char*);
    void set_price(unsigned);
    void set_supplier(_suppliers_);

    void set_next(std::shared_ptr<Node>);
    void set_prev(std::shared_ptr<Node>);

    // Getters

    unsigned get_id(); 
    const std::string& get_name();
    unsigned get_price();
    _suppliers_ get_supplier();

    std::shared_ptr<Node> get_prev();
    std::shared_ptr<Node> get_next();

    // Other methods

    // Destructor

    ~Node();
    
};

#endif