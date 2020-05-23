#include "../Comportamientos_Jugador/jugador.hpp"
#include "motorlib/util.h"

#include <iostream>
#include <cmath>
#include <set>
#include <stack>
#include <queue>
#include <vector>
#include <assert.h>
#include <thread>
#include <chrono>


static int recargado = 0;
static bool bikini_encontrado = false, zapatilla_encontrado = false, bateria_encontrada=false, tiene_bikini = false;
static bool he_cargado = false, camino_aux=false, tiene_zapatilla = false,  yendo_bikini=false, yendo_bateria = false, yendo_zapatilla = false;
static estado aux, bikini,zapatilla, bateria, actual;



//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************
void ComportamientoJugador::hacermaparesultadonorte(Sensores sensores){

    int pos_salidaF = sensores.posF, pos_salidaC = sensores.posC, auxF, auxC;
    int num_iteraciones = 3, cont = 0, cont2, total = 1;
    while(cont < 3){

        pos_salidaF--;
        pos_salidaC--;
        auxF = pos_salidaF;
        auxC = pos_salidaC;
        cont2 = 0;
        while(cont2 < num_iteraciones){
            if(sensores.terreno[total] == 'K' && !bikini_encontrado){

                bikini_encontrado = true;
                bikini.columna = auxC;
                bikini.fila = auxF;

            }
            if(sensores.terreno[total] == 'D' && !zapatilla_encontrado){

                zapatilla_encontrado = true;
                zapatilla.columna = auxC;
                zapatilla.fila = auxF;

            }
            if(sensores.terreno[total] == 'X'){

                bateria_encontrada = true;
                bateria.columna = auxC;
                bateria.fila = auxF;

            }
            mapaResultado[auxF][auxC]=sensores.terreno[total];
            total++;
            auxC++;
            cont2++;

        }

        num_iteraciones += 2;
        cont++;
    }

}

void ComportamientoJugador::hacermaparesultadoeste(Sensores sensores){

    int pos_salidaF = sensores.posF, pos_salidaC = sensores.posC, auxF, auxC;
    int num_iteraciones = 3, cont = 0, cont2, total = 1;
    while(cont < 3){

        pos_salidaF--;
        pos_salidaC++;
        auxF = pos_salidaF;
        auxC = pos_salidaC;
        cont2 = 0;
        while(cont2 < num_iteraciones){
            if(sensores.terreno[total] == 'K' && !bikini_encontrado){

                bikini_encontrado = true;
                bikini.columna = auxC;
                bikini.fila = auxF;

            }
            if(sensores.terreno[total] == 'D' && !zapatilla_encontrado){

                zapatilla_encontrado = true;
                zapatilla.columna = auxC;
                zapatilla.fila = auxF;

            }
            if(sensores.terreno[total] == 'X'){

                bateria_encontrada = true;
                bateria.columna = auxC;
                bateria.fila = auxF;

            }
            mapaResultado[auxF][auxC]=sensores.terreno[total];
            total++;
            auxF++;
            cont2++;

        }

        num_iteraciones += 2;
        cont++;
    }

}

void ComportamientoJugador::hacermaparesultadooeste(Sensores sensores){

    int pos_salidaF = sensores.posF, pos_salidaC = sensores.posC, auxF, auxC;
    int num_iteraciones = 3, cont = 0, cont2, total = 1;
    while(cont < 3){

        pos_salidaF++;
        pos_salidaC--;
        auxF = pos_salidaF;
        auxC = pos_salidaC;
        cont2 = 0;
        while(cont2 < num_iteraciones){
            if(sensores.terreno[total] == 'K' && !bikini_encontrado){

                bikini_encontrado = true;
                bikini.columna = auxC;
                bikini.fila = auxF;

            }
            if(sensores.terreno[total] == 'D' && !zapatilla_encontrado){

                zapatilla_encontrado = true;
                zapatilla.columna = auxC;
                zapatilla.fila = auxF;

            }
            if(sensores.terreno[total] == 'X'){

                bateria_encontrada = true;
                bateria.columna = auxC;
                bateria.fila = auxF;

            }
            mapaResultado[auxF][auxC]=sensores.terreno[total];
            total++;
            auxF--;
            cont2++;

        }

        num_iteraciones += 2;
        cont++;
    }

}

void ComportamientoJugador::hacermaparesultadosur(Sensores sensores){

    int pos_salidaF = sensores.posF, pos_salidaC = sensores.posC, auxF, auxC;
    int num_iteraciones = 3, cont = 0, cont2, total = 1;
    while(cont < 3){

        pos_salidaF++;
        pos_salidaC++;
        auxF = pos_salidaF;
        auxC = pos_salidaC;
        cont2 = 0;
        while(cont2 < num_iteraciones){
            if(sensores.terreno[total] == 'K' && !bikini_encontrado){

                bikini_encontrado = true;
                bikini.columna = auxC;
                bikini.fila = auxF;

            }
            if(sensores.terreno[total] == 'D' && !zapatilla_encontrado){

                zapatilla_encontrado = true;
                zapatilla.columna = auxC;
                zapatilla.fila = auxF;

            }
            if(sensores.terreno[total] == 'X'){

                bateria_encontrada = true;
                bateria.columna = auxC;
                bateria.fila = auxF;

            }
            mapaResultado[auxF][auxC]=sensores.terreno[total];
            total++;
            auxC--;
            cont2++;

        }

        num_iteraciones += 2;
        cont++;
    }

}

int ComportamientoJugador::Decision_bateria(const estado &estado1, const estado &estado_llegada, const estado &estado_bateria){

    int dist_bateria = (abs(estado1.fila - estado_bateria.fila) + abs(estado1.columna - estado_bateria.columna));
    int dist_destino = (abs(estado1.fila - estado_llegada.fila) + abs(estado1.columna - estado_llegada.columna));

    if(dist_bateria < dist_destino){

        return 1;

    }else{

        return 0;

    }

}




// Este es el método principal que debe contener los 4 Comportamientos_Jugador
// que se piden en la práctica. Tiene como entrada la información de los
// sensores y devuelve la acción a realizar.
Action ComportamientoJugador::think(Sensores sensores) {
	Action accion = actIDLE;

    mapaResultado[sensores.posF][sensores.posC] = sensores.terreno[0];
    switch (sensores.sentido){

        case norte:
            hacermaparesultadonorte(sensores);
        break;
        case este:
            hacermaparesultadoeste(sensores);
        break;
        case sur:
            hacermaparesultadosur(sensores);
        break;
        case oeste:
            hacermaparesultadooeste(sensores);
        break;

    }

        actual.fila        = sensores.posF;
        actual.columna     = sensores.posC;
        actual.orientacion = sensores.sentido;

        cout << "Fila: " << actual.fila << endl;
        cout << "Col : " << actual.columna << endl;
        cout << "Ori : " << actual.orientacion << endl;

        destino.fila       = sensores.destinoF;
        destino.columna    = sensores.destinoC;


    if(cambio){

        if(sensores.terreno[2]=='P' or sensores.terreno[2]=='M' or sensores.superficie[2]=='a'){

            accion = actTURN_R;


        }else{

            cambio = false;
            accion = actFORWARD;

        }

        return accion;

    }


    //----------------------------------------bikini y zapatilla
    /*
    if(sensores.posC == bikini_columna && sensores.posF == bikini_fila && !tiene_bikini && veo_ambas){

        tiene_bikini= true;
        hayplan=false;

    }

    if(sensores.posC == zapatilla_columna && sensores.posF == zapatilla_fila && !tiene_zapatilla && veo_ambas){

        tiene_zapatilla= true;
        hayplan=false;

    }

    if(bikini_encontrado && !tiene_bikini && !tiene_zapatilla && zapatilla_encontrado){

        veo_ambas=true;
        zapatilla_encontrado = false;
        aux = destino;
        bikini_temporal.fila = bikini_fila;
        bikini_temporal.columna = bikini_columna;
        destino.fila = zapatilla_fila;
        destino.columna = zapatilla_columna;
        hayplan = false;
        camino_aux= true;

    }

    if(camino_aux && tiene_zapatilla && !tiene_bikini && bikini_encontrado && veo_ambas){

        destino.fila       = bikini_temporal.fila;
        destino.columna    = bikini_temporal.columna;

    }

    if(camino_aux && tiene_zapatilla && tiene_bikini && veo_ambas){

        destino.fila       = aux.fila;
        destino.columna    = aux.columna;
        veo_ambas=false;
        camino_aux = false;

    }

*/
    //----------------------------------------bikini y zapatilla

    //----------------------------------------bateria

    if(sensores.posC == bateria.columna && sensores.posF == bateria.fila && !he_cargado){

        while(recargado < 80 && sensores.bateria < 2700 &&  sensores.vida > 300){

            recargado++;
            return actTURN_R;

        }
        recargado = 0;
        he_cargado=true;
        //destino=aux;
        hayplan=false;
        yendo_bateria = false;

    }



    actual.fila = sensores.posF;
    actual.columna = sensores.posC;
    if((!yendo_bikini && !yendo_zapatilla && bateria_encontrada && ((sensores.bateria < 1800 && Decision_bateria(actual, destino, bateria)== 1) || (sensores.bateria < 1300))) && sensores.vida > 300){
        aux = destino;
        destino.fila = bateria.fila;
        destino.columna = bateria.columna;
        hayplan = false;
        camino_aux= true;
        yendo_bateria = true;
        he_cargado=false;

    }


    if(camino_aux && he_cargado && !hayplan ){

        destino.fila       = aux.fila;
        destino.columna    = aux.columna;
        he_cargado=false;
        yendo_bateria = false;
        camino_aux=false;

    }


    //----------------------------------------------bateria


    //----------------------------------------bikini
    if(sensores.posC == bikini.columna && sensores.posF == bikini.fila && !tiene_bikini ){

        tiene_bikini= true;
        hayplan=false;
        yendo_bikini = false;

    }


    if((bikini_encontrado && !tiene_bikini && tiene_zapatilla) || (bikini_encontrado && !tiene_bikini && !zapatilla_encontrado )){

        bikini_encontrado = false;
        aux = destino;
        destino.fila = bikini.fila;
        destino.columna = bikini.columna;
        hayplan = false;
        camino_aux= true;
        yendo_bikini = true;

    }





    if(camino_aux && tiene_bikini && !hayplan && !yendo_bateria && !yendo_zapatilla ){

        destino.fila       = aux.fila;
        destino.columna    = aux.columna;
        camino_aux=false;

    }

    //----------------------------------------------bikini

    //----------------------------------------------zapatillas
    if(sensores.posC == zapatilla.columna && sensores.posF == zapatilla.fila && !tiene_zapatilla ){

        tiene_zapatilla= true;
        yendo_zapatilla = false;
        hayplan=false;

    }

    if((zapatilla_encontrado && !tiene_zapatilla && tiene_bikini ) || (zapatilla_encontrado && !tiene_zapatilla && !bikini_encontrado ) ){

        zapatilla_encontrado = false;
        aux = destino;
        destino.fila = zapatilla.fila;
        destino.columna = zapatilla.columna;
        hayplan = false;
        camino_aux= true;
        yendo_zapatilla = true;

    }


    if(camino_aux && tiene_zapatilla && !hayplan && !yendo_bikini && !yendo_bateria){

        destino.fila       = aux.fila;
        destino.columna    = aux.columna;
        camino_aux=false;

    }

    //---------------------------------------------zapatillas


	if(!hayplan ){
        hayplan = pathFinding (sensores.nivel, actual, destino, plan);
	}

	if(hayplan){

        if(sensores.nivel == 4){

            if((sensores.terreno[2]=='P' or sensores.terreno[2]=='M' ) and (plan.front()==actFORWARD)){

                hayplan = pathFinding (sensores.nivel, actual, destino, plan);
                accion=plan.front();
                plan.erase(plan.begin());

            }else if(sensores.superficie[2]=='a' and plan.front()==actFORWARD){

                hayplan = false;
                cambio = true;
                return actTURN_R;

            }else{

                accion = plan.front();
                plan.erase(plan.begin());

            }

        }else{

            accion = plan.front();
            plan.erase(plan.begin());

        }

	}

    if(destino.fila == actual.fila && destino.columna == actual.columna){

        accion = actIDLE;
        hayplan=false;

    }

    if (ultimafila==actual.fila && ultimaorientacion== actual.orientacion && ultimacolumna==actual.columna && actual.fila!=destino.fila){

        hayplan = false;

    }else{

        ultimafila=actual.fila;
        ultimaorientacion= actual.orientacion;
        ultimacolumna=actual.columna;

    }

    return accion;
}


// Llama al algoritmo de busqueda que se usará en cada comportamiento del agente
// Level representa el comportamiento en el que fue iniciado el agente.
bool ComportamientoJugador::pathFinding (int level, const estado &origen, const estado &destino, list<Action> &plan){
	switch (level){
		case 1: cout << "Busqueda en profundad\n";
			      return pathFinding_Profundidad(origen,destino,plan);
						break;
		case 2: cout << "Busqueda en Anchura\n";
			      return pathFinding_Anchura(origen,destino,plan);
						break;
		case 3: cout << "Busqueda Costo Uniforme\n";
                    return pathFinding_coste_uniforme(origen,destino, plan);
						break;
		case 4: cout << "Busqueda para el reto\n";
                    return pathFinding_a_estrella(origen, destino, plan);
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
	int costo;
	int sumacaminos = 0;
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


// Implementación de la búsqueda en profundidad.
// Entran los puntos origen y destino y devuelve la
// secuencia de acciones en plan, una lista de acciones.
bool ComportamientoJugador::pathFinding_Anchura(const estado &origen, const estado &destino, list<Action> &plan) {
	//Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado,ComparaEstados> generados; // Lista de Cerrados
	queue<nodo> cola;											// Lista de Abiertos

  nodo current;
	current.st = origen;
	current.secuencia.empty();

	cola.push(current);

  while (!cola.empty() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){

		cola.pop();
		generados.insert(current.st);



		// Generar descendiente de girar a la derecha
		nodo hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;
		if (generados.find(hijoTurnR.st) == generados.end()){
			hijoTurnR.secuencia.push_back(actTURN_R);
			cola.push(hijoTurnR);

		}

		// Generar descendiente de girar a la izquierda
		nodo hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;
		if (generados.find(hijoTurnL.st) == generados.end()){
			hijoTurnL.secuencia.push_back(actTURN_L);
			cola.push(hijoTurnL);
		}

		// Generar descendiente de avanzar
		nodo hijoForward = current;
		if (!HayObstaculoDelante(hijoForward.st)){
			if (generados.find(hijoForward.st) == generados.end()){
				hijoForward.secuencia.push_back(actFORWARD);
				cola.push(hijoForward);
			}
		}

		// Tomo el siguiente valor de la pila
		if (!cola.empty()){
			current = cola.front();
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

bool operator< (const nodo &nodo1, const nodo & nodo2) {   // sobrecarga operador ==
    if(nodo1.sumacaminos == nodo2.sumacaminos){

        return (nodo1.costo > nodo2.costo);

    }else{

        return (nodo1.sumacaminos > nodo2.sumacaminos);

    }


  }


int ComportamientoJugador::obtenerValorPosicion(const estado &stado){
	int res = 1;
	int fil = stado.fila;
	int col = stado.columna;
	unsigned char contenido_casilla;

	contenido_casilla = mapaResultado[fil][col];

	if(contenido_casilla == 'T')
		res = 2;
	else if(contenido_casilla == 'B')
		res = 50;
	else if(contenido_casilla == 'A')
		res = 100;
	else
		res = 1;
	return res;
}




// Implementación de la búsqueda en profundidad.
// Entran los puntos origen y destino y devuelve la
// secuencia de acciones en plan, una lista de acciones.
bool ComportamientoJugador::pathFinding_coste_uniforme(const estado &origen, const estado &destino, list<Action> &plan  ) {

	//Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado,ComparaEstados> generados; // Lista de Cerrados
	priority_queue<nodo> colap;

    nodo current;
	current.st = origen;
	current.costo=0;
	current.secuencia.empty();
	colap.push(current);


  while (!colap.empty() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){
		colap.pop();
		generados.insert(current.st);


		// Generar descendiente de girar a la derecha
		nodo hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;

		if ( generados.find(hijoTurnR.st) == generados.end()){

                hijoTurnR.secuencia.push_back(actTURN_R);
                hijoTurnR.costo += 1;
                colap.push(hijoTurnR);



		}


		// Generar descendiente de girar a la izquierda
		nodo hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;
		if ( generados.find(hijoTurnL.st) == generados.end()){
            hijoTurnL.costo += 1;
            hijoTurnL.secuencia.push_back(actTURN_L);
            colap.push(hijoTurnL);

		}


		// Generar descendiente de avanzar
		nodo hijoForward = current;
		if (!HayObstaculoDelante(hijoForward.st) && generados.find(hijoForward.st) == generados.end()){
            hijoForward.costo = hijoForward.costo + obtenerValorPosicion(hijoForward.st);
            hijoForward.secuencia.push_back(actFORWARD);
            colap.push(hijoForward);


		}


		// Tomo el siguiente valor de la pila
		if (!colap.empty()){
			current = colap.top();
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

int ComportamientoJugador::ManhattanCalculo(const estado &estado1, const estado &estado_llegada){

    int cuenta = (abs(estado1.fila - estado_llegada.fila) + abs(estado1.columna - estado_llegada.columna));

	return cuenta;

}

int ComportamientoJugador::calcularcaminocompleto(const estado &estado1, const estado &origen, const estado &fin){

    int hasta_origen = ManhattanCalculo(estado1, origen);
    int hasta_fin = ManhattanCalculo(estado1, fin);
    int total = (hasta_fin+hasta_origen);
	return total;

}



bool ComportamientoJugador::pathFinding_a_estrella(const estado &origen, const estado &destino, list<Action> &plan){
	//Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado,ComparaEstados> generados; // Lista de Cerrados
	priority_queue<nodo> cola;	// Lista de abiertos

	nodo current;
	current.st = origen;
	current.secuencia.empty();
	current.sumacaminos = calcularcaminocompleto(current.st, origen, destino);

	cola.push(current);

	while (!cola.empty() && (current.st.fila!=destino.fila or current.st.columna != destino.columna)){

		cola.pop();
		generados.insert(current.st);

		// Generar descendiente de girar a la derecha
		nodo hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;
		if (generados.find(hijoTurnR.st) == generados.end()){
            hijoTurnR.costo = current.costo + 1;
            hijoTurnR.sumacaminos =  calcularcaminocompleto(hijoTurnR.st, origen, destino);
			hijoTurnR.secuencia.push_back(actTURN_R);
			cola.push(hijoTurnR);
		}



		// Generar descendiente de girar a la izquierda
		nodo hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;
		if (generados.find(hijoTurnL.st) == generados.end()){
            hijoTurnL.costo = current.costo + 1;
            hijoTurnL.sumacaminos = calcularcaminocompleto(hijoTurnL.st, origen, destino);
			hijoTurnL.secuencia.push_back(actTURN_L);
			cola.push(hijoTurnL);
		}


        // Generar descendiente de avanzar
		nodo hijoForward = current;
		if(!HayObstaculoDelante(hijoForward.st) && generados.find(hijoForward.st) == generados.end()){ 	// El find devuelve end si el elemento no estÃ¡ en el conjunto
			hijoForward.costo +=obtenerValorPosicion(hijoForward.st);
			hijoForward.sumacaminos = calcularcaminocompleto(hijoForward.st, origen, destino);
			hijoForward.secuencia.push_back(actFORWARD);
			cola.push(hijoForward);


		}

		// Tomo el siguiente valor del set
		if (!cola.empty()){
			current = cola.top();
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
		else {
			cst.orientacion = (cst.orientacion+3)%4;
		}
		it++;
	}
}



int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}
