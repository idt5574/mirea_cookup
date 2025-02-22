#include "linked_list.h"

#include <iostream>
#include <fstream>
#include <vector>

DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& other) // Копирование связного списка
{
    *this = other;
}

DoublyLinkedList::DoublyLinkedList(const Product& data) // Создание связного списка только с одной переданной нодой
{
    head = std::make_shared<Node>(data);
    tail.swap(head);
}

DoublyLinkedList::DoublyLinkedList(const Product& d1, const Product& d2) // Создание связного списка с двумя переданными нодами
{
    head = std::make_shared<Node>(d1);
    tail = std::make_shared<Node>(d2);

    head->set_next(tail);
    tail->set_prev(head);
}

DoublyLinkedList::DoublyLinkedList(const char* f_name) // Загрузка связного списка из файла
{
    load(f_name);
}

void DoublyLinkedList::push(const Product& data) // Добавление элемента в начало списка
{
    shared_node_obj new_node = std::make_shared<Node>(data); // Новая нода (создаётся указатель и сразу привязывается к объекту new_node)

    new_node->set_next(head); // Сразу присваиваем голову списка следующей для новой ноды

    if(head != nullptr) // Если голова существует - ставим её предыдущей нодой новую
        head->set_prev(new_node);

    head = new_node; // Заменяем указатель головы на новую ноду
    new_node.reset(); // Отвязываем новую ноду от созданного объекта
}

void DoublyLinkedList::push(const Product& data, bool inEnd) // Добавление элемента в конец списка
{
    if(!inEnd) return push(data); // Если inEnd == false - начинаем процесс добавления в начало списка

    shared_node_obj new_node = std::make_shared<Node>(data); // Новая нода (создаётся указатель и сразу привязывается к объекту new_node)

    if(head == nullptr) // Если головы не существует, сразу привязываем к ней новый указатель
        head = new_node;
    else // иначе
    {
        new_node->set_prev(tail); // Ставим хвост списка предыдущим элементом для новой ноды
        tail->set_next(new_node); // Новую ноду ставим следующим элементом для хвоста
        tail = new_node; // Перепривязываем объект хвоста к новой ноде
    }

    new_node.reset(); // Отвязываем новую ноду от созданного объекта
}

void DoublyLinkedList::insert(const Product& data, int pos) // Добавление элемента на любую позицию внутри списка
{
    if(pos < 0) // Если позиция меньше нуля - добавить не может
    {
        std::cout << "ERROR! Invalid insertion position\n";
        return;
    }

    if(pos == 0) return push(data); // Если позиция равна нулю - просто добавляем объект в начало

    shared_node_obj curr = head; // Привязываем указатель головы к объекту curr
    int count {0}; // Счётчик позиций

    while (count < pos - 1 && curr != nullptr) // Выполняется до момента пока не дойдём до пред-позиции, либо пока curr не будет привязан к нулевому указателю
    {
        curr = curr->get_next(); // Привязываем объекту curr следующий элемент списка
        count++; // Увеличиваем на 1 счетчик
    }
    
    if(curr == nullptr) // Если curr привязан к нулевому указателю - значит позиция находится за границами списка
    {
        std::cout << "ERROR! Invalid insertion position\n";
        return;
    }

    shared_node_obj temp = std::make_shared<Node>(data); // Новая нода (создаётся указатель и сразу привязывается к объекту new_node)

    temp->set_next(curr->get_next()); // Для новой ноды следующей ставим следующую от пред позиции
    temp->set_prev(curr); // Предыдущей - пред-позицию

    curr->get_next()->set_prev(temp); // Для следующей ноды от пред-позиции предыдущую ставим новой
    curr->set_next(temp); // Следующей нодой пред-позиции ставим новую

    // Отвязываем указатели от созданных внутри метода объектов
    
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

bool DoublyLinkedList::save(const char* file_name)
{
    std::ofstream ofs(file_name, std::ios::out | std::ios::binary);
    if (!ofs.is_open()) {
        std::cout << "ERROR: File " << file_name << " wasn't opened for writing.\n";
        return false;
    }

    shared_node_obj curr = head;
    int len = length();
    ofs.write((char*)&len, sizeof(int));

    while (curr != nullptr)
    {
        ofs.write((char*)&curr->get_id(), sizeof(unsigned));

        int s = curr->get_name().size();
        ofs.write((char*)&s, sizeof(int));
        ofs.write(curr->get_name().c_str(), s);
        ofs.write((char*)&curr->get_price(), sizeof(unsigned));
        ofs.write((char*)&curr->get_supplier(), sizeof(_suppliers_));

        curr = curr->get_next();
    }
    
    ofs.close();
    return true;
}

bool DoublyLinkedList::load(const char* file_name)
{
    std::ifstream ifs(file_name, std::ios::in | std::ios::binary);
    if (!ifs.is_open()) {
        std::cout << "ERROR: File " << file_name << " wasn't opened for reading.\n";
        return false;
    }

    int len;
    ifs.read((char*)&len, sizeof(int));

    // Временно используем указатели для чтения данных
    for (int i = 0; i < len; i++)
    {
        unsigned id;
        int name_len;
        ifs.read((char*)&id, sizeof(unsigned));

        ifs.read((char*)&name_len, sizeof(int));

        // Используем временный массив для имени
        std::vector<char> name(name_len + 1); // Один байт под нулевой символ
        ifs.read(name.data(), name_len);
        name[name_len] = '\0';  // Добавляем нулевой символ в конец строки

        unsigned price;
        _suppliers_ supplier;
        ifs.read((char*)&price, sizeof(unsigned));
        ifs.read((char*)&supplier, sizeof(_suppliers_));

        push(Product(name.data(), price, supplier, id));
    }

    ifs.close();
    return true;
}

