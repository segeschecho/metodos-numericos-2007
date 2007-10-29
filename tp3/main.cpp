#include <iostream>
#include "matriz.h"
#include <math.h>

using namespace std;

/*
 *  tirarSeñal: Toma una pendiente, un punto de pase para generar una recta
 *              una matriz, un n que representa la dimension de la matriz
 *              imagen y el numero de la matriz a llenar
 */
void tirarSenal(long double a, long double b, Matriz<long double> &m, int filaALlenar){
    int n = sqrt(m.columnas());
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

        //veo si no es un valor duplicado
        if( (pares[i][0] != -1)){
            //si no es duplicado, veo si el que sigue es un duplicado y el
            //siguiente a este es un valor valido(si no me pase de rango)
            if( (pares[i+1][0] == -1) && (i+2 < cantPares) ){
                //menor en x
                col = (int)pares[i][0];
                //menor en y, arreglo para coordenadas de la matriz
                fil = n - 1 - (int)menor(pares[i][1], pares[i+2][1]);

                //calculo la distancia recorrida por la señal en cada cuadrado por
                //donde paso
                x = pares[i][0] - pares[i+2][0];
                y = pares[i][1] - pares[i+2][1];
                distancia = sqrt(pow(x,2) + pow(y,2));

                m.asignar(filaALlenar, fil*n + col, distancia);

                i += 2;
            }
            //si no, veo si fallo la primer guarda
            //si el siguiente no es un duplicado y es una posicion valida
            else if((pares[i+1][0] != -1) && (i+1 < cantPares))
            {
                //menor en x
                col = (int)pares[i][0];
                //menor en y, arreglo para coordenadas de la matriz
                fil = n - 1 - (int)menor(pares[i][1], pares[i+1][1]);

                //calculo la distancia recorrida por la señal en cada cuadrado por
                //donde paso
                x = pares[i][0] - pares[i+1][0];
                y = pares[i][1] - pares[i+1][1];
                distancia = sqrt(pow(x,2) + pow(y,2));

                m.asignar(filaALlenar, fil*n + col, distancia);

                i++;
            }
            //si no paso nada de lo anterior, entonces estoy llegando al final
            //hago que llegue al final
            else
                i++;
        }
        else
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

void metodo1(long double pendientes[], long double puntos[], Matriz<long double> &D)
{
    for(int i = 0; i < D.filas(); i++)
        tirarSenal(pendientes[i], puntos[i], D, i);
}

int main(int argc, char* argv[])
{
   	assert (argc == 4 ); //nombre del programa, archivos de entrada y salida y ruido
	char* archivoEntrada = argv[1];
	char* archivoSalida = argv[2];
	char* factorRuido = argv[3];

    cout << "Levantando archivo " << archivoEntrada << " ... ";
	FILE* pfile;
	pfile = fopen(archivoEntrada,"r");
	assert (pfile != NULL);

    char h1[16];
	char size[4];
	char bm[2];
	fscanf(pfile, "%2c", bm);
	assert(bm[0] == 'B');	// me fijo si es un bmp
	assert(bm[1] == 'M');

	fscanf(pfile, "%16c", h1);			//lo guardo para despues reconstruir el header
	fscanf(pfile, "%4c", size);
	unsigned int* ptr;				// leerlo de nuevo, me parece que basta con poner &size
	ptr = (unsigned int*) size;
	unsigned int ancho;
	ancho = *ptr;					// leerlo de nuevo, me parece que basta con poner &ancho
	                         		// fijarse en cplusplus
	char h2[32];
	fscanf(pfile, "%32c", h2);

	int offset;
	offset = ancho % 4; // calculo los bytes de basura que hay en cada fila

    Matriz<char> matriz(ancho,ancho);
    int temp;

    for (unsigned int i = 0; i < ancho; i++){
        for (unsigned int j = 0; j < ancho; j++){
            temp = fgetc(pfile);
            matriz.asignar(i,j,(char) temp);
            fscanf(pfile, "%*2c");  //salteo el GB del RGB pues
                                    //la imagen es monocromatica
        }
        pfile += offset;
    }
	fclose(pfile);
    cout << "OK" << endl << endl;

    cout << "Guardando archivo " << archivoSalida << " ... ";
	FILE* pAsalida;
	pAsalida = fopen(archivoSalida, "w"); //crea un nuevo archivo para escritura
	assert (pAsalida != 0);

    //construyo el header del archivo de salida
	fwrite(bm,1,2,pAsalida);
	fwrite(h1,1,16,pAsalida);
	fwrite(size,1,4,pAsalida);
	fwrite(h2,1,32,pAsalida);

    for(int i = 0; i < 20*20*3; i++)
        fprintf(pAsalida, "%c", 0);
	fclose(pAsalida);
    cout << "OK" << endl << endl;

    Matriz<long double> m(4,16);
    long double pendientes[4] = {1, 0, -1, -2};
    long double puntos[4] = {1.5, 2, 2.5, 3};

    metodo1(pendientes, puntos, m);

    cout << m << endl;

	return 0;
}
