#include "../include/tporo.h"

TPoro::TPoro() {
	color = NULL;
	x = y = volumen = 0;
}

TPoro::TPoro(int x, int y, double volumen) {
	color = NULL;
	Posicion(x, y);
	Volumen(volumen);
}

TPoro::TPoro(int x, int y, double volumen,char* color) {
	this->color = NULL;
	Posicion(x, y);
	Volumen(volumen);
	Color(color);
}

TPoro::TPoro(const TPoro & p) {
	color = NULL;
	Copia(p);
}

TPoro::~TPoro() {
	x = y = volumen = 0;
	if(color != NULL) {
		delete[] color;
		color = NULL;
	}
}

TPoro & TPoro::operator =(const TPoro & p) {
	if(this != &p) {
		(*this).~TPoro();
		Copia(p);
	}
	return *this;
}

void TPoro::Copia(const TPoro & p) {
	Posicion(p.x, p.y);
	Volumen(p.volumen);
	Color(p.color);
}

bool TPoro::operator ==(const TPoro & p) const {
	return x == p.x && y == p.y && volumen == p.volumen && cadenasIguales(color, p.color);
}

bool TPoro::operator !=(const TPoro & p) const {
	return !(x == p.x && y == p.y && volumen == p.volumen && cadenasIguales(color, p.color));
}


void TPoro::Posicion(int x, int y) {
	this->x = x;
	this->y = y;
}

void TPoro::Volumen(double v) {
	volumen = v;
}

void TPoro::Color(char* c) {
	if(color != NULL) {
		delete[] color;
		color = NULL;
	}
	if(c != NULL) {
		color = new char[strlen(c)+1];
		int i;
		for(i = 0; c[i]; i++) color[i] = tolower(c[i]);
		color[i] = '\0';
	}
}

int TPoro::PosicionX() const {
	return x;
}

int TPoro::PosicionY() const {
	return y;
}

double TPoro::Volumen() const {
	return volumen;
}

char* TPoro::Color() const {
	return color;
}

bool TPoro::EsVacio() const {
	return x == 0 && y == 0 && volumen == 0 && color == NULL;
}

ostream & operator<<(ostream & os, const TPoro & p) {
	if(p.EsVacio()) os << "()";
	else {
		os.setf(ios::fixed);
		os.precision(2);
		os << "(" << p.x << ", " << p.y << ") " << p.volumen << " ";
		if(p.color != NULL)	 os << p.color;
		else os << "-";
	}
	return os;
}

bool TPoro::cadenasIguales(const char* c1, const char* c2) const {
	return (c1 == NULL && c2 == NULL) || (c1 != NULL && c2 != NULL && strcmp(c1,c2) == 0);
}
