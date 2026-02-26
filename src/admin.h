#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "abonat.h"
#include "carte.h"

using namespace std;

class admin{
    protected:
        vector<abonat> abonati;
        vector<carte> books;
    public:
        admin(){}
        void add(abonat new_abonat) {abonati.push_back(new_abonat);}
        void add(carte new_book) {books.push_back(new_book);}

        abonat find_abonat(string info);
        carte find_book(string info);
        
        vector<abonat> get_abonati() {return abonati;}
        vector<carte> get_books() {return books;}
        
        void remove_abonat(string info);
        void remove_book(string info);

        carte get_carte(string isbn);

        void set_abonati(const std::vector<abonat>& v) 
        {
            abonati = v;
        }

        void set_books(const std::vector<carte>& v)
        {
            books = v;
        }
        ~admin(){}
};

#endif //ADMIN_H