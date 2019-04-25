#pragma once

#include <utility>
using namespace std;

class Tortuga
{
public:

	enum EstadoTortuga {vagar, camar, excavar, poner, tapar, camuflar, inactiva};
	typedef pair< int, int > T_posicion;

	// Construye una tortuga con velocidad 1, en estado "inactiva", en posicion (0,0).
	Tortuga();

	// Construye una tortuga con velocidad v, en estado e, en posicion p.
	Tortuga(double v, EstadoTortuga e, T_posicion p);

	~Tortuga();

	// Obtenedores:
	double obtVelocidad();
	T_posicion obtPosicion();
	EstadoTortuga obtEstado();

	// Asignadores:
	void asgVelocidad(double nv);
	void asgPosicion(T_posicion np);
	void asgEstado(EstadoTortuga ne);

	// EFE: avanza *this seg�n su velocidad y evoluciona su estado en el tic que le toque.
	void avanzar(int tic);

private:
	double velocidad;
	T_posicion posicion; // posicion.first == coordenada X, posicion.second = coordenada Y
	EstadoTortuga estado;
};

Tortuga::Tortuga()
{
}

Tortuga::Tortuga(double v, EstadoTortuga e, T_posicion p)
{
}

Tortuga::~Tortuga()
{
}

double Tortuga::obtVelocidad()
{
	return 0.0; // agregue su propio codigo
}

Tortuga::T_posicion Tortuga::obtPosicion()
{
	return pair<int, int>(0,0); // agregue su propio codigo
}

Tortuga::EstadoTortuga Tortuga::obtEstado()
{
	return vagar; // agregue su propio codigo
}

void Tortuga::asgVelocidad(double nv)
{
}

void Tortuga::asgPosicion(T_posicion np)
{
}

void Tortuga::asgEstado(EstadoTortuga ne)
{
}

void Tortuga::avanzar(int tic)
{
}
