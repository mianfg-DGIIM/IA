#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"

#include <list>
#include <set>

#define K_DESTINO 2
#define K_CERCANIA 7
#define TIEMPO_RECARGA_INMEDIATA 300

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

		has_bikini = false;
		has_zapatillas = false;

		loc_aldeano_delante = estado{-1, -1, -1};

		aRecarga = false;
		ultimo_recarga = false;

		/* MEJORA 2. Recargas */
		b_i = mapaResultado.size()*7;
		b_s = 1000;
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
		ultimo_recarga = false;

		/* MEJORA 2. Recargas */
		b_i = mapaResultado.size()*7;
		b_s = 1000;
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
	estado siguiente;

	int b_i, b_s;

	bool aRecarga;
	bool ultimo_recarga;

	set<estado> recargas;
	set<estado> bikinis, zapatillas;


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
	int peso(const char &celda) const;
	bool actualizarMapa(Sensores sensores);
	
	void PintaPlan(list<Action> plan);
	bool HayObstaculoDelante(estado &st);
};

#endif
