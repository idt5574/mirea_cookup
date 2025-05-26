#ifndef _BOOK_HPP_
#define _BOOK_HPP_

#include <algorithm>
#include <string>
#include <set>
#include <array>

#include "Author.hpp"
#include "custom_exceptions/StorageZoneExceptions.hpp"

// ==========

const std::array<std::string, 5>* storageZones;

// ==========

bool isZonesSetted = false;
bool isLibrarySetted = false;

// ==========

class Book
{
    std::string title, genre;
    Author author;

    std::string zone = "null";
    bool isAvailable = true;

    int _FindZone(const std::string& str)
    {
        for(int i = 0; i < 5; ++i)
            if((*storageZones)[i] == str)
                return i;

        return -1;
    }

public:

    Book() : title("Title"), genre("Genre"), author() {}

    Book(const std::string& title)
    : title(title), genre("Genre"), author() {}

    Book(const std::string& title, const std::string& genre)
    : title(title), genre(genre), author() {}

    Book(const std::string& title, const std::string& genre, const Author& author)
    : title(title), genre(genre), author(author) {}

    Book(const Book& other)
    : title(other.title), genre(other.genre), author(other.author) {}

    Book(Book&& move)
    : title(move.title), genre(move.genre), author(move.author) {}

    // ==========

    void SetTitle(const std::string& newTitle)
    { title = newTitle; }

    void SetGenre(const std::string& newGenre)
    { genre = newGenre; }

    void SetAuthor(const Author& newAuthor)
    { author = newAuthor; }

    void SetZone(const std::string& newZone)
    {
        if(!isZonesSetted)
            throw ZonesNotSettedException();
        
        int result = _FindZone(newZone);

        if (result == -1) 
            throw UnknownStorageZoneException();

        zone = newZone;
    }

    void SetAvailability(bool newAvailability)
    { isAvailable = newAvailability; }


    // ==========

    std::string GetTitle() const
    { return  title; }

    std::string GetGenre() const
    { return genre; }

    Author GetAuthor() const
    { return author; }

    std::string GetZone() const
    { return zone; }

    bool GetAvailability() const
    { return isAvailable; }

    // ==========

    Book operator = (const Book& other)
    {
        title = other.title;
        genre = other.genre;
        author = other.author;

        return *this;
    }

    Book operator = (Book&& move)
    {
        title = move.title;
        genre = move.genre;
        author = move.author;

        return *this;
    }

    // ==========

    // ==========

    ~Book() {}

};

// ==========

void SetStorageZones(const std::array<std::string, 5>* newStorageZones)
{
    if(isZonesSetted)
        throw ZonesAlreadySettedException();

    storageZones = newStorageZones;
    isZonesSetted = true;
}

#endif