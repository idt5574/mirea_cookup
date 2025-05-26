#ifndef _GENRE_STORAGE_HPP_
#define _GENRE_STORAGE_HPP_

#include <set>
#include <string>

#include "Book.hpp"
#include "custom_exceptions/GenreStorageExceptions.hpp"

// ==========

std::set<std::string>* genreStorage;
bool isGenreStorageSetted = false;

// ==========

void SetGenreStorage(std::set<std::string>* newGenresStorage)
{
    if(isGenreStorageSetted)
        throw GenreStorageIsAlreadySetted();

    genreStorage = newGenresStorage;
    isGenreStorageSetted = true;
}

void AddGenreToStorage(const std::string& genreName)
{
    if(!isGenreStorageSetted)
            throw GenreStorageIsNotSetted();

    genreStorage->insert(genreName);
}

void AddGenreToStorage(const Book& book)
{
    if(!isGenreStorageSetted)
        throw GenreStorageIsNotSetted();

    genreStorage->insert(book.GetGenre());
}

void RemoveGenreFromStorage(const std::string& genreName)
{
    if(!isGenreStorageSetted)
        throw GenreStorageIsNotSetted();
    
    if(genreStorage->count(genreName) == 0)
        return;

    genreStorage->erase(genreName);
}

void RemoveGenreFromStorage(const Book& book)
{
    if(!isGenreStorageSetted)
        throw GenreStorageIsNotSetted();
    
    if(genreStorage->count(book.GetGenre()) == 0)
        return;

    genreStorage->erase(book.GetGenre());
}

std::string GetStringOfGenres()
{
    std::string newString = "";

    for(std::string x : *genreStorage)
        newString += x + ' ';

    return newString;
}

#endif