#include <iostream>
#include <fstream>
#include "Matriz.h"
#include "Horno.h"

using namespace std;

Horno parser(ifstream &arch){
	int radio, cantAngulos, cantRadios, tint, text;
    char data[128];
    int cant = 0;
    int n = 0;
    int *radios = NULL;

    cout << "levantando datos del Archivo........" << endl << endl;
    //agarro el comentario
    arch.getline(data, 100);
    //agarro radio exterior
    arch.getline(data, 100);
    radio = atoi(data);

    //agarro el comentario
    arch.getline(data, 100);
    //agarro cantidad de angulos
    arch.getline(data, 100);
    cantAngulos = atoi(data);
    //agarro el comentario
    arch.getline(data, 100);
    //agarro cantidad de radios
    arch.getline(data, 100);
    cantRadios = atoi(data);
    //agarro el comentario
    arch.getline(data, 100);
    //agarro temperatura interior
    arch.getline(data, 100);
    tint = atoi(data);
    //agarro el comentario
    arch.getline(data, 100);
    //agarro temperatura exterior
    arch.getline(data, 100);
    text = atoi(data);
    Horno horno(radio, cantAngulos, cantRadios, tint, text);
    cout << "radio exterior: " << horno.getRadio() << endl;
    cout << "cant angulos: " << horno.getCantidadAngulos() << endl;
    cout << "cant radios: " << horno.getCantidadRadios() << endl;
    cout << "temperatura interior: " << horno.getTi() << endl;
    cout << "temp exterior: " << horno.getTinf() << endl;
    //agarro comentario
    arch.getline(data, 100);
    //agarro cosntante K
    arch.getline(data, 100);
    horno.setK(atof(data));
    cout << "K: " << horno.getK() << endl;
    //agarro comentario
    arch.getline(data, 100);
    //agarro constante H
    arch.getline(data, 100);
    horno.setH(atof(data));
    cout << "H: " << horno.getH() << endl;
    //agarro comentario
    arch.getline(data, 100);
    //agarro funcion de temperatura
    n = horno.getCantidadAngulos();
    radios = new int(n);

    while(cant < n){
        // agarro el radio para el angulo cant
        arch.getline(data, 100);
        radios[cant] = atoi(data);
        cout << "temperatura para el radio: " << cant << " es: "<< radios[cant] << endl;
        cant++;
    }

    cout << endl;
    horno.setFuncionTemperatura(radios);

    return horno;
}


int main(){
    ifstream arch("datos-entrada.txt");
    Horno h;
    Matriz mat(6,6);

    if(arch.is_open())
        h = parser(arch);
    else
    {
        cout << "error no se pudo abrir el archivo:" << endl;
        return -1;
    }

    cout << "Cerrando Archivo...";
    arch.close();
    cout << "OK" << endl << endl;

	mat.asignar(0, 0, 1);
	mat.asignar(0, 1, 2);
	mat.asignar(0, 2, 3);
	mat.asignar(0, 3, 4);
	mat.asignar(0, 4, 6);
	mat.asignar(0, 5, 3);


	mat.asignar(1, 0, 7);
	mat.asignar(1, 1, 2);
	mat.asignar(1, 2, 1);
	mat.asignar(1, 3, 15);
	mat.asignar(1, 4, 0);
	mat.asignar(1, 5, 9);

	mat.asignar(2, 0, 1);
	mat.asignar(2, 1, 3);
	mat.asignar(2, 2, 13);
	mat.asignar(2, 3, 11);
	mat.asignar(2, 4, 2);
	mat.asignar(2, 5, 5);

	mat.asignar(3, 0, 21);
	mat.asignar(3, 1, 1);
	mat.asignar(3, 2, 8);
	mat.asignar(3, 3, 6);
	mat.asignar(3, 4, 17);
	mat.asignar(3, 5, 12);

	mat.asignar(4, 0, 23);
	mat.asignar(4, 1, 7);
	mat.asignar(4, 2, 6);
	mat.asignar(4, 3, 14);
	mat.asignar(4, 4, 10);
	mat.asignar(4, 5, 9);

	mat.asignar(5, 0, 1);
	mat.asignar(5, 1, 3);
	mat.asignar(5, 2, 5);
	mat.asignar(5, 3, 29);
	mat.asignar(5, 4, 8);
	mat.asignar(5, 5, 4);

	cout << mat << endl;
	mat.triangular();
	cout << mat << endl;


	system("PAUSE");
	return EXIT_SUCCESS;
}
