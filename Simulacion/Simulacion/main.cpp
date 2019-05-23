//#include "pch.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <assert.h>     /* assert */
#include <random>
#include "Simulador.h"
#include "Contador.h"
#include "Tortuga.h"
using namespace std;

std::default_random_engine generador; // generador de aleatorios
std::uniform_real_distribution<double> random_uniform(0.0, 1.0); // distribuci�n uniforme


int main()
{

	typedef std::chrono::high_resolution_clock t_clock;
	t_clock::time_point beginning = t_clock::now();

	//...su c�digo

	t_clock::duration lapso = t_clock::now() - beginning;
	unsigned semilla = lapso.count();
	generador.seed(semilla);
	// simulador.simular(tt, generador, random_uniform); con tt el total de tics que se van a simular
	Simulador::random_logistic(0., 1.);

	/*int cantidadSimulaciones;
	int tiempoSimulado;
	int cantidadTortugas;
	int cantidadHilos;
	int ticks = tiempoSimulado * 60;
	Simulador simulador = new Simulador(); //O "Simulador simulador;"?

	/*1. Cargar y validar los datos del archivo �experimentos.csv�.*/
	/*2. Cargar y validar los archivos de datos de entrada.*/
	/*bool lecturaCorrecta = validarDatos< vector< T > >(arch_experimentos);
	if (lecturaCorrecta) {
		vector< vector< double > > experimentos = cargarDatos< vector< T > >(arch_experimentos);
		for (size_t i = 1; i < experimentos.size(); i++)
		{
			cantidadSimulaciones = experimentos[0][0];
			tiempoSimulado = experimentos[0][2];
			cantidadTortugas = experimentos[0][3];
			for (size_t j = 4; j < experimentos[0].size(); j++)
			{
				/*3. Ejecutar cada experimento indicado en el archivo �experimentos.csv�:*/
				/*3.1 Asignar la instancia de Simulador con los datos de entrada.*/
				/*3.2 Ejecutar la simulaci�n invocando Simulador::simular(...).*/
	/*			cantidadHilos = experimentos[0][j];
				simulador.cantidadHilos = cantidadHilos; //Agregar simulador.cantidadHilos
				simulador.simular(ticks);
			}
		}
	}*/
	Simulador simuladorP;
	simuladorP.inicializarArribada(0.5, 0.2);

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