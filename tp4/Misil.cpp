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
}

Misil :: Misil(char id, const long double* medicionesX, const long double* medicionesY, int cantMediciones)
{
    spline(medicionesX, cantMediciones, x);
    spline(medicionesY, cantMediciones, y);
    identificador = id;
    destruido = false;

}

Misil :: Misil(const Misil& m)
{
    for (int i = 0; i < 4; i++){
        x[i] = m.x[i];
        y[i] = m.y[i];
    }

    identificador = m.identificador;
    destruido = m.destruido;
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
    cout << "tiempo  " << tiempo << endl;
    cout << "tiempo^3  " << x[0]*pow(tiempo, 3) + x[1]*pow(tiempo, 2) + x[2]*pow(tiempo, 1) + x[3] << endl;
    return (x[0]*pow(tiempo, 3) + x[1]*pow(tiempo, 2) + x[2]*pow(tiempo, 1) + x[3]);
}

long double Misil :: posicionY (long double tiempo) const
{
    return (y[0]*pow(tiempo, 3) + y[1]*pow(tiempo, 2) + y[2]*pow(tiempo, 1) + y[3]);
}

Misil :: ~Misil(){}

void Misil :: spline (const long double* muestra, int numMuestras, long double* res)
{
    assert(numMuestras > 1);

    //las ecuaciones que se generan son 4*n y 4*n - 16
    Matriz sistema(4*(numMuestras - 1), 4*(numMuestras - 1));
    Matriz X (4*(numMuestras - 1), 1);
    Matriz b (4*(numMuestras - 1), 1);
    //durante el algoritmo siempre aprobechamos que matriz es inicializada a la matriz 0

    int fila = 0;

    //cada ecuacion entre los puntos es un polinomio de grado 3
    //de la forma a*X^3 + b*X^2 +c*X + d
    //donde las incignitas son las letras
    //cada fila del sistema tiene la forma
    //a0 b0 c0 d0 a1 b1 c1 d1 a2 b2 ....

    //hago que el polinomio cumpla con los puntos pasados
    for(int i = 1; i < numMuestras - 1; i++){
        //igualo el polinomio de intervalo [i - 1, i] al valor de f(i)
        //y guardo los coeficientes que acompañan a cada letra

       //guardo el coeficiente de a
        sistema.asignar(fila, 4*(i - 1), pow((long double)i + 1, 3));
        //guardo el coeficiente de b
        sistema.asignar(fila, 4*(i - 1) + 1, pow((long double)i + 1, 2));
        //guardo el coeficiente de c
        sistema.asignar(fila, 4*(i - 1) + 2, i + 1);
        //guardo el coeficiente de d
        sistema.asignar(fila, 4*(i - 1) + 3, 1);

        //asigno el valor de la imagen al vector b
        b.asignar(fila, 0, muestra[i]);

        fila++;

        //igualo el polinomio de intervalo [i, i + 1] al valor de f(i)
        //y guardo los coeficientes que acompañan a cada letra
        //guardo el coeficiente de a
        sistema.asignar(fila, 4*i, pow((long double)i + 1, 3));
        //guardo el coeficiente de b
        sistema.asignar(fila, 4*i + 1, pow((long double)i + 1, 2));
        //guardo el coeficiente de c
        sistema.asignar(fila, 4*i + 2, i + 1);
        //guardo el coeficiente de d
        sistema.asignar(fila, 4*i + 3, 1);

        //asigno el valor de la imagen al vector b
        b.asignar(fila, 0, muestra[i+1]);

        fila++;
    }

    //ahora hago que cumpla en los extremos
    //en el principio
    //guardo el coeficiente de a
    sistema.asignar(fila, 0, 1);
    //guardo el coeficiente de b
    sistema.asignar(fila, 1, 1);
    //guardo el coeficiente de c
    sistema.asignar(fila, 2, 1);
    //guardo el coeficiente de d
    sistema.asignar(fila, 3, 1);

    //asigno el valor de la imagen al vector b
    b.asignar(fila, 0,  muestra[0]);

    fila++;

    //en el final
    //guardo el coeficiente de a
    sistema.asignar(fila, 4*(numMuestras - 1) - 4, pow((long double)(numMuestras), 3));
    //guardo el coeficiente de b
    sistema.asignar(fila, 4*(numMuestras - 1) - 3, pow((long double)(numMuestras), 2));
    //guardo el coeficiente de c
    sistema.asignar(fila, 4*(numMuestras - 1) - 2, numMuestras);
    //guardo el coeficiente de d
    sistema.asignar(fila, 4*(numMuestras - 1) - 1, 1);

    //asigno el valor de la imagen al vector b
    b.asignar(fila, 0,  muestra[numMuestras - 1]);

    fila++;

    //tengo que derivar y igualarlas en los puntos del medio
    for(int i = 2; i < numMuestras; i++){
        //igualo las derivadas en el punto i
        //3*a([i-1,i])*X^2 + 2*b([i-1,i])*X + c([i-1,i]) = 0
        //3*a([i,i+1])*X^2 + 2*b([i,i+1])*X + c([i-1,i]) = 0
        //guardo el coeficiente de a
        sistema.asignar(fila, 4*(i - 2), 3*pow((long double)i, 2));
        //guardo el coeficiente de b
        sistema.asignar(fila, 4*(i - 2) + 1, 2*i);
        //guardo el coeficiente de c
        sistema.asignar(fila, 4*(i - 2) + 2, 1);
        //el coeficiente d es 0

        //guardo el coeficiente de a
        sistema.asignar(fila, 4*(i - 1), -3*pow((long double)i, 2));
        //guardo el coeficiente de b
        sistema.asignar(fila, 4*(i - 1) + 1, -2*i);
        //guardo el coeficiente de c
        sistema.asignar(fila, 4*(i - 1) + 2, -1);
        //el coeficiente d es 0

        fila ++;
    }

    //tengo que derivar dos veces e igualarlas.
    //las derivadas segundas de las puntas del grafico
    //son igualadas a cero
    for(int i = 2; i < numMuestras; i++){
        //igualo las derivadas en el punto i
        //6*a([i-1,i])*X + 2*b([i-1,i]) - (
        //6*a([i,i+1])*X + 2*b([i,i+1]) ) = 0
        //guardo el coeficiente de a
        sistema.asignar(fila, 4*(i - 2), 6*i);
        //guardo el coeficiente de b
        sistema.asignar(fila, 4*(i - 2) + 1, 2);
        //los coeficientes de c y d son 0

        //guardo el coeficiente de a
        sistema.asignar(fila, 4*(i - 1), -6*i);
        //guardo el coeficiente de b
        sistema.asignar(fila, 4*(i - 1) + 1, -2);
        //los coeficientes de c y d son 0

        fila ++;
    }

    //asigno las derivadas segundas de las puntas igual a cero
    //6*a([0])*1 + 2*b([0])
    //guardo el coeficiente de a
    sistema.asignar(fila, 0, 6);
    //guardo el coeficiente de b
    sistema.asignar(fila, 1, 2);

    fila++;

    //6*a([n])*Xn + 2*b([n])
    //guardo el coeficiente de a
    sistema.asignar(fila, 4*(numMuestras - 1) - 4, 6*numMuestras);
    //guardo el coeficiente de b
    sistema.asignar(fila, 4*(numMuestras - 1) - 3, 2);

    sistema.triangular(&b);
    sistema.resolver(X, b);

    res[0] = X.ver(4*(numMuestras - 1) - 4, 0);
    res[1] = X.ver(4*(numMuestras - 1) - 3, 0);
    res[2] = X.ver(4*(numMuestras - 1) - 2, 0);
    res[3] = X.ver(4*(numMuestras - 1) - 1, 0);

//    cout << sistema;
//    cout << X;
//    cout << endl << "ultimo polinomio " << res[0] << " " << res[1] << " " << res[2] << " " << res[3] << endl;
}

ostream& operator<<(ostream& os, const Misil& misil)
{
    os << "hold on" << endl;
    for(double i = 1; i <= 100; i+= 0.05){
        os << "plot([" << i << "],[" << misil.posicionY(i) << "], '*');\n";
    }
    return os;
}
