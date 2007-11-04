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
    char* argvtrucho[7] = {"exe", "10.bmp", "test2.bmp", "3", "0", "-g", "grafico.txt"};// "-g", "graficameEsta.txt"};
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
        Matriz velocidadesInversas(imagen.TellWidth()*imagen.TellHeight(),1);

        for (int i = 0; i < imagen.TellHeight(); i++){
            for (int j = 0; j < imagen.TellWidth(); j++){
                long double inverso = (1 / ((long double)imagen.GetPixel(j, i).Blue + 1));
                velocidadesInversas.asignar(i*imagen.TellWidth() + j,0,inverso);
            }
        }
        cout << "OK!" << endl << endl;

        int inicio = (int)time(NULL);
        Senales D(imagen.TellHeight(), metodo);

        cout << "Usando el metodo " << metodo;
        cout << ", generando " << D.getCantidadSenales();
        cout << " seniales..." << endl << endl;
        cout << "Operando... ";

        D.realizarTomografia(velocidadesInversas, factorRuido);

        cout << "OK!" << endl << endl;
        cout << "El algoritmo termino en " << time(NULL) - inicio << " segundos.\n" << endl;

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

    if (ayuda){
        cout << "El formato de la ejecucion del programa debe cumplir:\n";
        cout << argvtrucho[0] << " <input_file_bmp> <output_file_bmp> <metodo> <factor_ruido> [opciones...]" << endl << endl;
        cout << "Las opciones son:\n" << endl;
        cout << "-h\t\t\t\t\tImprime esta ayuda" << endl;
        cout << "-g <output_file_txt>\t\t\tPrepara un txt para graficar en matlab\n" << endl;
    }

    system("PAUSE");
	return 0;
}
