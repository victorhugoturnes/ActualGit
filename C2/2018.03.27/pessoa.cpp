#include "pessoa.h"
#include <iostream>

using namespace std;

void Pessoa::set(){
    char newLine;

    cout << "\nDigite o nome";

    cin.get(nome, 30, '\n');
    cin.get(newLine);

    cout << "\nDigite o Endereco";

    cin.get(endereco, 40, '\n');
    cin.get(newLine);
}

void Pessoa::get(){
    cout << "\nNome:" << nome <<"\n";
    cout << "\nEndereco:" << endereco << "\n";
}


Pessoa::~Pessoa(){
    cout <<"\nLiberando a Memoria Alocada para Pessoa\n";
}
