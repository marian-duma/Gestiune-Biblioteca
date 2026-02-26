#include "admin.h"
#include "exceptie.h"
#include "functii.h"

abonat admin::find_abonat(string info)
{
    for (auto& abonat : abonati)
    {
        if (str_to_upper(info) == str_to_upper(abonat.get_nume() + " " + abonat.get_prenume())) 
            return abonat;
        if (info == abonat.get_cnp()) 
            return abonat;
        if (info == to_string(abonat.get_id())) 
            return abonat;
    }

    return abonat(0, "NECUNOSCUT", "NECUNOSCUT", "NECUNOSCUT", "NECUNOSCUT", "NECUNOSCUT", Judet::Necunoscut);
}

carte admin::find_book(string info)
{
    for (auto& book : books)
    {
        if (str_to_upper(info) == str_to_upper(book.get_titlu() + ' ' + book.get_autor())) 
            return book;
        if (info == book.get_isbn()) 
            return book;
        if (str_to_upper(info) == str_to_upper(book.get_titlu()))
            return book;
    }
    carte Carte("NECUNOSCUT", "NECUNOSCUT", "NECUNOSCUT", 0);
    Carte.set_isbn("NECUNOSCUT");
    return Carte;
}

void admin::remove_abonat(string info)
{
    abonat a = admin::find_abonat(info);
    for(size_t i = 0; i < abonati.size();)
    {
        if(a == abonati[i])
        {
            abonati.erase(abonati.begin() + i);
        }
        else {
            ++i;
    
        }
    }
}

void admin::remove_book(string info)
{
    carte c = admin::find_book(info);
    for(size_t i = 0; i < books.size();)
    {
        if(c == books[i])
        {
            books.erase(books.begin() + i);
        }
        else{
            i++;
        }
    }
}

carte admin::get_carte(string isbn)
{
    for(carte& c: books)
    {
        if(c.get_isbn() == isbn) return c;
    }
    return carte();
}