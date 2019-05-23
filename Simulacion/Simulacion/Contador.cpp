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

Contador::TipoContador Contador::obtTipoContador()
{
	return tipo;
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

void Contador::asgTipoContador(TipoContador nt)
{
	tipo = nt;
}


// EFE: avanza *this según su velocidad y evoluciona su estado en el tic que le toque.
//En cada tic el contador avanza hacia adelante y en caso de que haya tortugas entra en estado contador
//El de los cuadrados no se mueve
//El de la vara vertical no se mueve 
//El de la trasversal horizontal si se va a ir moviendo de forma paralela al mar 
 //Cada contador avanza 6km por hora
//El contador avanza y cuenta a la vez por 15min pues son 1500m en total toda la playa
//y al finalizar espera por 20 minutos y luego vuelve a empezar.
void Contador::avanzar(int tic)
{
	//Avanza 100mts por minuto (Pues su v=6km/h constante)
	//Cuenta cada 20 min
	if (posicion.first == 1000) {
		estado = esperar;
		posicion.first = 0;
		tiempoEspera = 0;
	}
	if (tiempoEspera == 20) {
		estado = contar;
		posicion.first += 100;
	}
	else
	{
		tiempoEspera += 1;
	}
	if (estado == contar) {
		posicion.first += 100;
	}

}


