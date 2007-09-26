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

    Matriz temp(rad*angs, rad*angs);
	Matriz b(rad*angs, 1);
	Matriz X(1, rad*angs);
    temperaturas = new Matriz(rad, angs);

    int filaALlenar = 0;
	for(int r = 0; r < rad; r++){
        for(int a = 0; a < angs; a++)
        {
            if (r <= bordeInterno[a]){           //si es un punto del borde interno
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
                    long double coef1 = 1/pow(deltaR, 2) - 1/(r*deltaR);
                    long double coef2 = 1/(pow(deltaR, 2)*pow(r,2));
                    long double coef3 = -2/pow(deltaR,2) + 1/(r*deltaR) - 2/(pow(r,2)*pow(deltaR,2));
                    long double coef4 = 1/(pow(r,2)*pow(deltaR, 2));
                    long double coef5 = 1/pow(deltaR, 2);
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
					temp.asignar(filaALlenar, r*angs + a - 1, coef1);
					temp.asignar(filaALlenar, r*angs + a, coef1);
					temp.asignar(filaALlenar, r*angs + a + 1, coef1);
					temp.asignar(filaALlenar, (r + 1)*angs + a, coef1);
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
					b.asignar(filaALlenar, 1, tinf*k/h);
				}
            }
            filaALlenar++;
        }
	}

	X = temp.resolver(b);
	for(int r = 0; r < rad; r++)
		for(int a = 0; a < angs; a++)
			temperatura->asignar(r,a,X.ver(0, r*angs + a));
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
