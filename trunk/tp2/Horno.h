#ifndef _HORNO_H
#define _HORNO_H

#include <iostream>
#include <string.h>

using namespace std;

class Horno{
	//friend ostream& operator<<(ostream&, const Matriz&);
    public:
        /* Constructor */
        Horno(int radio = 1, int angulos = 4, int radios = 5, int tint = 5000, int text = 30, long double k = 1, long double h = 0.05);
        /* interfaz */
        void setFuncionTemperatura(int* radios);

        int getRadio();
        int getCantidadAngulos();
        int getCantidadRadios();
        int getTi();                       //Temperatura interior
        int getTinf();                     //Temperatura exterior
        long double getK();                        //constante K
        long double getH();                        //constante H
        int getRadioLimite(int angulo);
        /* Destructor */
        ~Horno();
    private:
        int rad;
        int angs;
        int rads;
        int ti;
        int tinf;
        long double k;
        long double h;
        int *radiosLimite;                 //valores conocidos.
};

#endif /*_HORNO_H*/
