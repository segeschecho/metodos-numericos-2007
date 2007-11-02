#include <iostream>
#include <time.h>
#include "Matriz.h"
#include "Senales.h"

using namespace std;

int main(int argc, char* argv[])
{
// 	assert (argc == 4 ); //nombre del programa, archivos de entrada y salida y ruido
//	char* archivoEntrada = argv[1];
//	char* archivoSalida = argv[2];
//	char* factorRuido = argv[3];
	char* archivoEntrada = "a.bmp";
    char* archivoSalida = "o.bmp";
	char* factorRuido = "0";

    srand(time(NULL));

    /*
     *  Levanto el archivo de entrada para capturar la matriz de pixels en un vector
     */
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

	int offset = ancho % 4; // calculo los bytes de basura que hay en cada fila

    Matriz velocidadesInversas(ancho*ancho,1);

    for (unsigned int i = 0; i < ancho*ancho; i++){
        int test = fgetc(pfile);
        long double inverso = (1 / (long double)(test + 1));
        velocidadesInversas.asignar(i,0,inverso);
        fscanf(pfile, "%*2c");  //salteo el GB del RGB pues
                                //la imagen es monocromatica

        if ((i + 1) % ancho == 0)
            for (int j = 0; j < offset; j++)
                fscanf(pfile, "%*1c");  //salteo la "basura"
    }

	fclose(pfile);
    cout << "OK" << endl << endl;

	FILE* pAsalida;
	pAsalida = fopen(archivoSalida, "w"); //crea un nuevo archivo para escritura
	assert (pAsalida != NULL);

    //construyo el header del archivo de salida
	fwrite(bm,1,2,pAsalida);
	fwrite(h1,1,16,pAsalida);
	fwrite(size,1,4,pAsalida);
	fwrite(h2,1,32,pAsalida);

//    for(int i = 0; i < 20*20*3; i++)
//        fprintf(pAsalida, "%c", 0);
	fclose(pAsalida);

    /*
     *  Ahora saco el vector de tiempos
     */

    long double puntos1[800][2];
    long double puntos2[800][2];
    for (int i = 0; i < 200; i++){
        puntos1[i][0] = 0;
        puntos2[i][0] = 20;
        puntos1[i][1] = 10;
        puntos2[i][1] = (i - 100)*0.1;
    }

    for (int i = 200; i < 400; i++){
        puntos1[i][0] = 0;
        puntos2[i][0] = 20;
        puntos1[i][1] = (i - 300)*0.1;
        puntos2[i][1] = 10;
    }

    for (int i = 400; i < 600; i++){
        puntos1[i][0] = 10;
        puntos2[i][0] = (i - 500)*0.1;
        puntos1[i][1] = 0;
        puntos2[i][1] = 20;
    }

    for (int i = 600; i < 800; i++){
        puntos1[i][0] = (i - 700)*0.1;
        puntos2[i][0] = 10;
        puntos1[i][1] = 0;
        puntos2[i][1] = 20;
    }

    Senales D(20, 1, puntos1, puntos2, 800);
    Matriz t(800,1);

    t.multiplicar(D.MatrizSenales(), velocidadesInversas);
    //ya tenemos la matriz t calculada, ahora tenemos que degenerarla y
    //volver a calcular las velocidades (valores de los pixels) con
    //cuadrados minimos, para reconstruir la imagen

    for (int i = 0; i < t.filas(); i++){
        t.asignar(i, 0, t.ver(i,0) + (rand() % 100)*atof(factorRuido)/1000);
    }

    velocidadesInversas.cuadradosMinimosLineales(D.MatrizSenales(), t);
    //ya reconstrui la imagen, ahora la guardo
    cout << "Guardando archivo " << archivoSalida << " ... ";
	pAsalida = fopen(archivoSalida, "a");
	assert (pAsalida != NULL);

    for (unsigned  int i = 0; i < ancho*ancho; i++){
        char valorPixel = (char)((1 / velocidadesInversas.ver(i,0)) - 1);
        fprintf(pAsalida, "%c" ,valorPixel);
        fprintf(pAsalida, "%c" ,valorPixel);
        fprintf(pAsalida, "%c" ,valorPixel);

        if ((i + 1) % ancho == 0)
            for (int j = 0; j < offset; j++)
                fprintf(pAsalida, "%c", valorPixel);
    }
	fclose(pAsalida);
    cout << "OK" << endl << endl;
	return 0;
}
