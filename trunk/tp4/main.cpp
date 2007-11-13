#include "Misil.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
    ifstream entrada;
    entrada.open("H:\\Simulador TP 4\\misilito3.txt", ios_base::in);
    unsigned int cantMisiles, cantMediciones, cantBombas;
    long double radioBomba, radioPlaneta;

    entrada >> cantMisiles;
    entrada >> cantMediciones;

    long double* muestraX;
    long double* muestraY;

    muestraX = new long double [cantMediciones];
    muestraY = new long double [cantMediciones];

    for (unsigned int i = 0 ; i < cantMediciones ; i++){
        entrada >> muestraX[i];
        entrada >> muestraY[i];
    }

    entrada >> cantBombas;
    entrada >> radioBomba;
    entrada >> radioPlaneta;


    entrada.close();
    ofstream salida;
    Misil test(0, muestraX, muestraY, cantMediciones);

    salida.open("H:\\Simulador TP 4\\bombita.txt", ios_base::out);

    if(!salida.is_open()){
        cout << "no abrio el archivo" << endl;
        return 0;
    }

    long double instante = cantMediciones + 2;
    salida << instante << " " << test.posicionX(instante) << " " << test.posicionY(instante);
//    salida << test;
    salida.close();

    delete muestraX;
    delete muestraY;
    return 0;
}
