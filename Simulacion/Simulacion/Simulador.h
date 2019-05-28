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
	void inicializarPlaya(vector< vector< double > > arch_secciones);

	// EFE: inicializa los cuadrantes con los datos en el archivo.
	//		Crea e inicializa los contadores correspondientes.
	void inicializarCuadrantes(vector< vector< double > > arch_cuadrantes);

	// EFE: inicializa los transectos verticales sobre la berma con los datos en el archivo.
	//		Crea e inicializa los contadores correspondientes.
	void inicializarTransectosVerticales(vector< vector< double > >arch_transectos_verticales);

	// EFE: inicializa el transecto paralelo a la berma con el ancho y largo indicado.
	//		Crea e inicializa los contadores correspondientes.
	void inicializarTransectoBerma(vector< vector< double > >transecto_paralelo_berma);

	// EFE: crea la cantidad indicada de tortugas y las inicializa usando la distribución normal 
	// con el promedio y desviación dados para la velocidad.
	void inicializarTortugas(int cantidad_tortugas);

	// EFE: distribuye la cantidad total de tortugas que arriban, minuto a minuto, durante 360 
	// minutos o 6 horas, siguiendo la distribución logística con parámetros u y s.
	void inicializarArribada(vector< vector< double > >comportamiento_tortugas);

	// EFE: guarda los parámetros de la función sinusoidal que se usa para generar la altura de la 
	// marea minuto a minuto por 360 minutos o 6 horas.
	// NOTA: se debe usar modelo sinusoidal con periodo en minutos.
	void inicializarMarea(vector< vector< double > > marea);

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

	vector< vector< double > > secciones;		//wtf?
	vector< vector< double > > cuadrantes;
	vector<Tortuga> vectorTortugas;
	vector<Contador> vectorContadores;
	vector<vector<Tortuga>> tortugaXSeccion;

	double stod_wrapper(string v) throw (invalid_argument, out_of_range) { return std::stod(v); }

	


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
	double vagar;
	double camar;
	double excavar;
	double poner;
	double tapar;
	double camuflar;
	double velocidadPromEst; //Velocidad promedio estimada
	double desviacionEstVelocidad; //desviación estándar de la velocidad
	double sEscala; //Parámetro s (escala) para la distribución logística de la arribada.
	double duracionPromedio; //Duración promedio de minutos desde “camar” hasta “camuflar”
	double desviacionEstDuracion; //Desviación estándar de la duración promedio entre “camar” y “camuflar”
	double baja;
	double alta;
	double tiempo;


};

Simulador::Simulador()
{
}


Simulador::~Simulador()
{
}

void Simulador::inicializarPlaya(vector< vector< double > > arch_secciones)
{
	
	// Estructura: vector de vectores cuyas filas son las secciones y las columnas
		//tienen la siguiente información:
	

		//C2: Distancia del nivel de marea media a la berma en metros
		//C3: Altura de la berma respecto del nivel de marea media
		//C4: Distancia de la berma a las dunas en metros

		//FALTA FUNCION VALIDARDATOS Y CARGARDATOS
		//ifstream ee(arch_secciones, ios::in);
		//secciones = lecturaDatosValidados< double >(&arch_secciones, stod_wrapper);
	secciones = arch_secciones;
	for (size_t i = 1; i < secciones.size(); i++)
	{
		secciones[i][0] += secciones[i - 1][0];
	}

}

void Simulador::inicializarCuadrantes(vector< vector< double > >arch_cuadrantes)
{
	//Cada posicion del vector cuadrantes contiene la información de un cuadrante
	//X II
	//Y II
	//X SD
	//Y SD
	cuadrantes = arch_cuadrantes;
	tiempoCuadrante = cuadrantes[0][1];
	cantidadContadoresC = cuadrantes[0][0];
	cuadrantes.erase(cuadrantes.begin());

}

void Simulador::inicializarTransectosVerticales(vector< vector< double > >arch_transectos_verticales)
{
	//Se tiene para cada transecto paralelo lo siguiente:
	// X II
	// Y II
	// Y SD
	vector< vector< double > > verticales = arch_transectos_verticales;
	tiempoVertical = verticales[0][1];
	cantidadContadoresV = verticales[0][0];
	verticales.erase(verticales.begin());
}

void Simulador::inicializarTransectoBerma(vector< vector< double > >transecto_paralelo_berma)
{
	vector< vector< double > > paralelo = transecto_paralelo_berma;
	tiempoParalelo = paralelo[0][1];
	rangoVision = paralelo[0][2];
	anchoParalelo = paralelo[1][0];
	largoParalelo = paralelo[1][1];

}

void Simulador::inicializarTortugas(int cantidad_tortugas)
{
	double cantidad = random_logistic(0.0, sEscala);
	std::default_random_engine generator;
	//std::normal_distribution<double> distribucionNormal(velocidadPromEst, desviacionEstVelocidad);

	//double number = distribucionNormal(generator);
	double velocidadT;

}

void Simulador::inicializarArribada(vector< vector< double > >comportamiento_tortugas)
{
	//Inicializar valores del vector tortugas desde el archivo "comportamiento_tortugas"
	vector<vector< double > > tortugas = comportamiento_tortugas;
	vagar = tortugas[0][0];
	camar = tortugas[0][1];
	excavar = tortugas[0][2];
	poner = tortugas[0][3];
	tapar = tortugas[0][4];
	camuflar = tortugas[0][5];
	velocidadPromEst = tortugas[0][6]; //Velocidad promedio estimada
	desviacionEstVelocidad = tortugas[0][7]; //desviación estándar de la velocidad
	sEscala = tortugas[0][8]; //Parámetro s (escala) para la distribución logística de la arribada.
	duracionPromedio = tortugas[0][9]; //Duración promedio de minutos desde “camar” hasta “camuflar”
	desviacionEstDuracion = tortugas[0][10]; //Desviación estándar de la duración promedio entre “camar” y “camuflar”
	//El parámetro u (mi) debe ser igual a cero

	//Almacenamiento de tortugas: Vector, Lista, Diccionario???
	//Vamos a seleccionar un vector cuyo índice va a ser su "id"

	//Inicializar vector con cantidad adecuada;

	std::default_random_engine generator;
	//std::normal_distribution<double> distribucionNormal(velocidadPromEst, desviacionEstVelocidad);

	//double number = distribucionNormal(generator);
	double velocidadT;

	//Inicializar tortugas
	//vector<Tortuga> vectorTortugas; Global?
	for (int i = 0; i < cantidadTortugas; i++) {
		//	velocidadT = distribucionNormal(generator);
		//	vectorTortugas[i].asgVelocidad(velocidadT);
	}
//-------------------------------------------
	//std::default_random_engine generator;
	//std::uniform_real_distribution<double> random_uniform(0.0, 1.0);
	//Entre línea de la marea baja y línea de marea en el tic en que está entrando la tortuga a la playa
	//std::uniform_real_distribution<double> distributionP(0.0, 1.0);


	/*vector<T> vectorArribada; Global (?) Contiene X y Y de tortugas, además del tic en que aparece (?)
	vectorArribada[0] = posicionX
	vectorArribada[1] = posicionY
	vectorArribada[2] = ticAparicion*/

	/*for (int i = 0; i < cantidadTortugas; i++) {
		//vectorTortugas[i] = distribucionLogistica(); //En el caso que la función de las posiciones y el tic de aparición
		double  randomTic = Aleatorizador::random_logistic(u, s);

	}*/

	//Se genera para cada tic la cantidad total de tortugas que van a inicializarse en este tic
	//double  randomTic = Aleatorizador::random_logistic(u, s);
	//cout << randomTic << endl;
}

void Simulador::inicializarMarea(vector< vector< double > >marea)
{
	baja = marea[0][0];
	alta = marea[0][1];
	tiempo = marea[0][2];

}

void Simulador::simular(int total_tics)
{
	for (int i = 0; i < total_tics; i++)
	{
		//Primero vamos a simular la marea en cada tic definiendo así la línea de la marea baja
		//y la de la marea alta en cada tic 
		double p = (alta - baja) / tiempo;
		double c = baja;
		double altura = p * i + c;
		//cout << altura << endl;

		
		//Luego inicializamos las tortugas que corresponan en este tic, para ello
		//revisamos el valor correspondiente en la distribuci logística para este tic
		//y esa cantidad la creamos, para cada tortuga generamos con la distribución 
		//uniforme la ubicación(coordenadas x y y) y la ubicamos en el sector correspondiente, 
		//según el sector en el que está vamos a meterla en el vector de tortugas por sección
		
	//FALTA
		//Luego se debe avanzar a as tortugas que ya se encuentran en camino
		//Seguido de eso se debe mover al contador paralelo
		

	/**Inicio Contador de Transecto Paralelo a la Berma.**/
	Contador::TipoContador tipoHorizontal = Contador::horizontal;
	vectorContadores[0].asgTipoContador(tipoHorizontal); //Contador en la posicion 0 de tipo Horizontal
	int xActual = 0;
	Contador::T_posicion pos = make_pair(xActual, 0);
	vectorContadores[0].asgPosicion(pos);
	int seccionActual = 0;
	int posicionActualTort;
	bool noEsta;
	bool contando = true;
	do {
		xActual = 0;
		pos = make_pair(xActual, 0);
		vectorContadores[0].asgPosicion(pos);
		seccionActual = 0;
		posicionActualTort;
		for (int i = 0; i < tortugasPorSeccion.size; i++)
		{
			noEsta = true;
			cantTortParalelo = 0;
			posicionActualTort = tortugasPorSeccion[seccionActual][i].obtPosicion.second;
			for (int j = 0; j < tortugasContadasSec.size; j++)
			{
				if (tortugasContadasSec[seccionActual][j].obtId == tortugasPorSeccion[seccionActual][i].obtId)
				{
					noEsta = false;
				}
			}
			if (posicionActualTort > (pos.second - anchoParalelo / 2) && posicionActualTort < (pos.second + anchoParalelo / 2) && !noEsta)
			{
				cantTortParalelo++;
				tortugasContadasSec[seccionActual].push_back(tortugasPorSeccion[seccionActual][i]);
			}
			seccionActual++;
		}
		pos = make_pair(xActual + 100, 0);
		vectorContadores[0].asgPosicion(pos);
		if (xActual > 750)
		{
			contando = false;
		}
	} while (contando);
	/**Final Contador de Transecto Paralelo a la Berma.**/

	//Y finalmente aquí se debe contar la cantidad de tortugas vista por cada contador en los diferentes métodos
		
	//La idea era paralelizar por secciones, se iba a contar con un vector que contenía la información de cada sección y un vector de
	// tortugas asociado a esa sección, por lo que cada hilo revisaría solo esas tortugas en cada sección en cada iteración.
		
	}
}

long Simulador::obtTotalTortugasArribaron(int nc, int i, int m)
{
	long totalTortugasArribaron;
	totalTortugasArribaron = nc * i / (4.2 * m);
	return totalTortugasArribaron;  // agregue su propio codigo
}

long Simulador::obtTotalTortugasAnidaron(double a, int d, int w, int m, int slj, int no, double prto)
{
	long totalTortugasAnidaron;
	totalTortugasAnidaron = (a * d / (2 * w * m * slj) * (no / prto));
	return totalTortugasAnidaron; // agregue su propio codigo
}

double Simulador::obtEstimacionXtransectosSobreBerma(int noc, int ne, int nv, double ac, int aci, int d, int m)
{
	double estimacionXtransectosSobreBerma;
	estimacionXtransectosSobreBerma = ((noc + 0.94 * ne + 0.47 * nv) * 2.25 * (ac / aci) * ((d / 60) / 64.8 * m));
	return estimacionXtransectosSobreBerma; // agregue su propio codigo
}

double Simulador::obtEstimacionXtransectoHorizontal(int noc, int ne, int nv, double ac, int aci, int d, int m)
{
	double estimacionXtransectoHorizontal;
	estimacionXtransectoHorizontal = ((noc + 0.94 * ne + 0.47 * nv) * 2.25 * (ac / aci) * ((d / 60) / 64.8 * m));
	return estimacionXtransectoHorizontal; // agregue su propio codigo
}

double Simulador::obtEstimacionXcuadrantes(int noc, int ne, int nv, double ac, int aci, int d, int m)
{
	double estimacionXcuadrantes;
	estimacionXcuadrantes = ((noc + 0.94 * ne + 0.47 * nv) * 2.25 * (ac / aci) * ((d / 60) / 64.8 * m));
	return estimacionXcuadrantes; // agregue su propio codigo
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

/* COMENTARIOS VARIOS
	For paralelizado en donde el i son cada tic durante las 6 horas (?)
	Debe trabajar con inicializarArribada y inicializarMarea ya que estas trabajan cada tic (?)
	Le pasa los i (tics) a Avanzar de Tortuga y Contador, además de inicializarMarea (?)
	*/
	//PARALELIZACIÓN
/* Hay diferentes formas de paralelizar
	Hsay que encontrar la cantidad de tortugas que hay en una zona en cada tic
	esto es lo que hay que optimizar sin el inconveniente de la matriz playa
	En cada sector controlar las tortugas de ese sector
	Hay que mover las tortugas, tienen que haer hiloscontrolandolas
	pero hay que distribuir las tortugas entre los hilos correctamente
	Es más fácil que cada tortuga pregunte solo a las de su sector si están en la misma pisicion
	Paralelizar poniendo al menos un hilo por sector
	Dividir hilos por sector y que un hilo se encargue de las tortugas de un sector
	CONTEO
	Forma en que recuperamos la cantidad de tortugas tiene que ser de forma eficiente
	Dividir hilos de tortugas de hilos de contadores
	Sabemos desde el inicio si la tortuga cayó en uno de los sectores en los que se cuenta o no
	entonces solo se deben contemplar esas tortugas.

	//

	Notas 13.05.19
	Asignar hilos a sectores
	Vamos a trabajar de 16 hilos en adelante. En el caso de 16 serían 15 para los sectores y 1 para el contador paralelo
	32: 2 hilos por sector, 1 al paralelo, 1 sin nada
	64: 4 por sector, 1 paralelo, 3 sin nada
	Se pueden partir los sectores en partes según la cantidad de hilos
	Considerar una clase Ssector
	Recordar dividir tortugas por sector desde que nacen
	En cada ciclo puede ser que primero tortugas se mueven y luego los contadores cuentan
