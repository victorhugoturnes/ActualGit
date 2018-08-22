#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#include "pessoa.h"


class Funcionario : public Pessoa{
    private:
    int faltas;
    char date_admissao[12];
    double salario_base;
public:
    Funcionario();
    void set();
    void get();
    ~Funcionario();
};

#endif // FUNCIONARIO_H
