#include "linked_list.h"

#include <iostream>

DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& other)
{
    *this = other;
}

DoublyLinkedList::DoublyLinkedList(const Product& data)
{
    head = std::make_shared<Node>(data);
    tail.swap(head);
}

DoublyLinkedList::DoublyLinkedList(const Product& d1, const Product& d2)
{
    head = std::make_shared<Node>(d1);
    tail = std::make_shared<Node>(d2);

    head->set_next(tail);
    tail->set_prev(head);
}

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

    if(head == nullptr)
        head = new_node;
    else
    {
        new_node->set_prev(tail);
        tail->set_next(new_node);
        tail = new_node;
    }

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
    if(head == NULL)
        return NULL;
    
    if(head->get_next() == NULL)
    {
        head.reset();
        return NULL;
    }

    shared_node_obj curr = tail->get_prev();
    tail = curr;
    tail->get_next().reset();
    tail->set_next(NULL);

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

    if(head == curr)
        head = curr->get_next();
    
    curr.reset();

    return head;
}

void DoublyLinkedList::traverse()
{
    shared_node_obj curr = head;

    std::cout << "START" << std::endl;

    while (curr != nullptr)
    {
        std::cout << curr->get_id() << ' ' << curr->get_name() << ' ' << curr->get_price() << ' ' << curr->get_supplier() << std::endl;
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
        std::cout << curr->get_id() << ' ' << curr->get_name() << ' ' << curr->get_price() << ' ' << curr->get_supplier() << std::endl;
        curr = curr->get_prev();
    }

    std::cout << "END" << std::endl;

    curr.reset();
}

void DoublyLinkedList::traverse(const char* str, bool isBackward=false)
{
    bool output_id = strstr(str, "ID") != nullptr,
        output_name = strstr(str, "NAME") != nullptr,
        output_price = strstr(str, "PRICE") != nullptr,
        output_supplier = strstr(str, "SUPPLIER") != nullptr,
        out = output_id || output_name || output_price || output_supplier;

    shared_node_obj curr = isBackward ? tail : head;

    std::cout << "START" << std::endl;

    for(; curr != nullptr && out; curr = (isBackward ? curr->get_prev() : curr->get_next()))
    {
        if(output_id) std::cout << curr->get_id() << ' ';
        if(output_name) std::cout << curr->get_name() << ' ';
        if(output_price) std::cout << curr->get_price() << ' ';
        if(output_supplier) std::cout << curr->get_supplier();
        std::cout << std::endl;
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

unsigned DoublyLinkedList::search(const Product& other)
{
    shared_node_obj curr = head;

    unsigned pos {0};

    while (curr != nullptr)
    {
        if(curr->get_id() == other.get_id() && (curr->get_name().compare(other.get_name()) == 0) && curr->get_price() == other.get_price() && curr->get_supplier() == other.get_supplier())
            return pos;

        curr = curr->get_next();
        pos++;
    }

    curr.reset();

    return _cant_find_object_;
}

const DoublyLinkedList& DoublyLinkedList::operator =(const DoublyLinkedList& other)
{
    if(this == &other) return *this;

    while (head != nullptr)
        pop();

    for(shared_node_obj curr = other.head; curr != nullptr; curr = curr->get_next())
        push((Product){curr->get_name(), curr->get_price(), curr->get_supplier(), curr->get_id()}, true);

    return *this;
}

const DoublyLinkedList& DoublyLinkedList::operator+(const DoublyLinkedList& other)
{
    DoublyLinkedList& lst {*this};

    for(shared_node_obj curr = other.head; curr != nullptr; curr = curr->get_next())
        lst.push((Product){curr->get_name(), curr->get_price(), curr->get_supplier(), curr->get_id()}, true);

    return lst;
}

const DoublyLinkedList& DoublyLinkedList::operator+(const Product& other)
{   
    DoublyLinkedList& lst {*this};

    lst.push((Product){other.get_name(), other.get_price(), other.get_supplier(), other.get_id()}, true);

    return lst; 
}

const DoublyLinkedList& DoublyLinkedList::operator -(const DoublyLinkedList& other)
{
    DoublyLinkedList& lst {*this};

    shared_node_obj curr = other.head;

    for(; curr != nullptr; curr = curr->get_next())
    {
        unsigned pos = lst.search((Product){curr->get_name(), curr->get_price(), curr->get_supplier(), curr->get_id()});
        
        if(pos == _cant_find_object_)
            continue;
        
        lst.remove(pos);
    }

    curr.reset();

    return lst;
}

const DoublyLinkedList& DoublyLinkedList::operator-(const Product& other)
{
    DoublyLinkedList& lst {*this};

    unsigned pos = lst.search(other);

    if(pos == _cant_find_object_) return lst;

    lst.remove(pos);

    return lst;
}

const DoublyLinkedList& DoublyLinkedList::operator+=(const DoublyLinkedList& other)
{
    shared_node_obj curr = other.head;

    for(; curr != nullptr; curr = curr->get_next())
        push((Product){curr->get_name(), curr->get_price(), curr->get_supplier(), curr->get_id()}, true);

    curr.reset();

    return *this;
}

const DoublyLinkedList& DoublyLinkedList::operator+=(const Product& other)
{
    push(other, true);

    return *this;
}

const DoublyLinkedList& DoublyLinkedList::operator-=(const DoublyLinkedList& other)
{
    shared_node_obj curr = other.head;
 
    for(; curr != nullptr && head != nullptr; curr = curr->get_next())
    {
        unsigned pos = search((Product){curr->get_name(), curr->get_price(), curr->get_supplier(), curr->get_id()});

        if(pos == _cant_find_object_) continue;
        remove(pos);
    }

    curr.reset();

    return *this;
}

const DoublyLinkedList& DoublyLinkedList::operator-=(const Product& other)
{
    unsigned pos = search(other);

    if(pos == _cant_find_object_) return *this;

    remove(pos);

    return *this;
}
