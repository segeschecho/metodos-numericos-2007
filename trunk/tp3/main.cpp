#include <iostream>
#include "matriz.h"
#include <math.h>

using namespace std;

void tirarSenal(long double a, long double b, Matriz<long double> &m, int n, int filaALlenar);
void ordenarPares(long double pares[][2], int filas);
long double menor(long double a, long double b);

int main()
{
    long double temp = 2.5;
    int redondeo = (int)temp;
    Matriz<long double> a(4,4);

    a.asignar(0,0,4);
    a.asignar(0,1,3);
    a.asignar(0,2,4);
    a.asignar(0,3,6);

    a.asignar(1,0,1);
    a.asignar(1,1,4);
    a.asignar(1,2,0);
    a.asignar(1,3,1);

    a.asignar(2,0,2);
    a.asignar(2,1,3);
    a.asignar(2,2,7);
    a.asignar(2,3,8);

    a.asignar(3,0,9);
    a.asignar(3,1,3);
    a.asignar(3,2,6);
    a.asignar(3,3,1);

    tirarSenal(1,2,a,4,1);

	cout << "valor en double " << temp <<  endl;
	cout << "valor en entero " << redondeo <<  endl;



	return 0;
}

/*
 *  tirarSeñal: Toma una pendiente, un punto de pase para generar una recta
 *              y un n que representa la dimension de la matriz imagen
 */
void tirarSenal(long double a, long double b, Matriz<long double> &m, int n, int filaALlenar){
    assert((b != 0 && a >= 0) || (b != n && a <= 0));
    long double pares[2*n][2];
    long double temp = 0;

    int i = 0;


    //genero el vector pares donde estan los resultados de aplicar
    // y = a*x + b
    // x = (y - b)/a
    // y lo guardo en pares x,y

    while(i < n){
        long double temp = a*i + b;

        if(temp < 0 || temp > n){
            //si se paso pongo en cero para que no cuente esas distancias.
            pares[i][0] = 0;
            pares[i][1] = 0;
        }
        else
        {
            pares[i][0] = i;
            pares[i][1] = temp;
        }

        i++;
    }

    i = 0;
    while(i < n){
        if(a == 0){
            pares[i+n][0] = 0;
            pares[i+n][1] = 0;
        }
        else
        {
            temp = (i - b)/a;

            if(temp < 0 || temp > n){
                pares[i+n][0] = 0;
                pares[i+n][1] = 0;
            }
            else
            {
                pares[i+n][0] = temp;
                pares[i+n][1] = i;
            }
        }
        i++;
    }

    //ordeno por la primer componente
    ordenarPares(pares, 2*n);

    i = 0;

    while(i < m.columnas()){
        m.asignar(filaALlenar, i, 0);
        i++;
    }

    i = 0;

    while(i < (n - 1)){  //n-1 es la cantidad de cuadrados afectados
        long double x = 0;
        long double y = 0;
        long double distancia = 0;
        long double fil = 0;
        long double col = 0;

        fil = (int)pares[i][0];                       //menor en x
        col = n - 1 - (int)menor(pares[i][1], pares[i+1][1]); //menor en y, arreglo para coordenadas de la matriz

        //calculo la distancia recorrida por la señal en cada cuadrado por donde paso
        x = pares[i][0] - pares[i+1][0];
        y = pares[i][1] - pares[i+1][1];
        distancia = sqrt(pow(x,2) + pow(y,2));

        m.asignar(filaALlenar, fil*n + col, distancia);

        i++;
    }
}

long double menor(long double a, long double b){
    if(a < b)
        return a;
    else
        return b;
}
/*
 * ordenarPares: ordena un vector de tuplas por su primer componente
 */
void ordenarPares(long double pares[][2], int filas){
    int topeInf = 0;
    long double temp1;  //variable temporal para el primer componente de la tupla
    long double temp2;  //variable temporal para el segundo componente de la tupla


    while (topeInf < (filas - 1)){
        int i = topeInf;
        int posMenor = i;
        long double menor = pares[i][0];

        while (i < filas){
            if(pares[i][0] < menor){
                menor = pares[i][0];
                posMenor = i;
            }
            i++;
        }

        /* hago el swap de los elementos */
        temp1 = pares[topeInf][0];
        temp2 = pares[topeInf][1];

        pares[topeInf][0] = pares[posMenor][0];
        pares[topeInf][1] = pares[posMenor][1];

        pares[posMenor][0] = temp1;
        pares[posMenor][1] = temp2;

        topeInf++;

    }
}
