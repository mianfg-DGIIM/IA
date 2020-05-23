#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"

#include <list>
#include <set>

#define MAX_ESPERA_ALDEANO 3
#define B_I 50	//WIP a lo mejor bajar un poco este índice y aumentar lo que recarga de una vez...
#define B_S 1000	// antes 1500->111
#define K_CERCANIA 7.5
#define CANTIDAD_RECARGA 15

struct estado {
	int fila;
	int columna;
	int orientacion;

	// he AÑADIDO la sobrecarga de los operadores ==, != y <, pues es necesaria
	// para algunas de las operaciones con las estructuras de datos usadas
	inline bool operator==(const estado &otro) const {
		return fila == otro.fila and columna == otro.columna and orientacion == otro.orientacion;
	}
	inline bool operator!=(const estado &otro) const {
		return !(*this == otro);
	}
	inline bool operator<(const estado &otro) const {
		if ((fila < otro.fila) or (fila == otro.fila and columna < otro.columna) or
	      (fila == otro.fila and columna == otro.columna and orientacion < otro.orientacion))
			return true;
		else
			return false; 
	}
};

// he AÑADIDO structs adicionales. Ver su especificación en jugador.cpp
struct estadoBZ;
struct estadoBZ_prio;

class ComportamientoJugador : public Comportamiento {
public:
	ComportamientoJugador(unsigned int size) : Comportamiento(size) {
		// Inicializar Variables de Estado
		fil = col = 99;
		brujula = 0; // 0: Norte, 1:Este, 2:Sur, 3:Oeste
		destino.fila = -1;
		destino.columna = -1;
		destino.orientacion = -1;
		hayplan = false;
	}
	ComportamientoJugador(std::vector<std::vector<unsigned char>> mapaR) : Comportamiento(mapaR) {
		// Inicializar Variables de Estado
		fil = col = 99;
		brujula = 0; // 0: Norte, 1:Este, 2:Sur, 3:Oeste
		destino.fila = -1;
		destino.columna = -1;
		destino.orientacion = -1;
		hayplan = false;

		has_bikini = false;
		has_zapatillas = false;

		loc_aldeano_delante = estado{-1, -1, -1};

		aRecarga = false;
		limRecarga = 10;


		esperando_aldeano = 0;
	}
	ComportamientoJugador(const ComportamientoJugador &comport) : Comportamiento(comport) {}
	~ComportamientoJugador() {}

	Action think(Sensores sensores);
	int interact(Action accion, int valor);
	void VisualizaPlan(const estado &st, const list<Action> &plan);
	ComportamientoJugador *clone() { return new ComportamientoJugador(*this); }

private:
	// Declarar Variables de Estado
	int fil, col, brujula;
	estado actual, destino;
	list<Action> plan;
	bool hayplan;

	bool has_bikini, has_zapatillas;
	estado loc_aldeano_delante;

	bool aRecarga;
	int limRecarga;

	set<estado> recargas; 

	int esperando_aldeano;


	// Métodos privados de la clase
	bool pathFinding(int level, const estado &origen, const estado &destino, list<Action> &plan);
	bool pathFinding_Profundidad(const estado &origen, const estado &destino, list<Action> &plan);
	bool pathFinding_Anchura(const estado &origen, const estado &destino, list<Action> &plan);
	bool pathFinding_CostoUniforme(const estado &origen, const estado &destino, list<Action> &plan);
	bool pathFinding_Anchura2(const estado &origen, const estado &destino, list<Action> &plan);
	bool pathFinding_CostoUniforme2(const estado &origen, const estado &destino, list<Action> &plan);
	bool pathFinding_AStar(const estado &origen, const estado &destino, list<Action> &plan);

	vector<pair<estado, Action> > siguientes(const estado &origen);
	vector<tuple<estadoBZ, Action, int> > siguientes_costo(const estadoBZ &origen);
	bool esDestino(const estado &st, const estado &destino) const;
	
	int heuristica(const estado &st1, const estado &st2);
	bool actualizarMapa(Sensores sensores);
	
	void PintaPlan(list<Action> plan);
	bool HayObstaculoDelante(estado &st);
};

#endif
