//#include "pch.h"
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


int main(int argc, const char * argv[])
{
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



	Simulador simulador;
	ifstream d("terreno.txt", ios::in);
	simulador.inicializarPlaya(d);


		
}


