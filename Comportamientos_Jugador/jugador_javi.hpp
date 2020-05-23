#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"

#include <list>

struct estado {
  int fila;
  int columna;
  int orientacion;
};



class ComportamientoJugador : public Comportamiento {
  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size) {
      // Inicializar Variables de Estado
      fil = col = 99;
      brujula = 0; // 0: Norte, 1:Este, 2:Sur, 3:Oeste
      destino.fila = -1;
      destino.columna = -1;
      destino.orientacion = -1;
      hayplan=false;
      cambio=false;
      ultimafila= -1;
      ultimacolumna=-1;
      ultimaorientacion=-1;
    }
    ComportamientoJugador(std::vector< std::vector< unsigned char> > mapaR) : Comportamiento(mapaR) {
      // Inicializar Variables de Estado
      fil = col = 99;
      brujula = 0; // 0: Norte, 1:Este, 2:Sur, 3:Oeste
      destino.fila = -1;
      destino.columna = -1;
      destino.orientacion = -1;
      hayplan=false;
      cambio = false;
      ultimafila= -1;
      ultimacolumna=-1;
      ultimaorientacion=-1;
    }
    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);
    void VisualizaPlan(const estado &st, const list<Action> &plan);
    ComportamientoJugador * clone(){return new ComportamientoJugador(*this);}

  private:
    // Declarar Variables de Estado
    int fil, col, brujula;
    estado actual, destino;
    list<Action> plan;
    bool cambio;
    int ultimafila, ultimacolumna, ultimaorientacion;
    bool hayplan;
    void hacermaparesultadonorte(Sensores sensores);
    void hacermaparesultadoeste(Sensores sensores);
    void hacermaparesultadooeste(Sensores sensores);
    void hacermaparesultadosur(Sensores sensores);
    // Métodos privados de la clase
    bool pathFinding(int level, const estado &origen, const estado &destino, list<Action> &plan);
    bool pathFinding_Profundidad(const estado &origen, const estado &destino, list<Action> &plan);
    bool pathFinding_Anchura(const estado &origen, const estado &destino, list<Action> &plan);
    bool pathFinding_coste_uniforme(const estado &origen, const estado &destino, list<Action> &plan);
    bool pathFinding_a_estrella(const estado &origen, const estado &destino, list<Action> &plan);

    int ManhattanCalculo(const estado &estado1, const estado &estado_llegada);
    int obtenerValorPosicion(const estado &stado);
    int calcularcaminocompleto(const estado &estado1, const estado &origen, const estado &fin);
    int Decision_bateria(const estado &estado1, const estado &estado_llegada, const estado &estado_bateria);

    void PintaPlan(list<Action> plan);
    bool HayObstaculoDelante(estado &st);


};

#endif
