#ifndef _MATRIZ_H
#define _MATRIZ_H

#include <iostream.h>
#include <string.h>

class Matriz{
  public:
      Matriz(unsigned int = 4, unsigned int = 4, long double a[][] = {0});
      int filas();
      int columnas();

      long double ver(unsigned int fila, unsigned int columna);
      void asignar(unsigned int fila, unsigned int columna, long double valor);
      void triangular(void);

      ~Matriz();
  private:
      long double *m;
      unsigned int filas;
      unsigned int columnas;
      /* metodos privados */
      permutar(unsigned int fila1, unsigned int fila2)
};






#endif /*_MATRIZ_H*/