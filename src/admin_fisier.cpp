#include "admin_fisier.h" 
#include <array>


admin_fisier::admin_fisier(string fisierAbonati, string fisierCarti) : 
admin(), nume_fisier_abonati(fisierAbonati), nume_fisier_carti(fisierCarti)
{
    fisier_abonati.open(nume_fisier_abonati, ios::app | ios::app); //Creare fisier daca nu exista
    fisier_abonati.close();
    
    fisier_carti.open(nume_fisier_carti, ios::out | ios::app); //Creare fisier daca nu exista
    fisier_carti.close();
}


void admin_fisier::write(abonat& c) 
{
    fisier_abonati.open(nume_fisier_abonati, ios::app);
    fisier_abonati << c.abonat_to_file();
    fisier_abonati.flush();
    fisier_abonati.close();
}

void admin_fisier::write(carte& c) 
{
    fisier_carti.open(nume_fisier_carti, ios::app);
    fisier_carti << c.carte_to_file();
    fisier_carti.close();
}


abonat admin_fisier::read_next_abonat() 
{
    string linie;
    static int current_line = 0;

    fisier_abonati.open(nume_fisier_abonati, ios::in);
    
    for(int i = 0; i < current_line; i++){
        getline(fisier_abonati, linie);
    }
    getline(fisier_abonati, linie);
    fisier_abonati.close();

    vector<string> arr = split(linie);
    current_line++;
    return abonat(arr);
}


carte admin_fisier::read_next_book() 
{
    static int current_line = 0;
    string linie;
    fisier_carti.open(nume_fisier_carti, ios::in);
    
    for(int i = 0; i < current_line && getline(fisier_carti, linie); i++);
    getline(fisier_carti, linie);
    fisier_carti.close();

    vector<string> arr = split(linie);
    current_line++;
    return carte(arr);
}

void admin_fisier::read_all_books()
{
    books.clear();
    string linie;
    vector<string> arr;
    fisier_carti.open(nume_fisier_carti, ios::in);

    while(getline(fisier_carti, linie))
    {
        arr = split(linie);
        add(carte(arr));
    }
    fisier_carti.close();
}

void admin_fisier::read_all_readers()
{
    abonati.clear();
    string linie;
    vector<string> arr;
    fisier_abonati.open(nume_fisier_abonati, ios::in);

    while(getline(fisier_abonati, linie))
    {
        arr = split(linie);
        add(abonat(arr));
    }
    fisier_abonati.close();
}

void admin_fisier::write_all_books()
{
    fisier_carti.open(nume_fisier_carti, ios::out | ios::trunc);
    for(carte& c: books)
    {
        fisier_carti << c.carte_to_file();
    }
    fisier_carti.close();
}        

void admin_fisier::write_all_readers()
{
    fisier_abonati.open(nume_fisier_abonati, ios::out | ios::trunc);
    for(abonat& a: abonati)
    {
        fisier_abonati << a.abonat_to_file();
    }
    fisier_abonati.close();
}    