# include "Tortuga.h"

// Construye una tortuga con velocidad 1, en estado "inactiva", en posicion (0,0).
Tortuga::Tortuga()
{
	velocidad = 1;
	estado = inactiva;
	posicion.first = 0;
	posicion.second = 0;
}

Tortuga::Tortuga(double v, EstadoTortuga e, T_posicion p)
{
	velocidad = v;
	estado = e;
	posicion.first = p.first;
	posicion.second = p.second;
}

Tortuga::~Tortuga()
{
}

double Tortuga::obtVelocidad()
{
	return velocidad;
}

Tortuga::T_posicion Tortuga::obtPosicion()
{
	return pair<int, int>(posicion.first, posicion.second); 
}

Tortuga::EstadoTortuga Tortuga::obtEstado()
{
	return estado;
}

void Tortuga::asgVelocidad(double nv)
{
	velocidad = nv;
}

void Tortuga::asgPosicion(T_posicion np)
{
	posicion.first = np.first;
	posicion.second = np.second;
}

void Tortuga::asgEstado(EstadoTortuga ne)
{
	estado = ne;
}

// EFE: avanza *this según su velocidad y evoluciona su estado en el tic que le toque.
// En cada avance la tortuga debe avanzar en dirección a la berma.
//Avanza, evalúa si 
//La tortuga sale del mar y se genera entonces un tiempo estimado usando la distribución normal
//Luego de generar ese tiempo estimado entonces la tortuga durante ese rato hace las acciones que vaya a realizar 
//Se proponen dos formas: distribuir de forma uniforme le tiempo entre las diferentes acciones
//generar valores random y que todos sumen el tiempo completo 

void Tortuga::avanzar(int tic)
{
	double number = distribution(generator);
		
}
