#include <iostream>

#include <string>
#include <array>
#include <set>
#include <map>

#include "ex3_headers/Author.hpp"
#include "ex3_headers/Book.hpp"
#include "ex3_headers/GenreStorage.hpp"

int main()
{
    const std::array<std::string, 5> customZones {
        "earlyReads",  
        "youngMinds",  
        "teenBooks",  
        "matureReads",  
        "adultBooks"  
    };

    std::set<std::string> genreStorage;

    Author coolGuy = {"Charles", "Petzold"};

    Book programming = {"CODE", "Programming", coolGuy};

    SetStorageZones(&customZones);

    SetGenreStorage(&genreStorage);

    AddGenreToStorage("Sigmo");
    AddGenreToStorage(programming);

    std::cout << GetStringOfGenres() << std::endl;

    // programming.SetZone("adultBooks");

    // try
    // {
    //     SetStorageZones(&customZones);
    // }
    // catch(const StorageZoneException& e)
    // {
    //     std::cerr << e.what() << '\n';
    // }

    std::cout << programming.GetZone() << std::endl;

    return 0;
}

/*
=Classes=

--- Book
- String genre
- String title
- Author author

--- Author
- String firstName
- String lastName
- String pantronymic


=Functions=

*/