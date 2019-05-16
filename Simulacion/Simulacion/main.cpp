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

int main()
{
	int cantidadSimulaciones;
	int tiempoSimulado;
	int cantidadTortugas;
	int cantidadHilos;
	int ticks; // = tiempoSimulado * 60;
	Simulador simulador;

	Contador contador;

	ifstream arch_experimentos("experimentos.csv", ios::in);
	if (!arch_experimentos)
		cout << "No encuentra el archivo de datos" << endl;

	/*1. Cargar y validar los datos del archivo “experimentos.csv”.*/
	/*2. Cargar y validar los archivos de datos de entrada.*/
	vector< vector< double > > experimentos = lecturaDatosValidados< double >(arch_experimentos, simulador.stod_wrapper);
	for (size_t i = 1; i < experimentos.size(); i++)
	{
		cantidadSimulaciones = experimentos[0][0];
		tiempoSimulado = experimentos[0][2];
		cantidadTortugas = experimentos[0][3];
		ticks = tiempoSimulado * 60;
		for (size_t j = 4; j < experimentos[0].size(); j++)
		{
			/*3. Ejecutar cada experimento indicado en el archivo “experimentos.csv”:*/
			/*3.1 Asignar la instancia de Simulador con los datos de entrada.*/
			/*3.2 Ejecutar la simulación invocando Simulador::simular(...).*/
			cantidadHilos = experimentos[0][j];
			simulador.cantidadHilos = cantidadHilos; //Agregar simulador.cantidadHilos
			simulador.simular(ticks);
		}
	}
}

template < typename T, class F >
vector< vector< double > >lecturaDatosValidados(ifstream& archivo, F t) throw (invalid_argument, out_of_range)
{
	/* lee el archivo dobles */
	ifstream d(archivo, ios::in);
	if (!d) {
		cout << "no encuentra el archivo de datos" << endl;
	}
	vector< vector< double > > vd;
	try {
		vd = cargarDatos(d, simulador.stod_wrapper); // usa wrapper de stod
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
vector< vector< double > >cargarDatos(ifstream& archivo, F t) throw (invalid_argument, out_of_range)
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

/*
Pruebas de Contador

	int a;

	Contador contador;

	Contador::EstadoContador estado = Contador::contar;
	Contador::T_posicion posicion = make_pair(3,7);
	Contador::TipoContador tipo = Contador::horizontal;
	double velocidad;

	contador.asgEstado(estado);
	contador.asgPosicion(posicion);
	contador.asgTipoContador(tipo);
	contador.asgVelocidad(10.3);

	estado = contador.obtEstado();
	posicion = contador.obtPosicion();
	tipo = contador.obtTipoContador();
	velocidad = contador.obtVelocidad();

	cout << "Estado: " << estado << ", Posicion X: " << posicion.first << ", Posicion Y: " << posicion.second << ", Tipo: " << tipo << ", Velocidad: " << velocidad << endl;

	contador.avanzar(60);

	estado = contador.obtEstado();
	posicion = contador.obtPosicion();
	tipo = contador.obtTipoContador();
	velocidad = contador.obtVelocidad();

	cout << "Estado: " << estado << ", Posicion X: " << posicion.first << ", Posicion Y: " << posicion.second << ", Tipo: " << tipo << ", Velocidad: " << velocidad << endl;

	cin >> a;
*/

/*
Pruebas de Tortuga

	int a;

	Tortuga tortuga;

	Tortuga::EstadoTortuga estado = Tortuga::vagar;
	Tortuga::T_posicion posicion = make_pair(3, 7);
	double velocidad;

	tortuga.asgEstado(estado);
	tortuga.asgPosicion(posicion);
	tortuga.asgVelocidad(10.3);

	estado = tortuga.obtEstado();
	posicion = tortuga.obtPosicion();
	velocidad = tortuga.obtVelocidad();

	cout << "Estado: " << estado << ", Posicion X: " << posicion.first << ", Posicion Y: " << posicion.second << ", Velocidad: " << velocidad << endl;

	tortuga.avanzar(60);

	estado = tortuga.obtEstado();
	posicion = tortuga.obtPosicion();
	velocidad = tortuga.obtVelocidad();

	cout << "Estado: " << estado << ", Posicion X: " << posicion.first << ", Posicion Y: " << posicion.second << ", Velocidad: " << velocidad << endl;

	cin >> a;
*/