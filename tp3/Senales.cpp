#include <math.h>
#include "Matriz.h"
#include "Senales.h"

/*************************************/
/*          METODOS PUBLICOS         */
/*************************************/

Senales :: Senales(unsigned int dimImagen, unsigned int metodo)
{
    D = NULL;
    dimension = dimImagen;
    switch(metodo){
        case 1:
            metodo1();
            break;
        case 2:
            metodo2();
            break;
        default:
            cout << "No existe el metodo. En su lugar se ejecutara el metodo 1" << metodo << endl << endl;
            metodo1();
            break;
    }
}

Senales :: Senales(Senales& s)
{
    D = new Matriz(s.D->filas(), s.D->columnas());
    *D = *(s.D);
    dimension = s.dimension;
    numSenales = s.numSenales;
}

void Senales :: prepararParaGraficarMetodo(ostream & os, int metodo)
{
    switch(metodo){
        case 1:
            graficarMetodo1(os);
            break;
        default:
            break;
    }
}

void Senales :: realizarTomografia(Matriz& resultado, unsigned long double factorRuido)
{
    Matriz t(numSenales, 1);

    t.multiplicar(*D, resultado);
    //ya tenemos el vector t (tiempos de cada senial) calculado,
    //ahora tenemos que degenerarlo y volver a calcular las
    //velocidades (valores de los pixels) con
    //cuadrados minimos, para reconstruir la imagen

    for (int i = 0; i < t.filas(); i++){
        t.asignar(i, 0, t.ver(i,0) + (rand()% 100)*factorRuido/1000000);
    }

    resultado.cuadradosMinimosLineales(*D, t);
}

unsigned int Senales :: getCantidadSenales(void)
{
    return numSenales;
}

Senales :: ~Senales()
{
    delete D;
}

/*************************************/
/*          METODOS PRIVADOS         */
/*************************************/

/*
 * metodo1: Tira señales desde las 2 paredes verticales de la imagen hacia los
 *          demas pixels que no esten en la misma pared.
 *          Este metodo genera 6*n^2 señales
 */
void Senales :: metodo1(void)
{
    numSenales = 6*dimension*dimension - 2*dimension;
    //este metodo genera 6*n^2 - 2*n señales, siendo n = dimension
    delete D;
    D = new Matriz(numSenales, dimension*dimension);

    int fila = 0;                                         //fila a llenar
    for(unsigned int i = 1; i < dimension; i++){
        for(unsigned int j = 1; j <= dimension; j++){
            //tiro las rectas de la pared izquierda
            tirarSenal(0, i, j, 0, fila);                 //sobre el piso
            tirarSenal(0, i, dimension, j, fila + 1);     //sobre pared derecha
            if(j != dimension)
                tirarSenal(0, i, j, dimension, fila + 2); //sobre el techo

            //tiro las rectas de la pared derecha
            tirarSenal(dimension, i, j, 0, fila + 3);    //sobre el piso
            tirarSenal(dimension, i, 0, j - 1, fila + 4);//sobre pared izquierda
            if(j != dimension)//sobre el techo
                tirarSenal(dimension, i, j - 1, dimension, fila + 5);

            fila += 6;
        }
    }
}

void Senales :: metodo2(void){
    //este metodo genera 6*n^2 - 2*n señales, siendo n = dimImagen
    delete D;
    unsigned int dimImagen = dimension;
    D = new Matriz(6*dimImagen*dimImagen - 2*dimImagen, dimImagen*dimImagen);

    int fila = 0;                         //fila a llenar
    //todos los puntos de las demas paredes
    int cantDestinos = 3*dimImagen - 1;

    for(unsigned int i = 0; i < dimImagen; i++){
        for(unsigned int j = 1; j <= dimImagen; j++){
            int filaoff = 0;
            //pared izquierda
            //tiro la señal hacia el piso
            tirarSenal(0, j/cantDestinos + i, j, 0, fila + filaoff);
            filaoff++;

            //tiro la señal hacia la pared derecha
            tirarSenal(0, (dimImagen + j)/cantDestinos + i, dimImagen, j, fila + filaoff);
            filaoff++;

            //tiro la señal hacia el techo
            if(j != dimImagen){
                if(i != (dimImagen - 1)){
                    tirarSenal(0, (2*dimImagen + j)/cantDestinos + i, j, dimImagen, fila + filaoff);
                    filaoff++;
                }
            }


            //pared derecha
            //tiro la señal hacia el piso
            tirarSenal(dimImagen, j/cantDestinos + i, dimImagen - j, 0, fila + filaoff);
            filaoff++;

            //tiro la señal hacia la pared izquierda
            tirarSenal(dimImagen, (dimImagen + j)/cantDestinos + i, 0, j, fila + filaoff);
            filaoff++;

            //tiro la señal hacia el techo
            if(j != dimImagen){
                if(i != (dimImagen - 1)){
                    tirarSenal(dimImagen, (2*dimImagen + j)/cantDestinos + i, dimImagen - j, dimImagen, fila + filaoff);
                    filaoff++;
                }
            }

            fila += filaoff;
        }
    }
}

void Senales :: tirarSenal(long double x1, long double y1, long double x2, long double y2, int filaALlenar)
{
    if (x1 == x2){   //si la senial es vertical hacemos las cuentas "a mano"
                     //una senial vertical pasa por toda una columna de pixel con distancia, recorriendo
                     //una distancia de 1 por cada uno
        for (unsigned int fil = 0; fil < dimension; fil++)
            if (x1 == dimension)
                D->asignar(filaALlenar, fil*dimension + dimension - 1, 1);
            else
                D->asignar(filaALlenar, fil*dimension + (int)x1, 1);
    }
    else{
        //primero construyo la recta
        //tengo un sistema de 2x2 que es: y1 = x1*a + b
        //                                y2 = x2*a + b
        //entonces: b = y1 - x1*a
        //          y2 = x2*a + y1 - x1*a
        //          a = (y2 - y1) / (x2 - x1)
        //          b = y1 - x1*((y2 - y1) / (x2 - x1))
        //          x2 - x1 != 0 paratodo x2, x1 reales, salvo que sea una senial vertical, lo cual tratamos anteriormente
        long double a = (y2 - y1) / (x2 - x1);
        long double b = y1 - x1*((y2 - y1) / (x2 - x1));
        long double** pares = new long double* [2*(dimension+1)];

        //2*(n+1) lo peor es que pase por la
        //diagonal entonces va a haber 2*(n+1) pares;

        long double yEntero;                  //para ver si hay pares repetidos
        int y = 0;                            //para tener el valor entero
        bool* yRepetidos = new bool [dimension + 1];

        for(unsigned int i = 0; i < dimension+1; i++){
            yRepetidos[i] = false;
        }

        for(unsigned int i = 0; i < 2*(dimension+1); i++){
            pares[i] = new long double [2];
        }

        int cantPares = 0;

        //genero el vector pares donde estan los resultados de aplicar
        // y = a*x + b
        // x = (y - b)/a
        // y lo guardo en pares x,y

        for (unsigned int i = 0; i <= dimension; i++){
            long double temp = a*i + b;

            if((temp >= 0) && (temp <= dimension)){
                pares[cantPares][0] = i;
                pares[cantPares][1] = temp;

                y = (int)temp;          //paso el valor a entero
                yEntero = y;            //lo guardo para comparar

                //veo si temp es entero
                //si lo es lo marco para despues no contarlo
                //(por que va a estar repetido)
                if (yEntero == temp){
                    yRepetidos[y] = true;
                }
                cantPares++;
            }
        }

        for (unsigned int i = 0; (i <= dimension) && (a != 0); i++){
            long double temp = (i - b)/a;

            if(temp >= 0 && temp <= dimension){
                //veo si ese "y" ya estaba antes
                if(!yRepetidos[i]){
                    pares[cantPares][0] = temp;
                    pares[cantPares][1] = i;
                    cantPares++;
                }
            }
        }

        //ordeno por la primer componente
        ordenarParesMenorAMayor(pares, cantPares);

        //ahora calculo la distancia que recorre la señal por cada pixel y
        //genero la fila para la matriz D con estos datos
        for(int i = 0; i < cantPares; i++){
            int fil;
            int col;

            //veo si no es un valor duplicado
            if( (pares[i][0] != -1)){
                //si no es duplicado, veo si el que sigue es un duplicado y el
                //siguiente a este es un valor valido(si no me pase de rango)
                if( (pares[i+1][0] == -1) && (i+2 < cantPares) ){
                    //menor en x
                    col = (int)pares[i][0];

                    //menor en y, arreglo para coordenadas de la matriz
                    if((int)pares[i][1] < (int)pares[i+2][1]){
                        fil = dimension - 1 - (int)pares[i][1];
                    }
                    else
                        fil = dimension - 1 - (int)pares[i+2][1];

                    //calculo la distancia recorrida por la señal en cada
                    //pixel por donde paso
                    long double x = pares[i][0] - pares[i+2][0];
                    long double y = pares[i][1] - pares[i+2][1];

                    D->asignar(filaALlenar, fil*dimension + col, sqrt(pow(x,2) + pow(y,2)));

                    i++; //si hay un repetido adelante tengo que avanzar 2
                }
                //si no, veo si fallo la primer guarda
                //si el siguiente no es un duplicado y es una posicion valida
                else if((pares[i+1][0] != -1) && (i+1 < cantPares))
                {
                    //menor en x
                    col = (int)pares[i][0];
                    //menor en y, arreglo para coordenadas de la matriz
                    if((int)pares[i][1] < (int)pares[i+1][1]){
                        fil = dimension - 1 - (int)pares[i][1];
                    }
                    else
                        fil = dimension - 1 - (int)pares[i+1][1];

                    //calculo la distancia recorrida por la señal en cada
                    //pixel por donde paso
                    long double x = pares[i][0] - pares[i+1][0];
                    long double y = pares[i][1] - pares[i+1][1];

                    D->asignar(filaALlenar, fil*dimension + col, sqrt(pow(x,2) + pow(y,2)));
                }
            }
        }

        for(unsigned int i = 0; i < 2*(dimension+1); i++){
            delete [] pares[i];
        }
        delete [] pares;
        delete [] yRepetidos;
    }
}

void Senales :: ordenarParesMenorAMayor(long double** pares, int filas){
    int topeInf = 0;
    long double temp1;  //variable temporal para el primer componente de la tupla
    long double temp2;  //variable temporal para el segundo componente de la tupla


    while (topeInf < (filas - 1)){
        int i = topeInf;
        int posMenor = i;
        long double menor = pares[i][0];

        while (i < filas){
            if(pares[i][0] < menor){
                menor = pares[i][0];
                posMenor = i;
            }
            i++;
        }

        /* hago el swap de los elementos */
        temp1 = pares[topeInf][0];
        temp2 = pares[topeInf][1];

        pares[topeInf][0] = pares[posMenor][0];
        pares[topeInf][1] = pares[posMenor][1];

        pares[posMenor][0] = temp1;
        pares[posMenor][1] = temp2;

        topeInf++;

    }
}

void Senales :: ordenarParesMayorAMenor(long double** pares, int filas){
    int topeInf = 0;
    long double temp1;  //variable temporal para el primer componente de la tupla
    long double temp2;  //variable temporal para el segundo componente de la tupla


    while (topeInf < (filas - 1)){
        int i = topeInf;
        int posMayor = i;
        long double mayor = pares[i][0];

        while (i < filas){
            if(pares[i][0] > mayor){
                mayor = pares[i][0];
                posMayor = i;
            }
            i++;
        }

        /* hago el swap de los elementos */
        temp1 = pares[topeInf][0];
        temp2 = pares[topeInf][1];

        pares[topeInf][0] = pares[posMayor][0];
        pares[topeInf][1] = pares[posMayor][1];

        pares[posMayor][0] = temp1;
        pares[posMayor][1] = temp2;

        topeInf++;

    }
}

void Senales :: anularRepetidos(long double** pares, int cantPares){
    int cant = cantPares;

    for (int i = 0; i < (cant - 1); i++) {
        if(pares[i][0] == pares[i+1][0]){
            pares[i+1][0] = -1;
            i++;            //salteo el anulado
        }
    }
}

void Senales :: graficarMetodo1(ostream & os){
    os << "COPIAR Y PEGAR LO SIGUIENTE EN EL MATLAB" << endl;
    os << "hold on" << endl;
    os << "axis([0 " << dimension << " 0 " << dimension << " ])" << endl;
    for(unsigned int i = 1; i < dimension; i++){
        for(unsigned int j = 1; j <= dimension; j++){
            //tiro las rectas de la pared izquierda
            os << "plot([0 " << j << "], [" << i << " 0], 'k')" << endl;
            os << "plot([0 " << dimension << "], [" << i << " " << j << "], 'k')" << endl;
            if(j != dimension)
                os << "plot([0 " << j << "], [" << i << " " << dimension << "], 'k')" << endl;

            //tiro las rectas de la pared derecha
            os << "plot([" << dimension << " " << j << "], [" << i << " 0], 'k')" << endl;
            os << "plot([" << dimension << " 0], [" << i << " " << j-1 << "], 'k')" << endl;
            if(j != dimension)
                os << "plot([" << dimension << " " << j-1 << "], [" << i << " " << dimension << "], 'k')" << endl;
        }
    }
}
