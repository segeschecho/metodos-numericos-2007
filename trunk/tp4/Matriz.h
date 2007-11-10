#ifndef _MATRIZ_H
#define _MATRIZ_H

#include <iostream>
#include <string.h>
#include <assert.h>
using namespace std;

class Matriz{
	friend ostream& operator<<(ostream&, const Matriz&);
	friend ostream& mostrarParaGraficar(ostream&, const Matriz&);
  public:
    Matriz(int = 4, int = 4);
    Matriz(const Matriz& mat);
    int filas() const;
    int columnas() const;

    long double ver(int fila, int columna) const;
    void asignar(int fila, int columna, long double valor);

    void traspuesta (Matriz& res) const;
    void multiplicar (const Matriz& A, const Matriz& B);
    void triangular (Matriz *b = NULL);
    void resolver (Matriz &X, Matriz &b);
    void cuadradosMinimosLineales (const Matriz& A, const Matriz& b);

    void operator= (const Matriz &m1);
    ~Matriz();
  private:
    long double** m;
    int fil;
    int col;
    /* metodos privados */
    void permutarFilas(int fila1, int fila2, Matriz *b);
    void permutarColumnas(int columna1, int columna2);
    void pivoteoParcial(int, Matriz *b);
    void pivoteoTotal(int, Matriz *b);
    void restarFilas(long double coef, int filaAanular, int filaActual, Matriz *b);
};

#endif /*_MATRIZ_H*/
