#include <math.h>
#include "Matriz.h"
#include "Senales.h"

/*************************************/
/*          METODOS PUBLICOS         */
/*************************************/

Senales :: Senales(unsigned int dimImagen, unsigned int metodo, long double puntos1[][2], long double puntos2[][2], unsigned int cantSenales)
{
    D = NULL;
    switch(metodo){
        case 1:
            metodo1(dimImagen, puntos1, puntos2, cantSenales);
            break;
    }
}

Senales :: Senales(Senales& s)
{
    D = new Matriz(s.D->filas(), s.D->columnas());
    *D = *(s.D);
}

const Matriz& Senales :: MatrizSenales(void){
    return *D;
}

/*************************************/
/*          METODOS PRIVADOS         */
/*************************************/

void Senales :: metodo1(unsigned int dimImagen, long double puntos1[][2], long double puntos2[][2], unsigned int n)
{
    delete D;
    D = new Matriz(n, dimImagen*dimImagen);
    for(int i = 0; i < D->filas(); i++)
        tirarSenal(puntos1[i][0], puntos1[i][1], puntos2[i][0], puntos2[i][1], i);
}

void Senales :: tirarSenal(long double x1, long double y1, long double x2, long double y2, int filaALlenar)
{
    //primero construyo la recta
    //tengo un sistema de 2x2 que es: y1 = x1*a + b
    //                                y2 = x2*a + b
    //entonces: b = y1 - x1*a
    //          y2 = x2*a + y1 - x1*a
    //          a = (y2 - y1) / (x2 - x1)
    //          b = y1 - x1*((y2 - y1) / (x2 - x1))
    //          x2 - x1 != 0 paratodo x2, x1 reales, salvo que sea una senial vertical, lo cual tratamos como caso particular

    long double a = (y2 - y1) / (x2 - x1);
    long double b = y1 - x1*((y2 - y1) / (x2 - x1));
    int n = (int)sqrt((long double)D->columnas()); //puedo hacer esto porque la matriz es de m*n^2
    long double** pares;
    pares = new long double* [2*(n+1)];   //2*(n+1) lo peor es que pase por la
                                          //diagonal entonces va a haber 2*(n+1) pares
    for(int i = 0; i < 2*(n+1); i++){
        pares[i] = new long double [2];
    }

    int cantPares = 0;

    //genero el vector pares donde estan los resultados de aplicar
    // y = a*x + b
    // x = (y - b)/a
    // y lo guardo en pares x,y

    for (int i = 0; i <= n; i++){
        long double temp = a*i + b;

        if((temp >= 0) && (temp <= n)){
            pares[cantPares][0] = i;
            pares[cantPares][1] = temp;
            cantPares++;
        }
    }

    for (int i = 0; (i <= n) && (a != 0); i++){
        long double temp = (i - b)/a;

        if(temp >= 0 && temp <= n){
            pares[cantPares][0] = temp;
            pares[cantPares][1] = i;
            cantPares++;
        }
    }

    //ordeno por la primer componente
    ordenarPares(pares, cantPares);

//    for(int i = 0; i < cantPares; i++){
//        cout << "(" << pares[i][0] << "," << pares[i][1] << ")" << ", ";
//    }
    //anulo los pares repetidos
    anularRepetidos(pares, cantPares);

    for(int i = 0; i < cantPares; i++){
        int fil;
        int col;

        //veo si no es un valor duplicado
        if( (pares[i][0] != -1)){
            //si no es duplicado, veo si el que sigue es un duplicado y el
            //siguiente a este es un valor valido(si no me pase de rango)
            if( (pares[i+1][0] == -1) && (i+2 < cantPares) ){
                //menor en x
                col = (int)pares[i][0];
                //menor en y, arreglo para coordenadas de la matriz
                if((int)pares[i][1] < (int)pares[i+2][1]){
                    fil = n - 1 - (int)pares[i][1];
                }
                else
                    fil = n - 1 - (int)pares[i+2][1];

                //calculo la distancia recorrida por la señal en cada cuadrado por
                //donde paso
                long double x = pares[i][0] - pares[i+2][0];
                long double y = pares[i][1] - pares[i+2][1];

                D->asignar(filaALlenar, fil*n + col, sqrt(pow(x,2) + pow(y,2)));

                i++; //si hay un repetido adelante tengo que avanzar 2
            }
            //si no, veo si fallo la primer guarda
            //si el siguiente no es un duplicado y es una posicion valida
            else if((pares[i+1][0] != -1) && (i+1 < cantPares))
            {
                //menor en x
                col = (int)pares[i][0];
                //menor en y, arreglo para coordenadas de la matriz
                if((int)pares[i][1] < (int)pares[i+1][1]){
                    fil = n - 1 - (int)pares[i][1];
                }
                else
                    fil = n - 1 - (int)pares[i+1][1];

                //calculo la distancia recorrida por la señal en cada cuadrado por
                //donde paso
                long double x = pares[i][0] - pares[i+1][0];
                long double y = pares[i][1] - pares[i+1][1];

                D->asignar(filaALlenar, fil*n + col, sqrt(pow(x,2) + pow(y,2)));
            }
        }
    }
}

void Senales :: ordenarPares(long double** pares, int filas){
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

void Senales :: anularRepetidos(long double** pares, int cantPares){
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
