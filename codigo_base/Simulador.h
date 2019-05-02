#pragma once

#include <fstream>
#include <math.h>
#include <assert.h>     /* assert */
#include <random>
using namespace std;

#include "Tortuga.h"
#include "Contador.h"

class Simulador
{
public:
	Simulador();
	~Simulador();

	/* FUNCIÓN STATIC PARA LA DISTRIBUCIÓN LOGÍSTICA A USAR EN LA DISTRIBUCIÓN TEMPORAL DE LA ARRIBADA */
	// REQ: ( location >= 0.0 ) && ( scale > 0.0).
	// EFE: retorna un valor entre 0.0 y 1.0 que representa una probabilidad basada en la distribución logística.
	static double random_logistic(double location, double scale);

	// Objeto compartido que genera los números al azar
	static default_random_engine generator;

	// Objeto compartido que genera números entre 0.0 y 1.0 al azar según la distribución uniforme
	static uniform_real_distribution<double> random_uniform;

	/*
	* INICIALIZADORES DE SIMULACIÓN
	*/

	// EFE:inicializa las secciones en que se divide la playa con los datos en el archivo.
	void inicializarPlaya(ifstream& arch_secciones);

	// EFE: inicializa los cuadrantes con los datos en el archivo.
	//		Crea e inicializa los contadores correspondientes.
	void inicializarCuadrantes(ifstream& arch_cuadrantes);

	// EFE: inicializa los transectos verticales sobre la berma con los datos en el archivo.
	//		Crea e inicializa los contadores correspondientes.
	void inicializarTransectosVerticales(ifstream& arch_transectos_verticales);

	// EFE: inicializa el transecto paralelo a la berma con el ancho y largo indicado.
	//		Crea e inicializa los contadores correspondientes.
	void inicializarTransectoBerma(ifstream& transecto_paralelo_berma);

	// EFE: crea la cantidad indicada de tortugas y las inicializa usando la distribución normal 
	// con el promedio y desviación dados para la velocidad.
	void inicializarTortugas(int cantidad_tortugas);

	// EFE: distribuye la cantidad total de tortugas que arriban, minuto a minuto, durante 360 
	// minutos o 6 horas, siguiendo la distribución logística con parámetros u y s.
	void inicializarArribada(ifstream& comportamiento_tortugas);

	// EFE: guarda los parámetros de la función sinusoidal que se usa para generar la altura de la 
	// marea minuto a minuto por 360 minutos o 6 horas.
	// NOTA: se debe usar modelo sinusoidal con periodo en minutos.
	void inicializarMarea(ifstream& marea);

	// REQ: total_tics <= 360.
	// EFE: simula el movimiento de las tortugas y el conteo de los contadores durante 6 horas.
	// NOTA: la tarea de simular representada por este método es la que debe paralelizarse usando hilos.
	void simular(int total_tics);

	/*
	* OBTENEDORES DE RESULTADOS DE LA SIMULACIÓN
	*/

	// RET: total de tortugas que arribaron en la simulación.
	long obtTotalTortugasArribaron();

	// RET: total de tortugas que anidaron en la simulación.
	long obtTotalTortugasAnidaron();

	// RET: estimación del total de tortugas que anidaron con base en el método de transectos sobre la berma.
	double obtEstimacionXtransectosSobreBerma();

	// RET: estimación del total de tortugas que arribaron con base en el método de transecto paralelo a la berma.
	double obtEstimacionXtransectoHorizontal();

	// RET: estimación del total de tortugas que anidaron con base en el método de cuadrantes.
	double obtEstimacionXcuadrantes();

private:

};

Simulador::Simulador()
{
}


Simulador::~Simulador()
{
}

void Simulador::inicializarPlaya(ifstream& arch_secciones)
{
}

void Simulador::inicializarCuadrantes(ifstream& arch_cuadrantes)
{
}

void Simulador::inicializarTransectosVerticales(ifstream& arch_transectos_verticales)
{
}

void Simulador::inicializarTransectoBerma(ifstream& transecto_paralelo_berma)
{
}

void Simulador::inicializarTortugas(int cantidad_tortugas)
{

}

void Simulador::inicializarArribada(ifstream& comportamiento_tortugas)
{
}

void Simulador::inicializarMarea(ifstream& marea)
{
}

void Simulador::simular(int total_tics)
{
}

long Simulador::obtTotalTortugasArribaron()
{
	return 0;  // agregue su propio codigo
}

long Simulador::obtTotalTortugasAnidaron()
{
	return 0; // agregue su propio codigo
}

double Simulador::obtEstimacionXtransectosSobreBerma()
{
	return 0.0; // agregue su propio codigo
}

double Simulador::obtEstimacionXtransectoHorizontal()
{
	return 0.0; // agregue su propio codigo
}

double Simulador::obtEstimacionXcuadrantes()
{
	return 0.0; // agregue su propio codigo
}

default_random_engine Simulador::generator; // inicialización de la variable static
uniform_real_distribution<double> Simulador::random_uniform(0.0, 1.0); // inicialización de la variable static
double Simulador::random_logistic(double location, double scale)
{
	assert(scale > 0.);
	assert(location >= 0.);
	return location - scale * log(1. / random_uniform(generator) - 1.);
}
