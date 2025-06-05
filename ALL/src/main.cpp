#include <iostream>
#include "tabbporo.h"
#include "tlistaporo.h"
#include "tporo.h"

using namespace std;

int main() {
    cout << "=== PRUEBAS DE LA FUNCIÓN EXAMEN ===" << endl << endl;
    
    // Crear poros de prueba con diferentes volúmenes
    TPoro p1(1, 1, 10.0, "rojo");    // volumen 10
    TPoro p2(2, 2, 5.0, "azul");     // volumen 5
    TPoro p3(3, 3, 15.0, "verde");   // volumen 15
    TPoro p4(4, 4, 3.0, "amarillo"); // volumen 3
    TPoro p5(5, 5, 12.0, "negro");   // volumen 12
    TPoro p6(6, 6, 20.0, "blanco");  // volumen 20
    TPoro p7(7, 7, 8.0, "violeta");  // volumen 8
    
    // PRUEBA 1: Árbol vacío
    cout << "PRUEBA 1: Árbol vacío" << endl;
    TABBPoro arbolVacio;
    TListaPoro lista1;
    lista1.Insertar(p1);
    lista1.Insertar(p2);
    cout << "Resultado: " << (arbolVacio.examen(lista1) ? "TRUE" : "FALSE") << " (esperado: FALSE)" << endl << endl;
    
    // PRUEBA 2: Lista vacía
    cout << "PRUEBA 2: Lista vacía" << endl;
    TABBPoro arbol1;
    arbol1.Insertar(p1);
    arbol1.Insertar(p2);
    TListaPoro listaVacia;
    cout << "Resultado: " << (arbol1.examen(listaVacia) ? "TRUE" : "FALSE") << " (esperado: FALSE)" << endl << endl;
    
    // Crear árbol para las siguientes pruebas
    TABBPoro arbol;
    arbol.Insertar(p1);  // 10 (raíz)
    arbol.Insertar(p2);  // 5 (izquierda de 10)
    arbol.Insertar(p3);  // 15 (derecha de 10)
    arbol.Insertar(p4);  // 3 (izquierda de 5)
    arbol.Insertar(p5);  // 12 (izquierda de 15)
    arbol.Insertar(p6);  // 20 (derecha de 15)
    arbol.Insertar(p7);  // 8 (derecha de 5)
    
    cout << "Árbol creado con volúmenes: 10(raíz), 5, 15, 3, 12, 20, 8" << endl;
    cout << "Estructura del árbol:" << endl;
    cout << "       10" << endl;
    cout << "      /  \\" << endl;
    cout << "     5    15" << endl;
    cout << "    / \\   / \\" << endl;
    cout << "   3   8 12  20" << endl << endl;
    
    // PRUEBA 3: Camino descendente válido (3 -> 20)
    cout << "PRUEBA 3: Camino descendente válido" << endl;
    TListaPoro lista2;
    lista2.Insertar(p4);  // volumen 3 (mínimo)
    lista2.Insertar(p1);  // volumen 10
    lista2.Insertar(p6);  // volumen 20 (máximo)
    lista2.Insertar(p2);  // volumen 5
    cout << "Lista con volúmenes: 3, 10, 20, 5 (min=3, max=20)" << endl;
    cout << "¿Existe camino descendente de 3 a 20? ";
    cout << (arbol.examen(lista2) ? "TRUE" : "FALSE") << " (esperado: TRUE)" << endl << endl;
    
    // PRUEBA 4: No hay camino descendente (20 -> 3)
    cout << "PRUEBA 4: No hay camino descendente (orden inverso)" << endl;
    TListaPoro lista3;
    lista3.Insertar(p6);  // volumen 20 (máximo)
    lista3.Insertar(p1);  // volumen 10
    lista3.Insertar(p4);  // volumen 3 (mínimo)
    cout << "Lista con volúmenes: 20, 10, 3 (min=3, max=20)" << endl;
    cout << "¿Existe camino descendente de 3 a 20? ";
    cout << (arbol.examen(lista3) ? "TRUE" : "FALSE") << " (esperado: TRUE)" << endl << endl;
    
    
    cout << "=== FIN DE LAS PRUEBAS ===" << endl;
    
    return 0;
}