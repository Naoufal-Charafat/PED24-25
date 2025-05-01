#include <iostream>

using namespace std;

#include "../include/tporo.h"
#include "../include/tvectorporo.h"

int
main(void)
{
  TPoro a(1, 2, 3, "rojo");
  TVectorPoro v(5), w;

  cout << "Longitud: " << v.Longitud() << endl;
  cout << "Longitud: " << w.Longitud() << endl;

  w = v;

  cout << "Longitud: " << v.Longitud() << endl;
  cout << "Longitud: " << w.Longitud() << endl;
}
