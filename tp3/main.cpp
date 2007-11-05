#include <iostream>
#include <fstream>
#include <time.h>
#include "Matriz.h"
#include "Senales.h"
#include "EasyBMP.h"

using namespace std;

int main(int argc, char* argv[]){
    bool ayuda = false;
    int argctrucho = 7;
    char* argvtrucho[7] = {"exe", "6.bmp", "test2.bmp", "3", "0", "-g", "grafico.txt"};// "-g", "graficameEsta.txt"};


    if(argctrucho >= 5){
        unsigned int metodo = atoi(argvtrucho[3]);
	    long double factorRuido = atof(argvtrucho[4]);

        srand((int)time(NULL));

        /*
         *  Levanto el archivo de entrada
         */
        cout << "Levantando archivo " << argvtrucho[1] << " ... ";
	    BMP imagen;
        imagen.ReadFromFile(argvtrucho[1]);

        //Creo la matriz para las velocidades inversas
        Matriz velocidadesInversas(imagen.TellWidth()*imagen.TellHeight(),1);
        //velocidades originales para calcular el Error cuadratico medio
        Matriz velocidadesOrig(imagen.TellWidth()*imagen.TellHeight(),1);

        for (int i = 0; i < imagen.TellHeight(); i++){
            for (int j = 0; j < imagen.TellWidth(); j++){
                long double inverso = (1 / ((long double)imagen.GetPixel(j, i).Blue + 1));

                velocidadesInversas.asignar(i*imagen.TellWidth() + j, 0, inverso);
                //guardo las velocidades orginales para hacer el ECM
                velocidadesOrig.asignar(i*imagen.TellWidth() + j, 0, (long double)imagen.GetPixel(j, i).Blue + 1);
            }
        }
        cout << "OK!" << endl << endl;

        //inicio: para calcular cuanto tarda el algoritmo
        int inicio = (int)time(NULL);
        Senales D(imagen.TellHeight(), metodo);

        cout << "Usando el metodo " << metodo;
        cout << ", generando " << D.getCantidadSenales();
        cout << " seniales..." << endl << endl;
        cout << "Operando... ";

        D.realizarTomografia(velocidadesInversas, factorRuido);

        cout << "OK!" << endl << endl;
        cout << "El algoritmo termino en " << time(NULL) - inicio << " segundos.\n" << endl;

        //muestro el Error cuadratico medio para ver la calidad
        //de la imagen reconstruida
        long double ecm = 0;
        for (int i = 0; i < imagen.TellHeight(); i++){
            for (int j = 0; j < imagen.TellWidth(); j++){
                long double orig = velocidadesOrig.ver(i*imagen.TellWidth() +j, 0);
                long double aprox = 1/velocidadesInversas.ver(i*imagen.TellWidth() +j, 0);
                ecm += (orig - aprox)*(orig - aprox);
            }
        }
        ecm = ecm/(imagen.TellWidth()*imagen.TellWidth());
        cout << "Error cuadratico Medio: " << ecm << endl << endl;

        //ya reconstrui la imagen, ahora la guardo
        cout << "Guardando archivo " << argvtrucho[2] << " ... ";

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
        imagen.WriteToFile(argvtrucho[2]);
        cout << "OK!" << endl << endl;

        //veo si se selecciono la opcion para graficar
        int parametro = 5;
        while (parametro < argctrucho){
            if (strcmp(argvtrucho[parametro], "-g") == 0){
                parametro++;
                if (parametro == argctrucho){
                    cout << "Parametro -g mal utilizado." << endl << endl;
                    ayuda = true;
                }
                else{
                    cout << "Preparando grafico... ";
                    ofstream paraMatlab;
                    paraMatlab.open(argvtrucho[parametro], ios_base::out);
                    if (paraMatlab.fail()){
                        cout << "FAIL!" << endl << endl;
                        ayuda = true;
                    }
                    else{
                        D.prepararParaGraficarMetodo(paraMatlab, metodo);
                    }
                    paraMatlab.close();
                    cout << "OK!" << endl << endl;
                }
            }

            if (strcmp(argvtrucho[parametro], "-h") == 0){
                ayuda = true;
            }

            parametro++;
        }
    }
    else
        ayuda = true;

    //muestro la ayuda
    if (ayuda){
        cout << "\nSimula el proceso de tomografia y reconstruccion\n\n";
        cout << argvtrucho[0] << " Input_file_bmp Output_file_bmp Metodo Factor_ruido [Opciones...]" << endl << endl;
        cout << "Input_file_bmp:       Imagen de entrada en formato BMP.\n";
        cout << "Output_file_bmp:      Imagen de salida en formato BMP.\n";
        cout << "Metodo:               Metodo de distribucion de señales de 1 a 3\n";
        cout << "Factor_ruido:         Factor de distorcion a aplicar en la imagen.\n";
        cout << "\nOpciones:\n" << endl;
        cout << "-h                    Imprime esta ayuda" << endl;
        cout << "-g <output_file_txt>  Prepara un txt para graficar en matlab\n" << endl;
    }

    system("PAUSE");
	return 0;
}
