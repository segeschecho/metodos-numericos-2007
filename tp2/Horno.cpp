#include "Horno.h"

Horno :: Horno(int radio, int cantAngulos, int cantRadios, int tint, int text, long double k, long double h, int* radiosLimite){

    rad = radio;
    angs = cantAngulos;
    rads = cantRadios;
    deltaR = rad/rads;
    deltaT = 2*PI/angs;
    ti = tint;
    tinf = text;
    this->k = k;
    this->h = h;

    bordeInterno = new int(angs);

    // guardo los radios para cada angulo
    // asi queda definida la funcion de temperatura.
    for(int cant = 0; cant < angs; cant++)
        bordeInterno[cant] = radiosLimite[cant];

    Matriz temp(rad*angs, rad*angs + 1);        // rad*angs + 1 nos incluye la solucion
    temperaturas = new Matriz(rad, angs);

    int filaALlenar = 0;
    for(int r = 0; r < rad; r++)
        for(int a = 0; a < angs; a++)
        {
            if (r <= bordeInterno[a]){           //quiere decir que es borde interno
                llenar_Fila_Punto_Interno(filaALlenar, a, r);
            }
            else{
                if(r != cantRadios - 1){          //si no es un punto del borde
                    double float coef1 = 1/pow(deltaR, 2) - 1/(r*deltaR);
                }
            }
            filaALlenar++;
        }
}

/* interfaz */

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

int Horno :: getBordeInterno(int angulo){
    return BordeInterno[angulo];
}
/* Destructor */
Horno :: ~Horno(){
    delete BordeInterno;
}
