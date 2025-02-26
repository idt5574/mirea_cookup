#include "node.h"

using shared_node_obj = std::shared_ptr<Node>; // Объявляем новое имя для типа shared_ptr<Node>

// Конструктор по умолчанию

Node::Node()
{
    data = Product();
}

// Конструктор копирования

Node::Node(const Node& other)
{
    data = other.data;
}

// Конструктор перемещения

Node::Node(Node&& move)
{
    data = move.data;
    move.data = Product();
}

Node::Node(const Product& other) // Конструктор преобразования
{
    data = other; // Переопределённый оператор присваивания продукта (см. Product.cpp)
}

// Следующая часть сеттеров сделана потому, что напрямую к объекту класса Product из объекта класса Node не можем

void Node::set_nameplate(const char* n)
{ data.set_name(n); }

void Node::set_price(unsigned p)
{ data.set_price(p); }

void Node::set_supplier(_suppliers_ s)
{ data.set_supplier(s); }

// Конец вспомогательных сеттеров

void Node::set_next(std::shared_ptr<Node> n) // Сеттер для следующего объекта
{ next.swap(n); }

void Node::set_prev(std::shared_ptr<Node> n) // Сеттер для предыдущего объекта
{ prev.swap(n); };

// Далее идут вспомогательные геттеры, сделанные потому, что напрямую к объекту класса Product из объекта класса Node не можем

const unsigned& Node::get_id()
{ return data.get_id(); }

const std::string& Node::get_name()
{ return data.get_name(); }

const unsigned& Node::get_price()
{ return data.get_price(); }

const _suppliers_& Node::get_supplier()
{ return data.get_supplier(); }

// Конец вспомогательных геттеров

shared_node_obj Node::get_prev() // Геттер предыдущего объекта
{ return prev; }

shared_node_obj Node::get_next() // Геттер следующего объекта
{ return next; }

const Node& Node::operator=(const Node& other)
{
    data = other.data;
}

const Node& Node::operator=(Node&& move)
{
    data = move.data;
    move.data = Product();
}

Node::~Node() // Деструктор
{
    // reset - особый метод для умных указателей, позволяющий отвязать текущий объект от привязанного к нему в даннный момент указателя
    prev.reset();
    next.reset();
}
