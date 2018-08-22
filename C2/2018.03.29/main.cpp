#include <iostream>
#include "ponto.h"

using namespace std;

int main()
{
    Ponto *p = new Ponto(10, 20);

    p->show();

    p->setx(40);

    p->show();

    delete p;

    return 0;
}
