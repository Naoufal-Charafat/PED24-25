#ifndef TVECTORPORO_H_
#define TVECTORPORO_H_

#include <iostream>
#include "tporo.h"
using namespace std;

class TVectorPoro {
	
private:
	int dimension;
	TPoro* datos;
	TPoro error;
public:
	//forma canónica
	TVectorPoro();
	TVectorPoro(int dimension);
	TVectorPoro(const TVectorPoro & v);
	~TVectorPoro();
	TVectorPoro & operator =(const TVectorPoro & v);

	void Copia(const TVectorPoro & v);

	//Metodos
	bool operator ==(const TVectorPoro & v) const;
	bool operator !=(const TVectorPoro & v) const;
	TPoro & operator[](int pos);
	TPoro operator[](int pos) const;
	int Longitud() const;
	int Cantidad() const;
	bool Redimensionar(int tam);

	//Metodos auxiliares
	TPoro* getDatosPtr();

	//Funciones amigas
	friend ostream & operator<<(ostream & os, const TVectorPoro & v);
};

#endif /* TVECTORPORO_H_ */
