#ifndef ADMIN_FISIER_H
#define ADMIN_FISIER_H


#include <iostream>
#include <fstream>

#include "admin.h"
#include "functii.h"
using namespace std;

class admin_fisier : public admin
{
    private:
        
        fstream fisier_abonati;
        fstream fisier_carti;

        string nume_fisier_abonati;
        string nume_fisier_carti;
    public:
        admin_fisier(string fisierAbonati, string fisierCarti);
        void write(abonat& c);
        void write(carte& c);

        abonat read_next_abonat();
        carte read_next_book();

        void read_all_books();
        void read_all_readers();

        void write_all_books();
        void write_all_readers();
};
#endif //ADMIN_FISIER_H