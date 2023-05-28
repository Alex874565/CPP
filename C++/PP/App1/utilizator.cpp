#ifndef LIBS
#define LIBS
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#endif

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

void stergere_produs(const std::string cod_bare){
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
    return ; //tbc
}

void vizualizare_cos(){
    return ; //tbc
}

void plasare_comanda(){
    return ; //tbc
}

void adaugare_produs(const std::string cod_bare, const std::string cantitate) {
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
        adaugare_produs(argv[2], argv[3]);
        return 0;
    }
    if(strcmp(argv[1], "stergere_produs")==0) {
        if(argc < 3) {
            std::cout << "EROARE: numar prea mic de parametrii";
            return -1;
        }
        stergere_produs(argv[2]);
        return 0;
    }
}
