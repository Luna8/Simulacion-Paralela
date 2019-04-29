#pragma once

#include <utility>
using namespace std;

class Contador
{
public:
	
	enum EstadoContador { contar, esperar };
	typedef pair< int, int > T_posicion;

	// Construye un contador con velocidad 1.0, en posicion (0,0), en estado esperar.
	Contador();

	// Construye un contador con velocidad v, en posicion p, en estado p. 
	Contador(double v, EstadoContador e, T_posicion p);

	~Contador();

	// Obtenedores:
	double obtVelocidad();
	T_posicion obtPosicion();
	EstadoContador obtEstado();

	// Asignadores:
	void asgVelocidad(double nv);
	void asgPosicion(T_posicion np);
	void asgEstado(EstadoContador ne);

	// EFE: avanza *this según su velocidad y evoluciona su estado en el tic que le toque.
	void avanzar(int tic);

private:
	double velocidad;
	T_posicion posicion; // posicion.first == coordenada X, posicion.second = coordenada Y
	EstadoContador estado;
	int tiempoEspera;
};

Contador::Contador()
{
}

Contador::Contador(double v, Contador::EstadoContador e, T_posicion p)
{

}

Contador::~Contador()
{
}

double Contador::obtVelocidad()
{
	return 6.0; // agregue su propio codigo
}

Contador::T_posicion Contador::obtPosicion()
{
	return pair< int, int >(0,0); // agregue su propio codigo
}

Contador::EstadoContador Contador::obtEstado()
{
	return esperar; // agregue su propio codigo
}

void Contador::asgVelocidad(double nv)
{
}

void Contador::asgPosicion(T_posicion np)
{
}

void Contador::asgEstado(EstadoContador ne)
{
}

void Contador::avanzar(int tic)
{
}