#ifndef LIBS
#define LIBS
#include <iostream>
#include <string>
#include <string.h>
#endif

class Produs;

class Categorie{
        std::string denumire;
        int nrProduse;
        Produs **produse;
    public:
        Categorie(const std::string, const int = 0, const Produs ** = NULL);
        Categorie(const Categorie&);
        ~Categorie();

        std::string getDenumire() const{return this -> denumire;};
        int getNrProduse() const{return this -> nrProduse;};
        Produs *getProdus(int i) const{return this -> produse[i];};

        void setDenumire(const std::string denumire){this -> denumire = denumire;};
        void setNrProduse(const int nrProduse){this -> nrProduse = nrProduse;};
        
        void addProdus(const Produs*);

        Categorie operator=(const Categorie&);
        friend std::ostream& operator<<(std::ostream&, const Categorie&);
        friend std::istream& operator>>(std::istream&, Categorie*);

        friend void vizualizare_categorie(const std::string);
        friend void adaugare_categorie(int argc, char **argv); //tbc 
        friend void modificare_categorie(const std::string, const std::string, const std::string);
        friend void stergere_categorie(const std::string);
    private:
        void init(const std::string, const int, const Produs**);
};