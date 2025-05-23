#ifndef TLISTAPORO_H_
#define TLISTAPORO_H_

#include "tporo.h"

class TListaNodo {
	friend class TListaPosicion;
	friend class TListaPoro;
private:
	TPoro e;
	TListaNodo *anterior;
	TListaNodo *siguiente;
public:
	TListaNodo();
	TListaNodo(const TListaNodo & n);
	~TListaNodo();
	TListaNodo & operator =(const TListaNodo & n);
};

class TListaPosicion {
	friend class TListaPoro;
private:
	TListaNodo* pos;
public:
	//Forma canónica
	TListaPosicion();
	TListaPosicion(const TListaPosicion & p);
	~TListaPosicion();
	TListaPosicion & operator =(const TListaPosicion & p);
	//void Copia(const TListaPosicion & p);
	
	//metodos
	bool operator ==(const TListaPosicion & p) const;
	TListaPosicion Anterior() const;
	TListaPosicion Siguiente() const;
	bool EsVacia() const;
};

class TListaPoro {
	//funciones amigas
	friend ostream & operator <<(ostream & os, const TListaPoro & l);
private:
	TListaNodo* primero;
	TListaNodo* ultimo;

	bool insertarVacio(const TPoro & p);
	bool insertarCabeza(const TPoro & p);
	bool insertarCola(const TPoro & p);
	bool insertarMedio(const TPoro & p, const TListaPosicion & pos);
public:
	//Forma canónica
	TListaPoro();
	TListaPoro(const TListaPoro & l);
	~TListaPoro();
	TListaPoro & operator =(const TListaPoro & l);
	void Copia(const TListaPoro & l);

	//Metodos
	bool operator ==(const TListaPoro & l) const;
	TListaPoro operator +(const TListaPoro & l) const;
	TListaPoro operator -(const TListaPoro & l) const;
	bool EsVacia() const;
	bool Insertar(const TPoro & p);
	bool Borrar(const TPoro & p);
	bool Borrar(TListaPosicion & pos);
	TPoro Obtener(const TListaPosicion & pos) const;
	bool Buscar(const TPoro & p) const;
	int Longitud() const;
	TListaPosicion Primera() const;
	TListaPosicion Ultima() const;
	TListaPoro ExtraerRango (int min, int max);

	void mezclar(const TListaPoro & l);
};

#endif /* TLISTAPORO_H_ */
