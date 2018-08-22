#include <iostream>
#include "ponto.h"

using namespace std;

Ponto::Ponto(double x, double y)
{
    this->x = x;
    this->y = y;
    cout << "its a... point?" << endl;
}

void Ponto::setx(double x)
{
    this->x = x;
}
void Ponto::sety(double y)
{
    this->y = y;
}

int Ponto::getx()
{
    return this->x;
}
int Ponto::gety()
{
    return this->y;
}

void Ponto::show()
{
    cout << "(" << x << "," << y << ")" <<endl;
}

Ponto::~Ponto()
{
    cout << "rip point" << endl;
}
