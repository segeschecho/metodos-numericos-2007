#ifndef _MATRIZ_H
#define _MATRIZ_H

#include <iostream>
#include <string.h>
using namespace std;

class Matriz{
	friend ostream& operator<<(ostream&, const Matriz&);
  public:
      Matriz(int = 4, int = 4);
      int filas();
      int columnas();

      long double ver(int fila, int columna);
      void asignar(int fila, int columna, long double valor);
      void triangular(void);

      ~Matriz();
//  private:
      long double **m;
      int fil;
      int col;
      /* metodos privados */
      void permutar(int fila1, int fila2);
      void pivotear(int);
      void restarFilas(long double coef, int filaAanular, int filaActual);
};






#endif /*_MATRIZ_H*/
