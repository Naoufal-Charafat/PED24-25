#include <iostream>

using namespace std;

#include "../include/tporo.h"
#include "../include/tvectorporo.h"

int
main(void)
{
  TVectorPoro a(5);
  TVectorPoro b;

  if(a == b)
    cout << "SI"  << endl;
  else
    cout << "NO" << endl;
}
