#include "Matriz.h"

Matriz :: Matriz(unsigned int fila, unsigned int col, long double a[][]){
    filas = fila;
    columnas = col;

    m = new long double[fila][col];
    memcpy
}
int Matriz :: filas(){
    return filas;
}
int Matriz :: columnas(){
    return columnas;
}

long double Matriz :: ver(unsigned int fila, unsigned int columna){
    return m[fila][columna];
}
void Matriz :: asignar(unsigned int fila, unsigned int columna, long double valor){
    m[fila][columna] = valor;
}
void Matriz :: triangular(void){

}

Matriz :: ~Matriz(){
    delete [][] m;
}