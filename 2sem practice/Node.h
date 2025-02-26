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

    // Setters

    void set_nameplate(const char*);
    void set_price(unsigned);
    void set_supplier(_suppliers_);

    void set_next(std::shared_ptr<Node>);
    void set_prev(std::shared_ptr<Node>);

    // Getters

    const unsigned& get_id(); 
    const std::string& get_name();
    const unsigned& get_price();
    const _suppliers_& get_supplier();

    std::shared_ptr<Node> get_prev();
    std::shared_ptr<Node> get_next();

    // Other methods

    // Переопределённые операции

    const Node& operator=(const Node&);
    const Node& operator=(Node&&);

    // Destructor

    ~Node();
    
};

#endif