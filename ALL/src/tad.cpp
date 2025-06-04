#include <iostream>
using namespace std;

#include "tporo.h"
#include "tvectorporo.h"
#include "tabbporo.h"
#include "tlistaporo.h"

int main() {
    cout << "==== PRUEBA DE TPORO ====" << endl;
    TPoro p1(1, 2, 3.5, "Rojo");
    TPoro p2(4, 5, 1.2, "Azul");
    TPoro p3(1, 2, 3.5, "rojo");

    cout << "TPoro p1: " << p1 << endl;
    cout << "TPoro p2: " << p2 << endl;
    cout << "TPoro p3 (igual a p1): " << p3 << endl;
    cout << "¿p1 == p3? " << (p1 == p3 ? "Sí" : "No") << endl;

    cout << "\n==== PRUEBA DE TVECTORPORO ====" << endl;
    TVectorPoro v(3);
    v[1] = p1;
    v[2] = p2;
    v[3] = p3;
    cout << "Vector de Poros: " << v << endl;
    cout << "Cantidad de elementos no vacíos: " << v.Cantidad() << endl;

    cout << "\n==== PRUEBA DE TLISTAPORO ====" << endl;
    TListaPoro lista;
    lista.Insertar(p2);
    lista.Insertar(p1);
    lista.Insertar(p3); // No se insertará por duplicado
    cout << "Lista de Poros (ordenada por volumen): " << lista << endl;
    cout << "¿Contiene p1? " << (lista.Buscar(p1) ? "Sí" : "No") << endl;
    cout << "Longitud de la lista: " << lista.Longitud() << endl;

    cout << "\n==== EXTRACCIÓN DE RANGO EN LISTA ====" << endl;
    TListaPoro extraida = lista.ExtraerRango(1, 1);
    cout << "Lista extraída (1,1): " << extraida << endl;
    cout << "Lista original tras extracción: " << lista << endl;

    cout << "\n==== PRUEBA DE TABBPORO ====" << endl;
    TABBPoro arbol;
    arbol.Insertar(p1);
    arbol.Insertar(p2);
    arbol.Insertar(p3); // No se insertará (mismo volumen que p1)
    cout << "Árbol en niveles: " << arbol << endl;
    cout << "Inorden: " << arbol.Inorden() << endl;
    cout << "Preorden: " << arbol.Preorden() << endl;
    cout << "Postorden: " << arbol.Postorden() << endl;
    cout << "Altura del árbol: " << arbol.Altura() << endl;
    cout << "Nodos totales: " << arbol.Nodos() << endl;
    cout << "Nodos hoja: " << arbol.NodosHoja() << endl;

    cout << "esto es  src/tad" << endl;

    return 0;
}
