#ifndef LIBS
#define LIBS
#include <iostream>
#include <string>
#include <string.h>
#endif

#ifndef CATEGORIEH
#define CATEGORIEH
#include "Categorie.h"
#endif

class Produs{
        std::string cod_de_bare;
        std::string denumire;
        int cantitate;
        double pret;
        Categorie *categorie;
    public:
        Produs(const std::string = "", const std::string = "", const int = 0, const double = 0, const Categorie& = Categorie(""));
        Produs(const Produs&);
        ~Produs();

        std::string getCodDeBare() const{return this->cod_de_bare;};
        std::string getDenumire() const{return this->denumire;};
        int getCantitate() const{return this->cantitate;};
        double getPret() const{return this->pret;};
        Categorie* getCategorie() const{return this -> categorie;};

        void setCodDeBare(const std::string cod_de_bare){this -> cod_de_bare = cod_de_bare;};
        void setDenumire(const std::string denumire){this -> denumire = denumire;};
        void setCantitate(const int cantitate){this -> cantitate = cantitate;};
        void setPret(const double pret){this -> pret = pret;};
        void setCategorie(const Categorie &categorie){if(this -> categorie != NULL){delete this -> categorie;}this -> categorie = new Categorie(categorie);};

        Produs operator=(const Produs&);
        friend std::ostream& operator<<(std::ostream &, const Produs&);
        friend std::istream& operator>>(std::istream &, Produs&);

        friend void adaugare_produs(const std::string, const std::string, const int, const double, const std::string);
        friend void modificare_produs(const std::string, const int);
        friend void modificare_produs(const std::string, const std::string, const std::string);
        friend void stergere_produs(const std::string); //implementare in App  

    private:
        void init(const std::string, const std::string, const int, const double, const Categorie&);
};