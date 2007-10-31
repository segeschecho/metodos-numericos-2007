#include <iostream>
#include <time.h>
#include "Matriz.h"
#include "Senales.h"

using namespace std;

int main(int argc, char* argv[])
{
    srand(time(NULL));
   	assert (argc == 4 ); //nombre del programa, archivos de entrada y salida y ruido
	char* archivoEntrada = argv[1];
	char* archivoSalida = argv[2];
	char* factorRuido = argv[3];

    /*
     *
     *  Levanto el archivo de entrada para capturar la matriz de pixels en un vector
     *
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

	int offset;
	offset = ancho % 4; // calculo los bytes de basura que hay en cada fila

    Matriz velocidadesInversas(ancho*ancho,1);

    for (unsigned int i = 0; i < ancho*ancho; i++){
        long double inverso = 1 / (fgetc(pfile) + 1);
        velocidadesInversas.asignar(i,0,inverso);
        fscanf(pfile, "%*2c");  //salteo el GB del RGB pues
                                //la imagen es monocromatica

        if(i % ancho == 0)
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

//    for(int i = 0; i < 20*20*3; i++)
//        fprintf(pAsalida, "%c", 0);
	fclose(pAsalida);
    cout << "OK" << endl << endl;

    /*
     *  Ahora saco el vector de tiempos
     */

    long double puntos1[20][2];
    long double puntos2[20][2];
    for (int i = 0; i < 20; i++){
        puntos1[i][0] = 0;
        puntos2[i][0] = 20;
        puntos1[i][1] = i;
        puntos2[i][1] = i;
    }

    Senales D(20, 1, puntos1, puntos2, 50);
    Matriz Dt(20*20, 20);
    Matriz DDt(20*20, 20);
    Matriz t(400,1);

    t.multiplicar(D.MatrizSenales(), velocidadesInversas);

    //ya tenemos la matriz t calculada, ahora tenemos que degenerarla y
    //volver a calcular las velocidades (valores de los pixels) con
    //cuadrados minimos, para reconstruir la imagen


    for (int i = 0; i < t.filas(); i++){
        t.asignar(i, 0, t.ver(i,0) + (rand() % 100)*atoi(factorRuido)/1000);
    }

    D.MatrizSenales().traspuesta(Dt);


	return 0;
}
