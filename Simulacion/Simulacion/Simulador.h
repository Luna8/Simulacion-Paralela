#pragma once

#include <fstream>
#include <sstream>
#include <math.h>
#include <assert.h>     /* assert */
#include <random>
#include <iostream>
using namespace std;

#include "Tortuga.h"
#include "Contador.h"
#include "Aleatorizador.h"

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
	void inicializarPlaya(ifstream arch_secciones);

	// EFE: inicializa los cuadrantes con los datos en el archivo.
	void inicializarCuadrantes(ifstream arch_cuadrantes);

	// EFE: inicializa los transectos verticales sobre la berma con los datos en el archivo.
	void inicializarTransectosVerticales(ifstream arch_transectos_verticales);

	// EFE: inicializa el transecto paralelo a la berma con el ancho y largo indicado.
	void inicializarTransectoBerma(ifstream arch_transecto_paralelo);

	// EFE: crea la cantidad indicada de tortugas y las inicializa usando la distribución normal 
	// con el promedio y desviación dados para la velocidad.
	void inicializarTortugas(ifstream comportamiento_tortugas);
	// REQ: cantidad >= 3.
	// EFE: crea la cantidad indicada de contadores y los inicializa usando la distribución normal 
	// con el promedio y desviación dados para la velocidad. Si cantidad > 3, los distribuye a partes
	// iguales entre cada método de estimación ubicándolos en la posición inicial apropiada a cada
	// método de estimación.
	// NOTA: se supone que hay al menos un contador para cada método de estimación.
	void inicializarContadores(int cantidad, double velocidad_promedio, double dsv_std_velocidad);

	// EFE: distribuye la cantidad total de tortugas que arriban, minuto a minuto, durante 360 
	// minutos o 6 horas, siguiendo la distribución logística con parámetros u y s.
	void inicializarArribada(double u, double s);

	// EFE: guarda los parámetros de la función sinusoidal que se usa para generar la altura de la 
	// marea minuto a minuto por 360 minutos o 6 horas.
	// NOTA: se debe usar modelo sinusoidal con periodo en minutos.
	void inicializarMarea(double baja, double alta, int periodo);

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

	template < typename T, class F >
	vector< vector< double > > cargarDatos(ifstream& archivo, F t) throw (invalid_argument, out_of_range);
	template < typename T, class F >
	vector< vector< double > > lecturaDatosValidados(ifstream& archivo, F t) throw (invalid_argument, out_of_range);
	vector< vector< double > > secciones;		//wtf?
	vector< vector< double > > cuadrantes;
	vector<Tortuga> vectorTortugas;
	vector<Contador> vectorContadores;
	double stod_wrapper(string v) throw (invalid_argument, out_of_range) { return std::stod(v); }

	int cantidadHilos; //Lo envía el main


private:
	int tiempoCuadrante;
	int tiempoVertical;
	int cantidadContadoresV;
	int cantidadContadoresC;
	int cantidadTortugas;
	int tiempoParalelo;
	int rangoVision;
	int anchoParalelo;
	int largoParalelo;

};

Simulador::Simulador()
{
}


Simulador::~Simulador()
{
}

void Simulador::inicializarPlaya(ifstream arch_secciones)
{
}

void Simulador::inicializarCuadrantes(ifstream arch_cuadrantes)
{
}

void Simulador::inicializarTransectosVerticales(ifstream arch_transectos_verticales)
{
}

void Simulador::inicializarTransectoBerma(ifstream arch_transecto_paralelo)
{
}

void Simulador::inicializarTortugas(ifstream comportamiento_tortugas)
{
}

void Simulador::inicializarContadores(int cantidad, double velocidad_promedio, double dsv_std_velocidad)
{
}

void Simulador::inicializarArribada(double u, double s)
{
}

void Simulador::inicializarMarea(double baja, double alta, int periodo)
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

template < typename T, class F >
vector< vector< double > >Simulador::lecturaDatosValidados(ifstream& archivo, F t) throw (invalid_argument, out_of_range)
{
	/* lee el archivo dobles */
	ifstream d(archivo, ios::in);
	if (!d) {
		cout << "no encuentra el archivo de datos" << endl;
	}
	vector< vector< double > > vd;
	try {
		vd = cargarDatos< double >(d); // usa wrapper de stod
	}
	catch (exception e) {
		cout << "valor invalido o fuera de limite" << endl;

	}
	/*for (auto f : vd)
		for (auto x : f)
			cout << x << ',' << endl;
	cin.ignore();*/
	return vd;
}

template < typename T, class F >
vector< vector< double > > Simulador::cargarDatos(ifstream& archivo, F t) throw (invalid_argument, out_of_range)
{
	vector< vector< T > > valores;
	vector< T > linea_valores;
	string linea;
	while (getline(archivo, linea)) {
		linea_valores.clear();
		stringstream ss(linea);
		string numero_S;
		T numero_T;
		while (getline(ss, numero_S, ',')) {
			try {
				numero_T = t(numero_S);
			}
			catch (exception e) {
				throw e;
			}
			linea_valores.push_back(numero_T);
		}
		valores.push_back(linea_valores);
	}
	return valores;

}