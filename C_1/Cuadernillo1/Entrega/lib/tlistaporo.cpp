#include "../include/tlistaporo.h"

/****************************
 *
 * TLISTANODO
 *
 ****************************/
// En estas funciones implemento los métodos básicos de la clase TListaNodo
// que representa un nodo en mi lista doblemente enlazada

// Constructor por defecto: inicializo con un TPoro vacío y punteros a NULL
TListaNodo::TListaNodo() : e() {
	anterior = NULL;
	siguiente = NULL;
}

// Constructor de copia: copio el TPoro y pongo los punteros a NULL
TListaNodo::TListaNodo(const TListaNodo & n) : e(n.e) {
	anterior = NULL;
	siguiente = NULL;
}

// Destructor: limpio los punteros
TListaNodo::~TListaNodo() {
	anterior = NULL;
	siguiente = NULL;
}

// Operador asignación: compruebo autoasignación, limpio y copio el TPoro
TListaNodo & TListaNodo::operator =(const TListaNodo & n) {
	if(this != &n) {
		e = n.e;  // Solo necesito copiar el TPoro, los punteros se manejan externamente
	}
	return *this;
}




/****************************
 *
 * TLISTAPOSICION
 *
 ****************************/
// Implemento los métodos de la clase TListaPosicion que representa una posición en mi lista
// enlazada de poros

TListaPosicion::TListaPosicion() {
	// Inicio mi posición como vacía
	pos = NULL;
}

TListaPosicion::TListaPosicion(const TListaPosicion & p) {
	// Copio directamente el puntero ya que solo necesito la referencia
	pos = p.pos;
}

TListaPosicion::~TListaPosicion() {
	// Limpio mi puntero
	pos = NULL;
}

TListaPosicion & TListaPosicion::operator =(const TListaPosicion & p) {
	if (this != &p) {
		pos = p.pos;  
	}
	return *this;
}

bool TListaPosicion::operator ==(const TListaPosicion & p) const {
	// Comparo si las posiciones apuntan al mismo nodo
	return pos == p.pos;
}

TListaPosicion TListaPosicion::Anterior() const {
	// Devuelvo una nueva posición apuntando al nodo anterior
	TListaPosicion anterior;
	anterior.pos = (pos != NULL) ? pos->anterior : NULL;
	return anterior;
}

TListaPosicion TListaPosicion::Siguiente() const {
	// Devuelvo una nueva posición apuntando al nodo siguiente
	TListaPosicion siguiente;
	siguiente.pos = (pos != NULL) ? pos->siguiente : NULL;
	return siguiente;
}

bool TListaPosicion::EsVacia() const {
	// Compruebo si mi posición es válida
	return pos == NULL;
}



/****************************
 *
 * TLISTAPORO
 *
 ****************************/
TListaPoro::TListaPoro() {
	// Inicializo mi lista vacía
	primero = ultimo = NULL;
}

TListaPoro::TListaPoro(const TListaPoro & l) {
	// Uso mi método Copia para duplicar la lista
	Copia(l);
}

TListaPoro::~TListaPoro() {
	// Limpio mi lista borrando desde el principio
	while(!Primera().EsVacia()) {
		TListaPosicion aux = Primera();
		Borrar(aux);
	}
}

TListaPoro& TListaPoro::operator =(const TListaPoro & l) {
	if(this != &l) {
		// Evito autoasignación, limpio mi contenido y copio el nuevo
		this->~TListaPoro();
		Copia(l);
	}
	return *this;
}

void TListaPoro::Copia(const TListaPoro & l) {
	// Inicio con lista vacía
	primero = ultimo = NULL;
	// Copio cada poro en orden, manteniendo la estructura ordenada
	for(TListaPosicion i = l.Primera(); !i.EsVacia(); i = i.Siguiente()) {
		Insertar(i.pos->e);
	}
}

bool TListaPoro::operator ==(const TListaPoro & l) const {
	TListaPosicion otroIndice = l.Primera();
	// Comparo elemento a elemento
	for(TListaPosicion i = Primera(); !i.EsVacia(); i = i.Siguiente()) {
		if(otroIndice.EsVacia() || i.pos->e != otroIndice.pos->e) {
			return false;
		}
		otroIndice = otroIndice.Siguiente();
	}
	// Si llego aquí, las listas son iguales
	return otroIndice.EsVacia();
}

TListaPoro TListaPoro::operator +(const TListaPoro & l) const {
	TListaPoro nuevaLista;
	// Primero añado mis elementos usando mi método Insertar que mantiene el orden
	for(TListaPosicion i = Primera(); !i.EsVacia(); i = i.Siguiente()) {
		nuevaLista.Insertar(i.pos->e);
	}
	// Luego añado los elementos de la otra lista, también ordenados
	for(TListaPosicion i = l.Primera(); !i.EsVacia(); i = i.Siguiente()) {
		nuevaLista.Insertar(i.pos->e); // Mi método Insertar evita duplicados automáticamente
	}
	return nuevaLista;
}

TListaPoro TListaPoro::operator -(const TListaPoro & l) const {
	TListaPoro nuevaLista;
	// Recorro mi lista y solo añado los que no estén en la otra
	for(TListaPosicion i = Primera(); !i.EsVacia(); i = i.Siguiente()) {
		if(!l.Buscar(i.pos->e)) {
			nuevaLista.Insertar(i.pos->e);
		}
	}
	return nuevaLista;
}

bool TListaPoro::insertarVacio(const TPoro & p) {
	// Creo mi primer nodo cuando mi lista está vacía
	TListaNodo *nuevoNodo = new TListaNodo();
	if(!nuevoNodo) return false; // Verifico si la asignación de memoria fue exitosa
	
	nuevoNodo->e = p;
	primero = ultimo = nuevoNodo;
	return true;
}

bool TListaPoro::insertarCabeza(const TPoro & p) {
	// Creo un nuevo nodo y verifico que se haya creado correctamente
	TListaNodo *nuevoNodo = new TListaNodo();
	if (!nuevoNodo) return false;
	
	nuevoNodo->e = p;
	primero->anterior = nuevoNodo;
	nuevoNodo->siguiente = primero;
	primero = nuevoNodo;
	return true;
}

bool TListaPoro::insertarCola(const TPoro & p) {
	// Creo un nuevo nodo y verifico que se haya creado correctamente
	TListaNodo *nuevoNodo = new TListaNodo();
	if (!nuevoNodo) return false;
	
	nuevoNodo->e = p;
	ultimo->siguiente = nuevoNodo;
	nuevoNodo->anterior = ultimo;
	ultimo = nuevoNodo;
	return true;
}

bool TListaPoro::insertarMedio(const TPoro & p, const TListaPosicion & pos) {
	// Creo un nuevo nodo y verifico que se haya creado correctamente
	TListaNodo *nuevoNodo = new TListaNodo();
	if (!nuevoNodo) return false;
	
	nuevoNodo->e = p;
	nuevoNodo->siguiente = pos.pos;
	nuevoNodo->anterior = pos.pos->anterior;
	pos.pos->anterior->siguiente = nuevoNodo;
	pos.pos->anterior = nuevoNodo;
	return true;
}

bool TListaPoro::Insertar(const TPoro & p) {
	// Si mi lista está vacía, uso mi método específico para ese caso
	if(EsVacia()) 
		return insertarVacio(p);

	TListaPosicion indice = Primera();
	double volumenNuevo = p.Volumen();

	// Recorro mi lista buscando la posición correcta según el volumen
	while(!indice.EsVacia()) {
		// Si encuentro un poro igual, no lo inserto
		if(indice.pos->e == p) 
			return false;
		
		double volumenIndice = indice.pos->e.Volumen();
		
		// Si el volumen nuevo es menor, inserto antes de la posición actual
		if(volumenNuevo < volumenIndice) {
			return (indice == Primera()) ? 
				   insertarCabeza(p) : 
				   insertarMedio(p, indice);
		}
		
		indice = indice.Siguiente();
	}
	
	// Si llegué al final, inserto en la cola
	return insertarCola(p);
}

bool TListaPoro::Borrar(TListaPosicion & pos) {
	// Si mi lista está vacía no puedo borrar nada
	if(EsVacia()) return false;

	bool borrado = true;

	// Si quiero borrar la primera posición
	if(pos == Primera()) {
		if(primero == ultimo) {
			// Si solo tengo un elemento, limpio mi lista
			primero = ultimo = NULL;
		} else {
			// Hago que mi primera sea la siguiente y arreglo enlaces
			primero = primero->siguiente;
			primero->anterior = NULL;
		}
	}
	// Si quiero borrar la última posición
	else if(pos == Ultima()) {
		// Hago que mi última sea la anterior y arreglo enlaces
		ultimo = ultimo->anterior;
		ultimo->siguiente = NULL;
	}
	// Si quiero borrar una posición intermedia
	else {
		// Busco la posición que quiero borrar
		TListaPosicion i;
		bool encontrado = false;
		
		for(i = Primera(); !i.EsVacia() && !encontrado; i = i.Siguiente()) {
			if(pos == i) {
				// Empalmo mis enlaces saltándome el nodo a borrar
				i.pos->anterior->siguiente = i.pos->siguiente;
				i.pos->siguiente->anterior = i.pos->anterior;
				encontrado = true;
			}
		}
		
		if(!encontrado) return false;
	}

	// Libero memoria y pongo la posición a NULL
	delete pos.pos;
	pos.pos = NULL;
	
	return borrado;
}

bool TListaPoro::Borrar(const TPoro & p) {
	// Busco mi poro en la lista y si lo encuentro lo borro usando su posición
	for(TListaPosicion i = Primera(); !i.EsVacia(); i = i.Siguiente()) {
		if(i.pos->e == p) {
			return Borrar(i);
		}
	}
	return false; // No encontré mi poro para borrar
}

TPoro TListaPoro::Obtener(const TListaPosicion & pos) const {
	// Si me dan una posición válida devuelvo su contenido, si no, devuelvo un TPoro vacío
	if (!pos.EsVacia()) {
		return pos.pos->e;
	}
	return TPoro();
}

bool TListaPoro::Buscar(const TPoro & p) const {
	// Recorro mi lista buscando un poro igual al que me pasan
	for(TListaPosicion i = Primera(); !i.EsVacia(); i = i.Siguiente()) {
		if(i.pos->e == p) {
			return true;
		}
	}
	return false;
}

int TListaPoro::Longitud() const {
	// Cuento cuántos elementos tengo en mi lista
	int longitud = 0;
	for(TListaPosicion i = Primera(); !i.EsVacia(); i = i.Siguiente()) {
		longitud++;
	}
	return longitud;
}

TListaPosicion TListaPoro::Primera() const {
	// Devuelvo una posición que apunta a mi primer elemento
	TListaPosicion pos;
	pos.pos = primero;
	return pos;
}

TListaPosicion TListaPoro::Ultima() const {
	// Devuelvo una posición que apunta a mi último elemento
	TListaPosicion pos;
	pos.pos = ultimo;
	return pos;
}

bool TListaPoro::EsVacia() const {
	// Verifico si mi lista está vacía comprobando mis punteros
	return primero == NULL;
}
//--
TListaPoro TListaPoro::ExtraerRango(int min, int max) {
	TListaPoro nuevaLista;
	int posActual = 1;
	
	// Solo proceso si el rango es válido
	if (min <= max) {
		// Ajusto mis límites para que estén dentro de rangos válidos
		min = (min <= 0) ? 1 : min;
		max = (max > Longitud()) ? Longitud() : max;

		// Recorro mi lista extrayendo los elementos del rango
		TListaPosicion i = Primera();
		while (!i.EsVacia()) {
			if (posActual >= min && posActual <= max) {
				// Guardo el elemento en mi nueva lista y lo borro de la original
				nuevaLista.Insertar(i.pos->e);
				TListaPosicion auxPos = i;
				i = i.Siguiente();
				Borrar(auxPos);
			} else {
				i = i.Siguiente();
			}
			posActual++;
		}
	}
	return nuevaLista;
}

ostream & operator<<(ostream & os, const TListaPoro & l) {
	// Imprimo mi lista en formato (elemento1 elemento2 ... elementoN)
	os << "(";
	TListaPosicion pos = l.Primera();
	
	while (!pos.EsVacia()) {
		os << l.Obtener(pos);
		if (!(pos == l.Ultima())) {
			os << " ";
		}
		pos = pos.Siguiente();
	}
	os << ")";
	return os;
}
