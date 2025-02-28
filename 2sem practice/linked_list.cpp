#include "linked_list.h"

#include <iostream>
#include <fstream>
#include <vector>

DoublyLinkedList::DoublyLinkedList()
{
    push(Product());
    length = 1;
}

DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& other) // Копирование связного списка
{
    shared_node_obj curr = other.head; // Новому "текущему" объекту присваиваем указатель на голову прибавляемого списка

    length = other.length;

    for(; curr != nullptr; curr = curr->get_next()) // Пока указатель "текущего" объекта не будет равен нулевому, перебираем все элементы прибавляемого списка
       push((Product){curr->get_id(), curr->get_name(), curr->get_price(), curr->get_supplier()}, true); // Добавляем новые элементы в конец текущего списка
    
    curr.reset(); // Отвязываем указатель от "текущего" объекта
}

DoublyLinkedList::DoublyLinkedList(DoublyLinkedList&& move)
{
    head = move.head;
    tail = move.tail;
    length = move.length;

    move.head.reset();
    move.tail.reset();  
    length = 0;
}

DoublyLinkedList::DoublyLinkedList(const Product& data) // Создание связного списка только с одной переданной нодой
{
    head = std::make_shared<Node>(data);
    tail.swap(head);

    length = 1;
}

DoublyLinkedList::DoublyLinkedList(const Product& d1, const Product& d2) // Создание связного списка с двумя переданными нодами
{
    head = std::make_shared<Node>(d1);
    tail = std::make_shared<Node>(d2);

    head->set_next(tail);
    tail->set_prev(head);
    length = 2;
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

    length++;
}

void DoublyLinkedList::push(const Product& data, bool inEnd) // Добавление элемента в конец списка
{
    if(!inEnd) return push(data); // Если inEnd == false - начинаем процесс добавления в начало списка

    shared_node_obj new_node = std::make_shared<Node>(data); // Новая нода (создаётся указатель и сразу привязывается к объекту new_node)

    if(head == nullptr)
    { // Если головы не существует, сразу привязываем к ней новый указатель
        head = new_node;
        tail = head;
    }
    else // иначе
    {
        new_node->set_prev(tail); // Ставим хвост списка предыдущим элементом для новой ноды
        tail->set_next(new_node); // Новую ноду ставим следующим элементом для хвоста
        tail = new_node; // Перепривязываем объект хвоста к новой ноде
    }

    new_node.reset(); // Отвязываем новую ноду от созданного объекта

    length++;
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

    length++;
}

shared_node_obj DoublyLinkedList::pop() // Удаление объекта с конца
{
    if(head == nullptr) // Если голова имеет нулевой указатель - ничего не делаем
        return nullptr;
    
    if(head->get_next() == nullptr) // Если следующий для головы указатель - нулевой, то отвязываем указатель от головы
    {
        head.reset();
        return nullptr;
    }

    shared_node_obj curr = tail->get_prev(); // Привязываем к curr предыдущий для хвоста указатель
    tail = curr; // Хвосту же привязываем curr (предыдущий)
    tail->get_next().reset(); // Отвязываем прошлый указатель хвоста (тк больше объектов на него не ссылается - память очистится)

    curr.reset(); // Отвязываем указатель от созданного объекта

    length--;

    return head;
}

shared_node_obj DoublyLinkedList::pop(bool inStart) // Удаление объекта из начала
{
    if(!inStart) return pop(); // Если inStart == false - удаляем объект из конца
    
    if(head == nullptr) // Если голова имеет нулевой указатель - ничего не делаем
        return nullptr;

    shared_node_obj temp = head; // Привязываем объекту указатель головы
    head = head->get_next(); // К голове же привязываем следующий от головы указатель

    if(head != nullptr) // Если после привязки голова не имеет нулевой указатель - задаём её предыдущий объект нулевым указателем
        head->set_prev(nullptr);
    
    temp.reset(); // Отвязываем от временного объекта указатель прошлой головы (память очищается тк больше на тот указатель никто не ссылается)

    length--;

    return head;
}

shared_node_obj DoublyLinkedList::remove(int pos) // Удаление объекта из любой позиции в границах списка
{
    if(!head) return head; // Если указатель головы нулевой - ничего не делаем

    shared_node_obj curr = head; // Привязывам к новому объекту указатель головы

    for(int i = 0; curr && i < pos; ++i) // Пока он не будет нулевым, либо пока не дойдём до конца списка, перебираем элементы друг за другом
        curr = curr->get_next();

    if(!curr) return head; // Если дошли до нулевого указателя - ничего дальше не делаем тк был передан некорректный индекс

    if(curr->get_prev()) // если объект на текущей позиции имеет предыдущий объект (не нулевой указатель)
        curr->get_prev()->set_next(curr->get_next()); // то для предыдущего объекта, следующим объектом ставим следующий для текущего объекта

    if(curr->get_next()) // если объект на текущей позиции имеет следующий объект (не нулевой указатель)
        curr->get_next()->set_prev(curr->get_prev()); // то для следующего объекта, предыдущим объектом ставим предыдущий для текущего объекта

    if(head == curr) // если голова ссылается на тот же объект, что и текущий
        head = curr->get_next(); // привязываем к голове следующий для текущего объекта указатель
    
    curr.reset(); // отвязываем от созданного объекта "текущий" указатель. На него больше ничто не ссылается, поэтому память очистится

    length--;

    return head;
}

unsigned DoublyLinkedList::get_length()
{ return length; }

void DoublyLinkedList::traverse() // Вывод списка в консоль в прямом порядке
{
    shared_node_obj curr = head; // К новому объекту привязываем указатель головы

    std::cout << "START" << std::endl;

    while (curr != nullptr) // Пока указатель нового объекта не равен нулевому
    {
        std::cout << curr->get_id() << ' ' << curr->get_name() << ' ' << curr->get_price() << ' ' << curr->get_supplier() << std::endl; // Выводим данные об объектах построчно
        curr = curr->get_next(); // Переприсваиваем указатель на следующий от текущего
    }

    std::cout << "END" << std::endl;

    curr.reset(); // Отвязываем указатель от нового объекта
}

void DoublyLinkedList::traverse(bool isBackward) // Вывод списка в консоль в обратном порядке
{
    if(!isBackward) return traverse(); // Если isBackward == false - выводим в прямом порядке

    shared_node_obj curr = tail; // К новому объекту привязываем указатель хвоста

    std::cout << "START" << std::endl;

    while (curr != nullptr) // Пока указатель нового объекта не равен нулевому
    {
        std::cout << curr->get_id() << ' ' << curr->get_name() << ' ' << curr->get_price() << ' ' << curr->get_supplier() << std::endl; // Выводим данные об объектах построчно
        curr = curr->get_prev(); // Переприсваиваем указатель на предыдущий от текущего
    }

    std::cout << "END" << std::endl;

    curr.reset(); // Отвязываем указатель от нового объекта
}

void DoublyLinkedList::traverse(const char* str, bool isBackward=false) // Вывод списка в консоль с параметром
{
    bool output_id = strstr(str, "ID") != nullptr,                              // Проверка на наличие спец. слов в переданной строке
        output_name = strstr(str, "NAME") != nullptr,                           // В зависимости от результатов проверки будет проведён вывод
        output_price = strstr(str, "PRICE") != nullptr,                         // тех или иных значений (но всегда в одном и том же порядке)
        output_supplier = strstr(str, "SUPPLIER") != nullptr,
        out = output_id || output_name || output_price || output_supplier;      // Проверка, нужно ли вообще выводить значения

    shared_node_obj curr = isBackward ? tail : head; // В зависимости от параметра isBackward, выбирается, откуда начнётся вывод элементов списка

    std::cout << "START" << std::endl;

    for(; curr != nullptr && out; curr = (isBackward ? curr->get_prev() : curr->get_next())) // Пока новый объект не равен текущему указателю
    {                                                                                        // Выводим заданные значения объектов
        if(output_id) std::cout << curr->get_id() << ' ';                                    // присваивая "текущему" объекту либо следующий,
        if(output_name) std::cout << curr->get_name() << ' ';                                // либо предыдущий объект
        if(output_price) std::cout << curr->get_price() << ' ';
        if(output_supplier) std::cout << curr->get_supplier();
        std::cout << std::endl;
    }

    std::cout << "END" << std::endl;

    curr.reset(); // Отвязываем от созданного объекта указатель
}

// int DoublyLinkedList::length() // Посчёт длины списка
// {
//     int len {0}; // Инициализация переменной, которая будет хранить нашу длину

//     for(shared_node_obj cur = head; cur != nullptr; cur = cur->get_next()) // Создаём новый объект, привязываем к нему указатель на голову списка
//         len++;                                                             // и до момента пока новый объект не будет равен нулевому указателю
//                                                                            // прибавляем 1 к длине. Каждую итерацию присваиваем "текущему" объекту следующий
//     return len;
// }

unsigned DoublyLinkedList::search(const Product& other) // Поиск строго определённого продукта в списке
{
    shared_node_obj curr = head; // Создаём новый объект, привязываем к нему указатель на голову списка

    unsigned pos {0}; // Тут будем хранить позицию найденного продукта

    while (curr != nullptr) // Пока "текущий" объект не равен нулевому
    {
        if(curr->get_id() == other.get_id() && (curr->get_name().compare(other.get_name()) == 0) && curr->get_price() == other.get_price() && curr->get_supplier() == other.get_supplier()) // ищем совпадающий объект
        {
            curr.reset(); // Если нашли - отвязываем от "текущего" объекта указатель
            return pos; // возвращаем найденную позицию (метод заканчивает выполнение)
        }

        curr = curr->get_next(); // Если не нашли - продолжаем перебор
        pos++; // Увеличиваем позицию на 1
    }

    curr.reset(); // отвязываем от "текущего" объекта указатель

    return _cant_find_object_; // Возвращаем спец. значение для ненайденного объекта
}

void DoublyLinkedList::clear()
{
    while (head != nullptr) // Пока голова не будет равна нулевому указателю - удаляем все элементы списка
        pop();
}

const DoublyLinkedList& DoublyLinkedList::operator =(const DoublyLinkedList& other) // Переопределение оператора присваивания копированием
{
    if(this == &other) return *this; // Если указатели равны - ничего не делаем

    clear();

    for(shared_node_obj curr = other.head; curr != nullptr; curr = curr->get_next()) // Переносим все элементы списка other в текущий
        push((Product){curr->get_id(), curr->get_name(), curr->get_price(), curr->get_supplier()}, true); // Вставка в конец

    return *this; // Возвращаем копию (константную ссылку) текущего объекта
}

const DoublyLinkedList& DoublyLinkedList::operator =(DoublyLinkedList&& move) // Переопределение оператора присваивания перемещением
{
    if(this == &move) return *this;

    clear();

    head = move.head;
    tail = move.tail;

    move.head.reset();
    move.tail.reset();

    return *this;
}

const DoublyLinkedList& DoublyLinkedList::operator+(const DoublyLinkedList& other) // Переопределение оператора суммирования для двух связных списков
{
    DoublyLinkedList& lst {*this}; // Новый связный список, равный текущему (копирование доступно благодаря переопределённому конструктору копирования)

    for(shared_node_obj curr = other.head; curr != nullptr; curr = curr->get_next()) // Проходим весь список other
        lst.push((Product){curr->get_id(), curr->get_name(), curr->get_price(), curr->get_supplier()}, true); // Поочерёдно добавляя каждый элемент в конец "нового" списка

    return lst; // Возвращаем полученный связный список
}

const DoublyLinkedList& DoublyLinkedList::operator+(const Product& other) // Переопределение операции суммирования для связного списка и продукта
{   
    DoublyLinkedList& lst {*this}; // Новый связный список, равный текущему (копирование доступно благодаря переопределённому конструктору копирования)

    lst.push((Product){other.get_id(), other.get_name(), other.get_price(), other.get_supplier()}, true); // Добавляем новый продукт в конец

    return lst; // Возвращаем новый список
}

const DoublyLinkedList& DoublyLinkedList::operator -(const DoublyLinkedList& other) // Переопределение операции вычитания для двух связных списков
{
    DoublyLinkedList& lst {*this}; // Новый связный список, равный текущему (копирование доступно благодаря переопределённому конструктору копирования)

    shared_node_obj curr = other.head; // Новому "текущему" объекту привязываем указатель на голову вычитаемого списка

    for(; curr != nullptr; curr = curr->get_next()) // Далее, пока "текущий" объект не равен нулевому, перебираем все элементы вычитаемого списка
    {
        unsigned pos = lst.search((Product){curr->get_id(), curr->get_name(), curr->get_price(), curr->get_supplier()}); // Проверяем, есть ли в текущем списке "текущий" объект
        
        if(pos == _cant_find_object_) // Если нет - переходим к следующему элементу перебора
            continue;
        
        lst.remove(pos); // Иначе удаляем этот элемент и переходим к следующему элементу перебора
    }

    curr.reset(); // Отвязываем от "текущего" объекта указатель

    return lst; // Возвращаем новый список
}

const DoublyLinkedList& DoublyLinkedList::operator-(const Product& other) // Переопределение операции вычитания для связного списка и продукта
{
    DoublyLinkedList& lst {*this}; // Новый связный список, равный текущему (копирование доступно благодаря переопределённому конструктору копирования)

    unsigned pos = lst.search(other); // Проверяем, есть ли переданный продукт в текущем списке

    if(pos == _cant_find_object_) return lst; // Если нет - возвращаем неизменённый новый список

    lst.remove(pos); // Иначе удаляем этот объект

    return lst; // И возвращаем новый список
}

const DoublyLinkedList& DoublyLinkedList::operator+=(const DoublyLinkedList& other) // Переопределение расширенной операции присваивания с суммированием для двух связных списков
{
    shared_node_obj curr = other.head; // Новому "текущему" объекту присваиваем указатель на голову прибавляемого списка

    for(; curr != nullptr; curr = curr->get_next()) // Пока указатель "текущего" объекта не будет равен нулевому, перебираем все элементы прибавляемого списка
        push((Product){curr->get_id(), curr->get_name(), curr->get_price(), curr->get_supplier()}, true); // Добавляем новые элементы в конец текущего списка

    curr.reset(); // Отвязываем указатель от "текущего" объекта

    return *this; // Возвращаем копию изменённого (текущего) списка
}

const DoublyLinkedList& DoublyLinkedList::operator+=(const Product& other) // Переопределение расширенной операции присваивания с суммированием для связного списка и продукта
{
    push(other, true); // Добавляем продукт в конец текущего списка

    return *this; // Возвращащаем копию изменённого (текущего) списка
}

const DoublyLinkedList& DoublyLinkedList::operator-=(const DoublyLinkedList& other) // Переопределение расширенной операции присваивания с вычитанием для двух связных списков
{
    shared_node_obj curr = other.head; // Привязываем к новому "текущему" объекту указатель на голову вычитаемого списка
 
    for(; curr != nullptr && head != nullptr; curr = curr->get_next()) // Пока голова текущего списка, либо пока указатель "текущего" объекта не будут равны нулевому объекту, перебираем все элементы вычитаемого списка
    {
        unsigned pos = search((Product){curr->get_id(), curr->get_name(), curr->get_price(), curr->get_supplier()}); // Ищем "текущий" объект в текущем списке

        if(pos == _cant_find_object_) continue; // Если нет - переходим к следующему объекту
        remove(pos); // Иначе удаляем из текущего списка "текущий" объект
    }

    curr.reset(); // Отвязываем от нового объекта указатель

    return *this; // Возвращаем копию изменённого (текущего) списка
}

const DoublyLinkedList& DoublyLinkedList::operator-=(const Product& other) // Переопределение расширенной операции присваивания с вычитанием для связного списка и продукта
{
    unsigned pos = search(other); // Ищем в текущем списке переданный продукт

    if(pos == _cant_find_object_) return *this; // Если нет - возвращаем копию текущего списка

    remove(pos); // Иначе удаляем продукт из списка

    return *this; // Возвращаем копию изменённого (текущего) списка
}

Node& DoublyLinkedList::operator[] (unsigned index)
{
    if(index >= length) return *head;

    shared_node_obj curr = head;

    for(int i = 0; curr != nullptr && i != index; i++, curr = curr->get_next());

    return *curr;
}

bool DoublyLinkedList::save(const char* file_name) // Метод записи связного списка в бинарный файл (filename - переданная строка с именем файла в который будет произведено сохранение)
{
    std::ofstream ofs(file_name, std::ios::out | std::ios::binary); // Открываем файлоый поток для файла с именем file_name в бинарном режиме записи
    if (!ofs.is_open()) { // Проверяем, открылся ли файл
        std::cout << "ERROR: File " << file_name << " wasn't opened for writing.\n"; // Если нет, то прерываем запись
        return false; // Запись прошла с ошибкой - возвращаем false
    }

    shared_node_obj curr = head; // Привязываем к новому "текущему" объекту указатель на голову текущего связного списка
    int len = length; // Сохраняем в переменной длину связного списка (чтоб было удобно загружать список из файла)
    ofs.write((char*)&len, sizeof(int)); // Первым делом записываем длину связного списка в бинарном файле

    while (curr != nullptr) // Далее пока не дойдём до конца связного списка
    {
        ofs.write((char*)&curr->get_id(), sizeof(unsigned)); // Записываем в бинарный файл айди текущего объекта

        int s = curr->get_name().size(); // Сохраняем в переменной длину имени объекта (чтоб было удобно записывать и загружать имя объекта)
        ofs.write((char*)&s, sizeof(int)); // Записываем в бинарный файл длину имени объекта
        ofs.write(curr->get_name().c_str(), s); // Записываем в бинарный файл имя объекта (как раз используя ранее сохранённую длину) 
        ofs.write((char*)&curr->get_price(), sizeof(double)); // Записываем в бинарный файл цену объекта
        ofs.write((char*)&curr->get_supplier(), sizeof(_suppliers_)); // Записываем в бинарный файл производителя объекта

        curr = curr->get_next(); // Переходим к следующему объекту (и так до последнего)
    }
    
    ofs.close(); // Закрываем файловый поток
    return true; // Запись прошла успешно - возвращаем true
}

bool DoublyLinkedList::load(const char* file_name) // Метод для считывания связного списка из бинарного файла
{
    std::ifstream ifs(file_name, std::ios::in | std::ios::binary); // Открываем файловый поток для файла с именем file_name в бинарном режиме считывания
    if (!ifs.is_open()) { // Поверяем, удалось ли открыть файл
        std::cout << "ERROR: File " << file_name << " wasn't opened for reading.\n"; // Если не удалось, сообщаем об этом в консоли
        return false; // Считывание не удалось - возвращаем false
    }

    int len; // Объявляем переменную для последующего считывания в неё длины связного списка
    ifs.read((char*)&len, sizeof(int)); // Считываем длину списка из файла (для этого мы её первым делом записывали в методе записи в бинарный файл)

    for (int i = 0; i < len; i++) // Пока i не будет равно длине связного списка
    {
        unsigned id; // Объявляем переменную для последующего считывания в неё айди из файла
        int name_len; // Объявляем переменную для последующего считывания в неё длины из файла
        ifs.read((char*)&id, sizeof(unsigned)); // Считываем из бинарного файла айди объекта

        ifs.read((char*)&name_len, sizeof(int)); // Считываем из бинарного файла длину имени объекта

        std::vector<char> name(name_len + 1); // Объявляем динамический массив символов под длину равной длине имени + 1 (+ 1 для нулевого символа)
        ifs.read(name.data(), name_len); // Считываем из бинарного файла имя объекта
        name[name_len] = '\0';  // Добавляем нулевой символ в конец строки

        double price; // Объявляем переменную для последующего считывания в неё цены объекта
        _suppliers_ supplier; // Объявляем переменную для последующего считывания в неё поставщика объекта
        ifs.read((char*)&price, sizeof(double)); // Считываем из бинарного файла цену объекта
        ifs.read((char*)&supplier, sizeof(_suppliers_)); // Считываем из бинарного файла поставщика объекта

        push({id, name.data(), price, supplier}, true); // Добавляем в текущий связный список продукт, со считанными из бинарного файла данными (объект добавляется в конец)
    }

    ifs.close(); // Закрываем файловый поток
    return true; // Считывание прошло успешно - возвращаем true
}
