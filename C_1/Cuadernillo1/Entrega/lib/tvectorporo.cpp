#include "../include/tvectorporo.h"

TVectorPoro::TVectorPoro() : error() {
	// Inicializo mi vector vacío
	datos = NULL;
	dimension = 0;
}

// Constructor con tamaño
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

// Constructor de copia
TVectorPoro::TVectorPoro(const TVectorPoro & v) {
	// Inicializo datos a NULL antes de copiar
	datos = NULL;
	Copia(v);
}

// Destructor
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

// Método privado para copiar el contenido de otro vector
// Este método se usa tanto en el constructor de copia como en el operador =
// y en el constructor por defecto
// para evitar duplicación de código
// y asegurar que la memoria se maneje correctamente
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

// Método para comparar dos vectores
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

// Método para acceder a un elemento del vector
// Permite acceder a un elemento por su posición (1-based indexing)
// Devuelve una referencia al elemento en la posición pos
// Si la posición es inválida, devuelve un objeto de error
// que se inicializa en el constructor por defecto
TPoro & TVectorPoro::operator [](int pos) {
	// Verifico que la posición sea válida (1-based indexing)
	if(pos >= 1 && pos <= dimension) 
		return datos[pos-1];
	return error;
}

// Método para acceder a un elemento del vector (versión const)
// Permite acceder a un elemento por su posición (1-based indexing)
// Devuelve una copia del elemento en la posición pos
// Si la posición es inválida, devuelve un objeto de error
// que se inicializa en el constructor por defecto
TPoro TVectorPoro::operator [](int pos) const {
	// Version const del operador []
	if(pos >= 1 && pos <= dimension) 
		return datos[pos-1];
	return error;
}

// Método para obtener la longitud del vector
int TVectorPoro::Longitud() const {
	return dimension;
}

// Método para contar la cantidad de poros no vacíos en el vector
// Recorre el vector y cuenta los elementos que no son vacíos
// Un poro se considera vacío si su posición es (0, 0), su volumen es 0
// y su color es NULL
// Devuelve la cantidad de poros no vacíos
// Si el vector está vacío, devuelve 0
int TVectorPoro::Cantidad() const {
	int cantidad = 0;
	// Cuento los poros no vacíos
	for(int i = 0; i < dimension; i++)
		if(!datos[i].EsVacio()) 
			cantidad++;
	return cantidad;
}

// Método para redimensionar el vector
// Cambia el tamaño del vector a un nuevo tamaño especificado por tam
// Si el nuevo tamaño es menor que el actual, se pierden los elementos
// que exceden el nuevo tamaño
// Si el nuevo tamaño es mayor que el actual, se reserva nuevo espacio
// y se copian los elementos existentes
// Devuelve true si la redimensión fue exitosa, false en caso contrario
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

// Método para obtener un puntero a los datos del vector
// Devuelve un puntero al array de TPoro
// Esto puede ser útil para acceder directamente a los datos
// sin necesidad de usar el operador []
// Permite manipular los datos directamente
// y puede ser útil en ciertas situaciones
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
