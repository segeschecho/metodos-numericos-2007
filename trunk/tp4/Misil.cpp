#include "Misil.h"
#include <math.h>

Misil :: Misil()
{
    for (int i = 0; i < 3; i++){
        x[i] = 0;
        y[i] = 0;
    }

    x[3] = 1;
    y[3] = 0;
    identificador = 0;
    destruido = false;
    cantMediciones = 2;
}

Misil :: Misil(char id, const long double* medicionesX, const long double* medicionesY, int numMuestras)
{
    identificador = id;
    destruido = false;
    cantMediciones = numMuestras;
    spline(medicionesX, x);
    spline(medicionesY, y);
}

Misil :: Misil(const Misil& m)
{
    for (int i = 0; i < 4; i++){
        x[i] = m.x[i];
        y[i] = m.y[i];
    }

    identificador = m.identificador;
    destruido = m.destruido;
    cantMediciones = m.cantMediciones;
}

char Misil :: id (void) const
{
    return identificador;
}

bool Misil :: estaDestruido (void) const
{
    return destruido;
}

long double Misil :: posicionX (long double tiempo) const
{
    return (x[0]*pow(tiempo - cantMediciones + 1, 3) + x[1]*pow(tiempo - cantMediciones + 1, 2) + x[2]*(tiempo - cantMediciones + 1) + x[3]);
}

long double Misil :: posicionY (long double tiempo) const
{
    return (y[0]*pow(tiempo - cantMediciones + 1, 3) + y[1]*pow(tiempo - cantMediciones + 1, 2) + y[2]*(tiempo - cantMediciones + 1) + y[3]);
}

Misil :: ~Misil(){}

void Misil :: spline (const long double* muestra, long double* res)
{
/*    Matriz coeficientesC(cantMediciones, cantMediciones);
    Matriz b(cantMediciones, 1);

    coeficientesC.asignar(0, 0, 3);
    coeficientesC.asignar(cantMediciones - 1, cantMediciones - 1, 3);
    for (int i = 1; i < cantMediciones - 1; i++) {
        b.asignar(i, 0, 3*(muestra[i + 1] - 2*muestra[i] + muestra[i - 1]));
        coeficientesC.asignar(i, i-1, (long double)1);
        coeficientesC.asignar(i, i, (long double)4);
        coeficientesC.asignar(i, i+1, (long double)1);
    }

    for(int i = 0; i < cantMediciones; i++)
        cout << muestra[i] << endl;

    cout << coeficientesC << endl;
    cout << b << endl;
    coeficientesC.triangular(&b);
    cout << coeficientesC << endl;
    cout << b << endl;

    /*
        La matriz para spline cubicos naturales es:
        3 0 0 0 ... 0 0 0 | 0
        1 4 1 0 ... 0 0 0 | 3*(a(2) - 2*a(1) + a(0))
        0 1 4 1 ... 0 0 0 | 3*(a(3) - 2*a(2) + a(1))
        .           .
        .           .
        .           .
        0 0 0 0 ... 1 4 1 | 3*(a(n) - 2*a(n-1) + a(n-2))
        0 0 0 0 ... 0 0 3 | 0

        siendo a(i) el coeficiente 'a' del spline 'i' y n = cantMediciones

        Al triangular desde la 2da fila hacia la anteultima mediante el metodo de gauss,
        el coeficiente siempre es 1/diagonal. Luego diagonal = 4 - 1*coeficiente.
        Solo necesitamos c(n-1), por lo que me interesa solamente el anteultimo valor de la diagonal.
    */

    long double diag;       //diag = resultado de la diagonal correspondiente a c(n-1)
    long double vectorB;    //el resultado correspondiente (del vector b)

    //CASO PARTICULAR: la matriz es de 2x2
    if (cantMediciones == 2){
        diag = 3;
        vectorB = 0;
    }
    else{
        diag = 4;
        vectorB = 3*(muestra[2] - 2*muestra[1] + muestra[0]);
        long double coef;    //auxiliar, para "restar fila1 - coef*fila2"

        for (int i = 2; i < cantMediciones - 1; i++) {
            coef = 1/diag;
            diag = 4 - coef;
            vectorB = 3*(muestra[i + 1] - 2*muestra[i] + muestra[i - 1]) - coef*vectorB;
        }
    }

    cout << diag;

    res[1] = vectorB/diag;
    //ya tengo el c(n-1), ahora necesito a(n-1), b(n-1) y d(n-1)
    //a(j) = f(j) (sale de evaluar la ecuacion del spline en x(n-1))
    res[3] = muestra[cantMediciones - 2];

    //Ahora que tengo a(n-1) y c(n-1) puedo sacar b(n-1)
    //uso que: b(j) = a(j+1)-a(j) -(2/3*c(j) + c(j+1)/3)
    //con j = n - 1 => b(n-1) = a(n) - a(n-1) - (2/3*c(n-1) + c(n)/3)
    //pero c(n) = 0 => b(n-1) = a(n) - a(n-1) - 2/3*c(n-1)
    res[2] = muestra[cantMediciones - 1] - muestra[cantMediciones - 2] - 2*res[1]/3;

    //Ahora solo me falta d(n-1)
    //d(j) = (c(j+1) - c(j))/3
    //d(n-1) = (c(n) - c(n-1))/3
    //pero c(n) = 0 => d(n-1) = c(n-1)/3
    res[0] = -res[1]/3;
}

ostream& operator<<(ostream& os, const Misil& misil)
{
    os << "hold on" << endl;
    for(double i = misil.cantMediciones - 1; i <= 8; i+= 0.05){
        os << "plot([" << misil.posicionX(i) << "],[" << misil.posicionY(i) << "], '*');\n";
    }
    return os;
}
