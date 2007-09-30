#include <iostream>
#include <fstream>
#include "Matriz.h"
#include "Horno.h"

using namespace std;

void guardarParaGrafico(ostream &out, Horno &h){
    Matriz m = *(h.temperaturas);

    int centroR = m.filas() - 1;             //radios

    int X = 0;
    int Y = 0;

    // guardo las X
    out << "X = [ ";

    for(int i = 0 ; i < m.filas(); i++){
        for(int j = 0 ; j < m.columnas(); j++){
            X = (int)((i*(h.rad)/(h.rads))*cos(j*2*PI/centroR));       //cuanto me muevo en "X" = Rcos(tita)

            out << " " << X;
        }
    }

    out << "]; " << endl << endl;
    // guardo las Y
    out << "Y =[ ";
    for(int i = 0 ; i < m.filas(); i++){
        for(int j = 0 ; j < m.columnas(); j++){
            Y = (int)((i*(h.rad)/(h.rads))*sin(j*2*PI/centroR));       //cuanto me muevo en "X"

            out << " " << Y;
        }
    }


    out << "]; " << endl << endl;

    //guardo los resultados del sistema
    out << *(h.temperaturas) << endl;
}

int main(){
    Horno h;
	unsigned int opcion = 0;

	cout << "Simulador para hornos de altas temperaturas\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

	while(opcion != 4){
		cout << "\n\n1. Cargar un horno\n";
		cout << "2. Guardar datos del horno actual para realizar graficos\n";
		cout << "3. Ver temperatura en un punto\n";
		cout << "4. Salir\n\n";
		cout << "Ingresar opcion: ";
		cin >> opcion;

		if(opcion == 1){
			char nombreDelArchivo[256];
			cout << "\n\nIngrese el nombre del archivo: ";
			cin >> nombreDelArchivo;

			ifstream archivoEntrada;
			archivoEntrada.open(nombreDelArchivo, ifstream::in);
			while(archivoEntrada.fail()){
				cout << "\n\nEl archivo no se encuentra. Ingrese el nombre del archivo: ";
				cin >> nombreDelArchivo;
			}

			h.cargar(archivoEntrada);
			archivoEntrada.close();
		}

		if(opcion == 2){
			char nombreDelArchivo[256];
			cout << "\n\nIngrese el nombre del archivo: ";
			cin >> nombreDelArchivo;

			ofstream archivoSalida;
			archivoSalida.open(nombreDelArchivo, ofstream::out);
			guardarParaGrafico(archivoSalida,h);
			archivoSalida.close();
		}

		if(opcion == 3){
			long double radio, angulo;
			cout << "Los datos deben ser ingresados en coordenadas polares\n";
			cout << "\nIngresar radio: ";
			cin >> radio;
			cout << "\nIngresar angulo(Radianes)";
			cin >> angulo;
			cout << h.getTemperatura(radio, angulo);
		}
	}

	system("PAUSE");
	return EXIT_SUCCESS;
}
