#include <iostream>

using namespace std;

#include "../include/tporo.h"
#include "../include/tvectorporo.h"

int
main(void)
{
  TPoro a(1, 2, 3, "rojo");
  TVectorPoro v(5);

  cout << "Cantidad: " << v.Cantidad() << endl;

  v[1] = a;
  cout << "Cantidad: " << v.Cantidad() << endl;

  v[2] = a;
  cout << "Cantidad: " << v.Cantidad() << endl;

  v[3] = a;
  cout << "Cantidad: " << v.Cantidad() << endl;

  v[4] = a;
  cout << "Cantidad: " << v.Cantidad() << endl;

  v[5] = a;
  cout << "Cantidad: " << v.Cantidad() << endl;
}
