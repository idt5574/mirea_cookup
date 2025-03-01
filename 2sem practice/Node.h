#ifndef _NODE_H_
#define _NODE_H_

#include "Product.cpp" // Копируем именно .cpp файл, тк если скопируем сюда заголовочный файл - не получим реализаций методов

#include <memory>

// Класс ноды (элемента связного списка)

class Node
{
    Product data; 

    std::shared_ptr<Node> prev {nullptr}; // Умный указатель на предыдущую ноду
    std::shared_ptr<Node> next {nullptr}; // Умный указатель на следующую ноду

public:

    // Constructors

    Node();
    Node(const Node&);
    Node(Node&&);

    Node(const Product&);
    Node(std::shared_ptr<Node>&);

    // Setters

    void set_nameplate(const char*);
    void set_price(double);
    void set_supplier(_suppliers_);

    void set_next(std::shared_ptr<Node>);
    void set_prev(std::shared_ptr<Node>);

    // Getters

    const unsigned& get_id(); 
    const std::string& get_name();
    const double& get_price();
    const _suppliers_& get_supplier();
    const Product& get_product();

    std::shared_ptr<Node> get_prev();
    std::shared_ptr<Node> get_next();

    // Other methods

    // Переопределённые операции

    const Node& operator=(const Node&);
    const Node& operator=(Node&&);

    const Node& operator=(double);
    const Node& operator=(unsigned);
    const Node& operator=(_suppliers_);
    const Node& operator=(const char*);
    const Node& operator=(const Product&);

    operator double();
    operator unsigned();
    operator _suppliers_();
    operator std::string();
    operator Product();

    // Destructor

    ~Node();
    
};

#endif