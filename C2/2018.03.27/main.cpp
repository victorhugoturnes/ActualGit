#include <iostream>
#include <stdlib.h>
#include <funcionario.h>

using namespace std;

int main()
{
    /*
    Pessoa *p = 0;
    p = new Pessoa();

    p->set();
    p->get();

    delete p;

    return 0;
*/
    Funcionario *f = new Funcionario();

    f->set();

    f->get();

    delete f;
}
