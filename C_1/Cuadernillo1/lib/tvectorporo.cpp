#include "../include/tvectorporo.h"

TVectorPoro::TVectorPoro() : error() {
	// Inicializo mi vector vacío
	datos = NULL;
	dimension = 0;
}

TVectorPoro::TVectorPoro(int dimension) : error() {
	// Inicializo datos a NULL por seguridad
	datos = NULL;
	if(dimension <= 0) {
		this->dimension = 0;
	}
	else {
		this->dimension = dimension;
		// Reservo memoria para mi array de poros
		datos = new TPoro[dimension];
	}
}

TVectorPoro::TVectorPoro(const TVectorPoro & v) {
	// Inicializo datos a NULL antes de copiar
	datos = NULL;
	Copia(v);
}

TVectorPoro::~TVectorPoro() {
	if(datos != NULL) {
		// Libero la memoria que había reservado
		delete[] datos;
		datos = NULL;
	}
	dimension = 0;
}

TVectorPoro & TVectorPoro::operator =(const TVectorPoro & v) {
	if(this != &v) {
		// Me aseguro de liberar la memoria antes de copiar
		this->~TVectorPoro();
		Copia(v);
	}
	return *this;
}

void TVectorPoro::Copia(const TVectorPoro & v) {
	dimension = v.dimension;
	// Me aseguro de liberar la memoria si ya tenía datos
	if(datos != NULL) {
		delete[] datos;  // Corrijo: usar delete[] para arrays
		datos = NULL;
	}
	if(dimension > 0) {
		datos = new TPoro[dimension];
		// Copio cada elemento del vector
		for(int i = 0; i < dimension; i++) 
			datos[i] = v.datos[i];
	}
	error = v.error;
}

bool TVectorPoro::operator ==(const TVectorPoro & v) const {
	if(dimension != v.dimension) 
		return false;
	// Comparo elemento a elemento
	for(int i = 0; i < dimension; i++)
		if(datos[i] != v.datos[i]) 
			return false;
	return true;
}

bool TVectorPoro::operator !=(const TVectorPoro & v) const {
	return !(*this == v);  // Mejoro: reutilizo el operador ==
}

TPoro & TVectorPoro::operator [](int pos) {
	// Verifico que la posición sea válida (1-based indexing)
	if(pos >= 1 && pos <= dimension) 
		return datos[pos-1];
	return error;
}

TPoro TVectorPoro::operator [](int pos) const {
	// Version const del operador []
	if(pos >= 1 && pos <= dimension) 
		return datos[pos-1];
	return error;
}

int TVectorPoro::Longitud() const {
	return dimension;
}

int TVectorPoro::Cantidad() const {
	int cantidad = 0;
	// Cuento los poros no vacíos
	for(int i = 0; i < dimension; i++)
		if(!datos[i].EsVacio()) 
			cantidad++;
	return cantidad;
}
//--
bool TVectorPoro::Redimensionar(int tam) {
	// Si el tamaño es inválido o igual al actual, no hago nada
	if(tam <= 0 || tam == dimension) 
		return false;

	// Reservo nuevo espacio
	TPoro* nuevo = new TPoro[tam];
	
	// Si reduzco el tamaño, ajusto la dimensión antes de copiar
	int copiarHasta = (tam < dimension) ? tam : dimension;
	
	// Copio los elementos al nuevo array
	for(int i = 0; i < copiarHasta; i++) 
		nuevo[i] = datos[i];
	
	// Libero la memoria antigua y actualizo mis atributos
	delete[] datos;
	datos = nuevo;
	dimension = tam;
	
	return true;
}

TPoro* TVectorPoro::getDatosPtr() {
	return datos;
}

ostream & operator<<(ostream & os, const TVectorPoro & v) {
	os << "[";
	// Itero por todas las posiciones imprimiendo cada elemento
	for(int i = 1; i <= v.dimension; i++) {
		os << i << " " << v[i];
		if(i != v.dimension) 
			os << " ";
	}
	os << "]";
	return os;
}
