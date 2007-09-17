#include "Matriz.h"

Matriz :: Matriz(int f, int c){
	//f = filas, c = columnas
    fil = f;
    col = c;

    m = new long double* [f];
	for(int i = 0; i < f; i++){
		m[i] = new long double [c];
		for(int j = 0; j < c; j++)
			m[i][j] = 0;
	}
}
int Matriz :: filas(){
    return fil;
}
int Matriz :: columnas(){
    return col;
}

long double Matriz :: ver(int fila, int columna){
    return m[fila][columna];
}
void Matriz :: asignar(int fila, int columna, long double valor){
    m[fila][columna] = valor;
}

/*
 *  triangular: triangula la matriz mediante el metodo de eliminacion gaussiana
 *              con pivoteo parcial.
 */
void Matriz :: triangular(void){
    int filaActual = 0; //notar que filaActual = columnaActual ya que es la que recorre la matriz en diagonal

    for(filaActual = 0 ; filaActual < fil ; filaActual++){
        pivotear(filaActual); //hago pivoteo parcial

        for(int filatemp = 1 ; filatemp < fil ; filatemp++){
            long double coeficiente = m[filatemp][filaActual]/m[filaActual][filaActual];
            restarFilas(coeficiente, filatemp, filaActual);
        }

    }
}

/*
 *  restarfilas: recibe un coeficiente, una fila a anular y la fila de pivote.
 *                y resta las filas por el coeficiente.
 */
void Matriz :: restarFilas(long double coef, int filaAanular, int filaActual){
    for(int i = filaActual; i < fil; i++){
        m[filaAanular][i] = m[filaAanular][i] - coef*m[filaActual][i];
    }
}

void Matriz :: permutar(int fila1, int fila2){
	long double* tmp;

	tmp = m[fila1];
	m[fila1] = m[fila2];
	m[fila2] = tmp;
}

void Matriz :: pivotear(int c){
	int max = 0;

	for(int i = c; i < fil; i++)
		if(m[i][c] > m[max][c])
			max = i;

	permutar(c, max);
}

Matriz :: ~Matriz(){
	for(int i = 0; i < fil; i++)
			delete [] m[i];
	delete [] m;
}


ostream& operator<<(ostream& os, const Matriz& matriz){
	for(int i = 0; i < matriz.fil; i++){
		cout << "FILA" << i << ": ";
		for(int j = 0; j < matriz.col; j++)
			cout << matriz.m[i][j] << "  ";
		cout << endl;
	}
	return os;
}
