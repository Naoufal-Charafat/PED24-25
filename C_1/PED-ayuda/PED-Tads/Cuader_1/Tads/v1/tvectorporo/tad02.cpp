#include <iostream>

using namespace std;

#include "../include/tporo.h"
#include "../include/tvectorporo.h"

int
main(void)
{
  TPoro auxOK;
  TVectorPoro a, b(5), c(10);

  cout << a.Longitud() << endl;
  cout << b.Longitud() << endl;
  cout << c.Longitud() << endl;
}
