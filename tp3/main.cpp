#include <iostream>
#include <fstream>
#include <time.h>
#include "Matriz.h"
#include "Senales.h"
#include "EasyBMP.h"
using namespace std;

int main(int argc, char* argv[])
{
/* 	assert (argc == 4 ); //nombre del programa, archivos de entrada y salida y ruido
	char* archivoEntrada = argv[1];
	char* archivoSalida = argv[2];
	unsigned int factorRuido = atof(argv[3]);*/
	char* archivoEntrada = "10.bmp";
    char* archivoSalida = "test.bmp";
	unsigned int factorRuido = 0;

    srand((int)time(NULL));

    /*
     *  Levanto el archivo de entrada
     */
    cout << "Levantando archivo " << archivoEntrada << " ... ";
	BMP imagen;
    imagen.ReadFromFile(archivoEntrada);
    Matriz velocidadesInversas(imagen.TellWidth()*imagen.TellHeight(),1);

    for (int i = 0; i < imagen.TellHeight(); i++){
        for (int j = 0; j < imagen.TellWidth(); j++){
            long double inverso = (1 / ((long double)imagen.GetPixel(j, i).Blue + 1));
            velocidadesInversas.asignar(i*imagen.TellWidth() + j,0,inverso);
        }
    }
    cout << "OK!" << endl << endl;

    int metodo = 1;
    int numSenales = 6*imagen.TellWidth()*imagen.TellHeight();// - 8*imagen.TellHeight() + 2;

    cout << "Usando el metodo: " << metodo;
    cout << ", generando " << 6*imagen.TellWidth()*imagen.TellHeight();
    cout << " seniales..." << endl << endl;
    cout << "Operando... " << endl << endl;

    //Ahora saco el vector de tiempos
    int inicio = (int)time(NULL);
    Senales D(imagen.TellHeight(), metodo);

    D.realizarTomografia(velocidadesInversas, factorRuido);

    ofstream paraMatlab;
    paraMatlab.open("test.txt", ios_base::out);
    if (paraMatlab.fail())
        cout << "Fallo en grafico!" << endl;
    else
        D.prepararParaGraficarMetodo(paraMatlab, 1);
    paraMatlab.close();

    cout << "OK!" << endl << endl;
    cout << "El algoritmo termino en " << time(NULL) - inicio << " segundos.\n" << endl;

    //ya reconstrui la imagen, ahora la guardo
    cout << "Guardando archivo " << archivoSalida << " ... ";

    for (int i = 0; i < imagen.TellWidth(); i++){
        for (int j = 0; j < imagen.TellHeight(); j++){
            RGBApixel nuevoPixel;
            char valorPixel = (char)((1 / velocidadesInversas.ver(i*imagen.TellWidth() + j,0)) - 1);
            nuevoPixel.Alpha = 0;
            nuevoPixel.Red = valorPixel;
            nuevoPixel.Green = valorPixel;
            nuevoPixel.Blue = valorPixel;
            imagen.SetPixel(j, i, nuevoPixel);
        }
    }
    imagen.WriteToFile(archivoSalida);
    cout << "OK!" << endl << endl;
	return 0;
}
