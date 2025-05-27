#ifndef _LIBRARY_HPP_
#define _LIBRARY_HPP_

#include <iostream>
#include <map>

#include "Book.hpp"

#include "custom_exceptions/LibraryExceptions.hpp"

class Library
{
    std::map<std::string, Book> library;
    bool isLibrarySetted;

public:

    Library() : library(), isLibrarySetted(false) {}

    void AddBook(const Book& newBook)
    {
        if(!isLibrarySetted)
            throw LibraryIsNotSettedException();

        library.insert({newBook.GetTitle(), newBook});
    }

    void RemoveBook(const std::string& bookTitle)
    {
        if(!isLibrarySetted)
            throw LibraryIsNotSettedException();

        try
        {
            library.at(bookTitle);
        }
        catch(const std::exception& e)
        {
            std::cerr << "Warning: You tried to delete a non-existent element from library. The process will continue" << '\n';
            return;
        }

        library.erase(bookTitle);
    }

    void RemoveBook(const Book& book)
    {
        if(!isLibrarySetted)
            throw LibraryIsNotSettedException();

        try
        {
            library.at(book.GetTitle());
        }
        catch(const std::exception& e)
        {
            std::cerr << "Warning: You tried to delete a non-existent element from library. The process will continue" << '\n';
            return;
        }

        library.erase(book.GetTitle());
    }

    const Book& TakeBook(const std::string& bookTitle)
    {
         
    }

};

#endif