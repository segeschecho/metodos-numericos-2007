#include "Matriz.h"
#define MOD(a) ((a < 0) ? (-a) : (a))

/*************************************/
/*          METODOS PUBLICOS         */
/*************************************/
Matriz :: Matriz(int f, int c)
{
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

Matriz :: Matriz(const Matriz& mat)
{
    m = NULL;
    *this = mat;
}

int Matriz :: filas() const
{
    return fil;
}

int Matriz :: columnas() const
{
    return col;
}

long double Matriz :: ver(int fila, int columna) const
{
    assert((fila < fil) && (columna < col));
    return (m[fila][columna]);
}

void Matriz :: asignar(int fila, int columna, const long double valor)
{
    assert((fila >= 0) && (columna >= 0));
    assert((fila < fil) && (columna < col));
    m[fila][columna] = valor;
}

void Matriz :: traspuesta (Matriz& res) const
{
    //primero borro la matriz que ya estaba
    if (res.m != NULL){
        for(int i = 0; i < fil; i++)
            delete res.m[i];
        delete res.m;
    }

    res.fil = col;
    res.col = fil;
    res.m = new long double* [fil];

    for(int i = 0; i < res.fil; i++){
        res.m[i] = new long double [col];
        for(int j = 0; j < res.col; j++){
            res.m[i][j] = m[j][i];
        }
    }
}

void Matriz :: multiplicar (const Matriz& A, const Matriz& B)
{
    assert(A.col == B.fil);

	//primero borro la matriz que ya estaba
    if (m != NULL){
        for (int i = 0; i < fil; i++)
            delete m[i];
        delete m;
    }

    fil = A.fil;
    col = B.col;
    m = new long double* [fil];

    for (int i = 0; i < fil; i++){
        m[i] = new long double [col];
        for (int j = 0; j < col; j++){
            long double suma = 0;
		    for (int k = 0; k < A.col; k++){
                suma += (A.m[i][k])*(B.m[k][j]);
            }
            m[i][j] = suma;
        }
    }
}

/*
 *  triangular: triangula la matriz mediante el metodo de eliminacion gaussiana
 *              con pivoteo parcial.
 */
void Matriz :: triangular(Matriz *b)
{
    int filaActual = 0; //notar que filaActual = columnaActual ya que es la que recorre la matriz en diagonal

    for(filaActual = 0 ; filaActual < fil ; filaActual++){
        pivoteoParcial(filaActual, b); //hago pivoteo parcial

        //si luego de hacer pivoteoParcial (o pivoteoTotal si se necesita) encuentro un cero en la diagonal
        //quiere decir que las filas de abajo son todas cero
        if (m[filaActual][filaActual] == 0) {
            break;
        }

        for(int filatemp = filaActual + 1 ; filatemp < fil ; filatemp++){
            long double coeficiente = (m[filatemp][filaActual])/(m[filaActual][filaActual]);
            restarFilas(coeficiente, filatemp, filaActual, b);
        }
    }
}

/*
 * PRECONDICION: Suponemos que la matriz implicita
 * es triangular superior
 */

void Matriz :: resolver(Matriz &X, Matriz &b)
{
    assert(X.fil == col);
    assert((b.fil == this->fil) && (b.col == X.col));

    for (int i = fil-1; i >= 0; i--){
        long double sumaPorFil = 0;

        for (int j = col-1; j > i; j--)
            sumaPorFil += m[i][j]*X.m[j][0];

        if(m[i][i] == 0)
            X.m[i][0] = 1;
        else
            X.m[i][0] = (b.m[i][0] - sumaPorFil)/m[i][i];
	}
}

void Matriz :: cuadradosMinimosLineales(const Matriz& A, const Matriz& b)
{
    //En este algoritmo se aprobecha que A(traspuesta)*A es simetrica
    Matriz caca(5, 3);
    caca.asignar(0, 0, 1);
    caca.asignar(0, 1, 2);
    caca.asignar(0, 2, 3);
    caca.asignar(1, 0, 1);
    caca.asignar(1, 1, 2);
    caca.asignar(1, 2, 3);
    caca.asignar(2, 0, 1);
    caca.asignar(2, 1, 2);
    caca.asignar(2, 2, 3);
    caca.asignar(3, 0, 1);
    caca.asignar(3, 1, 2);
    caca.asignar(3, 2, 3);
    caca.asignar(4, 0, 1);
    caca.asignar(4, 1, 2);
    caca.asignar(4, 2, 3);
    Matriz bb(5, 1);
    bb.asignar(0, 0, 1);
    bb.asignar(1, 0, 1);
    bb.asignar(2, 0, 1);
    bb.asignar(3, 0, 1);
    bb.asignar(4, 0, 1);
    Matriz res(3, 1);

    Matriz AtA(caca.col, caca.col);
    Matriz Atb(caca.col, 1);

    for (int i = 0; i < caca.fil; i++){
        for (int j = i; j < caca.col; j++){
            long double temp = 0;
            for (int c = 0; c < caca.fil; c++){
                temp += caca.m[c][i]*caca.m[c][j];
            }
            AtA.m[i][j] = temp;
            AtA.m[j][i] = temp;
        }
    }

    for (int i = 0; i < Atb.fil; i++){
        long double temp = 0;
        for (int j = 0; j < caca.fil; j++){
            temp += caca.m[j][i]*bb.m[j][0];
        }
        Atb.m[i][0] = temp;
    }

    cout << AtA << endl;
    cout << Atb << endl;
    AtA.triangular(&Atb);
    cout << AtA << endl;
    cout << Atb << endl;
    AtA.resolver(res, Atb);
    cout << res;
}

void Matriz :: operator =(const Matriz &m1)
{
    fil = m1.fil;
    col = m1.col;

	//primero borro la matriz que ya estaba
    if (m != NULL){
        for(int i = 0; i < fil; i++)
            delete m[i];
        delete m;
    }

    m = new long double*[fil];

    for(int i = 0; i < fil; i++){
        m[i] = new long double [col];
        for(int j = 0; j < col; j++){
            m[i][j] = m1.m[i][j];
        }
    }
}

Matriz :: ~Matriz()
{
    for(int i = 0; i < fil; i++)
        delete m[i];
    delete m;
}

/*************************************/
/*          METODOS PRIVADOS         */
/*************************************/

void Matriz :: permutarFilas(int fila1, int fila2, Matriz *b)
{
    long double* tmp;

    tmp = m[fila1];
    m[fila1] = m[fila2];
    m[fila2] = tmp;

    if(b != NULL){
        tmp = b->m[fila1];
        b->m[fila1] = b->m[fila2];
        b->m[fila2] = tmp;
    }
}

void Matriz :: permutarColumnas(int columna1, int columna2)
{
    long double tmp;

    for (int i = 0; i < fil; i++) {
        tmp = (m[i][columna1]);
        m[i][columna1] = m[i][columna2];
        m[i][columna2] = tmp;
	}
}

void Matriz :: pivoteoParcial(int c, Matriz *b)
{
    int max = c;

    for(int i = c; i < fil; i++){
        if(MOD(m[i][c]) > MOD(m[max][c]))
            max = i;
	}

	//si me aparece un cero en la diagonal (la matriz es singular), tengo que hacer pivoteo total para
	//intentar evitarlo
    if (m[max][c] == 0) {
		pivoteoTotal(c, b);
    }
    else {
        permutarFilas(c, max, b);
	}
}

void Matriz :: pivoteoTotal(int fila, Matriz *b)
{
    int maxI = fila;
    int maxJ = fila;

    for (int i = fila; i < fil; i++) {
        for (int j = 0; j < col; j++) {
            if(MOD(m[i][j]) > MOD(m[maxI][maxJ])){
                maxI = i;
                maxJ = j;
            }
        }
    }

    permutarFilas(fila, maxI, b);
    permutarColumnas(fila, maxJ);
}

/*
 *  restarfilas: recibe un coeficiente, una fila a anular y la fila de pivote.
 *                y resta las filas por el coeficiente.
 */

void Matriz :: restarFilas(long double coef, int filaAanular, int filaActual, Matriz *b)
{
    for(int i = filaActual; i < fil; i++){
        m[filaAanular][i] = m[filaAanular][i] - coef*m[filaActual][i];
        if(MOD(m[filaAanular][i]) < 1e-10) //10^(-10)
            m[filaAanular][i] = 0;
    }

    if(b != NULL)
	    b->m[filaAanular][0] = b->m[filaAanular][0] - coef*b->m[filaActual][0];
}

/*************************************/
/*          FUNCIONES FRIEND         */
/*************************************/

ostream& operator<<(ostream& os, const Matriz& matriz)
{
    for(int i = 0; i < matriz.fil; i++){
        os << "\nFila" << i << ": ";
        for(int j = 0; j < matriz.col; j++)
            os << matriz.m[i][j] << " ";
    }
    return os;
}

ostream& mostrarParaGraficar(ostream& os, const Matriz& matriz)
{
    os << "[ ";
    for(int i = 0; i < matriz.fil; i++){
        for(int j = 0; j < matriz.col; j++)
            os << matriz.m[i][j] << " ";
    }
    os << "];";
    return os;
}
