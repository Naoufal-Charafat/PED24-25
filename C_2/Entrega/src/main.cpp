#include <iostream>

using namespace std;

#include "tporo.h"
#include "tvectorporo.h"
#include "tabbporo.h"


int main()
{
{
  TPoro a(1, 2, 3, (char*) "rojo");

  cout << a << endl;
}
{
  TPoro a(1, 2, 3, (char*) "rojo");
  TVectorPoro v(5);

  v[1] = a;
  v[2] = a;
  v[3] = a;
  v[4] = a;
  v[5] = a;

  cout << v << endl;
}
{
  TPoro a(1, 2, 3, (char*) "rojo");
  TPoro b(1, 2, 3, (char*) "rojo");
  TPoro c(1, 2, 3, (char*) "rojo");

  TABBPoro arbol;
  arbol.Insertar(a);
  arbol.Insertar(b);
  arbol.Insertar(c);

  cout << arbol << endl;

}

}
