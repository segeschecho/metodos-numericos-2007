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
        Horno(){temperaturas = NULL; bordeInterno = NULL;}
        Horno(int radio, int angulos, int radios, int tint, int text, long double k, long double h, int* radiosLimite);

        /* interfaz */
		void cargar(istream& archivo);
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
//    private:
		//Atributos
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

		//Metodos privados
		void calcular_temperaturas(void);
};

#endif /*_HORNO_H*/
