#include "Misil.h"
#include <iostream>
#include <fstream>
#include <list>

using namespace std;

typedef struct _grupo {
    Misil* grupoMisiles[];
    long double instante;
    long double bombaX;
    long double bombaY;
} grupo;

Armageddon(ifstream& entrada, ofstream& salida)
{
    Misil* misiles;
    unsigned int cantMisiles;
	unsigned int cantBombas;
	long double radioPlaneta;
	long double radioBomba;
	long double intervalosDeTiempo;
    list<grupo> listaGrupos;
    parser(misiles, cantMisiles, cantBombas, radioPlaneta, radioBomba);
    
    for (unsigned int i = 0; i < cantMisiles; i++) {
        for (unsigned int j = i + 1; j < cantMisiles; j++) {
            //todos contra todos de a pares
            if (distancia(&misiles[i], &misiles[j]) < 2*radioBomba) {
                grupo nuevoGrupoDeDos;
                grupo.grupoMisiles = new Misil* [2];
                listaGrupos.push_front(nuevoGrupoDeDos);
                
                for (unsigned int k = j + 1; k < cantMisiles; k++) {
                    if(esalgunodelosdosanteriores)
                }
            }
        }
    }
}

int main(int argc, char* argv[])
{
    ifstream entrada;
    entrada.open("misilito3.txt", ios_base::in);
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

    salida.open("bombita.txt", ios_base::out);

    if(!salida.is_open()){
        cout << "no abrio el archivo" << endl;
        return 0;
    }

    long double instante = cantMediciones + 0.5;
    salida << instante << " " << test.posicionX(instante) << " " << test.posicionY(instante);
//    salida << test;
    salida.close();

    delete muestraX;
    delete muestraY;
    return 0;
}
