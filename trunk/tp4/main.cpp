#include "Misil.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
    ifstream entrada;
    entrada.open("D:\\Facultad\\Metodos Numericos\\Simulador TP 4\\misilito.txt", ios_base::in);
    unsigned int cantMisiles, cantMediciones, cantBombas;
    unsigned long double radioBomba, radioPlaneta;

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
    Misil test(0, muestraX, muestraY, 4);

    salida.open("d:\\Facultad\\Metodos Numericos\\Simulador TP 4\\bombita.txt", ios_base::out);

    salida << cantMediciones << " " << test.posicionX(cantMediciones) << " " << test.posicionY(cantMediciones);
    salida.close();

    delete muestraX;
    delete muestraY;
    return 0;
}