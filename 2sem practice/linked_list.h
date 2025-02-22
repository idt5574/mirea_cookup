#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include "node.cpp" // Вставляем node.cpp со всеми реализациями
// Вставлять product.cpp уже нет смысла, тк это было сделано в файле node.cpp

enum _extra_return_values_ // Особые значения, которые будут возвращаться при возникновении исключений при работе программы
{
    _cant_find_object_ = 128128128
};

// Класс двусвязного списка

class DoublyLinkedList
{
    shared_node_obj head; // Умный указатель на голову (первый объект связного списка)
    shared_node_obj tail; // Умный указатель на хвост (последний объект связного списка)

public:

    // Конструкторы

    DoublyLinkedList(const DoublyLinkedList&);

    DoublyLinkedList(const Product&);

    DoublyLinkedList(const Product&, const Product&);

    DoublyLinkedList(const char*);

    // Методы вставки элементов

    void push(const Product&); // Вставка в начало
    void push(const Product&, bool); // Вставка в конец

    void insert(const Product&, int); // Вставка в любую доступную позици (в текущих границах списка)

    shared_node_obj pop(); // Удаление объекта из конца
    shared_node_obj pop(bool); // Удаление объекта из начала

    shared_node_obj remove(int); // Удаление объекта под любым индексом в пределах текущих грациц списка

    void traverse(); // Вывод списка в консоль
    void traverse(bool); // Ревёрс-вывод списка в консоль
    void traverse(const char*, bool); // Вывод определённых значений элементов списка в консоль

    // const char* - строка.
    /* Если переданная строка содержит:
        1) ID - Будет выполнен вывод айди
        2) NAME - будет выполнен вывод имён
        3) PRICE - будет выполнен вывод цен
        4) SUPPLIER - будет выполнен вывод производителей

    !! Можно передать в строку сразу несколько параметров !!
    */

    // bool - по умолчанию принимает значение false
    /* false - вывод в прямом порядке
        true - вывод в обратном порядке
    */

    int length(); // Подсчёт длинны связного списка

    unsigned search(const Product&); // Поиск конкретного объекта в связном списке

    const DoublyLinkedList& operator =(const DoublyLinkedList&); // Переопределение операции присваивания связных списков

    const DoublyLinkedList& operator +(const DoublyLinkedList&); // Позволяет получить конкатенацию двух списков
    const DoublyLinkedList& operator +(const Product&); // Позволяет получить конкатенацию списка и продукта

    const DoublyLinkedList& operator -(const DoublyLinkedList&); // Вычитает из левого списка те объекты, которые присутствуют в правом (если они есть в левом)
    const DoublyLinkedList& operator -(const Product&); // Вычитает продукт из списка (если он в списке есть)

    const DoublyLinkedList& operator +=(const DoublyLinkedList&); // Добавляет к текущему списку элементы другого списка
    const DoublyLinkedList& operator +=(const Product&); // Добавляет к текущему списку новый продукт

    const DoublyLinkedList& operator -=(const DoublyLinkedList&); // Удаляет из текущего списка объекты из правого списка (если они есть в текущем)
    const DoublyLinkedList& operator -=(const Product&); // Удаляет из текущего списка продукт (если тот есть в списке)

    bool save(const char*); // Сохранение списка в файл
    bool load(const char*); // Загрузка списка в файл
    /* Если список не пустой, то объекты будут добавляться справа, ничего удалего из не будет*/
};

#endif