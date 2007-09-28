#include "Matriz.h"
#define MOD(a) ((a < 0) ? (-a) : (a))

ostream& operator<<(ostream& os, const Matriz& matriz){
	for(int i = 0; i < matriz.fil; i++){
		cout << "FILA" << i << ": ";
		for(int j = 0; j < matriz.col; j++)
			cout << matriz.m[i][j] << "     ";
		cout << endl;
	}
	return os;
}

Matriz :: Matriz(int f, int c){
	//f = filas, c = columnas
	assert((f > 0) && (c > 0));
    fil = f;
    col = c;

    m = new long double* [f];
	for(int i = 0; i < f; i++){
		m[i] = new long double[c];
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
	assert((fila >= 0) && (columna >= 0));
	assert((fila < fil) && (columna < col));
    m[fila][columna] = valor;
}

/*
 *  triangular: triangula la matriz mediante el metodo de eliminacion gaussiana
 *              con pivoteo parcial.
 */
void Matriz :: triangular(Matriz &b){
    int filaActual = 0; //notar que filaActual = columnaActual ya que es la que recorre la matriz en diagonal

    for(filaActual = 0 ; filaActual < fil ; filaActual++){
        pivotear(filaActual, b); //hago pivoteo parcial

        for(int filatemp = filaActual + 1 ; filatemp < fil ; filatemp++){
            long double coeficiente = m[filatemp][filaActual]/m[filaActual][filaActual];
            restarFilas(coeficiente, filatemp, filaActual, b);
        }
    }
}

/*
 * PRECONDICION: Suponemos que la matriz implicita
 * es triangular superior
 */

void Matriz :: resolver(Matriz &X, Matriz &b){
	assert(X.fil == col);
	assert((b.fil == this->fil) && (b.col == X.col));

	for (int i = fil-1; i >= 0; i--){
		long double sumaPorFil = 0;

		for (int j = col-1; j > i; j--)
			sumaPorFil += m[i][j]*X.m[j][0];
		X.m[i][0] = (b.m[i][0] - sumaPorFil)/m[i][i];
	}
}

void Matriz :: operator =(const Matriz &m1){
    fil = m1.fil;
    col = m1.col;

    //cout << fil << endl;
    //cout << col << endl;
    m = new long double *[fil];

    for(int i = 0; i < fil; i++){
		m[i] = new long double[col];
		for(int j = 0; j < col; j++){
	//	    cout << m1.m[i][j];
			m[i][j] = m1.m[i][j];
		}
	}
}

Matriz :: ~Matriz(){
//	cout << *this << endl;
	for(int i = 0; i < fil; i++)
		delete m[i];
	delete m;
}

void Matriz :: permutar(int fila1, int fila2, Matriz &b){
	long double* tmp;

	tmp = m[fila1];
	m[fila1] = m[fila2];
	m[fila2] = tmp;

	tmp = b.m[fila1];
	b.m[fila1] = b.m[fila2];
	b.m[fila2] = tmp;
}

void Matriz :: pivotear(int c, Matriz &b){
	int max = c;

	for(int i = c; i < fil; i++){
		if(MOD(m[i][c]) > MOD(m[max][c]))
			max = i;
	}

	permutar(c, max, b);
}

/*
 *  restarfilas: recibe un coeficiente, una fila a anular y la fila de pivote.
 *                y resta las filas por el coeficiente.
 */

void Matriz :: restarFilas(long double coef, int filaAanular, int filaActual, Matriz &b){
    for(int i = filaActual; i < fil; i++){
        m[filaAanular][i] = m[filaAanular][i] - coef*m[filaActual][i];
		if(MOD(m[filaAanular][i]) < 1e-10) //10^(-10)
			m[filaAanular][i] = 0;
    }

    b.m[filaAanular][0] = b.m[filaAanular][0] - coef*b.m[filaActual][0];
}
