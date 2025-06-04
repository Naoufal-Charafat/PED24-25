#include <iostream>
using namespace std;

#include "tporo.h"
#include "tvectorporo.h"
#include "tabbporo.h"
#include "tlistaporo.h"

int main() {
    // -------------------------------
    // 1. Prueba de TPoro
    // -------------------------------
    cout << "== TPoro ==" << endl;
    TPoro p1(1, 2, 3.0, "ROJO");
    TPoro p2(5, 7, 2.5, "azul");
    TPoro p3(4, 4, 1.5, "Verde");
    TPoro p4; // vacío

    cout << "Poro 1: " << p1 << endl;
    cout << "Poro 2: " << p2 << endl;
    cout << "Poro 3: " << p3 << endl;
    cout << "Poro vacío: " << p4 << endl;

    // -------------------------------
    // 2. Prueba de TVectorPoro
    // -------------------------------
    cout << "\n== TVectorPoro ==" << endl;
    TVectorPoro vector(3);
    vector[1] = p1;
    vector[2] = p2;
    vector[3] = p3;

    cout << "Vector de poros: " << vector << endl;
    cout << "Cantidad no vacíos: " << vector.Cantidad() << endl;

    // -------------------------------
    // 3. Prueba de TABBPoro
    // -------------------------------
    cout << "\n== TABBPoro ==" << endl;
    TABBPoro arbol;

    arbol.Insertar(p1);
    arbol.Insertar(p2);
    arbol.Insertar(p3);

    cout << "Recorrido Inorden: " << arbol.Inorden() << endl;
    cout << "Recorrido Preorden: " << arbol.Preorden() << endl;
    cout << "Recorrido Postorden: " << arbol.Postorden() << endl;
    cout << "Recorrido por Niveles: " << arbol.Niveles() << endl;
    cout << "Nodos totales: " << arbol.Nodos() << endl;
    cout << "Altura del árbol: " << arbol.Altura() << endl;

    // -------------------------------
    // 4. Prueba de TListaPoro
    // -------------------------------
    cout << "\n== TListaPoro ==" << endl;
    TListaPoro lista;

    lista.Insertar(p3);
    lista.Insertar(p2);
    lista.Insertar(p1); // se insertan ordenados por volumen

    cout << "Lista de poros: " << lista << endl;
    cout << "Longitud de la lista: " << lista.Longitud() << endl;

    // Recorrido hacia adelante
    cout << "Recorrido hacia adelante:" << endl;
    for (TListaPosicion pos = lista.Primera(); !pos.EsVacia(); pos = pos.Siguiente()) {
        cout << lista.Obtener(pos) << endl;
    }

    // Recorrido hacia atrás
    cout << "Recorrido hacia atrás:" << endl;
    for (TListaPosicion pos = lista.Ultima(); !pos.EsVacia(); pos = pos.Anterior()) {
        cout << lista.Obtener(pos) << endl;
    }

    return 0;
}
