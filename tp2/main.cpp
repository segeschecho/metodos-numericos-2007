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
    radios = new int(cantAngulos);
    n = cantAngulos;
    while(cant < n){
        // agarro el radio para el angulo cant
        arch.getline(data, 100);
        radios[cant] = atoi(data);
        cout << "temperatura para el radio: " << cant << " es: "<< radios[cant] << endl;
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

    ifstream arch("datos-entrada.txt");
    Horno h;
    Matriz mat(6,6);

    if(arch.is_open()){
        cout << "entro al parserrrrrrrrrrrrrr" << endl;
        h = parser(arch);
        cout << "holssssssss" << endl;
    }
    else
    {
        cout << "error no se pudo abrir el archivo:" << endl;
        return -1;
    }

    cout << "Cerrando Archivo...";
    arch.close();
    cout << "OK" << endl << endl;


	system("PAUSE");
	return EXIT_SUCCESS;
}
