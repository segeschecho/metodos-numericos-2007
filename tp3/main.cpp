#include <iostream>
#include <fstream>
#include <time.h>
#include "Matriz.h"
#include "Senales.h"
#include "EasyBMP.h"

using namespace std;

int main(int argc, char* argv[]){
    bool ayuda = false;
    if(argc >= 5){
        unsigned int metodo = atoi(argv[3]);
	    long double factorRuido = atof(argv[4]);
        if (factorRuido < 0){
            factorRuido = 0;
        }

        srand((int)time(NULL));

        /*
         *  Levanto el archivo de entrada
         */
        cout << "Levantando archivo " << argv[1] << " ... ";
	    BMP imagen;
        imagen.ReadFromFile(argv[1]);

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
        cout << " senales..." << endl << endl;
        cout << "Operando ... ";

        D.realizarTomografia(velocidadesInversas, factorRuido);
        int fin = (int)time(NULL);

        cout << "OK!" << endl << endl;
        cout << "El algoritmo termino en " << fin - inicio << " segundos.\n" << endl;

        //muestro el Error cuadratico medio para ver la calidad
        //de la imagen reconstruida
        long double ecm = 0;
        for (int i = 0; i < imagen.TellHeight(); i++){
            for (int j = 0; j < imagen.TellWidth(); j++){
                long double orig = velocidadesOrig.ver(i*imagen.TellWidth() +j, 0);
                long double aprox = 1/velocidadesInversas.ver(i*imagen.TellWidth() + j, 0);
                ecm += (orig - aprox)*(orig - aprox);
            }
        }
        ecm = ecm/(imagen.TellWidth()*imagen.TellWidth());
        cout << "Error cuadratico Medio: " << ecm << endl << endl;

        //ya reconstrui la imagen, ahora la guardo
        cout << "Guardando archivo " << argv[2] << " ... ";

        for (int i = 0; i < imagen.TellWidth(); i++){
            for (int j = 0; j < imagen.TellHeight(); j++){
                RGBApixel nuevoPixel;
                long double valorPixel = (1/(velocidadesInversas.ver(i*imagen.TellWidth() + j,0))) - 1;
                if (valorPixel < 0)
                    valorPixel = 0;

                if (valorPixel > 255)
                    valorPixel = 255;
                nuevoPixel.Alpha = 0;
                nuevoPixel.Red = (unsigned char)valorPixel;
                nuevoPixel.Green = (unsigned char)valorPixel;
                nuevoPixel.Blue = (unsigned char)valorPixel;
                imagen.SetPixel(j, i, nuevoPixel);
            }
        }
        imagen.WriteToFile(argv[2]);
        cout << "OK!" << endl << endl;

        //veo si se selecciono la opcion para graficar
        int parametro = 5;
        while (parametro < argc){
            if (strcmp(argv[parametro], "-g") == 0){
                parametro++;
                if (parametro == argc){
                    cout << "Parametro -g mal utilizado." << endl << endl;
                    ayuda = true;
                }
                else{
                    cout << "Preparando grafico ... ";
                    ofstream paraMatlab;
                    paraMatlab.open(argv[parametro], ios_base::out);
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

            if (strcmp(argv[parametro], "-h") == 0){
                ayuda = true;
            }

            parametro++;
        }
    }
    else
        ayuda = true;

    //muestro la ayuda
    if (ayuda){
        cout << "\nSimular el proceso de tomografia y reconstruccion\n\n";
        cout << argv[0] << " <Input_file_bmp> <Output_file_bmp> <Metodo> <Factor_ruido> [Opciones...]" << endl << endl;
        cout << "Input_file_bmp:       Imagen de entrada en formato BMP.\n";
        cout << "Output_file_bmp:      Imagen de salida en formato BMP.\n";
        cout << "Metodo:               Metodo de distribucion de se�ales de 1 a 3\n";
        cout << "Factor_ruido:         Factor de distorcion a aplicar en la imagen.\n";
        cout << "\nOpciones:\n" << endl;
        cout << "-h                    Imprime esta ayuda" << endl;
        cout << "-g <output_file_txt>  Prepara un txt para graficar en matlab\n" << endl;
    }
    system("PAUSE");
	return 0;
}
