#include "funcionario.h"
#include <iostream>

using namespace std;

Funcionario::Funcionario() : Pessoa()
{
    this->faltas = 0;
    this->date_admissao[0] = '\0';
    this->salario_base = 0;
}

void Funcionario::set()
{
    char newLine;
    cout << "ENTRADA DE DADOS DE FUNCIONARIOS" << endl;
    Pessoa::set();
    cout << "\nDigite o salario base: ";
    cin >> salario_base;
    cout << "\nDigite a data de admissao (dd/mm/yyyy): ";
    cin.get(newLine);
    cin.get(this->date_admissao, 12, '\n');
    cout << "\nDigite o numero de faltas: ";
    cin >> faltas;
}

void Funcionario::get()
{
    cout << "SAIDA DE DADOS DE FUNCIONARIO" << endl;
    Pessoa::get();
    cout << "\nSalario base: " << salario_base;
    cout << "\nData de admissao (dd/mm/yyyy): " << date_admissao;
    cout << "\nFaltas: " << faltas;

}

Funcionario::~Funcionario()
{
    cout << "aaand its dead" << endl;
}
