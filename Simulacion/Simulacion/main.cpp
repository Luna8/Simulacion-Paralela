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
std::uniform_real_distribution<double> random_uniform(0.0, 1.0); // distribución uniforme

double stod_wrapper(string v) throw (invalid_argument, out_of_range) { return std::stod(v); }


vector< vector< double > > lecturaDatosValidados(string file);


int main()
{

	Simulador simulador;
	//Lectura de archivos
	
	//ifstream d("C:\\Users\B26607\Documents\Simulacion-Paralela\archivos\terreno.csv", ios::in);
	string file;
	//Lectura terreno
	file = "terreno.csv";
	vector< vector< double > > vd;
	ifstream d(file, ios::in);
	vd = lecturaDatosValidados(file);
	simulador.inicializarPlaya(vd);
	
	file = "cuadrantes.csv";
	vector< vector< double > > vd;
	ifstream d(file, ios::in);
	vd = lecturaDatosValidados(file);
	simulador.inicializarCuadrantes(vd);

	file = "transectos_verticales.csv";
	vector< vector< double > > vd;
	ifstream d(file, ios::in);
	vd = lecturaDatosValidados(file);
	simulador.inicializarTransectosVerticales(vd);

	file = "transecto_paralelo_berma.csv";
	vector< vector< double > > vd;
	ifstream d(file, ios::in);
	vd = lecturaDatosValidados(file);
	simulador.inicializarTransectoBerma(vd);

	file = "comportamiento_tortugas.csv";
	vector< vector< double > > vd;
	ifstream d(file, ios::in);
	vd = lecturaDatosValidados(file);
	simulador.inicializarArribada(vd);

	
	/*
	typedef std::chrono::high_resolution_clock t_clock;
	t_clock::time_point beginning = t_clock::now();

	//...su código

	t_clock::duration lapso = t_clock::now() - beginning;
	unsigned semilla = lapso.count();
	generador.seed(semilla);
	// simulador.simular(tt, generador, random_uniform); con tt el total de tics que se van a simular
	Simulador::random_logistic(0., 1.);*/

	/*int cantidadSimulaciones;
	int tiempoSimulado;
	int cantidadTortugas;
	int cantidadHilos;
	int ticks = tiempoSimulado * 60;
	Simulador simulador = new Simulador(); //O "Simulador simulador;"?

	/*1. Cargar y validar los datos del archivo “experimentos.csv”.*/
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
				/*3. Ejecutar cada experimento indicado en el archivo “experimentos.csv”:*/
				/*3.1 Asignar la instancia de Simulador con los datos de entrada.*/
				/*3.2 Ejecutar la simulación invocando Simulador::simular(...).*/
	/*			cantidadHilos = experimentos[0][j];
				simulador.cantidadHilos = cantidadHilos; //Agregar simulador.cantidadHilos
				simulador.simular(ticks);
			}
		}
	}*/
	//Simulador simuladorP;
	//simuladorP.inicializarArribada(0.5, 0.2);

}


vector< vector< double > > lecturaDatosValidados(string file)
{
	Simulador simulador;
	
	/* lee el archivo dobles */
	ifstream d(file, ios::in);
	if (!d) {
		cout << "no encuentra el archivo de datos" << endl;
		
	}
	vector< vector< double > > vd;
	try {
		vd = simulador.cargarDatos< double >(d, stod_wrapper); // usa wrapper de stod
	}
	catch (exception e) {
		cout << "valor invalido o fuera de limite" << endl;

		/*for (auto f : vd)
			for (auto x : f)
				cout << x << ',' << endl;
		cin.ignore();*/
		
	}
	return vd;
}

