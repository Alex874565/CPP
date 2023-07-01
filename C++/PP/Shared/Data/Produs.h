#ifndef LIBS
#define LIBS
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#endif

#ifndef CATEGORIEH
#define CATEGORIEH
#include "Categorie.h"
#endif

class Produs_Simplu {
protected:
    std::string cod_de_bare;
    int cantitate;
public:
    std::string getCodDeBare() const{return this->cod_de_bare;};
    int getCantitate() const{return this->cantitate;};

    void setCodDeBare(const std::string cod_de_bare){this -> cod_de_bare = cod_de_bare;};
    void setCantitate(const int cantitate){this -> cantitate = cantitate;};

    template <typename T> friend T& operator>>(T&, Produs_Simplu&);
    template <typename T> friend T& operator<<(T&, const Produs_Simplu&);
};

class Produs : public Produs_Simplu{
        std::string denumire;
        double pret;
        Categorie *categorie;
    public:
        Produs(const std::string = "", const std::string = "", const int = 0, const double = 0, const Categorie& = Categorie(""));
        Produs(const Produs&);
        ~Produs();


        std::string getDenumire() const{return this->denumire;};
        double getPret() const{return this->pret;};
        Categorie* getCategorie() const{return this -> categorie;};

        void setDenumire(const std::string denumire){this -> denumire = denumire;};
        void setPret(const double pret){this -> pret = pret;};
        void setCategorie(const Categorie &categorie){if(this -> categorie != NULL){delete this -> categorie;}this -> categorie = new Categorie(categorie);};

        Produs operator=(const Produs&);
        template <typename T> friend T& operator>>(T&, Produs&);
        template <typename T> friend T& operator<<(T&, const Produs&);
        friend std::string& operator>>(std::string&, Produs&);

        friend void adaugare_produs(const std::string, const std::string, const int, const double, const std::string);
        friend void modificare_produs(const std::string, const int);
        friend void modificare_produs(const std::string, const std::string, const std::string);
        friend void stergere_produs(const std::string); //implementare in App

    private:
        void init(const std::string, const std::string, const int, const double, const Categorie&);
};
