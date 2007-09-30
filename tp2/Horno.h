#ifndef _HORNO_H
#define _HORNO_H

#include <iostream>
#include <string.h>
#include <math.h>
#include "Matriz.h"

#define PI 3.1415926535897932484626433832795

using namespace std;

class Horno{
	friend void cargar(istream& archivo, Horno &h);
	friend void guardarParaGrafico(ostream &out, const Horno &h);
    public:
        /* Constructor */
		Horno(){temperaturas = NULL; bordeInterno = NULL;}
        Horno(int radio, int angulos, int radios, int tint, int text, long double k, long double h, int* radiosLimite);

        /* interfaz */
		long double		getTemperatura(long double radio, long double theeta) const;
        long double     getRadio() const;
        int             getCantidadAngulos() const;
        int             getCantidadRadios() const;
        int             getTi() const;
        int             getTinf() const;
        long double     getK() const;
        long double     getH() const;
        int	            funcionRadio(int angulo) const;
        void            operator=(const Horno &h1);

		/* Destructor */
        ~Horno();
    private:
		//Atributos
        Matriz* temperaturas;       //temperatura en cada punto discretizado del horno
        long double rad;            //radio del horno desde el centro al borde exterior
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
