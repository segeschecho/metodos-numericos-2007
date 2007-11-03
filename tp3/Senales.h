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
    Senales(unsigned int dimension, unsigned int metodo);//, long double puntos1[][2], long double puntos2[][2], unsigned int cantSenales);
    Senales(Senales& s);

    //hace un txt para graficar el metodo, enviado por parametro, en matlab
    void realizarTomografia(Matriz& velocidades, unsigned int factorRuido);
    void prepararParaGraficarMetodo(ostream & os, int metodo);
    const Matriz& matrizSenales(void);
    ~Senales(){delete D;}

  private:
    unsigned int dimension;
    unsigned int numSenales;
    Matriz* D;

    //toma los arreglos pendientes y puntos, y los combina elemento a elemento
//    void metodo1(unsigned int dimension, long double puntos1[][2], long double puntos2[][2], unsigned int n);

    //tira se�ales primero desde la pared izquierda hacia las demas
    //y despues desde la pared derecha hacia las demas
    void metodo1(void);

    //similar que el metodo uno solo que por cada se�al enviada se desplaza
    //el punto de pase.
    void metodo2(void);


    //Toma una pendiente, un punto de pase para generar una recta
    //una matriz, un n que representa la dimension de la matriz
    //imagen y el numero de la matriz a llenar
    void tirarSenal(long double x1, long double y1, long double x2, long double y2, int filaALlenar);

    //ordena un vector de tuplas por su primer componente de menor a mayor
    void ordenarParesMenorAMayor(long double** pares, int filas);

    //ordena un vector de tuplas por su primer componente de mayor a menor
    void ordenarParesMayorAMenor(long double** pares, int filas);

    //recorre el vector de pares de coordenadas y anula los
    //repetidos poniendo un -1 en la coordenada x, indicando que
    //esta repetida.
    void anularRepetidos(long double** pares, int cantPares);

    void graficarMetodo1(ostream & os);
};

#endif /*_SENALES_H*/
