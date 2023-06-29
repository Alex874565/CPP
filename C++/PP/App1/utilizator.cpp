#ifndef LIBS
#define LIBS
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#endif

#include <vector>

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

std::string fila_cos = "../Shared/Files/cos_cumparaturi.txt";
std::string fila_stoc = "../Shared/Files/stoc.txt";

void stergere_produs(const std::string cod_bare){

    //NETERMINAT

    std::ifstream fin;
    std::ofstream fout;
    int produs_contor; //cate elemente sunt inainte de stergere
    int new_contor = 0; //cate elemente raman dupa stergere
    std::vector<std::string> lines;
    std::string line;
    fin.open( fila_cos.c_str() );

    // citim numarul de produse din cos
    fin >> produs_contor;
    fin.ignore();

    // inseram string-ul corespunzator fiecarui produs
    // din cos in vector
    for( int i = 0; i < produs_contor; i++ ) {
        getline(fin, line);
        if( strcmp( split(line).c_str(), cod_bare.c_str() ) != 0 ) {
            lines.push_back(line);
            new_contor ++;
        }
    }

    fin.close();
    fout.open( fila_cos.c_str() );

    // updatam contorul si produsele din fisier
    fout << new_contor << std::endl;
    for( int i = 0; i < new_contor; i++ )
        fout << lines[i] << std::endl;

}

void modificare_produs(const std::string, const int){
    return ; //tbc
}

void vizualizare_categorie(const std::string){
    return ; //tbc
}

void vizualizare_produse(){
    Produs p;
    std::ifstream fin(fila_stoc);
    int numar_produse_din_stoc;
    fin >> numar_produse_din_stoc;
    fin.ignore();

    for(int i = 0; i<numar_produse_din_stoc; i++) {
        fin >> p;
        std::cout << p << std::endl;
    }
}

void afisare_produs(std::string cod_bare) {

    //aceasta functie afiseaza un produs dupa codul sau de bare

    Produs p;
    std::ifstream fin(fila_stoc);
    int numar_produse_din_stoc;
    fin >> numar_produse_din_stoc;
    fin.ignore();

    for(int i = 0; i<numar_produse_din_stoc; i++) {
        fin >> p;
        if(p.getCodDeBare() == cod_bare) {
            std::cout << p;
            fin.close();
            return;
        }
    }
    fin.close();
}

void vizualizare_cos(){
    std::ifstream fin(fila_cos.c_str());
    int numar_produse_din_cos;
    char* produs_cos = new char[100];

    fin>>numar_produse_din_cos;
    fin.ignore();

    for(int i = 0; i<numar_produse_din_cos; i++) {
        fin >> produs_cos;
        char *cod_bare_produs = strtok(produs_cos, ";");
        char *cantitate_de_produs = strtok(NULL, ";");

        afisare_produs(cod_bare_produs);
        std::cout << " cantitate in cos: " << cantitate_de_produs << std::endl;
    }
}

void plasare_comanda(){
    return ; //tbc
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
        fout << lines[i] << std::endl;
    fout << cod_bare << ";" << cantitate << std::endl;

}

int main(int argc, char** argv) {
    if(argc == 1) return 0;
    if(strcmp(argv[1], "adaugare_produs")==0) {
        if(argc < 4) {
            std::cout << "EROARE: numar prea mic de parametrii";
            return -1;
        }
        adaugare_produs(argv[2], stoi(std::string(argv[3])));
        return 0;
    }
    else if(strcmp(argv[1], "stergere_produs")==0) {
        if(argc < 3) {
            std::cout << "EROARE: numar prea mic de parametrii";
            return -1;
        }
        stergere_produs(argv[2]);
        return 0;
    }
    else if(strcmp(argv[1], "vizualizare_cos")==0) {
        if(argc != 2) {
            std::cout << "EROARE: numar incorect de parametrii";
            return -1;
        }
        vizualizare_cos();
        return 0;
    }
    else if(strcmp(argv[1], "vizualizare_produse")==0) {
        if(argc != 2) {
            std::cout << "EROARE: numar incorect de parametrii";
            return -1;
        }
        vizualizare_produse();
        return 0;
    }
}
