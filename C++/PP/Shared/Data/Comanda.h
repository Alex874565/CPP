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

#ifndef DATAH
#define DATAH
#include "Data.h"
#endif

class Comanda{
        Produs **produse;
        Data *data_comanda;
        Data *data_livrare;
        std::string adresa_livrare;
    public:
        Comanda(const Produs **, const Data&, const Data&, const std::string);
        Comanda(const Comanda&);
        ~Comanda();

        Produs* getProdus(const int i) const{return this->produse[i];};
        Data getDataComanda() const;
        Data getDataLivrare() const;
        std::string getAdresaLivrare() const{return this->adresa_livrare;};

        friend void plasare_comanda(); //tbc       
};