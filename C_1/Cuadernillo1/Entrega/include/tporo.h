#ifndef TPORO_H_
#define TPORO_H_

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
using namespace std;

class TPoro {
//Parte privada	
private:
	int x, y;
	double volumen;
	char* color;

// Forma canónica	
public:
	TPoro();
	TPoro(int x, int y, double volumen);
	TPoro(int x, int y, double volumen, const char* color);
	TPoro(const TPoro & p);
	~TPoro();
	TPoro & operator=(const TPoro & p);
	
	void Copia(const TPoro & p);

	bool operator==(const TPoro & p) const;
	bool operator!=(const TPoro & p) const;

	void Posicion(int x, int y);
	void Volumen(double v);
	void Color(const char* c);

	int PosicionX() const;
	int PosicionY() const;
	double Volumen() const;
	char* Color() const;
	bool EsVacio() const;
	bool cadenasIguales(const char* c1, const char* c2) const;


	// Funciones amigas
	friend ostream & operator<<(ostream & os, const TPoro & p);
};

#endif /* TPORO_H_ */

