#ifndef LIBS
#define LIBS
#include <iostream>
#include <string>
#include <string.h>
#endif

#include <fstream>
#include <sstream>

#ifndef PRODUSH
#define PRODUSH
#include "Produs.h"
#endif

void Categorie::init(const std::string denumire, const int nrProduse, const Produs** produse){
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
    this->denumire = c.denumire;
    this->nrProduse = c.nrProduse;
    this->produse = new Produs*[100];
    for(int i = 0; i < this->nrProduse; i++){
        this->produse[i] = new Produs(*(c.produse[i]));
    }
}

Categorie::~Categorie(){
    if(this -> produse){
        for(int i = 0; i < this->nrProduse; i++){
            delete this->produse[i];
        }
    }
}

Categorie Categorie::operator=(const Categorie& c){
    this->denumire = c.denumire;
    this->nrProduse = c.nrProduse;
    this->produse = new Produs*[100];
    for(int i = 0; i < this->nrProduse; i++){
        this->produse[i] = new Produs(*(c.produse[i]));
    }
    return *this;
}

void Categorie::setProdus(const Produs &p, const int i){
    if(this->produse[i] != NULL){
        delete this->produse[i];
    }
    this->produse[i] = new Produs(p);
}

std::ostream& operator<<(std::ostream& stream, const Categorie& c){
    stream << c;
    return stream;
}

int operator>>(std::ifstream& stream, Categorie& c){
    char *str0 = new char[50];
    if(stream.getline(str0, 50)){
        c.setDenumire(str0);
        stream.getline(str0, 50);
        c.setNrProduse((int)std::strtol(str0, NULL, 10));
        for(int i = 0; i < c.getNrProduse(); i++){
            char *str = new char[50];
            stream.getline(str, 50);
            Produs p;
            p.setCodDeBare(strtok(str, " "));
            p.setDenumire(strtok(NULL, " "));
            p.setCantitate((int)std::strtol(strtok(NULL, " "), NULL, 10));
            p.setPret(std::strtod(strtok(NULL, " "), NULL));
            p.setCategorie(c.getDenumire());
            c.setProdus(p, i);
        }
        return 1;
    }else{
        return 0;
    }
}