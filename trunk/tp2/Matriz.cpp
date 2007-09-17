#include "Matriz.h"

Matriz :: Matriz(unsigned int f, unsigned int c){
	//f = filas, c = columnas
    fil = f;
    col = c;

    m = new long double* [f];
	for(unsigned int i = 0; i < f; i++){
		m[i] = new long double [c];
		for(unsigned int j = 0; j < c; j++)
			m[i][j] = 0;
	}
}
int Matriz :: filas(){
    return fil;
}
int Matriz :: columnas(){
    return col;
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
	for(unsigned int i = 0; i < fil; i++)
			delete [] m[i];
	delete [] m;
}