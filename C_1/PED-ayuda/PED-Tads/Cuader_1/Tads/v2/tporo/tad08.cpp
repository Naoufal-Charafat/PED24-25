#include <iostream>

using namespace std;

#include "../include/tporo.h"

int
main(void)
{
  TPoro a;

  if(a.EsVacio())
    cout << "VACIO" << endl;
  else
    cout << "NO VACIO" << endl;

  a.Color("rojo");

  if(a.EsVacio())
    cout << "VACIO" << endl;
  else
    cout << "NO VACIO" << endl;
}
