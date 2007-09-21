#ifndef _HORNO_H
#define _HORNO_H

#include <iostream>
#include <string.h>

using namespace std;

class Horno{
	//friend ostream& operator<<(ostream&, const Matriz&);
    public:
        /* Constructor */
        Horno();
        /* interfaz */
        void setRadio(int d);
        void setCantidadAngulos(int ang);
        void setCantidadRadios(int rad);
        void setTi(int t);                 //Temperatura interior
        void setTinf(int t);               //Temperatura exterior
        void setK(long double k);          //constante K
        void setH(long double h);          //constante H
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
        int diam;
        int angs;
        int rads;
        int ti;
        int tinf;
        long double k;
        long double h;
        int *radiosLimite;                 //valores conocidos.
};

#endif /*_HORNO_H*/
