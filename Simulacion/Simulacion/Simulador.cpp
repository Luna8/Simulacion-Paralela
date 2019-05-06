#include "Simulador.h"

Simulador::Simulador()
{



}


Simulador::~Simulador()
{
}

// EFE:inicializa las secciones en que se divide la playa con los datos en el archivo.
void Simulador::inicializarPlaya(ifstream arch_secciones)
{
	//Estructura: vector de vectores cuyas filas son las secciones y las columnas 
	//tienen la siguiente información:
	//C1: Posición inicial en x
	//C2: Distancia del nivel de marea media a la berma en metros
	//C3: Altura de la berma respecto del nivel de marea media
	//C4: Distancia de la berma a las dunas en metros

	//FALTA FUNCION VALIDARDATOS Y CARGARDATOS
	bool lecturaCorrecta = validarDatos(arch_secciones);
	if (lecturaCorrecta){
		vector< vector< T > > secciones = cargarDatos(arch_secciones);
		for (size_t i = 1; i < secciones.size(); i++)
		{
			secciones[i][0] += secciones[i-1][0];
		}
	}
}

// EFE: inicializa los cuadrantes con los datos en el archivo.
void Simulador::inicializarCuadrantes(ifstream arch_cuadrantes)
{

	//Cada posicion del vector cuadrantes contiene la información de un cuadrante
	//X II
	//Y II
	//X SD
	//Y SD
	bool lecturaCorrecta = validarDatos(arch_cuadrantes);
	if (lecturaCorrecta) {
		vector< vector< T > > cuadrantes = cargarDatos(arch_secciones);
		tiempoCuadrante = cuadrantes[0][1];
		cuadrantes.erase(cuadrantes.begin());
		
	}
}

// EFE: inicializa los transectos verticales sobre la berma con los datos en el archivo.
void Simulador::inicializarTransectosVerticales(ifstream arch_transectos_verticales)
{
	//Se tiene para cada transecto paralelo lo siguiente:
	// X II
	// Y II
	// Y SD
	bool lecturaCorrecta = validarDatos(arch_transectos_verticales);
	if (lecturaCorrecta) {
		vector< vector< T > > verticales = cargarDatos(arch_transectos_verticales);
		tiempoVertical = verticales[0][1];
		cantidadContadores = verticales[0][0];
		verticales.erase(verticales.begin());

	}
}

// EFE: inicializa el transecto paralelo a la berma con el ancho y largo indicado.
void Simulador::inicializarTransectoBerma(ifstream arch_transecto_paralelo)
{
	bool lecturaCorrecta = validarDatos(arch_transecto_paralelo);
	if (lecturaCorrecta) {
		vector< vector< T > > paralelo = cargarDatos(arch_transecto_paralelo);
		tiempoParalelo = paralelo[0][1];
		rangoVision = paralelo[0][2];
		anchoParalelo = paralelo[1][0];
		largoParalelo = paralelo[1][1];

	}
}

//ALLEN
// EFE: crea la cantidad indicada de tortugas y las inicializa usando la distribución normal 
// con el promedio y desviación dados para la velocidad.
void Simulador::inicializarTortugas(ifstream comportamiento_tortugas)
{
	bool lecturaCorrecta = validarDatos(comportamiento_tortugas);
	if (lecturaCorrecta) {
		//Inicializar valores del vector tortugas desde el archivo "comportamiento_tortugas"
		vector< T > tortugas = cargarDatos(comportamiento_tortugas);
		vagar = tortugas[0];
		camar = tortugas[1];
		excavar = tortugas[2];
		poner = tortugas[3];
		tapar = tortugas[4];
		camuflar = tortugas[5];
		velocidadPromEst = tortugas[6]; //Velocidad promedio estimada
		desviacionEstVelocidad = tortugas[8]; //desviación estándar de la velocidad
		sEscala = tortugas[9]; //Parámetro s (escala) para la distribución logística de la arribada.
		duracionPromedio = tortugas[10]; //Duración promedio de minutos desde “camar” hasta “camuflar”
		desviacionEstDuracion = tortugas[11]; //Desviación estándar de la duración promedio entre “camar” y “camuflar”
		//El parámetro u (mi) debe ser igual a cero

		//Inicializar tortugas
		//vector<Tortuga> vectorTortugas; Global?
		for (int i = 0; i < cantidadTortugas; i++) {
			velocidadT = distribucionNormal(); //distribucionNormal() (?)
			vectorTortugas[i].asgVelocidad(velocidadT);
		}
	}
}

//ANA
void Simulador::inicializarContadores(int cantidad, double velocidad_promedio, double dsv_std_velocidad)
{
}

//ALLEN
// EFE: distribuye la cantidad total de tortugas que arriban, minuto a minuto, durante 360 
// minutos o 6 horas, siguiendo la distribución logística con parámetros u y s.
void Simulador::inicializarArribada(double u, double s)
{
	/*vector<T> vectorArribada; Global (?) Contiene X y Y de tortugas, además del tic en que aparece (?)
	vectorArribada[0] = posicionX
	vectorArribada[1] = posicionY
	vectorArribada[2] = ticAparicion*/
	for (int i = 0; i < cantidadTortugas; i++) {
		vectorArribada = distribucionLogistica(); //En el caso que la función de las posiciones y el tic de aparición
	}
}

//ANA
void Simulador::inicializarMarea(double baja, double alta, int periodo)
{
}

void Simulador::simular(int total_tics)
{
	/*
	For paralelizado en donde el i son cada tic durante las 6 horas (?)
	Debe trabajar con inicializarArribada y inicializarMarea ya que estas trabajan cada tic (?)
	Le pasa los i (tics) a Avanzar de Tortuga y Contador, además de inicializarMarea (?)
	*/
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

bool Simulador::validarDatos(ifstream archivo) {
	/* lee el archivo dobles */
	ifstream d("dobles.txt", ios::in);
	if (!d)
		cout << "no encuentra el archivo de datos" << endl;
	vector< vector< double > > vd;
	try {
		vd = cargaDatos< double >(d, stod_wrapper); // usa wrapper de stod
	}
	catch (exception e) {
		cout << "valor invalido o fuera de limite" << endl;
	}
	for (auto f : vd)
		for (auto x : f)
			cout << x << ',' << endl;
	cin.ignore();
	return 0;
}

template < typename T, class F >
vector< vector< T > > Simulador::cargarDatos(ifstream archivo) {
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
