#include <iostream>

using namespace std;

int main()
{
    long double temp = 2.5;
    int redondeo = (int)temp;

	cout << "valor en double " << temp <<  endl;
	cout << "valor en entero " << redondeo <<  endl;

	return 0;
}

/*
 *  tirarSeñal: Toma una pendiente, un punto de pase para generar una recta
 *              y un n que representa la dimesion de la matriz.
 */
void tirarSeñal(long double a, long double b, Matriz<long double> &m, int n, int filaALlenar){
    assert((b != 0 && a >= 0) || (b != n && a <= 0));
    long double pares[2*n][2] = {0};
    int cuadradosAfectados[2*n][3] = {0};  //donde pongo las coordenadas y distancia recorrida por la señal
    long double


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
    selectionSort(pares);

    i = 0;

    while(i < n^2){
        m.asignar(filaALlenar, i, 0);
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
        distancia = sqrt(x^2 + y^2);

        m.asignar(filaALlenar, fil*n + col, distancia);

        i++;
    }
}
