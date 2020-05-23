#include "../Comportamientos_Jugador/jugador.hpp"
#include "motorlib/util.h"

#include <iostream>
#include <cmath>
#include <set>
#include <queue>
#include <stack>
#include <unordered_map>


// Este es el método principal que debe contener los 4 Comportamientos_Jugador
// que se piden en la práctica. Tiene como entrada la información de los
// sensores y devuelve la acción a realizar.
Action ComportamientoJugador::think(Sensores sensores) {
	bool visto = false;

	// actualizar coordenadas
	actual.fila = sensores.posF;
	actual.columna = sensores.posC;
	actual.orientacion = sensores.sentido;
	destino.fila = sensores.destinoF;
	destino.columna = sensores.destinoC;

	// calcular la recarga más cercana
	estado loc_recarga;
	if ( !recargas.empty() ) {
		loc_recarga = *recargas.begin();
		int min_recarga = heuristica(actual, loc_recarga);
		
		for ( estado r : recargas ) {
			if ( heuristica(actual, r) < min_recarga ) {
				min_recarga = heuristica(actual, r);
				loc_recarga = r;
			}
		}
	}

	//WIP quizás perder batería no es tan importante al principio ;)
	// podemos modificar el valor de '?' en función de qué valor de batería se tenga
	// para incitar a explorar el mundo
	// CUIDADO y si no encontramos la recarga? :(

	// WIP criterio de recalculo

	if ( sensores.nivel == 4 ) {
		visto = actualizarMapa(sensores);

		/*
		RECARGA DE BATERÍA
		El jugador recargará la batería de acuerdo a los siguientes criterios:
			- si la batería es inferior a B_I
				- irá inmediatamente a recargar X
			- si la batería está entre B_I y B_S
				- si por el camino al destino se encuentra cerca* de una recarga
					- recargará X y volverá al destino
		
		Donde:
			B_I es
			B_S es
			X se calcula en función de la batería que le queda al jugador
			*este concepto de "cerca" lo implementaremos con la heurística,
			 estará "cerca" si la heurística es menor que una cierta distancia,
			 determinada por el tamaño del mapa
		*/


		// WIPrenta dirigirse de acuerdo al tiempo?

		if ( sensores.bateria <= B_I && !hayplan )
			aRecarga = true;
		else if ( B_I < sensores.bateria && sensores.bateria < B_S ){//&& !hayplan ) {
			// si se encuentra en el destino
			// detectar
			
			// WIP optimizar distancias, B_I, B_S, MAX_CERCANIA, CANTIDAD_RECARGA
			if ( heuristica(actual, loc_recarga) < mapaResultado.size()/K_CERCANIA ) {
				//cout << "Está cerca de la recarga" << endl;
				aRecarga = true;
				hayplan = false;	// de este modo se desviará parcialmente de su
									// camino para ir a la recarga
			}
		}
	}
	
	if (!hayplan || visto) {
		if ( aRecarga && !recargas.empty() ) {
			hayplan = pathFinding(sensores.nivel, actual, loc_recarga, plan);
		} else
			hayplan = pathFinding(sensores.nivel, actual, destino, plan);
	}

	switch ( mapaResultado[sensores.posF][sensores.posC] ) {
		case 'K':	has_bikini = true; break;
		case 'D':	has_zapatillas = true; break;
		case 'X':	// efectuar recarga una vez que estamos en casilla de recarga
			if ( aRecarga ) {
				aRecarga = false;
				hayplan = true;
				plan.clear();
				/*
				WIP valor adaptativo de recarga
				Si está en situación de muy baja, recarga mucho
				si está en intervalo de confianza, recarga menos
				*/
			
				int cantidad_recarga = -sensores.bateria/130+265/13;
				for ( int i = 0; i < cantidad_recarga; i++ ) {
					plan.push_back(actIDLE);
				}
			}
			break;
	}

	Action sigAccion;
	if (hayplan and plan.size()>0) {
		sigAccion = plan.front();
		// si el nivel es el 4, vemos si la acción es correcta (básicamente
		// que no nos choquemos con un aldeano)
		if ( sensores.nivel == 4 ) {
			// chocarse con un aldeano
			// WIP Mejorar handling aldeano ---
			if ( sigAccion == actFORWARD )
				if ( sensores.superficie[2] == 'a' ) {
					if ( esperando_aldeano < MAX_ESPERA_ALDEANO ) {
						sigAccion = actIDLE;
						esperando_aldeano++;
					} else {
						esperando_aldeano = 0;
						sigAccion = actTURN_L;
					}
					hayplan = false;
				} else if ( sensores.terreno[2] == 'M' or sensores.terreno[2] == 'P' ) {
					sigAccion = actIDLE;
					hayplan = false;
				} else {
					esperando_aldeano = 0;
				}
			
		}
		plan.erase(plan.begin());
	} else {
		hayplan = false;
	}

	return sigAccion;
}


// Llama al algoritmo de busqueda que se usará en cada comportamiento del agente
// Level representa el comportamiento en el que fue iniciado el agente.
bool ComportamientoJugador::pathFinding (int level, const estado &origen, const estado &destino, list<Action> &plan){
	switch (level){
		case 1: cout << "Busqueda en profundad\n";
			      return pathFinding_AStar(origen,destino,plan);
						break;
		case 2: cout << "Busqueda en Anchura\n";
			      return pathFinding_Anchura2(origen,destino,plan);
						break;
		case 3: cout << "Busqueda Costo Uniforme\n";
				  return pathFinding_CostoUniforme2(origen,destino,plan);
						break;
		case 4: cout << "Busqueda para el reto\n";
				  return pathFinding_AStar(origen,destino,plan);
						break;
	}
	cout << "Comportamiento sin implementar\n";
	return false;
}


//---------------------- Implementación de la busqueda en profundidad ---------------------------

// Dado el código en carácter de una casilla del mapa dice si se puede
// pasar por ella sin riegos de morir o chocar.
bool EsObstaculo(unsigned char casilla){
	if (casilla=='P' or casilla=='M')
		return true;
	else
	  return false;
}


// Comprueba si la casilla que hay delante es un obstaculo. Si es un
// obstaculo devuelve true. Si no es un obstaculo, devuelve false y
// modifica st con la posición de la casilla del avance.
bool ComportamientoJugador::HayObstaculoDelante(estado &st){
	int fil=st.fila, col=st.columna;

  // calculo cual es la casilla de delante del agente
	switch (st.orientacion) {
		case 0: fil--; break;
		case 1: col++; break;
		case 2: fil++; break;
		case 3: col--; break;
	}

	// Compruebo que no me salgo fuera del rango del mapa
	if (fil<0 or fil>=mapaResultado.size()) return true;
	if (col<0 or col>=mapaResultado[0].size()) return true;

	// Miro si en esa casilla hay un obstaculo infranqueable
	if (!EsObstaculo(mapaResultado[fil][col])){
		// No hay obstaculo, actualizo el parámetro st poniendo la casilla de delante.
    st.fila = fil;
		st.columna = col;
		return false;
	}
	else{
	  return true;
	}
}

struct nodo{
	estado st;
	list<Action> secuencia;
};

struct ComparaEstados{
	bool operator()(const estado &a, const estado &n) const{
		if ((a.fila > n.fila) or (a.fila == n.fila and a.columna > n.columna) or
	      (a.fila == n.fila and a.columna == n.columna and a.orientacion > n.orientacion))
			return true;
		else
			return false;
	}
};


// Implementación de la búsqueda en profundidad.
// Entran los puntos origen y destino y devuelve la
// secuencia de acciones en plan, una lista de acciones.
bool ComportamientoJugador::pathFinding_Profundidad(const estado &origen, const estado &destino, list<Action> &plan) {
	//Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado,ComparaEstados> generados; // Lista de Cerrados
	stack<nodo> pila;											// Lista de Abiertos

  nodo current;
	current.st = origen;
	current.secuencia.empty();

	pila.push(current);

  while (!pila.empty() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){

		pila.pop();
		generados.insert(current.st);

		// Generar descendiente de girar a la derecha
		nodo hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;
		if (generados.find(hijoTurnR.st) == generados.end()){
			hijoTurnR.secuencia.push_back(actTURN_R);
			pila.push(hijoTurnR);

		}

		// Generar descendiente de girar a la izquierda
		nodo hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;
		if (generados.find(hijoTurnL.st) == generados.end()){
			hijoTurnL.secuencia.push_back(actTURN_L);
			pila.push(hijoTurnL);
		}

		// Generar descendiente de avanzar
		nodo hijoForward = current;
		if (!HayObstaculoDelante(hijoForward.st)){
			if (generados.find(hijoForward.st) == generados.end()){
				hijoForward.secuencia.push_back(actFORWARD);
				pila.push(hijoForward);
			}
		}

		// Tomo el siguiente valor de la pila
		if (!pila.empty()){
			current = pila.top();
		}
	}

  cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna){
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else {
		cout << "No encontrado plan\n";
	}


	return false;
}

// ------ Algunos métodos útiles -------------------------------

/**
 * @brief Comprobar si el estado está en el destino
 * @param st: estado a comprobar
 * @param destino: estado de destino (se ignorará la orientación)
 * @return true si se trata del destino, false en caso contrario
 */
bool ComportamientoJugador::esDestino(const estado &st, const estado &destino) const {
	return st.fila == destino.fila and st.columna == destino.columna;
}

// ------ Implementación de la busqueda en anchura -------------

namespace std{
template <> struct hash<estado> {
	typedef estado argument_type;
	typedef std::size_t result_type;
	/**
	 * @brief Función hash para unordered_map con clave estado
	 */
	std::size_t operator()(const estado &id) const noexcept {
		return std::hash<int>()(id.fila ^ (id.columna << 4)
			^ (id.orientacion << 8));
	}
};
}

/**
 * @brief Obtener todos los estados posibles siguientes a partir de uno origen
 * @param origen: estado origen desde el que expandir
 * @return los descendientes alcanzables, un vector de pares de la forma
 * 		{ estado, acción requerida para llegar a ese estado }
 */
vector<pair<estado, Action> > ComportamientoJugador::siguientes(const estado &origen) {
	vector<pair<estado, Action> > siguientes;

	Action actions[] = {actFORWARD, actTURN_R, actTURN_L};

	for ( int i = 0; i < 3; i++ ) {
		estado descendiente = origen;

		descendiente.orientacion = (origen.orientacion + i*(i+1)/2 ) % 4;
		/*
				Nótese que f(i)=i*(i+1)/2 hace f(0)=0, f(1)=1, f(2)=3. Lo usamos
				para poder encapsular el código y no repetir sentencias para cada nodo.
				Esto es porque
					nuevo_hijo.st.orientacion = (nuevo_hijo.st.orientacion + k) % 4;
				donde
						| 0 si la acción es actFORWARD
					k = | 1 si la acción es actTURN_R
						| 3 si la acción es actTURL_L
			*/

		bool push = true;

		if ( i == 0 )
			if ( HayObstaculoDelante(descendiente) )
				push = false;

		if ( push )
			siguientes.push_back(make_pair(descendiente, actions[i]));
	}

	return siguientes;
}

/**
 * @brief Implementación optimizada de la búsqueda en anchura
 * @param origen: estado de origen
 * @param destino: punto de destino
 * @param plan: secuencia de acciones
 * @return true si encuentra un camino, false en caso contrario
 */
bool ComportamientoJugador::pathFinding_Anchura2(const estado &origen, const estado &destino, list<Action> &plan) {
	cout << "Calculando plan en anchura v2\n";
	plan.clear();
	
	queue<estado> frontera;
	frontera.push(origen);

	unordered_map<estado, pair<estado, Action> > viene_de;

	viene_de[origen] = make_pair(origen, actIDLE);
	
	estado actual = frontera.front();

	while ( !frontera.empty() and !esDestino(actual, destino) ) {
		frontera.pop();

		for ( auto siguiente : siguientes(actual) )
			// si no se encuentra en viene_de
			if ( viene_de.find(siguiente.first) == viene_de.end() ) {
				frontera.push(siguiente.first);
				viene_de[siguiente.first] = make_pair(actual, siguiente.second);
			}
		
		if ( !frontera.empty() )
			actual = frontera.front();
	}

	cout << "Terminada la busqueda\n";

	// llegado aquí en viene_de tenemos una estructura que nos permite recuperar
	// el mínimo camino desde el origen
	if ( esDestino(actual, destino) ) {
		cout << "Cargando el plan\n";
		while ( actual != origen ) {
			plan.push_front(viene_de[actual].second);
			actual = viene_de[actual].first;
		}
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);

		return true;
	} else
		return false;
}

/**
 * @brief Primera implementación de la búsqueda en anchura
 * 
 * ESTA NO ES LA IMPLEMENTACIÓN USADA. En el método pathFinding_Anchura2 aparece
 * una implementación alternativa y mucho más eficiente. Véase el PDF adjunto para
 * más detalles sobre esta práctica. @see pathFinding_Anchura2
 * 
 * @param origen: estado de origen
 * @param destino: punto de destino
 * @param plan: secuencia de acciones
 * @return true si encuentra un camino, false en caso contrario
 */
bool ComportamientoJugador::pathFinding_Anchura(const estado &origen, const estado &destino, list<Action> &plan) {
	//Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado,ComparaEstados> generados;	// Lista de Cerrados
	queue<nodo> pila;						// Lista de Abiertos

	nodo current;
	current.st = origen;
	current.secuencia.empty();

	pila.push(current);

	Action actions[] = {actFORWARD, actTURN_R, actTURN_L};

	while (!pila.empty() and !esDestino(current.st, destino)){

		pila.pop();
		generados.insert(current.st);

		// Generar descendientes
		for ( int i = 0; i < 3; i++ ) {
			nodo nuevo_hijo = current;
			nuevo_hijo.st.orientacion = (nuevo_hijo.st.orientacion + i*(i+1)/2 ) % 4;
			/*
					Nótese que f(i)=i*(i+1)/2 hace f(0)=0, f(1)=1, f(2)=3. Lo usamos
					para poder encapsular el código y no repetir sentencias para cada nodo.
					Esto es porque
						nuevo_hijo.st.orientacion = (nuevo_hijo.st.orientacion + k) % 4;
					donde
						    | 0 si la acción es actFORWARD
						k = | 1 si la acción es actTURN_R
						    | 3 si la acción es actTURL_L
				*/

			bool push = true;

			if ( i == 0 )
				if ( HayObstaculoDelante(nuevo_hijo.st) )
					push = false;

			if ( push )
				if ( generados.find(nuevo_hijo.st) == generados.end() ) {
					nuevo_hijo.secuencia.push_back(actions[i]);
					pila.push(nuevo_hijo);
				}
		}

		// Tomo el siguiente valor de la pila
		if (!pila.empty()){
			current = pila.front();
		}
	}

	cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna){
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	} else {
		cout << "No encontrado plan\n";
		return false;
	}
}

// ------ Implementación de la busqueda en costo uniforme ------

/**
 * Struct de estado con información de bikini y zapatillas
 * 
 * Cuando sea necesario calcular el coste, diferenciamos los estados, además
 * de por su posición (fila y columna) y orientación, por si tiene o no bikini
 * o zapatillas
 */
struct estadoBZ {
	estado st;
	bool has_bikini;
	bool has_zapatillas;

	inline bool operator==(const estadoBZ &otro) const {
		return st == otro.st and has_bikini == otro.has_bikini and has_zapatillas == otro.has_zapatillas;
	}

	inline bool operator!=(const estadoBZ &otro) const {
		return !(*this == otro);
	}
};

namespace std {
template <> struct hash<estadoBZ> {
	typedef estado argument_type;
	typedef std::size_t result_type;
	/**
	 * @brief Función hash para unordered_map con clave estadoBZ
	 */
	std::size_t operator()(const estadoBZ &item) const noexcept {
		return std::hash<int>()(item.st.fila ^ (item.st.columna << 4)
			^ (item.st.orientacion << 8) ^ (item.has_bikini << 9)
			^ (item.has_zapatillas << 10));
	}
};
}

/**
 * Struct de estadoBZ usado para la cola con prioridad
 */
struct estadoBZ_prio {
	estadoBZ e;
	/**
	 * Prioridad en cola
	 */
	int c;

	inline bool operator<(const estadoBZ_prio &otro) const {
		return c > otro.c;
	}
};

/**
 * @brief Obtener todos los estados posibles siguientes a partir de uno origen
 * @param origen: estado origen desde el que expandir
 * @return los descendientes alcanzables, un vector de tuplas de la forma
 * 		{ estado, acción requerida para llegar a ese estado, coste de llegar a ese estado }
 */
vector<tuple<estadoBZ, Action, int> > ComportamientoJugador::siguientes_costo(const estadoBZ &origen) {
	vector<tuple<estadoBZ, Action, int> > siguientes;

	Action actions[] = {actFORWARD, actTURN_R, actTURN_L};

	for ( int i = 0; i < 3; i++ ) {
		estadoBZ descendiente = origen;

		descendiente.st.orientacion = (origen.st.orientacion + i*(i+1)/2 ) % 4;
		/*
				Nótese que f(i)=i*(i+1)/2 hace f(0)=0, f(1)=1, f(2)=3. Lo usamos
				para poder encapsular el código y no repetir sentencias para cada nodo.
				Esto es porque
					nuevo_hijo.st.orientacion = (nuevo_hijo.st.orientacion + k) % 4;
				donde
						| 0 si la acción es actFORWARD
					k = | 1 si la acción es actTURN_R
						| 3 si la acción es actTURL_L
			*/

		int costo = 0;
		char celda = mapaResultado[descendiente.st.fila][descendiente.st.columna];

		if		( celda == 'K' )	descendiente.has_bikini = true;
		else if	( celda == 'D' )	descendiente.has_zapatillas = true;

		if		( celda == 'A' )	costo += descendiente.has_bikini ? 10 : 100;
		else if	( celda == 'B' )	costo += descendiente.has_zapatillas ? 5 : 50;
		else if	( celda == 'T' )	costo += 2;
		else if	( celda == 'R' )	costo += 0;	// A* no funciona bien con pesos negativos
		else if ( celda == '?' )	costo += 3;
		else						costo += 1;

		bool push = true;

		if ( i == 0 )
			if ( HayObstaculoDelante(descendiente.st) )
				push = false;

		if ( push )
			siguientes.push_back(make_tuple(descendiente, actions[i], costo));
	}

	return siguientes;
}

/**
 * @brief Implementación optimizada de la búsqueda en costo uniforme
 * @param origen: estado de origen
 * @param destino: punto de destino
 * @param plan: secuencia de acciones
 * @return true si encuentra un camino, false en caso contrario
 */
bool ComportamientoJugador::pathFinding_CostoUniforme2(const estado &origen, const estado &destino, list<Action> &plan) {
	cout << "Calculando plan en costo uniforme v2\n";
	plan.clear();
	
	priority_queue<estadoBZ_prio> frontera;
	estadoBZ inicial;
	inicial.st = origen;
	inicial.has_bikini = has_bikini;
	inicial.has_zapatillas = has_zapatillas;

	frontera.push(estadoBZ_prio{inicial, 0});

	unordered_map<estadoBZ, pair<estadoBZ, Action> > viene_de;
	unordered_map<estadoBZ, double> coste;

	viene_de[inicial] = make_pair(inicial, actIDLE);
	coste[inicial] = 0;
	
	estadoBZ actual = frontera.top().e;

	while ( !frontera.empty() and !esDestino(actual.st, destino) ) {
		frontera.pop();

		for ( auto siguiente : siguientes_costo(actual) ) {
			// calcular nuevo coste
			int nuevo_coste = coste[actual] + std::get<2>(siguiente);
			// añadir si no ha sido añadido o para actualizar el coste
			if ( coste.find(get<0>(siguiente)) == coste.end() or nuevo_coste < coste[get<0>(siguiente)] ) {
				coste[get<0>(siguiente)] = nuevo_coste;
				viene_de[get<0>(siguiente)] = make_pair(actual, get<1>(siguiente));
				frontera.push(estadoBZ_prio{get<0>(siguiente), nuevo_coste});
			}
		}

		if ( !frontera.empty() )
			actual = frontera.top().e;
	}

	cout << "Terminada la busqueda\n";

	// llegado aquí en viene_de tenemos una estructura que nos permite recuperar
	// el mínimo camino desde el origen
	if ( esDestino(actual.st, destino) ) {
		cout << "Cargando el plan\n";
		while ( actual.st != origen ) {
			plan.push_front(viene_de[actual].second);
			actual = viene_de[actual].first;
		}
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);

		return true;
	} else
		return false;
}

/**
 * Nodo para búsqueda por costo uniforme (primera implementación)
 * @see pathFinding_CostoUniforme
 */
struct nodoC {
	estado st;
	unsigned int costo;
	list<Action> secuencia;
	bool has_bikini, has_zapatillas;
	bool operator<(const nodoC &otro) const {
		return costo > otro.costo;
	}
};

/**
 * @brief Primera implementación de la búsqueda en costo uniforme
 * 
 * ESTA NO ES LA IMPLEMENTACIÓN USADA. En el método pathFinding_CostoUniforme2 aparece
 * una implementación alternativa y mucho más eficiente. Véase el PDF adjunto para
 * más detalles sobre esta práctica. @see pathFinding_CostoUniforme2
 * 
 * @param origen: estado de origen
 * @param destino: punto de destino
 * @param plan: secuencia de acciones
 * @return true si encuentra un camino, false en caso contrario
 */
bool ComportamientoJugador::pathFinding_CostoUniforme(const estado &origen, const estado &destino, list<Action> &plan) {
	//Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado,ComparaEstados> generados;	// Lista de Cerrados
	priority_queue<nodoC> pila;				// Lista de Abiertos

	nodoC current;
	current.st = origen;
	current.costo = 0;
	current.secuencia.empty();
	current.has_bikini = has_bikini;
	current.has_zapatillas = has_zapatillas;

	pila.push(current);

	Action actions[] = {actFORWARD, actTURN_R, actTURN_L};

	while (!pila.empty() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){

		pila.pop();
		generados.insert(current.st);

		// generar descendientes
		for ( int i = 0; i < 3; i++ ) {
			nodoC nuevo_hijo = current;
			nuevo_hijo.st.orientacion = (nuevo_hijo.st.orientacion + i*(i+1)/2 ) % 4;
				/*
					Nótese que f(i)=i*(i+1)/2 hace f(0)=0, f(1)=1, f(2)=3. Lo usamos
					para poder encapsular el código y no repetir sentencias para cada nodo.
					Esto es porque
						nuevo_hijo.st.orientacion = (nuevo_hijo.st.orientacion + k) % 4;
					donde
						    | 0 si la acción es actFORWARD
						k = | 1 si la acción es actTURN_R
						    | 3 si la acción es actTURL_L
				*/

			// calcular el costo
			int nuevo_costo = nuevo_hijo.costo;
			char celda = mapaResultado[nuevo_hijo.st.fila][nuevo_hijo.st.columna];

			if		( celda == 'K' )	nuevo_hijo.has_bikini = true;
			else if	( celda == 'D' )	nuevo_hijo.has_zapatillas = true;

			if		( celda == 'A' )	nuevo_costo += nuevo_hijo.has_bikini ? 10 : 100;
			else if	( celda == 'B' )	nuevo_costo += nuevo_hijo.has_zapatillas ? 5 : 50;
			else if	( celda == 'T' )	nuevo_costo += 2;
			else if	( celda == 'R' )	nuevo_costo -= 10;
			else						nuevo_costo += 1;

			if	( nuevo_costo < 0 )		nuevo_hijo.costo = 0;
			else						nuevo_hijo.costo = nuevo_costo;
			
			bool push = true;

			if ( i == 0 )
				if ( HayObstaculoDelante(nuevo_hijo.st) )
					push = false;

			if ( push )
				if ( generados.find(nuevo_hijo.st) == generados.end() ) {
					nuevo_hijo.secuencia.push_back(actions[i]);
					pila.push(nuevo_hijo);
				}
		}

		// Tomo el siguiente valor de la pila
		if (!pila.empty()){
			current = pila.top();
		}
	}

	cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna){
		cout << "Cargando el plan\n";
		cout << "Costo calculado: " << current.costo << endl;
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else {
		cout << "No encontrado plan\n";
	}

	return false;
}

// ------ Implementación del agente reactivo/deliberativo ------

/**
 * @brief Heurística para A*
 * Se trata de la distancia Manhattan entre la posición de ambos estados, es decir,
 * 		d_manhattan( (st1.st.fila, st1.st.columna), (st2.st.fila, st2.st.columna) )
 * @param st1: estado de primer vértice
 * @param st2: estado de segundo vértice
 * @return distancia Manhattan entre st1 y st2, d_manhattan(st1, st2)
 */
inline int ComportamientoJugador::heuristica(const estado &st1, const estado &st2) {
	return abs(st1.fila - st2.fila) + abs(st1.columna - st2.columna);
}

/**
 * @brief Actualizar el mapa visible
 * Además de actualizarlo, guardará la localización de las recargas
 * @param sensores: sensores del juego
 * @return si el mapa ha sido actualizado (ha visto algo nuevo)
 */
bool ComportamientoJugador::actualizarMapa(Sensores sensores) {
	int a = 0;
	int a_f, a_c, b_f, b_c;
	int F = sensores.posF, C = sensores.posC;
	bool mapa_actualizado = false;

	switch (sensores.sentido) {
		case norte:	a_f = 0; a_c = 1; b_f = -1; b_c = -1;	break;
		case sur:	a_f = 0; a_c = -1; b_f = 1; b_c = 1;	break;
		case este:	a_f = 1; a_c = 0; b_f = -1; b_c = 1;	break;
		case oeste:	a_f = -1; a_c = 0; b_f = 1; b_c = -1;
	}

	for (int i = 0; i <=3; i++) {
		for (int j=0; j < 2*i+1; j++) {
			mapa_actualizado = (mapaResultado[F+j*a_f][C+j*a_c] == '?');
			mapaResultado[F+j*a_f][C+j*a_c]= sensores.terreno[a];
			if ( sensores.terreno[a] == 'X' )
				recargas.insert(estado{F+j*a_f, C+j*a_c, -1});
			a++;
		}
		F += b_f; C += b_c;
	}

	return mapa_actualizado;
}

/**
 * @brief Implementación de la búsqueda A*
 * @param origen: estado de origen
 * @param destino: punto de destino
 * @param plan: secuencia de acciones
 * @return true si encuentra un camino, false en caso contrario
 */
bool ComportamientoJugador::pathFinding_AStar(const estado &origen, const estado &destino, list<Action> &plan) {
	cout << "Calculando plan en A*\n";
	plan.clear();
	
	priority_queue<estadoBZ_prio> frontera;
	estadoBZ inicial;
	inicial.st = origen;
	inicial.has_bikini = has_bikini;
	inicial.has_zapatillas = has_zapatillas;

	frontera.push(estadoBZ_prio{inicial, 0});

	unordered_map<estadoBZ, pair<estadoBZ, Action> > viene_de;
	unordered_map<estadoBZ, double> coste;

	viene_de[inicial] = make_pair(inicial, actIDLE);
	coste[inicial] = 0;
	
	estadoBZ actual = frontera.top().e;

	while ( !frontera.empty() and !esDestino(actual.st, destino) ) {
		frontera.pop();

		for ( auto siguiente : siguientes_costo(actual) ) {
			// calcular nuevo coste (aquí lo llamamos g)
			int g = coste[actual] + /*mapaResultado.size()/20**/std::get<2>(siguiente);
			// añadir si no ha sido añadido o para actualizar el coste
			if ( coste.find(get<0>(siguiente)) == coste.end() or g < coste[get<0>(siguiente)] ) {
				coste[get<0>(siguiente)] = g;
				int f = g + heuristica(get<0>(siguiente).st, destino);
				viene_de[get<0>(siguiente)] = make_pair(actual, get<1>(siguiente));
				frontera.push(estadoBZ_prio{get<0>(siguiente), f});
			}
		}

		if ( !frontera.empty() )
			actual = frontera.top().e;
	}

	cout << "Terminada la busqueda\n";

	// llegado aquí en viene_de tenemos una estructura que nos permite recuperar
	// el mínimo camino desde el origen
	if ( esDestino(actual.st, destino) ) {
		cout << "Cargando el plan\n";
		while ( actual.st != origen ) {
			plan.push_front(viene_de[actual].second);
			actual = viene_de[actual].first;
		}
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);

		return true;
	} else
		return false;
}


// Sacar por la términal la secuencia del plan obtenido
void ComportamientoJugador::PintaPlan(list<Action> plan) {
	auto it = plan.begin();
	while (it!=plan.end()){
		if (*it == actFORWARD){
			cout << "A ";
		}
		else if (*it == actTURN_R){
			cout << "D ";
		}
		else if (*it == actTURN_L){
			cout << "I ";
		}
		else {
			cout << "- ";
		}
		it++;
	}
	cout << endl;
}



void AnularMatriz(vector<vector<unsigned char> > &m){
	for (int i=0; i<m[0].size(); i++){
		for (int j=0; j<m.size(); j++){
			m[i][j]=0;
		}
	}
}


// Pinta sobre el mapa del juego el plan obtenido
void ComportamientoJugador::VisualizaPlan(const estado &st, const list<Action> &plan){
  AnularMatriz(mapaConPlan);
	estado cst = st;

	auto it = plan.begin();
	while (it!=plan.end()){
		if (*it == actFORWARD){
			switch (cst.orientacion) {
				case 0: cst.fila--; break;
				case 1: cst.columna++; break;
				case 2: cst.fila++; break;
				case 3: cst.columna--; break;
			}
			mapaConPlan[cst.fila][cst.columna]=1;
		}
		else if (*it == actTURN_R){
			cst.orientacion = (cst.orientacion+1)%4;
		}
		else if (*it == actTURN_L){
			cst.orientacion = (cst.orientacion+3)%4;
		}
		it++;
	}
}



int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}
