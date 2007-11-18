#include "Misil.h"
#include <math.h>
#include <time.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <list>

using namespace std;

struct Grupo {
    list<Misil*> grupoMisiles;
    long double instante;
    long double bombaX;
    long double bombaY;
};

struct Par {
    long double x;
    long double y;
};

void parser(ifstream &in, Misil **misiles, unsigned int &cantMisiles, unsigned int &cantMediciones,
            unsigned int &cantBombas, long double &radioPlaneta, long double &radioBomba){
    in >> cantMisiles;
    in >> cantMediciones;

    *misiles = new Misil[cantMisiles];
    long double *muestraX = new long double[cantMediciones];
    long double *muestraY = new long double[cantMediciones];

    for(unsigned int i = 0; i < cantMisiles; i++){
        for(unsigned int j = 0; j < cantMediciones; j++){
            in >> muestraX[j];
            in >> muestraY[j];
        }
        (*misiles)[i] = Misil(muestraX, muestraY, cantMediciones);
    }
    in >> cantBombas;
    in >> radioBomba;
    in >> radioPlaneta;
    in.close();

    delete muestraX;
    delete muestraY;
}

short int destruidos(list<Misil*>& misiles) {
    short int res = 0;
    list<Misil*>::iterator it;
    for (it = misiles.begin() ; it != misiles.end() ; it++) {
        if ((*it)->destruido) {
            res++;
        }
    }

    return res;
}

inline long double distancia (const Par& p1, const Par& p2) {
    return (sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)));
}

bool interseccionDeMediatrices(Misil** grupoMisiles, float instante,
                               long double radioBomba, Par& res) {
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
    return (distancia(res, m) <= radioBomba);
}

unsigned int Armageddon(ifstream& entrada, ofstream& salida, float paso) {
    Misil* misiles = NULL;
    unsigned int cantMisiles;
    unsigned int cantMuestras;
	unsigned int cantBombas;
	long double radioPlaneta;
	long double radioBomba;
    parser(entrada, &misiles, cantMisiles, cantMuestras, cantBombas, radioPlaneta, radioBomba);
    bool* impactoMisil = new bool[cantMisiles];
    for (unsigned int i = 0; i < cantMisiles; i++) {
        impactoMisil[i] = false;
    }
    //cantImpactados representa la cantidad de misiles que hayan hecho impacto
    //con el planeta, hasta un instante dado
    unsigned int cantImpactados = 0;

    list<Grupo> listaGrupos;
    Par centroCoord;
    centroCoord.x = 0;
    centroCoord.y = 0;
    float instante = cantMuestras + paso;
    while (cantImpactados < cantMisiles) {
        for (unsigned int i = 0; i < cantMisiles ; i++) {
            if (!impactoMisil[i]) {
                Par m1;
                m1.x = misiles[i].posicionX(instante);
                m1.y = misiles[i].posicionY(instante);
                //si el misil no impacto el planeta
                if (distancia(m1, centroCoord) > radioPlaneta) {
                    for (unsigned int j = i + 1; (j < cantMisiles) ; j++) {
                        bool encontroTres = false;
                        if (!impactoMisil[j]) {
                            //todos contra todos de a pares
                            Par m2;
                            m2.x = misiles[j].posicionX(instante);
                            m2.y = misiles[j].posicionY(instante);
                            if (distancia(m2, centroCoord) > radioPlaneta) {
                                //ya defino donde va a ser el lugar hipotetico que explotara la bomba
                                //posiblemente cuando encuentre un 3er misil en rango, este lugar sera modificado
                                //para que la bomba le pegue a los 3
                                Par bomba;
                                bomba.x = (misiles[i].posicionX(instante) + misiles[j].posicionX(instante)) / 2;
                                bomba.y = (misiles[i].posicionY(instante) + misiles[j].posicionY(instante)) / 2;

                                long double distanciaij = distancia(m1, m2);

                                //si la distancia del misil1 con respecto al misil2 es menor o igual al diametro
                                //entonces el misil2 y misil1 pueden ser explotados con una bomba
                                if (distanciaij <= 2*radioBomba) {

                                    for (unsigned int k = j + 1; k < cantMisiles ; k++) {
                                        if (!impactoMisil[k]) {
                                            //el grupito de dos anterior busca un tercero
                                            Par m3;
                                            m3.x = misiles[k].posicionX(instante);
                                            m3.y = misiles[k].posicionY(instante);
                                            if (distancia(m3, centroCoord) > radioPlaneta) {
                                                long double distanciaik = distancia(m1, m3);
                                                long double distanciajk = distancia(m2, m3);
                                                //el tercer misil sera aquel cuya distancia contra los otros
                                                //integrantes del grupo sea menor o igual al diametro
                                                if((distanciaik <= 2*radioBomba) && (distanciajk <= 2*radioBomba)) {
                                                    //el grupito de dos encontro un tercero.
                                                    //todos los puntos dentro de un circulo
                                                    //tienen distancia entre si menor o igual al diametro.
                                                    //agrego el nuevo misil junto con los otros:

                                                    Par iM;
                                                    Misil* grupoMisiles[3] = {&misiles[i], &misiles[j], &misiles[k]};
                                                    encontroTres = true;

                                                    if (interseccionDeMediatrices(grupoMisiles, instante, radioBomba, iM)){
                                                        bomba.x = iM.x;
                                                        bomba.y = iM.y;
                                                    }
                                                    else{
                                                        //Si la interseccion de mediatrices no sirve, quiere decir que los misiles
                                                        //estan casi alineados, entonces tengo que ubicar la bomba en el punto medio de los dos misiles
                                                        //que distan mas lejos uno de otro
                                                        if (distanciaij < distanciaik) {
                                                            if (distanciajk < distanciaik) {
                                                                bomba.x = (misiles[i].posicionX(instante) + misiles[k].posicionX(instante)) / 2;
                                                                bomba.y = (misiles[i].posicionY(instante) + misiles[k].posicionY(instante)) / 2;
                                                            }
                                                            else {
                                                                bomba.x = (misiles[j].posicionX(instante) + misiles[k].posicionX(instante)) / 2;
                                                                bomba.y = (misiles[j].posicionY(instante) + misiles[k].posicionY(instante)) / 2;
                                                            }
                                                        }
                                                        else {
                                                            if (distanciaij < distanciajk) {
                                                                bomba.x = (misiles[j].posicionX(instante) + misiles[k].posicionX(instante)) / 2;
                                                                bomba.y = (misiles[j].posicionY(instante) + misiles[k].posicionY(instante)) / 2;
                                                            }
                                                            else {
                                                                bomba.x = (misiles[i].posicionX(instante) + misiles[j].posicionX(instante)) / 2;
                                                                bomba.y = (misiles[i].posicionY(instante) + misiles[j].posicionY(instante)) / 2;
                                                            }
                                                        }
                                                    }
                                                    //si la bomba no le pega al planeta entonces agrego el grupo
                                                    if (distancia(bomba, centroCoord) > radioBomba + radioPlaneta) {
                                                        //como el chequeo de la distancia se termina con 3 misiles, puede suceder
                                                        //que dentro del rango de explosion se encuentren otros misiles aun no detectados
                                                        Par misil;
                                                        Grupo nuevoGrupo;
                                                        nuevoGrupo.instante = instante;
                                                        nuevoGrupo.bombaX = bomba.x;
                                                        nuevoGrupo.bombaY = bomba.y;
                                                        
                                                        for (unsigned int indice = 0; indice < cantMisiles; indice++) {
                                                            misil.x = misiles[indice].posicionX(instante);
                                                            misil.y = misiles[indice].posicionY(instante);
                                                            if (distancia(misil, bomba) <= radioBomba) {
                                                                nuevoGrupo.grupoMisiles.push_back(&misiles[indice]);
                                                            }
                                                        }
                                                        
                                                        listaGrupos.push_back(nuevoGrupo);
                                                    }//end if (distancia(bomba, centroCoord) > radioBomba + radioPlaneta)
                                                }//end if ((distanciaik <= 2*radioBomba) && (distanciajk <= 2*radioBomba))
                                            }//end if (distancia(m3, centroCoord) > radioPlaneta)
                                            else {
                                                impactoMisil[k] = true;
                                                cantImpactados++;
                                            }
                                        }//end if (!impactoMisil[k]
                                    }//end for (unsigned int k = j + 1; k < cantMisiles; k++)

                                    if((!encontroTres) && (distancia(bomba, centroCoord) > radioBomba + radioPlaneta)) {
                                        //Si no encontro tres y va a crear un grupo de 2, no puede haber otro dentro del radio
                                        //pues sino lo hubiesemos encontrado como grupo de 3
                                        Grupo nuevoGrupo;
                                        nuevoGrupo.instante = instante;
                                        nuevoGrupo.grupoMisiles.push_back(&misiles[i]);
                                        nuevoGrupo.grupoMisiles.push_back(&misiles[j]);
                                        nuevoGrupo.bombaX = bomba.x;
                                        nuevoGrupo.bombaY = bomba.y;
                                        //agrego el grupo a la lista
                                        listaGrupos.push_back(nuevoGrupo);
                                    }
                                }//end if(distanciaij <= 2*radioBomba)
                            }//end if (distancia(m2, centroCoord) > radioPlaneta)
                            else {
                                impactoMisil[j] = true;
                                cantImpactados++;
                            }
                        }//end if (!impactoMisil[j])
                    }//fin del ciclo de busqueda de 2do misil
                }//end if (distancia(m1, centroCoord) > radioPlaneta)
                else {
                    impactoMisil[i] = true;
                    cantImpactados++;
                }
            }//end if (!impactoMisil[i])
        }//end for (unsigned int i = 0; i < cantMisiles; i++)
        instante += paso;
    }//end while (cantImpactados < cantMisiles)

    unsigned int misilesDestruidos = 0;
    if (!(listaGrupos.empty())) {
        while ((cantBombas > 0) && (misilesDestruidos < cantMisiles)) {
            //De los grupos que tengo, quiero aprovechar los mejores casos
            Grupo* mejorCaso = &(listaGrupos.front());
            list<Grupo>::iterator it;
            for (it = listaGrupos.begin() ; it != listaGrupos.end(); it++) {
                if ( ((mejorCaso->grupoMisiles.size() - destruidos(mejorCaso->grupoMisiles)) < (it->grupoMisiles.size() - destruidos(it->grupoMisiles)))){
                    mejorCaso = &(*it);
                }
            }

            //caso en el que todos los grupos encontrados contienen misiles destruidos
            if ((mejorCaso->grupoMisiles.size() - destruidos(mejorCaso->grupoMisiles)) <= 1)
                break;

            //Ahora que tengo el mejor caso, quiero explotar la bomba y destruir los misiles
            misilesDestruidos += (unsigned int)mejorCaso->grupoMisiles.size() - destruidos(mejorCaso->grupoMisiles);
            list<Misil*>::iterator it2;
            for (it2 = mejorCaso->grupoMisiles.begin() ; it2 != mejorCaso->grupoMisiles.end() ; it2++) {
                (*it2)->destruir();
            }

            salida << mejorCaso->instante << " " << mejorCaso->bombaX << " " << mejorCaso->bombaY << endl;
            cantBombas--;
        }
    }

    //caso en el que rompo misiles al azar porque termine de verificar grupos
    for(int i = cantBombas; (i > 0) && (cantBombas > 0) && (misilesDestruidos < cantMisiles) ; i--) {
        Par misilito;
        for (unsigned int m = 0 ; m < cantMisiles ; m++) {
            if (!misiles[m].estaDestruido()) {
                //destruyo el misil en el primer instante posible
                misilito.x = misiles[m].posicionX(cantMuestras + paso);
                misilito.y = misiles[m].posicionY(cantMuestras + paso);
                if (distancia(misilito, centroCoord) > (radioPlaneta + radioBomba)) {
                    misiles[m].destruir();
                    salida << cantMuestras + paso << " " << misilito.x << " " << misilito.y << endl;
                    misilesDestruidos += 1;
                    cantBombas--;
                }
            }
        }
    }

    //si rompiendo todos los misiles aun quedan bombas, entonces exploto bombas en
    //(0, (radioPlaneta + 2*radioBomba)) para que los seres vivientes de ese planeta
    //disfruten los fuegos artificiales
    while (cantBombas > 0) {
        salida << cantMuestras + paso << " " << 0 << " " << (radioPlaneta + 2*radioBomba) << endl;
        cantBombas--;
    }

    delete [] impactoMisil;
    delete [] misiles;

    return misilesDestruidos;
}

int main(int argc, char* argv[]) {
    bool ayuda = false;
    if(argc >= 3){
        float paso = (float)0.05;

        //veo si se selecciono la opcion para setear el paso
        int parametro = 3;
        while (parametro < argc){
            if (strcmp(argv[parametro], "-p") == 0){
                paso = (float)atof(argv[parametro + 1]);
            }

            if (strcmp(argv[parametro], "-h") == 0){
                ayuda = true;
            }

            parametro++;
        }


        ofstream salida;
        salida.open(argv[2], ios_base::out);
        assert(salida.is_open());

        cout << "Levantando archivo " << argv[1] << " ... ";
        ifstream entrada;
        entrada.open(argv[1], ios_base::in);
        assert(entrada.is_open());
        cout << "OK!" << endl << endl;

        cout << "Operando ... ";
        int inicio = (int)time(NULL);
        unsigned int misilesDestruidos;
        misilesDestruidos = Armageddon(entrada, salida, paso);
        int fin = (int)time(NULL);
        cout << "OK!" << endl << endl;
        cout << "El algoritmo termino en " << fin - inicio << " segundo/s.\n" << endl;

        if (misilesDestruidos == 0) {
            cout << "Coronel! No logramos destruir ningun misil :'(";
        }
        else {
            cout << "Coronel! Destruimos " << misilesDestruidos;
            (misilesDestruidos > 1) ? (cout << " misiles!") : (cout << " misil!");
        }

        cout << endl << endl;

        cout << "Archivo " << argv[2] << " guardado" << endl << endl;
    }
    else
        ayuda = true;

    //muestro la ayuda
    if (ayuda){
        cout << "\nSalvando el planeta: \n\n";
        cout << argv[0] << " <Input_file_txt> <Output_file_txt> [Opciones...]" << endl << endl;
        cout << "Input_file_txt:       Archivo de entrada en formato txt.\n";
        cout << "Output_file_txt:      Archivo de salida en formato txt.\n";
        cout << "\nOpciones:\n" << endl;
        cout << "-h                    Imprime esta ayuda" << endl;
        cout << "-p <paso>             Setea el paso (en segundos) de tiempo." << endl;
        cout << "Por defecto el paso es de a 0.05 segundos.\n" << endl;
    }
	return 0;
}
/*    ifstream entrada;
    ofstream salida;
    entrada.open("D:\\Facultad\\Metodos Numericos\\Simulador TP 4\\misilesFede.txt", ios_base::in);
    assert(entrada.is_open());
    salida.open("D:\\Facultad\\Metodos Numericos\\Simulador TP 4\\bombitas.txt", ios_base::out);
    assert(salida.is_open());
    Armageddon(entrada, salida, 0.05);
/*    unsigned int cantMisiles, cantMediciones, cantBombas;
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
    salida.close();

    delete muestraX;
    delete muestraY;

    system("PAUSE");
    return 0;
}
*/