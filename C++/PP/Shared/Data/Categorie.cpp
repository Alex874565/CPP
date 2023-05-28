#ifndef LIBS
#define LIBS
#include <iostream>
#include <string>
#include <string.h>
#endif

#ifndef PRODUSH
#define PRODUSH
#include "Produs.h"
#endif

void Categorie::init(std::string denumire, const int nrProduse, const Produs** produse){
    this->denumire = denumire;
    this->nrProduse = nrProduse;
    this->produse = new Produs*[100];
    for(int i = 0; i < this->nrProduse; i++){
        this->produse[i] = new Produs(*produse[i]);
    }
}

Categorie::Categorie(const std::string denumire, const int nrProduse, const Produs ** produse){
    this->init(denumire, nrProduse, produse);
}

Categorie::Categorie(const Categorie& c){
    this->init(c.denumire, c.nrProduse, NULL); //tbc
}

Categorie::~Categorie(){
    for(int i = 0; i < this->nrProduse; i++){
        delete this->produse[i];
    }
    delete [] this->produse;
}

void Categorie::addProdus(const Produs *){
    return ; //tbc
}

//Categorie Categorie::operator=(const Categorie& c){
//    this->init(c.denumire, c.nrProduse, c.produse);
//}

std::ostream& operator<<(std::ostream& stream, const Categorie& c){
    stream << c;
    return stream;
}

std::ifstream& operator>>(std::ifstream& stream, Categorie*){
    
    return stream; //tbc
}