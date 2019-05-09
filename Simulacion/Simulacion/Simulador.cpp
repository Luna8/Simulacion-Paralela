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
	ifstream ee(arch_secciones, ios::in);
	bool lecturaCorrecta = validarDatos(ee, stoi_wrapper);
	if (lecturaCorrecta){
		secciones = cargarDatos(ee, stoi_wrapper);
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
		cuadrantes = cargarDatos(arch_secciones);
		tiempoCuadrante = cuadrantes[0][1];
		cantidadContadoresC = cuadrantes[0][0];
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
		cantidadContadoresV = verticales[0][0];
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
		double vagar = tortugas[0];
		double camar = tortugas[1];
		double excavar = tortugas[2];
		double poner = tortugas[3];
		double tapar = tortugas[4];
		double camuflar = tortugas[5];
		double velocidadPromEst = tortugas[6]; //Velocidad promedio estimada
		double desviacionEstVelocidad = tortugas[8]; //desviación estándar de la velocidad
		double sEscala = tortugas[9]; //Parámetro s (escala) para la distribución logística de la arribada.
		double duracionPromedio = tortugas[10]; //Duración promedio de minutos desde “camar” hasta “camuflar”
		double desviacionEstDuracion = tortugas[11]; //Desviación estándar de la duración promedio entre “camar” y “camuflar”
		//El parámetro u (mi) debe ser igual a cero

		//Almacenamiento de tortugas: Vector, Lista, Diccionario???
		//Vamos a seleccionar un vector cuyo índice va a ser su "id"
		
		//Inicializar vector con cantidad adecuada;

		std::default_random_engine generator;
		std::normal_distribution<double> distribucionNormal(velocidadPromEst, desviacionEstVelocidad);

		double number = distribucionNormal(generator);
		double velocidadT;
			
		//Inicializar tortugas
		//vector<Tortuga> vectorTortugas; Global?
		for (int i = 0; i < cantidadTortugas; i++) {
			velocidadT = distribucionNormal(generator);
			vectorTortugas[i].asgVelocidad(velocidadT);
		}
	}
}

//ANA
// REQ: cantidad >= 3.
	// EFE: crea la cantidad indicada de contadores y los inicializa usando la distribución normal 
	// con el promedio y desviación dados para la velocidad. Si cantidad > 3, los distribuye a partes
	// iguales entre cada método de estimación ubicándolos en la posición inicial apropiada a cada
	// método de estimación.
	// NOTA: se supone que hay al menos un contador para cada método de estimación.
void Simulador::inicializarContadores(int cantidad, double velocidad_promedio, double dsv_std_velocidad)
{
	if (cantidad > 3) {
		std::default_random_engine generator;
		std::normal_distribution<double> distribucionNormal(velocidad_promedio, dsv_std_velocidad);

		double number = distribucionNormal(generator);
		double velocidadC;
		//Asignamos velocidades aleatorias para cada contador
		for (int i = 0; i < cantidad; i++)
		{
			velocidadC = distribucionNormal(generator); 
			vectorContadores[i].asgVelocidad(velocidadC);
		}
		//Ahora los asignamos a su posición inicial y el tipo
		vectorContadores[0].asgTipoContador(Contador::horizontal);
		vectorContadores[0].asgPosicion(pair< int, int >(0, 0));
		
		for (int i = 1; i < cantidadContadoresV; i++) {
			vectorContadores[i].asgTipoContador(Contador::vertical);
			
		}

		for (int i = (cantidadContadoresV+1); i < cantidadContadoresC+cantidadContadoresV+1; i++) {
			vectorContadores[i].asgTipoContador(Contador::cuadrante);
		}




	}
	else {
		cout << "Cantidad de contadores menor a la mínima" << endl;
	}
}

//ALLEN
// EFE: distribuye la cantidad total de tortugas que arriban, minuto a minuto, durante 360 
// minutos o 6 horas, siguiendo la distribución logística con parámetros u y s.
void Simulador::inicializarArribada(double u, double s)
{
	std::default_random_engine generator;
	std::uniform_real_distribution<double> random_uniform(0.0, 1.0);
	//Entre línea de la marea baja y línea de marea en el tic en que está entrando la tortuga a la playa
	std::uniform_real_distribution<double> distributionP(0.0, 1.0);

	
	/*vector<T> vectorArribada; Global (?) Contiene X y Y de tortugas, además del tic en que aparece (?)
	vectorArribada[0] = posicionX
	vectorArribada[1] = posicionY
	vectorArribada[2] = ticAparicion*/
	for (int i = 0; i < cantidadTortugas; i++) {
		vectorArribada = distribucionLogistica(); //En el caso que la función de las posiciones y el tic de aparición
		double  randomTic = Aleatorizador::random_logistic(u, s);

	}
}

//ANA
// EFE: guarda los parámetros de la función sinusoidal que se usa para generar la altura de la
// marea minuto a minuto por 360 minutos o 6 horas.
// NOTA: se debe usar modelo sinusoidal con periodo en minutos.
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
uniform_real_distribution<double> Simulador::random_uniform(0.0 , 1.0); // inicialización de la variable static
double Simulador::random_logistic(double location, double scale)
{
	assert(scale > 0.);
	assert(location >= 0.);
	return location - scale * log(1. / random_uniform(generator) - 1.);
}
template < typename T, class F >
bool Simulador::validarDatos(ifstream& archivo, F t) throw (invalid_argument, out_of_range)
{
	/* lee el archivo dobles */
	ifstream d(archivo, ios::in);
	if (!d)
		cout << "no encuentra el archivo de datos" << endl;
	vector< vector< double > > vd;
	try {
		vd = cargarDatos< double >(d); // usa wrapper de stod
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

*/
