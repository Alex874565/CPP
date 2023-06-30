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

Categorie::Categorie(){
    this -> produse = new Produs*[100];
    this -> nrProduse = 0;
}

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
        this->produse[i] = new Produs(*c.produse[i]);
    }
}

Categorie::~Categorie(){
    if(this -> produse && this -> nrProduse){
        delete [] this->produse;
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

template <typename T> T& operator<<(T& stream, const Categorie& c){
    stream << c.denumire.c_str() << '\n' << c.nrProduse;
    for(int i = 0; i < c.nrProduse; i++){
        stream << '\n' << *c.produse[i];
    }
    return stream;
}

template <typename T> int operator>>(T& stream, Categorie& c){
    char *str0 = new char[50];
    if(stream.getline(str0, 50)){
        c.denumire = str0;
        stream.getline(str0, 50);
        int nrProduse = (int)std::strtol(str0, NULL, 10);
        for(int i = 0; i < nrProduse; i++){
            char *str = new char[50];
            stream.getline(str, 50);
            Produs p;
            p.setCodDeBare(strtok(str, ";"));
            p.setDenumire(strtok(NULL, ";"));
            p.setCantitate((int)std::strtol(strtok(NULL, ";"), NULL, 10));
            p.setPret(std::strtod(strtok(NULL, ";"), NULL));
            p.setCategorie(c.getDenumire());
            c.addProdus(new Produs(p));
        }
        return 1;
    }else{
        return 0;
    }
}

void Categorie::addProdus(Produs *p){
    this -> produse[this -> nrProduse] = new Produs(*p);
    this -> nrProduse += 1;
}

void Categorie::delProdus(const std::string cod_de_bare){
    for(int i = 0; i < this -> nrProduse; i++){
        if(this -> produse[i] -> getCodDeBare() == cod_de_bare){
            this -> nrProduse -= 1;
            for(int j = i; j < this -> nrProduse; j++){
                this -> produse[j] = new Produs(*this -> produse[j + 1]);
            }
            delete this -> produse[this -> nrProduse];
            break;
        }
    }
}