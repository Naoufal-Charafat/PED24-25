#include "../include/tporo.h"

TPoro::TPoro()
{
	color = NULL;
	x = y = volumen = 0;
}

TPoro::TPoro(int x, int y, double volumen)
{
	color = NULL;
	Posicion(x, y);
	Volumen(volumen);
}

TPoro::TPoro(int x, int y, double volumen, const  char *color)
{
	this->color = NULL;
	Posicion(x, y);
	Volumen(volumen);
	Color(color);
}

TPoro::TPoro(const TPoro &p)
{
	color = NULL;
	Copia(p);
}

TPoro::~TPoro()
{
	x = y = volumen = 0;
	if (color != NULL)
	{
		delete[] color;
		color = NULL;
	}
}

TPoro &TPoro::operator=(const TPoro &p)
{
	if (this != &p)
	{
		(*this).~TPoro();
		Copia(p);
	}
	return *this;
}

void TPoro::Copia(const TPoro &p)
{
	Posicion(p.x, p.y);
	Volumen(p.volumen);
	Color(p.color);
}

bool TPoro::operator==(const TPoro &p) const
{
	// Primero compruebo la posición y el volumen ya que son comparaciones rápidas
	if (x != p.x || y != p.y || volumen != p.volumen)
		return false;
	
	// Luego compruebo los colores solo si llegamos hasta aquí
	return cadenasIguales(color, p.color);
}

bool TPoro::operator!=(const TPoro &p) const
{
	return !(*this == p);
}

void TPoro::Posicion(int x, int y)
{ 
	this->x = x;
	this->y = y;
}

void TPoro::Volumen(double v)
{
	volumen = v;
}

void TPoro::Color(const char *c)
{
	
	delete[] color;
	color = NULL;

	if (c != NULL)
	{
		size_t len = strlen(c);
		color = new char[len + 1];
		
		
		for (size_t i = 0; i < len; i++)
			color[i] = tolower(c[i]);
		color[len] = '\0';
	}
}

int TPoro::PosicionX() const
{
	return x;
}

int TPoro::PosicionY() const
{
	return y;
}

double TPoro::Volumen() const
{
	return volumen;
}

char *TPoro::Color() const
{
	return color;
}

bool TPoro::EsVacio() const
{ 
	bool defaultPosition = (x == 0 && y == 0);
	bool defaultVolume = (volumen == 0);
	bool defaultColor = (color == NULL);
	
	return defaultPosition && defaultVolume && defaultColor;
}

ostream &operator<<(ostream &os, const TPoro &p)
{
	if (p.EsVacio())
	{
		return os << "()";
	} 

	os.setf(ios::fixed);
	os.precision(2);
	os << "(" << p.PosicionX() << ", " << p.PosicionY() << ") "
	   << p.Volumen() << " "
	   << (p.Color() ? p.Color() : "-");

	return os;
}

bool TPoro::cadenasIguales(const char *c1, const char *c2) const
{	
	if (c1 == NULL && c2 == NULL)
		return true;
	
	if (c1 == NULL || c2 == NULL)
		return false;
	
	return strcmp(c1, c2) == 0;
}
