#include "node.h"

using shared_node_obj = std::shared_ptr<Node>;

Node::Node(const Product& other)
{
    data = std::make_shared<Product>(other);
}

void Node::set_nameplate(const char* n)
{ data->set_name(n); }

void Node::set_price(unsigned p)
{ data->set_price(p); }

void Node::set_supplier(_suppliers_ s)
{ data->set_supplier(s); }

void Node::set_next(std::shared_ptr<Node> n)
{ next.swap(n); }

void Node::set_prev(std::shared_ptr<Node> n)
{ prev.swap(n); };

unsigned Node::get_id()
{ return data->get_id(); }

const std::string& Node::get_name()
{ return data->get_name(); }

unsigned Node::get_price()
{ return data->get_price(); }

_suppliers_ Node::get_supplier()
{ return data->get_supplier(); }

shared_node_obj Node::get_prev()
{ return prev; }

shared_node_obj Node::get_next()
{ return next; }

Node::~Node()
{
    data.reset();
    prev.reset();
    next.reset();
}
