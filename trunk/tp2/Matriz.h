#ifndef _MATRIZ_H
#define _MATRIZ_H

#include <iostream>
#include <string.h>
#include <assert.h>
using namespace std;

class Matriz{
	friend ostream& operator<<(ostream&, const Matriz&);
  public:
    Matriz(int = 4, int = 4);
    Matriz(const Matriz& mat);
    int filas() const;
    int columnas() const;

    long double ver(int fila, int columna) const;
    void asignar(int fila, int columna, long double valor);
    void triangular(Matriz *b = NULL);
    void resolver(Matriz &X, Matriz &b);
    void operator =(const Matriz &m1);
    ~Matriz();
  private:
    long double **m;
    int fil;
    int col;
    /* metodos privados */
    void permutar(int fila1, int fila2, Matriz *b);
    void pivotear(int, Matriz *b);
    void restarFilas(long double coef, int filaAanular, int filaActual, Matriz *b);
};






#endif /*_MATRIZ_H*/
