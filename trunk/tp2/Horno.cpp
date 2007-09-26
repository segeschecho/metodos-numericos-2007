#include "Horno.h"
#define PI 3.1415926535897932484626433832795

Horno :: Horno(int radio, int cantAngulos, int cantRadios, int tint, int text, long double k, long double h, int* radiosLimite){
    rad = radio;
    angs = cantAngulos;
    rads = cantRadios;
    deltaR = (long double)rad/(long double)rads;
    deltaT = 2*PI/(long double)angs;
    ti = tint;
    tinf = text;
    this->k = k;
    this->h = h;

    bordeInterno = new int(angs);

    // guardo los radios para cada angulo
    // asi queda definida la funcion de temperatura.
    for(int cant = 0; cant < angs; cant++)
        bordeInterno[cant] = radiosLimite[cant];

    Matriz temp(rads*angs, rads*angs);
	Matriz b(rads*angs, 1);
	Matriz X(rads*angs, 1);
    temperaturas = new Matriz(rads, angs);

    int filaALlenar = 0;
	for(int r = 0; r < rads; r++){
        for(int a = 0; a < angs; a++)
        {
            if ((r == 0) || (r <= bordeInterno[a])){           //si es un punto del borde interno
			//sabemos que por la 2da ecuacion, la temperatura de los puntos
			//dentro de este borde es 5000, entonces se que el coeficiente
			//del punto en cuestion sera 1, y su correspondiente
			//resultado en b es 5000

			//ahora asigno el coeficiente en la matriz
			//viendo la matriz como un arreglo de filas,
			//dentro de la fila a llenar:
			//T[r][a] = 1
				temp.asignar(filaALlenar, r*angs + a, 1);
				b.asignar(filaALlenar, 0, 5000);
            }
            else{
                if(r != cantRadios - 1){          //si no es un punto del borde interno
                    long double coef1 = 1/(deltaR*deltaR) - 1/((r+1)*deltaR);
                    long double coef2 = 1/((deltaT*deltaT)*((r+1)*(r+1)));
                    long double coef3 = -2/(deltaR*deltaR) + 1/((r+1)*deltaR) - 2/((r+1)*(r+1)*deltaT*deltaT);
                    long double coef4 = 1/(((r+1)*(r+1))*(deltaT*deltaT));
                    long double coef5 = 1/(deltaR*deltaR);
					//coef 1 a 5 son los 5 coeficientes de las incognitas que quedan
					//luego de la discretizacion del Laplaciano

					//ahora asigno los coeficientes en la matriz
					//viendo la matriz como un arreglo de filas,
					//dentro de la fila a llenar:
					//T[r-1][a] = coef1
					//T[r][a-1] = coef2
					//T[r][a]   = coef3
					//T[r][a+1] = coef4
					//T[r+1][a] = coef5
					temp.asignar(filaALlenar, (r - 1)*angs + a, coef1);
					temp.asignar(filaALlenar, r*angs + a - 1, coef2);
					temp.asignar(filaALlenar, r*angs + a, coef3);
					temp.asignar(filaALlenar, r*angs + a + 1, coef4);
					temp.asignar(filaALlenar, (r + 1)*angs + a, coef5);
                }
				else{	//si el punto es del borde externo
					long double coef = -k/(h*deltaR);
					//coef cubre los 2 coeficientes que resultan de discretizar
					//la 3er ecuacion en cuestion

					//ahora asigno los coeficientes en la matriz
					//viendo la matriz como un arreglo de filas,
					//dentro de la fila a llenar:
					//T[r][a] = coef
					//T[r-1][a] = coef + 1
					temp.asignar(filaALlenar, r*angs + a, coef);
					temp.asignar(filaALlenar, (r - 1)*angs + a, coef + 1);
					b.asignar(filaALlenar, 0, tinf*k/h);
				}
            }
            filaALlenar++;
        }
	}

	temp.triangular(b);
	temp.resolver(X,b);
	for(int r = 0; r < rads; r++)
		for(int a = 0; a < angs; a++)
			temperaturas->asignar(r,a,X.ver(r*angs + a, 0));
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

void Horno :: operator=(const Horno &h1){
    rad = h1.rad;
    angs = h1.angs;
    rads = h1.rads;
    deltaR = h1.deltaR;
    deltaT = h1.deltaT;         //delta Theeta
    ti = h1.ti;
    tinf = h1.tinf;
    k = h1.k;
    h = h1.h;

    temperaturas = new Matriz(rad, angs);
    *temperaturas = *(h1.temperaturas);

    bordeInterno = new int(angs);
    for(int i = 0; i < angs; i++)
        bordeInterno[i] = h1.bordeInterno[i];
}

int Horno :: getBordeInterno(int angulo){
    return bordeInterno[angulo];
}
/* Destructor */
Horno :: ~Horno(){
    delete bordeInterno;
}
