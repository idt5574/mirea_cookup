#include "Node.h"

template <typename T>
using shared_node_obj = std::shared_ptr<Node<T>>;

template <typename T>
Node<T>::Node() = default;

template <typename T>
Node<T>::Node(const Node<T>& other) : data(other.data) {}

template <typename T>
Node<T>::Node(Node<T>&& move) : data(move.data) 
{
    move.data = T();
}

template <typename T>
Node<T>::Node(const T& object) : data(object) {}

template <typename T>
Node<T>::Node(std::shared_ptr<Node<T>>& other) : data(other.get()->data) {}

// Setters

template <typename T>
void Node<T>::set_next(std::shared_ptr<Node<T>> new_next)
{
    next.reset();
    next = new_next;
}

template <typename T>
void Node<T>::set_prev(std::shared_ptr<Node<T>> new_prev)
{
    prev.reset();
    prev = new_prev;
}

// Getters

template <typename T>
T& Node<T>::get_raw_data()
{
    return data;
}

template <typename T>
std::shared_ptr<Node<T>> Node<T>::get_prev()
{
    return prev;
}

template <typename T>
std::shared_ptr<Node<T>> Node<T>::get_next()
{
    return next;
}

// Other methods

// Переопределённые операции

template <typename T>
const Node<T>& Node<T>::operator=(const Node<T>& other)
{
    data = other.data;
}

template <typename T>
const Node<T>& Node<T>::operator=(Node<T>&& move)
{
    data = move.data;
    move.data = T();
}

// Destructor

template <typename T>
Node<T>::~Node()
{
    next.reset();
    prev.reset();
}