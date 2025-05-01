#include "../include/tvectorporo.h"

TVectorPoro::TVectorPoro() : error() {
	datos = NULL;
	dimension = 0;
}

TVectorPoro::TVectorPoro(int dimension) : error() {
	datos = NULL;
	if(dimension <= 0) {
		this->dimension = 0;
	}
	else {
		this->dimension = dimension;
		datos = new TPoro[dimension];
	}
}

TVectorPoro::TVectorPoro(const TVectorPoro & v) {
	datos = NULL;
	Copia(v);
}

TVectorPoro::~TVectorPoro() {
	if(datos != NULL) {
		delete[] datos;
		datos = NULL;
	}
	dimension = 0;
}

TVectorPoro & TVectorPoro::operator =(const TVectorPoro & v) {
	if(this != &v) {
		(*this).~TVectorPoro();
		Copia(v);
	}
	return *this;
}

void TVectorPoro::Copia(const TVectorPoro & v) {
	dimension = v.dimension;
	if(datos != NULL) delete datos; //No es estrictamente necesario
	datos = new TPoro[dimension];
	for(int i = 0; i < dimension; i++) datos[i] = v.datos[i];
	error = v.error;
}

bool TVectorPoro::operator ==(const TVectorPoro & v) const {
	if(dimension != v.dimension) return false;
	else
		for(int i = 0; i < dimension; i++)
			if(datos[i] != v.datos[i]) return false;
	return true; //Legará aquí sólo cuando las dimensiones coincidan y haya recorrido el bucle teniendo todos sus elementos iguales
}

bool TVectorPoro::operator !=(const TVectorPoro & v) const {
	if(dimension != v.dimension) return true;
	else
		for(int i = 0; i < dimension; i++)
			if(datos[i] != v.datos[i]) return true;
	return false; //Legará aquí sólo cuando las dimensiones coincidan y haya recorrido el bucle teniendo todos sus elementos iguales
}

TPoro & TVectorPoro::operator [](int pos) {
	if(pos >= 1 && pos <= dimension) return datos[pos-1];
	else return error;
}

TPoro TVectorPoro::operator [](int pos) const {
	if(pos >= 1 && pos <= dimension) return datos[pos-1];
	else return error;
}

int TVectorPoro::Longitud() const {
	return dimension;
}

int TVectorPoro::Cantidad() const {
	int cantidad = 0;
	for(int i = 0; i < dimension; i++)
		if(!datos[i].EsVacio()) cantidad++;
	return cantidad;
}

bool TVectorPoro::Redimensionar(int tam) {
	if(tam <= 0 || tam == dimension) return false;
	TPoro* nuevo = new TPoro[tam];
	if(tam < dimension) dimension = tam; //Si vamos a hacerlo mas pequeño, cambiamos la dimension ANTES
	for(int i = 0; i < dimension; i++) nuevo[i] = datos[i]; //Copiamos los antiguos. Caso reduccion -> hasta que nos quepa en la nueva dimension
	dimension = tam; //En cualquier caso, reduccion o ampliacion, cambiamos el tamaño
	delete[] datos; //Eliminamos lo antiguo
	datos = nuevo; //Asignamos lo nuevo
	return true; //Llegará aquí a no ser que haga el primer if
}

TPoro* TVectorPoro::getDatosPtr() {
	return datos;
}

ostream & operator<<(ostream & os, const TVectorPoro & v) {
	os << "[";
	for(int i = 1; i <= v.dimension; i++) {
		os << i << " " << v[i];
		if(i != v.dimension) os << " ";
	}
	os << "]";
	return os;
}
