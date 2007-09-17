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

void Matriz :: permutar(unsigned int fila1, unsigned int fila2){
	long double* tmp;

	tmp = m[fila1];
	m[fila1] = m[fila2];
	m[fila2] = tmp;
}

Matriz :: ~Matriz(){
	for(unsigned int i = 0; i < fil; i++)
			delete [] m[i];
	delete [] m;
}

/*
ostream& operator<<(ostream& os, const Matriz& matriz){
	cout << " ";
	for(int i = 0; i < matriz.col; i++)
		cout << "---"
		cout << "---"
	cout << "---"
	return os;
}*/