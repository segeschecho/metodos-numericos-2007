#include "Horno.h"

Horno :: Horno(int radio, int angulos, int radios, int tint, int text, long double k, long double h){
    rad = radio;
    angs = angulos;
    rads = radios;
    ti = tint;
    tinf = text;
    this->k = k;
    this->h = h;
    radiosLimite = NULL;
}

/* interfaz */

void Horno :: setFuncionTemperatura(int* radios){
    int cant = 0;

    radiosLimite = new int(angs);

    // guardo los radios para cada angulo
    // asi queda definida la funcion de temperatura.
    while(cant < angs){
        radiosLimite[cant] = radios[cant];
        cant++;
    }
}

int Horno :: getRadio(){
    return rad;
}

int Horno :: getCantidadAngulos(){
    return angs;
}

int Horno :: getCantidadRadios(){
    return rads;
}

int Horno :: getTi(){
    return ti;
}                       //Temperatura interior

int Horno :: getTinf(){
    return tinf;
}                     //Temperatura exterior

long double Horno :: getK(){
    return k;
}                        //constante K

long double Horno :: getH(){
    return h;
}                        //constante H

int Horno :: getRadioLimite(int angulo){
    return radiosLimite[angulo];
}
/* Destructor */
Horno :: ~Horno(){
    delete radiosLimite;
}
