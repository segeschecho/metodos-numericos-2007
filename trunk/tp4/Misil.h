#include "Matriz.h"

#ifndef _MISIL_H
#define _MISIL_H

class Misil{
   	friend ostream& operator<<(ostream& os, const Misil& misil);
public:
    Misil();
    // Asegurar que los identificadores van a ser distintos
    Misil(char id, const long double* medicionesX, const long double* medicionesY, unsigned int cantMediciones);
    // Constructor por copia viola el invariante de los identificadores, usar con precaucion
    Misil(const Misil&);

    char id (void) const;
    bool estaDestruido (void) const;
    long double posicionX (long double tiempo) const;
    long double posicionY (long double tiempo) const;

    ~Misil();
//private:
    char identificador;
    bool destruido;
    long double x[4];
    long double y[4];

    void spline (const long double* muestra, unsigned int numMuestras, long double* res);
};

#endif /* _MISIL_H */
