#ifndef _MATRIZ_H
#define _MATRIZ_H

#include <iostream>
#include <string.h>

class Matriz{
//	friend ostream& operator<<(ostream&, const Matriz&);
  public:
      Matriz(unsigned int = 4, unsigned int = 4);
      int filas();
      int columnas();

      long double ver(unsigned int fila, unsigned int columna);
      void asignar(unsigned int fila, unsigned int columna, long double valor);
      void triangular(void);

      ~Matriz();
//  private:
      long double **m;
      unsigned int fil;
      unsigned int col;
      /* metodos privados */
      void permutar(unsigned int fila1, unsigned int fila2);
};






#endif /*_MATRIZ_H*/