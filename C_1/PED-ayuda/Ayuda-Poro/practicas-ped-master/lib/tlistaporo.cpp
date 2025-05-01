#include "../include/tlistaporo.h"

/****************************
 *
 * TLISTANODO
 *
 ****************************/
TListaNodo::TListaNodo() : e() {
	anterior = siguiente = NULL;
}


TListaNodo::TListaNodo(const TListaNodo & n) : e(n.e) {
	anterior = siguiente = NULL;
}

TListaNodo::~TListaNodo() {
	anterior = siguiente = NULL;
}

TListaNodo & TListaNodo::operator =(const TListaNodo & n) {
	if(this != &n) {
		(*this).~TListaNodo();
		e = n.e;
	}
	return *this;
}




/****************************
 *
 * TLISTAPOSICION
 *
 ****************************/
TListaPosicion::TListaPosicion() {
	pos = NULL;
}

TListaPosicion::TListaPosicion(const TListaPosicion & p) {
	pos = p.pos;
}

TListaPosicion::~TListaPosicion() {
	pos = NULL;
}

TListaPosicion & TListaPosicion::operator =(const TListaPosicion & p) {
	if (this != &p) {
		(*this).~TListaPosicion();
		pos = p.pos;
	}
	return *this;
}

bool TListaPosicion::operator ==(const TListaPosicion & p) const {
	return pos == p.pos;
}

TListaPosicion TListaPosicion::Anterior() const {
	TListaPosicion lp;
	if(pos != NULL) lp.pos = pos->anterior;
	else lp.pos = NULL;
	return lp;
}

TListaPosicion TListaPosicion::Siguiente() const {
	TListaPosicion lp;
	if(pos != NULL) lp.pos = pos->siguiente;
	else lp.pos = NULL;
	return lp;
}

bool TListaPosicion::EsVacia() const {
	return pos == NULL;
}



/****************************
 *
 * TLISTAPORO
 *
 ****************************/
TListaPoro::TListaPoro() {
	primero = ultimo = NULL;
}

TListaPoro::TListaPoro(const TListaPoro & l) {
	Copia(l);
}

TListaPoro::~TListaPoro() {
	while(!Primera().EsVacia()) {
		TListaPosicion aux = Primera();
		Borrar(aux);
	}
}

TListaPoro& TListaPoro::operator =(const TListaPoro & l) {
	if(this != &l) {
		(*this).~TListaPoro();
		Copia(l);
	}
	return *this;
}

void TListaPoro::Copia(const TListaPoro & l) {
	primero = ultimo = NULL;
	for(TListaPosicion i = l.Primera(); !i.EsVacia(); i = i.Siguiente())
		Insertar(i.pos->e);
	//primero y ultimo se asignan automaticamente desde insertar
}

bool TListaPoro::operator ==(const TListaPoro & l) const {
	TListaPosicion otroIndice = l.Primera();
	for(TListaPosicion i = Primera(); !i.EsVacia(); i = i.Siguiente()) {
		//Comparamos que para cada posicion los objetos, LOS POROS, sean iguales o no
		if(otroIndice.EsVacia() || i.pos->e != otroIndice.pos->e) return false;
		otroIndice = otroIndice.Siguiente();
	}
	return true; //Llega aqui sólo cuando ha recorrido ambas listas y nunca fueron distintas
}

TListaPoro TListaPoro::operator +(const TListaPoro & l) const {
	TListaPoro nuevaLista;
	for(TListaPosicion i = Primera(); !i.EsVacia(); i = i.Siguiente())
		nuevaLista.Insertar(i.pos->e); //Copio los de mi lista a la nueva lista
	for(TListaPosicion i = l.Primera(); !i.EsVacia(); i = i.Siguiente())
			nuevaLista.Insertar(i.pos->e); //Copio los de la otra lista a la nueva lista (insertar se encarga de ponerlos en su sitio)
	return nuevaLista;
}

TListaPoro TListaPoro::operator -(const TListaPoro & l) const {
	TListaPoro nuevaLista;
	for(TListaPosicion i = Primera(); !i.EsVacia(); i = i.Siguiente())
		if(!l.Buscar(i.pos->e)) nuevaLista.Insertar(i.pos->e); //Si en la lista mía hay un poro que NO está en la otra lista, lo inserto
	return nuevaLista;
}

bool TListaPoro::insertarVacio(const TPoro & p) {
	TListaNodo *nuevoNodo = new TListaNodo();
	nuevoNodo->e = p;
	primero = ultimo = nuevoNodo;
	return true;
}

bool TListaPoro::insertarCabeza(const TPoro & p) {
	TListaNodo *nuevoNodo = new TListaNodo();
	nuevoNodo->e = p;
	primero->anterior = nuevoNodo;
	nuevoNodo->siguiente = primero;
	primero = nuevoNodo;
	return true;
}

bool TListaPoro::insertarCola(const TPoro & p) {
	TListaNodo *nuevoNodo = new TListaNodo();
	nuevoNodo->e = p;
	ultimo->siguiente = nuevoNodo;
	nuevoNodo->anterior = ultimo;
	ultimo = nuevoNodo;
	return true;
}

bool TListaPoro::insertarMedio(const TPoro & p, const TListaPosicion & pos) {
	TListaNodo *nuevoNodo = new TListaNodo();
	nuevoNodo->e = p;
	nuevoNodo->siguiente = pos.pos;
	nuevoNodo->anterior = pos.pos->anterior;
	pos.pos->anterior->siguiente = nuevoNodo;
	pos.pos->anterior = nuevoNodo;
	return true;
}

bool TListaPoro::Insertar(const TPoro & p) {
	if(EsVacia()) return insertarVacio(p);
	else {
		TListaPosicion indice = Primera();
		double volumenNuevo = p.Volumen();
		while(!indice.EsVacia()) {
			double volumenIndice = indice.pos->e.Volumen();
			if(indice.pos->e == p) return false;
			else if(volumenNuevo >= volumenIndice) indice = indice.Siguiente();
			else if(indice == Primera()) return insertarCabeza(p);
			else return insertarMedio(p, indice);
		}
		return insertarCola(p);
	}
}

bool TListaPoro::Borrar(TListaPosicion & pos) {
	bool encontrado = false;
	if(!EsVacia()) {
		if(pos == Primera()) {
			if(primero == ultimo) primero = ultimo = NULL; //Solo ocurre si en la lista habia un solo elemento
			else {
				primero = primero->siguiente; //Si quiero borrar la primera, ahora la primera será la segunda
				primero->anterior = NULL;
			}
			encontrado = true;
		}
		else if(pos == Ultima()) {
			ultimo = ultimo->anterior; //Si quiero borrar la ultima, ahora la ultima sera la penultima
			ultimo->siguiente = NULL;
			encontrado = true;
		}
		else {
			for(TListaPosicion i = Primera(); !i.EsVacia(); i = i.Siguiente()) {
				if(pos == i) { //estoy en la posicion que quiero que se borre
					//Empalmo los punteros: no quiero que ninguno me apunte a mi
					i.pos->siguiente->anterior = i.pos->anterior;
					i.pos->anterior->siguiente = i.pos->siguiente;
					encontrado = true;
				}
			}
		}
		if(encontrado) {
			//En cualquier caso, si he encontrado la posicion que quiero borrar, la borro
			delete pos.pos;
			pos.pos = NULL;
		}
	}
	return encontrado;
}

bool TListaPoro::Borrar(const TPoro & p) {
	//Le busco la posicion en la que esta el poro que me pasan y lo borro desde su posicion
	for(TListaPosicion i = Primera(); !i.EsVacia(); i = i.Siguiente()) {
		if(i.pos->e == p) {
			Borrar(i);
			return true;
		}
	}
	return false; //Si no lo ha encontrado, no lo ha podido borrar
}

TPoro TListaPoro::Obtener(const TListaPosicion & pos) const {
	for(TListaPosicion i = Primera(); !i.EsVacia(); i = i.Siguiente())
		if(i == pos) return i.pos->e;
	return TPoro(); //Si no lo ha encontrado, devuelve uno vacio
}

bool TListaPoro::Buscar(const TPoro & p) const {
	for(TListaPosicion i = Primera(); !i.EsVacia(); i = i.Siguiente())
			if(i.pos->e == p) return true;
	return false; //Si no lo ha encontrado, falso
}

int TListaPoro::Longitud() const {
	int lon = 0;
	for(TListaPosicion i = Primera(); !i.EsVacia(); i = i.Siguiente()) lon++;
	return lon;
}

TListaPosicion TListaPoro::Primera() const {
	TListaPosicion indice;
	indice.pos = primero;
	return indice;
}

TListaPosicion TListaPoro::Ultima() const {
	TListaPosicion indice;
	indice.pos = ultimo;
	return indice;
}

bool TListaPoro::EsVacia() const {
	return primero == NULL && ultimo == NULL;
}

TListaPoro TListaPoro::ExtraerRango(int min, int max) {
	TListaPoro nuevaLista;
	int numIndice, longitud = Longitud();

	//Condicion necesaria para que saque algun rango
	if(min <= max) {
		//Arreglamos los rangos por si aun cumpliendo la condicion basica algunos estan mal
		if(min <= 0) min = 1;
		if(max > longitud) max = longitud;

		//Inserto los que estan dentro en la nueva lista y los borro de la mia
		numIndice = 1;
		for(TListaPosicion i = Primera(); !i.EsVacia();) {
			if(numIndice >= min && numIndice <= max) {
				nuevaLista.Insertar(Obtener(i));
				TListaPosicion aux = i;
				i = i.Siguiente();
				Borrar(aux);
			}
			else i = i.Siguiente();
			numIndice++; //Solo incremento
		}
	}

	return nuevaLista;
}

ostream & operator<<(ostream & os, const TListaPoro & l) {
	os << "(";
	for(TListaPosicion i = l.Primera(); !i.EsVacia(); i = i.Siguiente()) {
		os << l.Obtener(i);
		if(!(i == l.Ultima())) os << " ";
	}
	os << ")";
	return os;
}
