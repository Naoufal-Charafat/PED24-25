#include <iostream>
#include <sstream>
#include <cstdlib>
#include "../include/tporo.h"
#include "../include/tvectorporo.h"
#include "../include/tlistaporo.h"
using namespace std;

void TADPoro1() {
	TPoro p1;
	if (p1.PosicionX() != 0) cerr << "Constructor por defecto X. Esperado " << 0 << ", actual " << p1.PosicionX() << endl;
	if (p1.PosicionY() != 0) cerr << "Constructor por defecto Y. Esperado " << 0 << ", actual " << p1.PosicionY() << endl;
	if (p1.Volumen() != 0) cerr << "Constructor por defecto volumen. Esperado " << 0 << ", actual " << p1.Volumen() << endl;
	if (p1.Color() != NULL) cerr << "Constructor por defecto color. Esperado NULL" << endl;

	TPoro p2 = TPoro(-10, 0, -30);
	if (p2.PosicionX() != -10) cerr << "Constructor por parámetro X. Esperado " << -10 << ", actual " << p2.PosicionX() << endl;
	if (p2.PosicionY() != 0) cerr << "Constructor por parámetro Y. Esperado " << 0 << ", actual " << p2.PosicionY() << endl;
	if (p2.Volumen() != -30) cerr << "Constructor por parámetro volumen. Esperado " << -30 << ", actual " << p2.Volumen() << endl;
	if (p2.Color() != NULL) cerr << "Constructor por parámetro color. Esperado NULL" << endl;

	TPoro p3 = TPoro(-10, 0, -30, (char*) "Na Na");
	if (p3.PosicionX() != -10) cerr << "Constructor por parámetro [color] X. Esperado " << -10 << ", actual " << p3.PosicionX() << endl;
	if (p3.PosicionY() != 0) cerr << "Constructor por parámetro [color] Y. Esperado " << 0 << ", actual " << p3.PosicionY() << endl;
	if (p3.Volumen() != -30) cerr << "Constructor por parámetro [color] volumen. Esperado " << -30 << ", actual " << p3.Volumen() << endl;
	if (strcmp(p3.Color(),"na na") != 0) cerr << "Constructor por parámetro [color] color. Esperado " << "na na" << ", actual " << p3.Color() << endl;

	TPoro pc(p3);
	p3 = TPoro();
	if (pc.PosicionX() != -10) cerr << "Constructor por parámetro [color] X. Esperado " << -10 << ", actual " << pc.PosicionX() << endl;
	if (pc.PosicionY() != 0) cerr << "Constructor por parámetro [color] Y. Esperado " << 0 << ", actual " << pc.PosicionY() << endl;
	if (pc.Volumen() != -30) cerr << "Constructor por parámetro [color] volumen. Esperado " << -30 << ", actual " << pc.Volumen() << endl;
	if (strcmp(pc.Color(),"na na") != 0) cerr << "Constructor por parámetro [color] color. Esperado " << "na na" << ", actual " << pc.Color() << endl;
}

void TADPoro2() {
	TPoro p1(10, 20, -10, (char*) "Negro Cabron");
	p1.Posicion(-10, -20);
	p1.Volumen(10);
	p1.Color((char*) "Negro Carbon");

	if(p1.PosicionX() != -10) cerr << "Setter Posicion. Esperado X=" << -10 << ", actual X=" << p1.PosicionX() << endl;
	if(p1.PosicionY() != -20) cerr << "Setter Posicion. Esperado Y=" << -20 << ", actual X=" << p1.PosicionY() << endl;
	if(p1.Volumen() != 10) cerr << "Setter Volumen. Esperado " << 10 << ", actual " << p1.Volumen() << endl;
	if(strcmp(p1.Color(), "negro carbon") != 0) cerr << "Setter Color. Esperado " << "negro carbon" << ", actual " << p1.Color() << endl;

	TPoro p2(p1);
	TPoro p3 = p2;
	TPoro p4; //p4 con color NULL
	if(p1 == p4 || p2 == p4 || p3 == p4) cerr << "Operador == no funciona correctamente";
	if(p1 != p2 || p1 != p3 || p2 != p3) cerr << "Operador != no funciona correctamente";

	TPoro p5, p6(10,0,0), p7(0,10,0), p8(0,0,10), p9(0,0,0,(char*)"");
	if(!p5.EsVacio() || p6.EsVacio() || p7.EsVacio() || p8.EsVacio() || p9.EsVacio()) cerr << "EsVacio no funciona correctamente" << endl;

	stringstream ss;

	ss << p1;
	if(ss.str() != "(-10, -20) 10.00 negro carbon") cerr << "el operador << no funciona correctamente.\nEsperado: " << "(-10, -20) 10.00 negro carbon" << endl << "Actual: " << ss.str() << endl;

	ss.str("");
	ss << p5;
	if(ss.str() != "()") cerr << "el operador << no funciona correctamente.\nEsperado: " << "()" << endl << "Actual: " << ss.str() << endl;

	ss.str("");
	ss << TPoro(10,0,0);
	if(ss.str() != "(10, 0) 0.00 -") cerr << "el operador << no funciona correctamente.\nEsperado: " << "(10, 0) 0.00 -" << endl << "Actual: " << ss.str() << endl;
}

void TADVector1() {
	TVectorPoro v1;
	if(v1.Longitud() != 0) cerr << "Constructor por defecto dimension. Esperado " << 0 << ", actual " << v1.Longitud() << endl;
	if(v1.getDatosPtr() != NULL) cerr << "Constructor por defecto datos. Esperado NULL" << endl; //NOTA: Hay que definir un getter extra

	TVectorPoro v2(10);
	if(v2.Longitud() != 10) cerr << "Constructor por parametros dimension. Esperado " << 10 << ", actual " << v2.Longitud();
	if(v2.getDatosPtr() == NULL) cerr << "Constructor por parametros datos. Esperado NOT NULL" << endl;
	if(v2.Cantidad() != 0) cerr << "Constructor por parametros cantidad. Esperado " << 0 << ", actual " << v2.Cantidad();

	TVectorPoro v3(v2);
	v2 = TVectorPoro();
	if(v3.Longitud() != 10) cerr << "Constructor por parametros dimension. Esperado " << 10 << ", actual " << v3.Longitud();
	if(v3.getDatosPtr() == NULL) cerr << "Constructor por parametros datos. Esperado NOT NULL" << endl;
	if(v3.Cantidad() != 0) cerr << "Constructor por parametros cantidad. Esperado " << 0 << ", actual " << v3.Cantidad();
}

void TADVector2() {
	TVectorPoro v1(2), v2(v1), v3 = v1, v4(1);
	if(v3.Longitud() != v2.Longitud()) cerr << "Constructor por parametros dimension. Esperado " << v2.Longitud() << ", actual " << v3.Longitud();
	if(v3.getDatosPtr() == v2.getDatosPtr()) cerr << "Constructor por parametros datos. Esperado diferente de" << v2.getDatosPtr() << endl;
	if(v3.Cantidad() != v2.Cantidad()) cerr << "Constructor por parametros cantidad. Esperado " << v2.Longitud() << ", actual " << v3.Cantidad();

	if(v1 != v2 || v1 != v3) cerr << "operador != no funciona correctamente" << endl;
	if(v1 == v4) cerr << "operador == no funciona correctamente" << endl;

	TPoro e, p(1, 2, -1, (char*) "JORDI GORDO");
	v1[2] = p;
	if(v1[2] != p) cerr << "los operadores [] no funcionan correctamente" << endl;
	if(v1[0] != e) cerr << "los operadores [] no lanzan error cuando accedes a posiciones que no existen" << endl;
	if(v1[3] != e) cerr << "los operadores [] no lanzan error cuando accedes a posiciones que no existen" << endl;

	if(v1.Cantidad() != 1) cerr << "Cantidad. Esperado " << 1 << ", actual " << v1.Cantidad() << endl;
	v1.Redimensionar(20);
	v1[20] = p;
	if(v1.Longitud() != 20) cerr << "Longitud. Esperado " << 20 << ", actual " << v1.Longitud() << endl;
	if(v1.Cantidad() != 2) cerr << "Cantidad. Esperado " << 2 << ", actual " << v1.Cantidad() << endl;
	v1.Redimensionar(0);
	if(v1.Longitud() != 20) cerr << "Longitud. Esperado " << 20 << ", actual " << v1.Longitud() << endl;
	if(v1.Cantidad() != 2) cerr << "Cantidad. Esperado " << 2 << ", actual " << v1.Cantidad() << endl;
	if(v1[2] != p || v1[20] != p) cerr << "Redimensionar. Los objetos no se conservan" << endl;
	TVectorPoro v5 = v1;
	v1[1] = p;
	v1.Redimensionar(1);
	if(v1.Longitud() != 1) cerr << "Longitud. Esperado " << 1 << ", actual " << v1.Longitud() << endl;
	if(v1.Cantidad() != 1) cerr << "Cantidad. Esperado " << 1 << ", actual " << v1.Cantidad() << endl;

	v1 = TVectorPoro();
	stringstream ss;
	ss << v1;
	if(ss.str() != "[]") cerr << "Operador << no funciona bien"  << endl << "Esperado: " << "[]" << endl << "Actual: " << ss.str() << endl;

	string salidaV5Esperada = "[1 () 2 (1, 2) -1.00 jordi gordo "
			"3 () 4 () 5 () 6 () 7 () 8 () 9 () 10 () 11 () 12 () 13 () 14 () 15 () 16 () 17 () 18 () 19 () "
			"20 (1, 2) -1.00 jordi gordo]";
	ss.str("");
	ss << v5;
	if(ss.str() != salidaV5Esperada) cerr << "Operador << no funciona bien" << endl << "Esperado: " << salidaV5Esperada << endl << "Actual: " << ss.str() << endl;
}

void TADLista() {
	//Poros de prueba
		TPoro p1(1, 2, 3, (char*) "p1");
		TPoro p2(3, 2, 1, (char*) "p2");
		TPoro p3(2, 3, 1, (char*) "p3");
		TPoro p4(2, 3, 3, (char *) "p4");
		TPoro p5(2, 2, 2, (char *) "p5");
		TPoro p6(0, 0, 0);

		TListaPoro l1, l1Copia; //Lista vacia
		bool vaciaVacia = l1.EsVacia(); //True
		TListaPosicion primeraVacia = l1.Primera(); //Posicion vacia
		TListaPosicion ultimaVacia = l1.Ultima(); //Posicion vacia tambien
		l1.Borrar(primeraVacia); //No borra nada
		l1.Borrar(ultimaVacia); //Sorpresa: tampoco borra nada

		//Los vamos insertando. Importante el orden en el que lo insertamos
		l1.Insertar(p2);
		l1.Insertar(p1);
		l1.Insertar(p1);
		l1.Insertar(p3);
		l1.Insertar(p4);
		l1.Insertar(p5);

		l1Copia.Insertar(p2);
		l1Copia.Insertar(p1);
		l1Copia.Insertar(p1);
		l1Copia.Insertar(p3);
		l1Copia.Insertar(p4);
		l1Copia.Insertar(p5);

		bool operadorIgual = l1 == l1Copia; //Comprueba que el operador de copia funcione bien

		bool vaciaLlena = l1.EsVacia(); //False
		TListaPosicion primeraLlena = l1Copia.Primera(); //Apunta a p2
		TListaPosicion ultimaLlena = l1Copia.Ultima(); //Apunta a p4

		TListaPoro l2(l1), l3 = l2; //Constructor de copia, operador de asignacion
		bool iguales = l1 == l2 && l1 == l3 && l2 == l3; //True


		//Insertamos en l2 un nuevo poro (un poro vacio). Ahora debe de ser diferente a l1 y l3
		l2.Insertar(p6);
		bool diferentes = l1 == l2 && l2 == l3; //False


		l2.Borrar(p6); //Borro el que acabo de insertar
		l2.Borrar(p6); //No borra nada. Ya esta borrado
		l2.Borrar(primeraLlena); //Le pasamos una posicion a un nodo de l1; no borra nada
		TListaPosicion segundaL2 = l2.Primera().Siguiente();
		l2.Borrar(segundaL2); //Borramos la segunda
		int longitudL2 = l2.Longitud(); //4

		TListaPoro l4, l2Backward;//lista nueva vacia y lista2 hacia atras
		stringstream ssl2Backward;
		string expectedl2Backward = "((3, 2) 1.00 p2 (2, 2) 2.00 p5 (1, 2) 3.00 p1 (2, 3) 3.00 p4)";
		for(TListaPosicion i = l2.Ultima(); !i.EsVacia(); i = i.Anterior()) {
			l2Backward.Insertar(l2.Obtener(i)); //Por mucho que la recorra al reves, el insertar me los pone en orden
		}
		for(int i = 0; i < longitudL2; i++) { //Borro toda una lista entera
			TListaPosicion aux = l2.Primera();
			l2.Borrar(aux);
		}
		int longitudL2Vacia = l2.Longitud();
		ssl2Backward << l2Backward;

		//Comprobamos las salidas y los extraer rango
		stringstream ssl1a, ssl1b, ssl1c, ssl1d;
		string expectedl1a = "((3, 2) 1.00 p2 (2, 3) 1.00 p3 (2, 2) 2.00 p5 (1, 2) 3.00 p1 (2, 3) 3.00 p4)";
		string expectedl1b = "()";
		string expectedl1c = "((2, 2) 2.00 p5 (1, 2) 3.00 p1 (2, 3) 3.00 p4)";
		string expectedl1d = "((3, 2) 1.00 p2 (2, 3) 1.00 p3)";
		ssl1a << l1;
		ssl1b << l1.ExtraerRango(5,3);
		ssl1c << l1.ExtraerRango(3,5);
		ssl1d << l1;


		//Comparo salidas despues de usar los operadores - y +
		stringstream ssl2, ssl4, ssl4b;
		string expectedl2 = "((2, 2) 2.00 p5 (1, 2) 3.00 p1 (2, 3) 3.00 p4)";
		string expectedl4 = "()";
		string expectedl4b = expectedl2;
		l2 = l3-l1;
		l4 = l1-l3;
		ssl2 << l2;
		ssl4 << l4;

		l4 = l4 + l2;
		ssl4b << l4;

		//EMPEZAMOS A COMPARAR
		if(vaciaVacia == false) cerr << "Lista 1 EsVacia antes de insertar. Esperado True" << endl;
		if(primeraVacia.EsVacia() == false) cerr << "Primer elemento de la Lista 1 antes de insertar. Esperado vacío" << endl;
		if(ultimaVacia.EsVacia() == false) cerr << "Ultimo elemento de la Lista 1 antes de insertar. Esperado vacío" << endl;
		if(vaciaLlena == true) cerr << "Lista 1 EsVacia después de insertar. Esperado False" << endl;
		if(l1Copia.Obtener(primeraLlena) != p2) cerr << "Primer elemento de la Lista 1 después de insertar. Esperado p2 {" << p2 << "} Actual " << l1Copia.Obtener(primeraLlena) << endl;
		if(l1Copia.Obtener(ultimaLlena) != p4) cerr << "Último elemento de la Lista 1 después de insertar. Esperado p4 {" << p4 << "} Actual " << l1Copia.Obtener(ultimaLlena) << endl;
		if(operadorIgual == false) cerr << "El operador == no funciona correctamente";
		if(iguales == false) cerr << "Constructor de copia y/o operador de asignación no funcionan correctamente. O puede que sea el operador ==" << endl;
		if(diferentes == true) cerr << "Constructor de copia y/o operador de asignación no funcionan correctamente. O puede que sea el operador ==" << endl;
		if(longitudL2 != 4) cerr << "Borrar (posicion o elemento) no funciona correctamente. Esperado Longitud 4. Actual " << longitudL2 << endl;
		if(longitudL2Vacia != 0) cerr << "Borrar (posicion o elemento) no funciona correctamente. Esperado Longitud 0. Actual " << longitudL2Vacia << endl;

		//COMPARAMOS SALIDAS
		if(ssl1a.str() != expectedl1a) cerr << "Salida Lista 1 no coincide." << endl << "\tEsperado: " << ssl1a.str() << endl << "\tActual: " << expectedl1a << endl;
		if(ssl1b.str() != expectedl1b) cerr << "Salida Lista 1 extraer rango 5-3 no coincide." << endl << "\tEsperado: " << ssl1b.str() << endl << "\tActual: " << expectedl1b << endl;
		if(ssl1c.str() != expectedl1c) cerr << "Salida Lista 1 extraer rango 3-5 no coincide." << endl << "\tEsperado: " << ssl1c.str() << endl << "\tActual: " << expectedl1c << endl;
		if(ssl1d.str() != expectedl1d) cerr << "Salida Lista 1 despues de extraer rango 3-5 no coincide." << endl << "\tEsperado: " << ssl1d.str() << endl << "\tActual: " << expectedl1d << endl;

		if(ssl2.str() != expectedl2) cerr << "Salida Lista 2 despues de operador - con l3 y l1." << endl << "\tEsperado: " << ssl2.str() << endl << "\tActual: " << expectedl2 << endl;
		if(ssl4.str() != expectedl4) cerr << "Salida Lista 4 despues de operador - con l1 y l3." << endl << "\tEsperado: " << ssl4.str() << endl << "\tActual: " << expectedl4 << endl;
		if(ssl4b.str() != expectedl4b) cerr << "Salida Lista 4 despues de operador + con l4 y l2." << endl << "\tEsperado: "<< ssl4b.str() << endl << "\tActual: " << expectedl4b << endl;
}

int main(int argc, char const* argv[]) {
	if(argc > 1) {
		for(int i = 1; i < argc; i++) {
			string opcion(argv[i]);
			if(opcion == "PORO1") TADPoro1();
			else if(opcion == "PORO2") TADPoro2();
			else if(opcion == "VECTOR1") TADVector1();
			else if(opcion == "VECTOR2") TADVector2();
			else if(opcion == "LISTA") TADLista();
			else if(opcion == "ALL") {
				TADPoro1();
				TADPoro2();
				TADVector1();
				TADVector2();
				TADLista();
			}
			else cerr << "Argumento " << opcion << " no reconocido " << endl;
		}
	}
	else cerr << "Uso: ./tad [<ALL>] o [<PORO1> <PORO2> <VECTOR 1> <VECTOR 2> <LISTA>]" << endl;
	return 0;
}
