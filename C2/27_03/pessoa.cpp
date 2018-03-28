#include "pessoa.h"
#include <iostream>

using namespace std;

Pessoa::~Pessoa(){
    cout <<"\n Liberando a Memoria Aloada para Pessoa";
}

void Pessoa::setar(){
    char newLine;
    cout << "\n Digite o nome";
    cin.get(nome, 30, '\n');
    cin.get(newLine);
    cout << "\n Digite o Endereco";
    cin.get(endereco, 40, '\n');
    cin.get(newLine);
}

void Pessoa::mostrar(){
    cout << "\n Nome:" << nome <<"\n";
    cout << "\n Endereco:" << endereco << "\n";
}
