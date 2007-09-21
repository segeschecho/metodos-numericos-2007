#include "Horno.h"

Horno :: Horno(){
    diam = 0;
    angs = 0;
    rads = 0;
    ti = 0;
    tinf = 0;
    k = 0;
    h = 0;
    radiosLimite = NULL;
}

/* interfaz */

void Horno :: setRadio(int d){
    diam = d;
}

void Horno :: setCantidadAngulos(int ang){
    angs = ang;
}

void Horno :: setCantidadRadios(int rad){
    rads = rad;
}

void Horno :: setTi(int t){
    ti = t;
}

void Horno :: setTinf(int t){
    tinf = t;
}

void Horno :: setK(long double k){
    this->k = k;
}

void Horno :: setH(long double h){
    this->h = h;
}

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
    return diam;
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
    delete(radiosLimite);
}
