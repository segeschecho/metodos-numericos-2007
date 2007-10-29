#include <iostream>
#include "matriz.h"
#include <math.h>

using namespace std;

void tirarSenal(long double a, long double b, Matriz<long double> &m, int n, int filaALlenar);
void ordenarPares(long double pares[][2], int filas);
long double menor(long double a, long double b);
void anularRepetidos(long double pares[][2], int cantPares);

int main()
{
    long double temp = 2.5;
    int redondeo = (int)temp;
    Matriz<long double> m(4,16);

    m.asignar(0,0,4);
    m.asignar(0,1,3);
    m.asignar(0,2,4);
    m.asignar(0,3,6);
    m.asignar(0,4,4);

    m.asignar(1,0,1);
    m.asignar(1,1,4);
    m.asignar(1,2,0);
    m.asignar(1,3,1);
    m.asignar(1,4,2);

    m.asignar(2,0,2);
    m.asignar(2,1,3);
    m.asignar(2,2,7);
    m.asignar(2,3,8);
    m.asignar(2,4,6);

    m.asignar(3,0,9);
    m.asignar(3,1,3);
    m.asignar(3,2,6);
    m.asignar(3,3,1);
    m.asignar(3,4,1);


    long double pend = 1;
    long double ptoPase = 0;

    cout << m << endl;

    tirarSenal(pend,ptoPase,m,4,1);

    cout << m << endl;
	cout << "valor en double " << temp <<  endl;
	cout << "valor en entero " << redondeo <<  endl;



	return 0;
}

/*
 *  tirarSeñal: Toma una pendiente, un punto de pase para generar una recta
 *              una matriz, un n que representa la dimension de la matriz
 *              imagen y el numero de la matriz a llenar
 */
void tirarSenal(long double a, long double b, Matriz<long double> &m, int n, int filaALlenar){
    assert((b <= 0 && a >= 0) || (b >= n && a <= 0) || (b > 0 && b < n));
    long double pares[2*(n+1)][2];  //2*(n+1) lo peor es que pase por la
                                    //diagonal entonces va a haber 2*(n+1) pares
    long double temp = 0;
    int cantPares = 0;

    int i = 0;


    //genero el vector pares donde estan los resultados de aplicar
    // y = a*x + b
    // x = (y - b)/a
    // y lo guardo en pares x,y

    while(i <= n){
        long double temp = a*i + b;

        if((temp >= 0) && (temp <= n)){
            pares[cantPares][0] = i;
            pares[cantPares][1] = temp;
            cantPares++;
        }

        i++;
    }

    i = 0;
    while((i <= n) && (a != 0)){
        temp = (i - b)/a;

        if(temp >= 0 && temp <= n){
            pares[cantPares][0] = temp;
            pares[cantPares][1] = i;
            cantPares++;
        }
        i++;
    }

    //ordeno por la primer componente
    ordenarPares(pares, cantPares);

    for(i = 0; i<cantPares; i++){
        cout << "(" << pares[i][0] << "," << pares[i][1] << ")" << ", ";
    }
    cout << endl;
    //anulo los pares repetidos
    anularRepetidos(pares, cantPares);

    i = 0;

    while(i < m.columnas()){
        m.asignar(filaALlenar, i, 0);
        i++;
    }

    i = 0;

    while(i < cantPares){
        long double x = 0;
        long double y = 0;
        long double distancia = 0;
        long double fil = 0;
        long double col = 0;

        if( (pares[i][0] != -1)){
            if( (pares[i+1][0] == -1) && (i+2 < cantPares) ){
                //menor en x
                fil = (int)pares[i][0];
                //menor en y, arreglo para coordenadas de la matriz
                col = n - 1 - (int)menor(pares[i][1], pares[i+2][1]);

                //calculo la distancia recorrida por la señal en cada cuadrado por
                //donde paso
                x = pares[i][0] - pares[i+2][0];
                y = pares[i][1] - pares[i+2][1];
                distancia = sqrt(pow(x,2) + pow(y,2));

                m.asignar(filaALlenar, fil*n + col, distancia);

                i = i + 2;
            }
            else if(pares[i+1][0] != -1)
            {
                //menor en x
                fil = (int)pares[i][0];
                //menor en y, arreglo para coordenadas de la matriz
                col = n - 1 - (int)menor(pares[i][1], pares[i+1][1]);

                //calculo la distancia recorrida por la señal en cada cuadrado por
                //donde paso
                x = pares[i][0] - pares[i+1][0];
                y = pares[i][1] - pares[i+1][1];
                distancia = sqrt(pow(x,2) + pow(y,2));

                m.asignar(filaALlenar, fil*n + col, distancia);

                i++;
            }
            else
                i++;
        }
        else
            i = i + 2;
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

/*
 * anularRepetidos: recorre el vector de pares de coordenadas y anula los
 *                  repetidos poniendo un -1 en la coordenada x, indicando que
 *                  esta repetida.
 */
void anularRepetidos(long double pares[][2], int cantPares){
    int cant = cantPares;
    int i = 0;

    while (i < (cant - 1)){
        if(pares[i][0] == pares[i+1][0]){
            pares[i+1][0] = -1;
            i = i + 2;           //salteo el anulado
        }
        else
           i++;
    }


}
