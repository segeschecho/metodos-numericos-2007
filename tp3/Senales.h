#ifndef _SENALES_H
#define _SENALES_H

#include <iostream>
#include <string.h>
#include <assert.h>
#include "Matriz.h"
using namespace std;

class Senales{
  public:
    Senales(){D = NULL;}
    Senales(unsigned int dimImagen, unsigned int metodo, long double puntos1[][2], long double puntos2[][2], unsigned int cantSenales);
    Senales(Senales& s);

    const Matriz& MatrizSenales(void);
    ~Senales(){delete D;}

  private:
    Matriz* D;

    //toma los arreglos pendientes y puntos, y los combina elemento a elemento
    void metodo1(unsigned int dimension, long double puntos1[][2], long double puntos2[][2], unsigned int n);

    //Toma una pendiente, un punto de pase para generar una recta
    //una matriz, un n que representa la dimension de la matriz
    //imagen y el numero de la matriz a llenar
    void tirarSenal(long double x1, long double y1, long double x2, long double y2, int filaALlenar);

    //ordena un vector de tuplas por su primer componente
    void ordenarPares(long double pares[][2], int filas);

    //recorre el vector de pares de coordenadas y anula los
    //repetidos poniendo un -1 en la coordenada x, indicando que
    //esta repetida.
    void anularRepetidos(long double pares[][2], int cantPares);
};

#endif /*_SENALES_H*/
