#ifndef LIBS
#define LIBS
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#endif

#include <vector>
#include <ctime>

#ifndef COMANDACPP
#define COMANDACPP
#include "../Shared/Data/Comanda.cpp"
#endif

#ifndef CATEGORIECPP
#define CATEGORIECPP
#include "../Shared/Data/Categorie.cpp"
#endif

#ifndef PRODUSCPP
#define PRODUSCPP
#include "../Shared/Data/Produs.cpp"
#endif

std::string split( const std::string to_be_split, const char separator=';' ) {
    // returneaza literele lui to_be_split
    // care apar inaintea primei aparitii
    // ale lui separator

    std::string temp;
    int iter = 0;
    while( to_be_split[iter] != '\0'
        && to_be_split[iter] != separator ) {
        temp += to_be_split[iter];
        iter ++;
    }
    temp += '\0';
    return temp;

}

void afisare_produs_pentru_user(const Produs& p) {
    std::cout << "Denumire: " << p.getDenumire() << "(" << p.getCodDeBare() <<"), Pret: " << p.getPret() << "lei, Cantitate in stoc: " << p.getCantitate() << std::endl;
}

std::string fila_cos = "../Shared/Files/cos_cumparaturi.txt";
std::string fila_stoc = "../Shared/Files/stoc.txt";
std::string fila_categorii = "../Shared/Files/categorii.txt";
std::string fila_comenzi = "../Shared/Files/comenzi.txt";

void adauga_la_cantitatea_produsului_din_stoc(std::string cod_bare, int cantitate) {

    std::ifstream fin;
    fin.open(fila_stoc.c_str());
    std::vector<Produs*> p;
    Produs aux;
    int nr_produse;

    fin >> nr_produse;
    fin.ignore();

    for(int i = 0; i<nr_produse; i++) {
        fin >> aux;
        if(aux.getCodDeBare() == cod_bare)
            aux.setCantitate(aux.getCantitate() + cantitate);
        p.push_back(new Produs(aux));
    }

    fin.close();
    std::ofstream fout(fila_stoc);
    fout << nr_produse << std::endl;

    for(Produs *el : p)
        fout << *el << std::endl;

    fout.close();

}

void stergere_produs(const std::string cod_bare){

    std::ifstream fin(fila_cos);
    Produs_Simplu aux_ps;
    std::vector<Produs_Simplu*> p1;
    int nr_produse_cos;
    int found = 0;

    fin >> nr_produse_cos;
    fin.ignore();

    for(int i = 0; i<nr_produse_cos; i++) {
        fin >> aux_ps;
        if(aux_ps.getCodDeBare() != cod_bare)
            p1.push_back(new Produs_Simplu(aux_ps));
        if(aux_ps.getCodDeBare() == cod_bare) {
            adauga_la_cantitatea_produsului_din_stoc(cod_bare, aux_ps.getCantitate());
            found = 1;
        }
    }

    fin.close();
    std::ofstream fout(fila_cos);
    fout << (nr_produse_cos-found) << std::endl;

    for(Produs_Simplu *el : p1 )
        fout << *el << std::endl;

    fout.close();

}

void vizualizare_categorie(const std::string denumire_categorie){
    Categorie *c = new Categorie;
    std::ifstream fin(fila_categorii);

    while(fin>>*c) {
        //std::cout << c.getDenumire() << " " << denumire_categorie << " "
        // << (c.getDenumire() == denumire_categorie) << std::endl;
        if(c->getDenumire() == denumire_categorie) {
           // std::cout << c.getDenumire() <<std::endl;
            int N = c->getNrProduse();
            for(int i = 0; i<N; i++)
                afisare_produs_pentru_user(*(c->getProdus(i)));
        }
        c = new Categorie;
    }
    fin.close();
}

void vizualizare_produse(){
    Produs p;
    std::ifstream fin(fila_stoc);
    int numar_produse_din_stoc;
    fin >> numar_produse_din_stoc;
    fin.ignore();

    for(int i = 0; i<numar_produse_din_stoc; i++) {
        fin >> p;
        afisare_produs_pentru_user(p);
    }
}

int afisare_produs(std::string cod_bare) {

    //aceasta functie afiseaza un produs dupa codul sau de bare

    Produs p;
    std::ifstream fin(fila_stoc);
    int numar_produse_din_stoc;
    fin >> numar_produse_din_stoc;
    fin.ignore();

    for(int i = 0; i<numar_produse_din_stoc; i++) {
        fin >> p;
        if(p.getCodDeBare() == cod_bare) {
            afisare_produs_pentru_user(p);
            fin.close();
            return p.getPret();
        }
    }
    fin.close();
    return 0;
}

void vizualizare_cos(){
    std::ifstream fin(fila_cos.c_str());
    int numar_produse_din_cos;
    char* produs_cos = new char[100];
    int pret_total = 0;

    fin>>numar_produse_din_cos;
    fin.ignore();

    for(int i = 0; i<numar_produse_din_cos; i++) {
        fin >> produs_cos;
        char *cod_bare_produs = strtok(produs_cos, ";");
        int cantitate_de_produs = stoi(std::string(strtok(NULL, ";")));

        pret_total += afisare_produs(cod_bare_produs) * cantitate_de_produs;
        std::cout << " cantitate in cos: " << cantitate_de_produs << std::endl;
    }
    std::cout << "Pret Total Comanda: " << pret_total << "lei.";
}

void plasare_comanda(std::string adresa){
    using namespace std;
    time_t now = time(0);
    tm *ltm = localtime(&now);
    ofstream fout(fila_comenzi, ios::app);

    fout << ltm->tm_mday << "-" << (1+ltm->tm_mon) << "-" << ltm->tm_year << ";";
    fout << "UNKNOWN;";
    fout << adresa.c_str() << endl;

    ifstream fin(fila_cos);
    int nr_produse;
    Produs_Simplu p;

    fin >> nr_produse;
    fin.ignore();

    for(int i = 0; i<nr_produse; i++) {
        fin >> p;
        fout << p.getCodDeBare().c_str() << ";" << p.getCantitate() << std::endl;
    }

    fin.close();
    fout.close();
    fout.open(fila_cos);
    fout << 0;
    fout.close();
}

bool avem_produsul(const std::string cod_bare, const int cantitate) {
    std::ifstream fin(fila_stoc);
    int numar_de_produse_din_stoc;
    std::vector<Produs*> vector_produse;
    bool avem_produsul = false; //bool-ul care la sfarsit va raspunde la predicatul functiei

    fin >> numar_de_produse_din_stoc;
    fin.ignore();

    for(int i = 0; i<numar_de_produse_din_stoc; i++) {
        vector_produse.push_back(new Produs);
        fin >> *vector_produse[i];
        if(vector_produse[i]->getCodDeBare() == cod_bare && vector_produse[i]->getCantitate() >= cantitate) {
            //am gasit produsul cu codul de bare cautat
            //in plus avem cantitate destula de produs
            //asa ca updatam cantitatea din stoc si bool-ul
            //echivalent cu valoarea acestei functii
            vector_produse[i]->setCantitate(vector_produse[i]->getCantitate()-cantitate);
            avem_produsul = true;
        }
    }

    fin.close();
    std::ofstream fout(fila_stoc);

    fout << numar_de_produse_din_stoc << std::endl;
    for( Produs* el : vector_produse ) {
        //adaugam toate produsele pe care le-am citit
        fout << *el;
        fout << std::endl;
    }
    fout.close();
    return avem_produsul;

}

void adaugare_produs(const std::string cod_bare, const int cantitate) {

    //daca nu exista produsul cu acest cod de bare
    //sau nu exista cantitate destul de mare de
    //acest produs nu putem adauga in cos
    if(!avem_produsul(cod_bare, cantitate))
        return;

    //in cazul in care avem si cantitatea si produsul
    //adaugam in cos

    std::ifstream fin;
    std::ofstream fout;
    int produs_contor;
    std::vector<std::string> lines;
    std::string line;
    fin.open( fila_cos.c_str() );

    //citim numarul de produse din cos
    fin >> produs_contor;
    fin.ignore();

    // inseram cate string-ul corespunzator fiecarui produs
    // din cos in vector
    for( int i = 0; i < produs_contor; i++ ) {
        getline(fin, line);
        lines.push_back(line);
    }

    fin.close();
    fout.open( fila_cos.c_str() );

    // updatam contorul din fisier
    fout << produs_contor + 1 << std::endl;
    for( int i = 0; i < produs_contor; i++ )
        fout << lines[i].c_str() << std::endl;
    fout << cod_bare.c_str() << ";" << cantitate << std::endl;

}

void modificare_produs(const std::string cod_de_bare, const int cantitate_noua){
    stergere_produs(cod_de_bare);
    adaugare_produs(cod_de_bare, cantitate_noua);
}


int main(int argc, char** argv) {
    if(argc == 1) {
        std::cout << "./utilizator.exe plasare_comanda - pentru a plasa comanda" << std::endl;
        std::cout << "./utilizator.exe vizualizare_categorie <nume_categorie> - pentru a vedea produsele din stoc dintr-o categorie" << std::endl;
        std::cout << "./utilizator.exe modificare_comanda <cod_de_bare> <cantitate_noua> - pentru a modifica cantitatea de produs din cos" << std::endl;
        std::cout << "./utilizator.exe vizualizare_produse - pentru a vedea produsele din stoc" << std::endl;
        std::cout << "./utilizator.exe vizualizare_cos - pentru a vedea produsele din cos" << std::endl;
        std::cout << "./utilizator.exe stergere_produs <cod_de_bare> - pentru a sterge un produs din cos" << std::endl;
        std::cout << "./utilizator.exe adaugare_produs <cod_de_bare> <cantitate> - pentru a adauga o anumita cantitate de produs in cos" << std::endl;

        return 0;
    }
    if(strcmp(argv[1], "adaugare_produs")==0) {
        if(argc != 4) {
            std::cout << "EROARE: sintaxa incorecta! sintaxa corecta: ./utilizator.exe adaugare_produs <cod_de_bare> <cantitate>";
            return -1;
        }
        adaugare_produs(argv[2], stoi(std::string(argv[3])));
        return 0;
    }
    else if(strcmp(argv[1], "stergere_produs")==0) {
        if(argc != 3) {
            std::cout << "EROARE: sintaxa incorecta! sintaxa corecta: ./utilizator.exe stergere_produs <cod_de_bare>";
            return -1;
        }
        stergere_produs(argv[2]);
        return 0;
    }
    else if(strcmp(argv[1], "vizualizare_cos")==0) {
        if(argc != 2) {
            std::cout << "EROARE: sintaxa incorecta! sintaxa corecta: ./utilizator.exe vizualizare_cos";
            return -1;
        }
        vizualizare_cos();
        return 0;
    }
    else if(strcmp(argv[1], "vizualizare_produse")==0) {
        if(argc != 2) {
            std::cout << "EROARE: sintaxa incorecta! sintaxa corecta: ./utilizator.exe vizualizare_produse";
            return -1;
        }
        vizualizare_produse();
        return 0;
    }
    else if(strcmp(argv[1], "modificare_produs")==0) {
        if(argc != 4) {
            std::cout << "EROARE: sintaxa incorecta! sintaxa corecta: ./utilizator.exe modificare_comanda <cod_de_bare> <cantitate_noua>";
            return -1;
        }
        modificare_produs(argv[2], stoi(std::string(argv[3])));
        return 0;
    }
    else if(strcmp(argv[1], "vizualizare_categorie")==0) {
        if(argc != 3) {
            std::cout << "EROARE: sintaxa incorecta! sintaxa corecta: ./utilizator.exe vizualizare_categorie <nume_categorie>";
            return -1;
        }
        vizualizare_categorie(argv[2]);
        return 0;
    }
    else if(strcmp(argv[1], "plasare_comanda")==0) {
        if(argc != 2) {
            std::cout << "EROARE: sintaxa incorecta! sintaxa corecta: ./utilizator.exe plasare_comanda";
            return -1;
        }
        std::string s;
        std::cout << "Please give us your address: ";
        std::getline(std::cin, s);
        std::cout << std::endl;
        plasare_comanda(s);
        return 0;
    }
    else {
        std::cout << "Aceasta comanda nu exista! Incercati una dintre urmatoarele: " << std::endl;
        std::cout << "./utilizator.exe plasare_comanda - pentru a plasa comanda" << std::endl;
        std::cout << "./utilizator.exe vizualizare_categorie <nume_categorie> - pentru a vedea produsele din stoc dintr-o categorie" << std::endl;
        std::cout << "./utilizator.exe modificare_comanda <cod_de_bare> <cantitate_noua> - pentru a modifica cantitatea de produs din cos" << std::endl;
        std::cout << "./utilizator.exe vizualizare_produse - pentru a vedea produsele din stoc" << std::endl;
        std::cout << "./utilizator.exe vizualizare_cos - pentru a vedea produsele din cos" << std::endl;
        std::cout << "./utilizator.exe stergere_produs <cod_de_bare> - pentru a sterge un produs din cos" << std::endl;
        std::cout << "./utilizator.exe adaugare_produs <cod_de_bare> <cantitate> - pentru a adauga o anumita cantitate de produs in cos" << std::endl;
    }
    return 0;
}
