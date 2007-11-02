#include <iostream>
#include <fstream>
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

    srand((int)time(NULL));

    /*
     *  Levanto el archivo de entrada para capturar la matriz de pixels en un vector
     */
    cout << "Levantando archivo " << archivoEntrada << " ... ";
	ifstream pfile;
    pfile.open(archivoEntrada, ifstream::in);
    assert (pfile.is_open());
//	pfile = fopen(archivoEntrada,"r");
//	assert (pfile != NULL);

    char h1[16];
	char size[4];
	char bm[2];
	pfile.read(bm, 2);
	assert(bm[0] == 'B');	// me fijo si es un bmp
	assert(bm[1] == 'M');

	pfile.read(h1, 16);			//lo guardo para despues reconstruir el header
	pfile.read(size, 4);
    // leerlo de nuevo, me parece que basta con poner &size
	unsigned int* ptr = (unsigned int*) size;
	unsigned int ancho = *ptr;

    char h2[32];
	pfile.read(h2, 32);

	int offset = ancho % 4; // calculo los bytes de basura que hay en cada fila

    Matriz velocidadesInversas(ancho*ancho,1);

    for (unsigned int i = 0; i < ancho*ancho; i++){
        long double inverso = (1 / (long double)(pfile.get() + 1));
        velocidadesInversas.asignar(i,0,inverso);
    	pfile.ignore(2); //salteo el GB del RGB pues
                         //la imagen es monocromatica

        if ((i + 1) % ancho == 0)
          	pfile.ignore(offset); //salteo la basura
    }

	pfile.close();
    cout << "OK" << endl << endl;

	ofstream pAsalida;
    pAsalida.open(archivoSalida, ofstream::out); //crea un nuevo archivo para escritura
	assert (pAsalida.is_open());

    //construyo el header del archivo de salida
	pAsalida.write(bm, 2);
    pAsalida.write(h1, 16);
    pAsalida.write(size, 4);
    pAsalida.write(h2, 32);
    
	pAsalida.close();

    /*
     *  Ahora saco el vector de tiempos
     */

    long double puntos1[80][2];
    long double puntos2[80][2];
    for (int i = 0; i < 20; i++){
        puntos1[i][0] = 0;
        puntos2[i][0] = 3;
        puntos1[i][1] = 1.5;
        puntos2[i][1] = (i - 10)*0.5;
    }

    for (int i = 20; i < 40; i++){
        puntos1[i][0] = 0;
        puntos2[i][0] = 3;
        puntos1[i][1] = (i - 30)*0.5;
        puntos2[i][1] = 1.5;
    }

    for (int i = 40; i < 60; i++){
        puntos1[i][0] = 1.5;
        puntos2[i][0] = (i - 50)*0.5;
        puntos1[i][1] = 0;
        puntos2[i][1] = 3;
    }

    for (int i = 60; i < 80; i++){
        puntos1[i][0] = (i - 70)*0.5;
        puntos2[i][0] = 1.5;
        puntos1[i][1] = 0;
        puntos2[i][1] = 3;
    }
/*    for (int i = 200; i < 400; i++){
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
*/
    Senales D(ancho, 1);//, puntos1, puntos2, 80);
    Matriz t(6*ancho*ancho,1);

    t.multiplicar(D.MatrizSenales(), velocidadesInversas);
    //ya tenemos la matriz t calculada, ahora tenemos que degenerarla y
    //volver a calcular las velocidades (valores de los pixels) con
    //cuadrados minimos, para reconstruir la imagen

    for (int i = 0; i < t.filas(); i++){
        t.asignar(i, 0, t.ver(i,0) + (rand()% 100)*atof(factorRuido)/1000);
    }

    velocidadesInversas.cuadradosMinimosLineales(D.MatrizSenales(), t);
    //ya reconstrui la imagen, ahora la guardo
    cout << "Guardando archivo " << archivoSalida << " ... ";
    pAsalida.open(archivoSalida, ofstream::app);
	assert (pAsalida.is_open());
    pAsalida.seekp(18);

    for (unsigned  int i = 0; i < ancho*ancho; i++){
        char valorPixel = (char)((1 / velocidadesInversas.ver(i,0)) - 1);
        pAsalida << valorPixel << valorPixel << valorPixel;

        if ((i + 1) % ancho == 0)
            for (int j = 0; j < offset; j++)
                pAsalida << valorPixel; //lo relleno con basura donde debe ir
    }
	pAsalida.close();
    cout << "OK" << endl << endl;
	return 0;
}
