#include "Contador.h"

// Construye un contador con velocidad 1.0, en posicion (0,0), en estado esperar.
Contador::Contador()
{
	velocidad;
	posicion.first = 0; 
	posicion.second = 0;
	estado = esperar;
}

// Construye un contador con velocidad v, en posicion p, en estado p. 
Contador::Contador(double v, Contador::EstadoContador e, T_posicion p)
{
	velocidad = v;
	posicion.first = p.first; // posicion.first == coordenada X, posicion.second = coordenada Y
	posicion.second = p.second;
	estado = e;
}

Contador::~Contador()
{
}

double Contador::obtVelocidad()
{
	return velocidad;
}

Contador::T_posicion Contador::obtPosicion()
{
	return pair< int, int >(posicion.first, posicion.second); // agregue su propio codigo
}

Contador::EstadoContador Contador::obtEstado()
{
	return estado; // agregue su propio codigo
}

void Contador::asgVelocidad(double nv)
{
	velocidad = nv;
}

void Contador::asgPosicion(T_posicion np)
{
	posicion.first = np.first;
	posicion.second = np.second;
}

void Contador::asgEstado(EstadoContador ne)
{
	estado = ne;
}

// EFE: avanza *this según su velocidad y evoluciona su estado en el tic que le toque.
//En cada tic el contador avanza hacia adelante y en caso de que haya tortugas entra en estado contador
//El de los cuadrados no se mueve
//El de la vara vertical no se mueve 
//El de la trasversal horizontal si se va a ir moviendo de forma paralela al mar 
 
void Contador::avanzar(int tic)
{

}


