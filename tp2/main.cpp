#include <iostream>
#include <fstream>
#include "Matriz.h"
#include "Horno.h"

using namespace std;

Horno parser(ifstream &arch){
	int radio, cantAngulos, cantRadios, tint, text;
	long double h, k;
    char data[128];
    int cant = 0;
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
    //agarro comentario
    arch.getline(data, 100);
    //agarro cosntante K
    arch.getline(data, 100);
    k = atof(data);
    //agarro comentario
    arch.getline(data, 100);
    //agarro constante H
    arch.getline(data, 100);
    h = atof(data);
    //agarro comentario
    arch.getline(data, 100);
    //agarro funcion de temperatura
    radios = new int [cantAngulos];

    while(cant < cantAngulos){
        // agarro el radio para el angulo cant
        arch.getline(data, 100);
        radios[cant] = atoi(data);
//        cout << "temperatura para el radio: " << cant << " es: "<< radios[cant] << endl;
        cant++;
    }

    Horno horno(radio, cantAngulos, cantRadios, tint, text, k, h, &radios[0]);
    cout << "radio exterior: " << horno.getRadio() << endl;
    cout << "cant angulos: " << horno.getCantidadAngulos() << endl;
    cout << "cant radios: " << horno.getCantidadRadios() << endl;
    cout << "temperatura interior: " << horno.getTi() << endl;
    cout << "temp exterior: " << horno.getTinf() << endl;
    cout << "K: " << horno.getK() << endl;
    cout << "H: " << horno.getH() << endl;
    cout << endl;

    return horno;
}


int main(){
/*
	Matriz mat(3,3);
	Matriz b(3,1);
	Matriz X(3,1);
	mat.asignar(0,0,1);
	mat.asignar(0,1,4);
	mat.asignar(0,2,1);
	mat.asignar(1,0,1);
	mat.asignar(1,1,6);
	mat.asignar(1,2,-1);
	mat.asignar(2,0,2);
	mat.asignar(2,1,-1);
	mat.asignar(2,2,2);

	b.asignar(0,0,7);
	b.asignar(1,0,13);
	b.asignar(2,0,5);

	cout << "mat = \n"<< mat << endl << endl;
	cout << "b = \n" << b << endl << endl;
	mat.triangular(b);
	cout << "mat = \n"<< mat << endl << endl;
	cout << "X = \n" << X << endl << endl;
	cout << "b = \n" << b << endl << endl;

	mat.resolver(X, b);
	cout << "mat = \n"<< mat << endl << endl;
	cout << "X = \n" << X << endl << endl;
	cout << "b = \n" << b << endl << endl;
*/
    ifstream archivo("datos-entrada.txt");
    Horno h;
    Matriz mat(6,6);

    if(archivo.is_open()){
        h.cargar(archivo);
		cout << *(h.temperaturas);
    }
    else{
		cout << "Error! No se pudo abrir el archivo" << endl;
		system("PAUSE");
        return -1;
    }

    archivo.close();

	system("PAUSE");
	return EXIT_SUCCESS;
}
