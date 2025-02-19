#include "linked_list.h"

#include <iostream>

void DoublyLinkedList::push(const Product& data)
{
    shared_node_obj new_node = std::make_shared<Node>(data);

    new_node->set_next(head);

    if(head != nullptr) 
        head->set_prev(new_node);

    head = new_node;
    new_node.reset();
}

void DoublyLinkedList::push(const Product& data, bool inEnd)
{
    if(!inEnd) return push(data);

    shared_node_obj new_node = std::make_shared<Node>(data);

    new_node->set_next(head);

    if(head != nullptr) 
        head->set_prev(new_node);

    
    tail = new_node;
    new_node.reset();
}

void DoublyLinkedList::insert(const Product& data, int pos)
{
    if(pos < 0)
    {
        std::cout << "ERROR! Invalid insertion position\n";
        return;
    }

    if(pos == 0) return push(data);

    shared_node_obj curr = head;
    int count {0};

    while (count < pos - 1 && curr != nullptr)
    {
        curr = curr->get_next();
        count++;
    }
    
    if(curr == nullptr)
    {
        std::cout << "ERROR! Invalid insertion position\n";
        return;
    }

    shared_node_obj temp = std::make_shared<Node>(data);
    temp->set_next(curr->get_next());
    temp->set_prev(curr);

    curr->get_next()->set_prev(temp);
    curr->set_next(temp);

    temp.reset();
    curr.reset();
}

shared_node_obj DoublyLinkedList::pop()
{
    if(head == nullptr)
        return nullptr;
    
    if(head->get_next() == nullptr)
    {
        head.reset();
        return nullptr;
    }

    shared_node_obj curr = head->get_prev();
    tail = curr;
    tail->get_next().reset();
    tail->set_next(nullptr);

    curr.reset();

    return head;
}

shared_node_obj DoublyLinkedList::pop(bool inStart)
{
    if(!inStart) return pop();
    
    if(head == nullptr)
        return nullptr;

    shared_node_obj temp = head;
    head = head->get_next();

    if(head != nullptr)
        head->set_prev(nullptr);
    
    temp.reset();

    return head;
}

shared_node_obj DoublyLinkedList::remove(int pos)
{
    if(!head) return head;

    shared_node_obj curr = head;

    for(int i = 0; curr && i < pos; ++i)
        curr = curr->get_next();

    if(!curr) return head;

    if(curr->get_prev())
        curr->get_prev()->set_next(curr->get_next());

    if(curr->get_next())
        curr->get_next()->set_prev(curr->get_prev());
    
    curr.reset();

    return head;
}

void DoublyLinkedList::traverse()
{
    shared_node_obj curr = head;

    std::cout << "START" << std::endl;

    while (curr != nullptr)
    {
        std::cout << curr->get_name() << std::endl;
        curr = curr->get_next();
    }

    std::cout << "END" << std::endl;

    curr.reset();
}

void DoublyLinkedList::traverse(bool isBackward)
{
    if(!isBackward) return traverse();

    shared_node_obj curr = tail;

    std::cout << "START" << std::endl;

    while (curr != nullptr)
    {
        std::cout << curr->get_name() << std::endl;
        curr = curr->get_prev();
    }

    std::cout << "END" << std::endl;

    curr.reset();
}

int DoublyLinkedList::length()
{
    int len {0};

    for(shared_node_obj cur = head; cur != nullptr; cur = cur->get_next())
        len++;
    
    return len;
}
