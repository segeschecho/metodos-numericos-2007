#include "Misil.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <list>

using namespace std;

struct Grupo {
    Misil** grupoMisiles;
    long double instante;
    long double bombaX;
    long double bombaY;
};

struct Par {
    long double x;
    long double y;
};

void parser(ifstream &in, Misil *misiles, unsigned int &cantMisiles, unsigned int &cantBombas, long double &radioPlaneta, long double &radioBomba){
    int cantMediciones = 0;

    in >> cantMisiles;
    in >> cantMediciones;

    cout << "cant mediciones " << cantMediciones << endl;
    cout << "cant misiles " << cantMisiles << endl;

    misiles = new Misil[cantMisiles];
    long double *muestraX = new long double[cantMediciones];
    long double *muestraY = new long double[cantMediciones];

    for(int i = 0; i < cantMisiles; i++){
        for(int j = 0; j < cantMediciones; j++){
            in >> muestraX[j];
            cout << "muestra en x " << muestraX[j];
            in >> muestraY[j];
            cout << " muestra en y " << muestraY[j] << endl;
        }

        misiles[i] = Misil((char)i, muestraX, muestraY, cantMediciones);
    }
    in >> cantBombas;
    in >> radioBomba;
    in >> radioPlaneta;

    cout << "num bombas " << cantBombas << endl;
    cout << "radio planeta " << radioPlaneta << endl;
    cout << "radio bomba " << radioBomba << endl;

    delete muestraX;
    delete muestraY;
}

inline long double distancia (const Par& p1, const Par& p2) {
    return (sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)));
}

bool interseccionDeMediatrices(Misil** grupoMisiles, float instante, Par res) {
    long double x1 = grupoMisiles[0]->posicionX(instante);
    long double x2 = grupoMisiles[1]->posicionX(instante);
    long double x3 = grupoMisiles[2]->posicionX(instante);
    long double y1 = grupoMisiles[0]->posicionY(instante);
    long double y2 = grupoMisiles[1]->posicionY(instante);
    long double y3 = grupoMisiles[2]->posicionY(instante);

    //chequeo los casos en que no se puede usar mediatrices
    if ((x1 == x2 && x1 == x3) || (y1 == y2 && y1 == y3))
       return false;

    long double a1, b1, a2, b2;

    long double puntoMedioX1 = (x1 + x2)/2;
    long double puntoMedioX2 = (x1 + x3)/2;

    long double puntoMedioY1 = (y1 + y2)/2;
    long double puntoMedioY2 = (y1 + y3)/2;

        //calculo la ecuacion de la recta perpendicular al segmento (x1,y1) (x2,y2)
    if (x1 == x2){   //si los puntos estan verticales hacemos las cuentas "a mano
        //coeficientes de la recta perpendicular al segmento
        a1 = 0;
        b1 = (y1 + y2)/2;
    }
    else{
        //calculo la pendiente del segmento
        a1 = (y2 - y1) / (x2 - x1);

        //calculo los coeficientes para la recta perpendicular del segmento
        //si a2 == 0 quiere decir que es una recta horizontal, cuya
        //recta perpendicular es vertical(que no es una funcion)
        if(a1 != 0){
            a1 = -1/a1;
            b1 = puntoMedioY1 - a1*puntoMedioX1;
        }
        else
            b1 = 0;
    }

    //calculo la ecuacion de la recta perpendicular al segmento (x1,y1) (x3,y3)
    if (x1 == x3){
        a2 = 0;
        b2 = (y1 + y3)/2;
    }
    else{
        //calculo la pendiente del segmento
        a2 = (y3 - y1) / (x3 - x1);

        //calculo los coeficientes para la recta perpendicular del segmento
        //si a2 == 0 quiere decir que es una recta horizontal, cuya
        //recta perpendicular es vertical(que no es una funcion)
        if(a2 != 0){
            a2 = -1/a2;
            b2 = puntoMedioY2 - a2*puntoMedioX2;
        }
        else
            b2 = 0;
    }


    //calculo la interseccion
    if(a1 == 0){
        res.y = a2*puntoMedioX1 + b2;
        res.x = puntoMedioX1;
    }
    else if(a2 == 0){
        res.y = a1*puntoMedioX2 + b1;
        res.x = puntoMedioX2;
    }
    else{
        //si son rectas normales las igualo y calculo la interseccion.
        res.x = (b2 - b1)/(a1 - a2);
        res.y = a1*res.x + b1;
    }

    Par m;
    m.x = x1;
    m.y = y1;
    return distancia(res, m) < 2;
}

void Armageddon(ifstream& entrada, ofstream& salida, float paso, float tmax)
{
    Misil* misiles;
    unsigned int cantMisiles;
    unsigned int cantMuestras;
	unsigned int cantBombas;
	long double radioPlaneta;
	long double radioBomba;
	long double intervalosDeTiempo;
    list<Grupo> listaGrupos;
    parser(entrada, misiles, cantMisiles, cantBombas, radioPlaneta, radioBomba);

    for (float instante = cantMuestras + paso; instante < tmax; instante += paso) {
        for (unsigned int i = 0; i < cantMisiles; i++) {
            for (unsigned int j = i + 1; j < cantMisiles; j++) {
                //todos contra todos de a pares
                Par m1;
                Par m2;
                m1.x = misiles[i].posicionX(instante);
                m1.y = misiles[i].posicionY(instante);
                m2.x = misiles[j].posicionX(instante);
                m2.y = misiles[j].posicionY(instante);

                if (distancia(m1, m2) <= 2*radioBomba) {
                    //si la distancia del misil1 con respecto al misil2 es menor o igual al diametro
                    //agrego el grupito de 2 a la lista
                    //cada candidato representa un misil susceptible de ser agregado al grupo
                    short int candidato1 = i;
                    short int candidato2 = j;
                    short int candidato3 = -1;

                    for (unsigned int k = j + 1; k < cantMisiles; k++) {
                        //el grupito de dos anterior busca un tercero
                        Par m3;
                        m3.x = misiles[k].posicionX(instante);
                        m3.y = misiles[k].posicionY(instante);
                        long double distanciaik = distancia(m1, m3);
                        long double distanciajk = distancia(m2, m3);
                        //el tercer misil sera aquel cuya distancia contra los otros
                        //integrantes del grupo sea menor o igual al diametro
                        if((distanciaik <= 2*radioBomba) && (distanciajk <= 2*radioBomba)) {
                            //el grupito de dos encontro un tercero.
                            //todos los puntos dentro de un circulo
                            //tienen distancia entre si menor o igual al diametro.
                            //agrego el nuevo misil junto con los otros:
                            Grupo nuevoGrupoDeDos;
                            nuevoGrupoDeDos.instante = instante;
                            nuevoGrupoDeDos.grupoMisiles = new Misil* [3];
                            nuevoGrupoDeDos.grupoMisiles[0] = &misiles[i];
                            nuevoGrupoDeDos.grupoMisiles[1] = &misiles[j];
                            nuevoGrupoDeDos.grupoMisiles[2] = &misiles[k];

                            Par iM;
                            if (interseccionDeMediatrices(nuevoGrupoDeDos.grupoMisiles, instante, iM)){
                                nuevoGrupoDeDos.bombaX = iM.x;
                                nuevoGrupoDeDos.bombaY = iM.y;
                            }
                            else{
                                nuevoGrupoDeDos.bombaX = (misiles[i].posicionX(instante) + misiles[i].posicionX(instante)) / 2;
                                nuevoGrupoDeDos.bombaY = (misiles[i].posicionY(instante) + misiles[i].posicionY(instante)) / 2;
                            }

                            listaGrupos.push_front(nuevoGrupoDeDos);
                        }
                        else{
                            Grupo nuevoGrupoDeDos;
                            nuevoGrupoDeDos.instante = instante;
                            nuevoGrupoDeDos.bombaX = (misiles[i].posicionX(instante) + misiles[i].posicionX(instante)) / 2;
                            nuevoGrupoDeDos.bombaY = (misiles[i].posicionY(instante) + misiles[i].posicionY(instante)) / 2;
                            nuevoGrupoDeDos.grupoMisiles = new Misil* [2];
                            nuevoGrupoDeDos.grupoMisiles[0] = &misiles[i];
                            nuevoGrupoDeDos.grupoMisiles[1] = &misiles[j];
                            listaGrupos.push_front(nuevoGrupoDeDos);
                        }
                    }
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
