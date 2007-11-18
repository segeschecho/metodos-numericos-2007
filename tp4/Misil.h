#include <iostream>
using namespace std;

#ifndef _MISIL_H
#define _MISIL_H

class Misil{
   	friend ostream& operator<<(ostream& os, const Misil& misil);
public:
    Misil();
    Misil(const long double* medicionesX, const long double* medicionesY, int numMuestras);
    Misil(const Misil&);

    void operator= (const Misil& m2);
    bool estaDestruido (void) const;
    void destruir (void);
    long double posicionX (long double tiempo) const;
    long double posicionY (long double tiempo) const;

    ~Misil();
private:
    int cantMediciones;
    bool destruido;
    long double x[4];
    long double y[4];

    void spline (const long double* muestra, long double* res);
};

#endif /* _MISIL_H */
