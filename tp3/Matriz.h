#ifndef _MATRIZ_H
#define _MATRIZ_H

#include <iostream>
#include <string.h>
#include <assert.h>
using namespace std;

#define MOD(a) ((a < 0) ? (-a) : (a))

template<class T>
class Matriz{
    template<class T1>
    friend ostream& operator<<(ostream&, const Matriz<T1> &);
    template<class T1>
    friend ostream& mostrarParaGraficar(ostream&, const Matriz<T1> &);
  public:
    Matriz(int = 30, int = 30);
    Matriz(const Matriz<T>& mat);
    int filas() const;
    int columnas() const;

    const T& ver(int fila, int columna) const;
    void asignar(int fila, int columna, const T& valor);

    void traspuesta (Matriz<T>& res) const;
    void multiplicar (const Matriz<T>& B, Matriz<T>& res) const;
    void triangular (Matriz<T> *b = NULL);
    void resolver (Matriz<T> &X, Matriz<T> &b);
    void operator= (const Matriz<T> &m1);
    ~Matriz();
  private:
    T** m;
    int fil;
    int col;
    /* metodos privados */
    void permutarFilas(int fila1, int fila2, Matriz<T> *b);
    void permutarColumnas(int columna1, int columna2);
    void pivoteoParcial(int, Matriz<T> *b);
    void pivoteoTotal(int, Matriz<T> *b);
    void restarFilas(long double coef, int filaAanular, int filaActual, Matriz<T> *b);
};

/*************************************/
/*          METODOS PUBLICOS         */
/*************************************/
template<class T>
Matriz<T> :: Matriz(int f, int c){
    //f = filas, c = columnas
    assert((f > 0) && (c > 0));
    fil = f;
    col = c;

    m = new T* [f];
    for(int i = 0; i < f; i++)
        m[i] = new T[c];
}

template<class T>
Matriz<T> :: Matriz(const Matriz<T>& mat){
    m = NULL;
    *this = mat;
}

template<class T>
int Matriz<T> :: filas() const{
    return fil;
}

template<class T>
int Matriz<T> :: columnas() const{
    return col;
}

template<class T>
const T& Matriz<T> :: ver(int fila, int columna) const{
    assert((fila < fil) && (columna < col));
    return &(m[fila][columna]);
}

template<class T>
void Matriz<T> :: asignar(int fila, int columna, const T& valor){
    assert((fila >= 0) && (columna >= 0));
    assert((fila < fil) && (columna < col));
    m[fila][columna] = valor;
}

template<class T>
void Matriz<T> :: traspuesta (Matriz<T>& res) const
{
    //primero borro la matriz que ya estaba
    if (res.m != NULL){
        for(int i = 0; i < fil; i++)
            delete res.m[i];
        delete res.m;
    }

    res.fil = col;
    res.col = fil;
    res.m = new T*[fil];

    for(int i = 0; i < res.fil; i++){
        res.m[i] = new T[col];
        for(int j = 0; j < res.col; j++){
            res.m[i][j] = m[j][i];
        }
    }
}

template<class T>
void Matriz<T> :: multiplicar (const Matriz<T>& B, Matriz<T>& res) const
{
    assert(col == B.fil);

	//primero borro la matriz que ya estaba
    if (res.m != NULL){
        for (int i = 0; i < res.fil; i++)
            delete res.m[i];
        delete res.m;
    }

    res.fil = fil;
    res.col = B.col;
    res.m = new T*[fil];

    for (int i = 0; i < res.fil; i++){
        res.m[i] = new T[col];
        for (int j = 0; j < res.col; j++){
            res.m[i][j] = 0;
		    for (int k = 0; k < col; k++){
                res.m[i][j] += (m[i][k])*(B.m[k][i]);
            }
        }
    }
}

/*
 *  triangular: triangula la matriz mediante el metodo de eliminacion gaussiana
 *              con pivoteo parcial.
 */
template<class T>
void Matriz<T> :: triangular(Matriz<T> *b){
    int filaActual = 0; //notar que filaActual = columnaActual ya que es la que recorre la matriz en diagonal

    for(filaActual = 0 ; filaActual < fil ; filaActual++){
        pivoteoParcial(filaActual, b); //hago pivoteo parcial

        //si luego de hacer pivoteoParcial (o pivoteoTotal si se necesita) encuentro un cero en la diagonal
        //quiere decir que las filas de abajo son todas cero
        if (m[filaActual][filaActual] == 0) {
            break;
        }

        for(int filatemp = filaActual + 1 ; filatemp < fil ; filatemp++){
            long double coeficiente = ((long double)m[filatemp][filaActual])/((long double)m[filaActual][filaActual]);
            restarFilas(coeficiente, filatemp, filaActual, b);
        }
    }
}

/*
 * PRECONDICION: Suponemos que la matriz implicita
 * es triangular superior
 */

template<class T>
void Matriz<T> :: resolver(Matriz<T> &X, Matriz<T> &b){
    assert(X.fil == col);
    assert((b.fil == this->fil) && (b.col == X.col));

    for (int i = fil-1; i >= 0; i--){
        T sumaPorFil = 0;

        for (int j = col-1; j > i; j--)
            sumaPorFil += m[i][j]*X.m[j][0];

        if(m[i][i] == 0)
            X.m[i][0] = 1;
        else
            X.m[i][0] = (b.m[i][0] - sumaPorFil)/m[i][i];
	}
}

template<class T>
void Matriz<T> :: operator =(const Matriz<T> &m1){
    fil = m1.fil;
    col = m1.col;

	//primero borro la matriz que ya estaba
    if (m != NULL){
        for(int i = 0; i < fil; i++)
            delete m[i];
        delete m;
    }

    m = new T*[fil];

    for(int i = 0; i < fil; i++){
        m[i] = new T[col];
        for(int j = 0; j < col; j++){
            m[i][j] = m1.m[i][j];
        }
    }
}

template<class T>
Matriz<T> :: ~Matriz(){
    for(int i = 0; i < fil; i++)
        delete m[i];
    delete m;
}

/*************************************/
/*          METODOS PRIVADOS         */
/*************************************/

template<class T>
void Matriz<T> :: permutarFilas(int fila1, int fila2, Matriz<T> *b){
    T* tmp;

    tmp = m[fila1];
    m[fila1] = m[fila2];
    m[fila2] = tmp;

    if(b != NULL){
        tmp = b->m[fila1];
        b->m[fila1] = b->m[fila2];
        b->m[fila2] = tmp;
    }
}

template<class T>
void Matriz<T> :: permutarColumnas(int columna1, int columna2){
    T tmp;
    
    for (int i = 0; i < fil; i++) {
        tmp = (m[i][columna1]);
        m[i][columna1] = m[i][columna2];
        m[i][columna2] = tmp;
	}
}

template<class T>
void Matriz<T> :: pivoteoParcial(int c, Matriz<T> *b){
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

template<class T>
void Matriz<T> :: pivoteoTotal(int fila, Matriz<T> *b){
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

template<class T>
void Matriz<T> :: restarFilas(long double coef, int filaAanular, int filaActual, Matriz<T> *b){
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

template<class T1>
ostream& operator<<(ostream& os, const Matriz<T1>& matriz){
    for(int i = 0; i < matriz.fil; i++){
        os << "\nFila" << i << ": ";
        for(int j = 0; j < matriz.col; j++)
            os << (long double)matriz.m[i][j] << " ";
    }
    return os;
}

template<class T1>
ostream& mostrarParaGraficar(ostream& os, const Matriz<T1>& matriz){
    os << "[ ";
    for(int i = 0; i < matriz.fil; i++){
        for(int j = 0; j < matriz.col; j++)
            os << matriz.m[i][j] << " ";
    }
    os << "];";
    return os;
}

#endif /*_MATRIZ_H*/
