#ifndef _HORNO_H
#define _HORNO_H

#include <iostream>
#include <string.h>
#include <math.h>
#include "Matriz.h"

using namespace std;

class Horno{
	//friend ostream& operator<<(ostream&, const Matriz&);
    public:
        /* Constructor */
        Horno(int radio = 1, int angulos = 4, int radios = 5, int tint = 5000, int text = 30, long double k = 1, long double h = 0.05, int* radiosLimite = NULL);
        /* interfaz */

        int getRadio();
        int getCantidadAngulos();
        int getCantidadRadios();
        int getTi();
        int getTinf();
        long double getK();
        long double getH();
        int getBordeInterno(int angulo);

        void operator=(const Horno &h1);
		/* Destructor */
        ~Horno();
    private:
        Matriz* temperaturas;       //temperatura en cada punto discretizado del horno
        int rad;                    //radio del horno desde el centro al borde exterior
        int angs;                   //angulos en los que se divide el horno
        int rads;                   //cantidad de radios por angulo
        long double deltaR;         //delta Radio
        long double deltaT;         //delta Theeta
        int ti;                     //temperatura interior
        int tinf;                   //temperatura en el infinito
        long double k;              //constante k
        long double h;              //constante h
        int *bordeInterno;          //borde interno del horno.
};

#endif /*_HORNO_H*/
