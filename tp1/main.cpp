#include <iostream>
#include <iomanip>
#include "VLFloat.h"

using namespace std;

void mostrarF(float *x)
{
    unsigned char c0 = *((char*)x + 3);
    unsigned char c1 = *((char*)x + 2);
    unsigned char c2 = *((char*)x + 1);
    unsigned char c3 = *((char*)x);

    char todo[33];

    unsigned char pot = 128;
    for(int i=0; i<8; ++i)
    {
        todo[i] = '0' + (c0 / pot) % 2;
        pot /= 2;
    }

    pot = 128;
    for(int i=8; i<16; ++i)
    {
        todo[i] = '0' + (c1 / pot) % 2;
        pot /= 2;
    }

    pot = 128;
    for(int i=16; i<24; ++i)
    {
        todo[i] = '0' + (c2 / pot) % 2;
        pot /= 2;
    }

    pot = 128;
    for(int i=24; i<32; ++i)
    {
        todo[i] = '0' + (c3 / pot) % 2;
        pot /= 2;
    }

    todo[32] = 0;

    char signo = todo[0];
    char exponente[9];
    char mantisa[24];

    int _exponente = 0;
    float _mantisa = 1.0;

    for(int i=0, pot=128; i<8; ++i)
    {
        exponente[i] = todo[i+1];
        _exponente += (exponente[i] - '0') * pot;
        pot /= 2;
    }

    float _pot = 0.5;
    for(int i=0; i<23; ++i)
    {
        mantisa[i] = todo[i+9];
        _mantisa += (mantisa[i] - '0') * _pot;
        _pot /= 2;
    }

    exponente[8] = 0;
    mantisa[23] = 0;

    printf( "signo = %c, ", signo );
    printf( "exp = %s (%d), ", exponente, _exponente );
    printf( "    mant = 1.%s \n", mantisa );
//  printf( "%3.5f = %s \n", *x, todo );
}

/********************/
/*  mostrar double  */
/********************/
void mostrarD(double *x)
{
    unsigned char c0 = *((char*)x + 7);
    unsigned char c1 = *((char*)x + 6);
    unsigned char c2 = *((char*)x + 5);
    unsigned char c3 = *((char*)x + 4);
    unsigned char c4 = *((char*)x + 3);
    unsigned char c5 = *((char*)x + 2);
    unsigned char c6 = *((char*)x + 1);
    unsigned char c7 = *((char*)x);


    char todo[64];

    unsigned char pot = 128;
    for(int i=0; i<8; ++i)
    {
        todo[i] = '0' + (c0 / pot) % 2;
        pot /= 2;
    }

    pot = 128;
    for(int i=8; i<16; ++i)
    {
        todo[i] = '0' + (c1 / pot) % 2;
        pot /= 2;
    }

    pot = 128;
    for(int i=16; i<24; ++i)
    {
        todo[i] = '0' + (c2 / pot) % 2;
        pot /= 2;
    }

    pot = 128;
    for(int i=24; i<32; ++i)
    {
        todo[i] = '0' + (c3 / pot) % 2;
        pot /= 2;
    }

    /* ultimos 4 bytes  */
    pot = 128;
    for(int i=32; i<40; ++i)
    {
        todo[i] = '0' + (c4 / pot) % 2;
        pot /= 2;
    }

    pot = 128;
    for(int i=40; i<48; ++i)
    {
        todo[i] = '0' + (c5 / pot) % 2;
        pot /= 2;
    }

    pot = 128;
    for(int i=48; i<56; ++i)
    {
        todo[i] = '0' + (c6 / pot) % 2;
        pot /= 2;
    }

    pot = 128;
    for(int i=56; i<64; ++i)
    {
        todo[i] = '0' + (c7 / pot) % 2;
        pot /= 2;
    }

    todo[64] = 0;

    char signo = todo[0];
    char exponente[11];
    char mantisa[52];

    int _exponente = 0;
    double _mantisa = 1.0;

    for(int i=0, pot=1024; i<11; ++i)
    {
        exponente[i] = todo[i+1];
        _exponente += (exponente[i] - '0') * pot;
        pot /= 2;
    }

    double _pot = 0.5;
    for(int i=0; i<53; ++i)
    {
        mantisa[i] = todo[i+12];
        _mantisa += (mantisa[i] - '0') * _pot;
        _pot /= 2;
    }

    exponente[12] = 0;
    mantisa[52] = 0;

    printf( "signo = %c, ", signo );
    printf( "exp = %s (%d), ", exponente, _exponente );
    printf( "mant = 1.%s \n", mantisa );
//  printf( "%3.5f = %s \n", *x, todo );
}

void mostrarLD(long double *x)
{
    
    unsigned char c0 = *((char*)x + 9);
    unsigned char c1 = *((char*)x + 8);
    unsigned char c2 = *((char*)x + 7);
    unsigned char c3 = *((char*)x + 6);
    unsigned char c4 = *((char*)x + 5);
    unsigned char c5 = *((char*)x + 4);
    unsigned char c6 = *((char*)x + 3);
    unsigned char c7 = *((char*)x + 2);
    unsigned char c8 = *((char*)x + 1);
    unsigned char c9 = *((char*)x);


    char todo[96];

    unsigned char pot = 128;
    for(int i=0; i<8; ++i)
    {
        todo[i] = '0' + (c0 / pot) % 2;
        pot /= 2;
    }

    pot = 128;
    for(int i=8; i<16; ++i)
    {
        todo[i] = '0' + (c1 / pot) % 2;
        pot /= 2;
    }

    pot = 128;
    for(int i=16; i<24; ++i)
    {
        todo[i] = '0' + (c2 / pot) % 2;
        pot /= 2;
    }

    pot = 128;
    for(int i=24; i<32; ++i)
    {
        todo[i] = '0' + (c3 / pot) % 2;
        pot /= 2;
    }

    /* ultimos 4 bytes  */
    pot = 128;
    for(int i=32; i<40; ++i)
    {
        todo[i] = '0' + (c4 / pot) % 2;
        pot /= 2;
    }

    pot = 128;
    for(int i=40; i<48; ++i)
    {
        todo[i] = '0' + (c5 / pot) % 2;
        pot /= 2;
    }

    pot = 128;
    for(int i=48; i<56; ++i)
    {
        todo[i] = '0' + (c6 / pot) % 2;
        pot /= 2;
    }

    pot = 128;
    for(int i=56; i<64; ++i)
    {
        todo[i] = '0' + (c7 / pot) % 2;
        pot /= 2;
    }

    pot = 128;
    for(int i=64; i<72; ++i)
    {
        todo[i] = '0' + (c8 / pot) % 2;
        pot /= 2;
    }

    pot = 128;
    for(int i=72; i<80; ++i)
    {
        todo[i] = '0' + (c9 / pot) % 2;
        pot /= 2;
    }
    
    
    todo[80] = 0;
    
    
    char signo = todo[0];
    char exponente[15];
    char mantisa[63];

    int _exponente = 0;
    double _mantisa = 1.0;

    for(int i=0, pot=1024; i<15; ++i)
    {
        exponente[i] = todo[i+1];
        _exponente += (exponente[i] - '0') * pot;
        pot /= 2;
    }

    double _pot = 0.5;
    for(int i=0; i<64; ++i)
    {
        mantisa[i] = todo[i+16];
        _mantisa += (mantisa[i] - '0') * _pot;
        _pot /= 2;
    }

    exponente[15] = 0;
    mantisa[63] = 0;
/*
    printf( "signo = %c, ", signo );
    printf( "exp = %s (%d), ", exponente, _exponente );
    printf( "mant = 1.%s \n", mantisa );
//  printf( "%3.5f = %s \n", *x, todo );*/
}

unsigned int factorial(unsigned int n)
{
	unsigned int res = n;

	if (n == 0)
		return 1;

	while (n > 2){
		res *= n - 1;
		n--;
	}

	return res;
}

VLFloat taylor(long double valor, unsigned int n, unsigned int precision){
	VLFloat res(precision, 1);	//lo inicializo en 1 para no calcular el 1er termino de la serie
	VLFloat x(precision);

	x = valor;
    cout.precision(50);   
	
	while (n > 0){
		res = res + (x^n)/factorial(n);
		n--;
	}

    return res;
}

int main()
{
	unsigned int p, orden;
	long double valor;

	cout << "Aproximacion de e^(-x) con presicion y orden variable" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

	cout << "\n\n\n\nsizeof(long double) = " << sizeof(long double) << " bytes";
	cout << "\n\n";

	cout << "Ingresar precision con el cual quiere trabajar el punto flotante: ";
	cin >> p;

	cout << "\n\n";

	cout << "Ingresar orden con el cual quiere aproximar a e^(-x): ";
	cin >> orden;

	cout << "\n\n";

	cout << "Ingresar x: ";
	cin >> valor;
	
	cout << "\n\n";

	cout << "Resultado: " << taylor(valor, orden, p) << endl;

/*
	long double d;
	long double p;
   /*  pruebo el polinomio de taylor de 3 terminos en 0.1
       p(0.1) =  1 + 0.1/2 + 0.1/6

	d = 0.987654321;

	cout.setf(ios::fixed, ios::floatfield);
	cout << "valor long double :" << setprecision(25) << d << endl;
	mostrarLD(&d);
	cout << "\n\n\n";

	p = truncar(5, &d);
	cout << "valor long double :" << setprecision(25) << d << endl;
	mostrarLD(&d);
	cout << "\n\n\n";
	cout << "valor long double de p :" << setprecision(25) << p << endl;
/*
	c = 0.264873;

   unsigned char c0 = *((char*)&c + 7);

	printf("valor double : %.25f\n", c);
	mostrarD(&c);

	redondear(30, &c);
	printf("\n\nvalor double : %.25f\n", c);
	mostrarD(&c);
	b = c;
	c = b;
	printf("valor double : %.25f\n", c);
	mostrarD(&c);
	printf("valor float  : %.25f\n", b);
	mostrarF(&b);


	printf("entero : %d\n", sizeof(a));
	printf("float : %d\n", sizeof(b));
	printf("double : %d\n", sizeof(c));
	printf("long double : %d\n", sizeof(d));*/

	system("PAUSE");
	return EXIT_SUCCESS;
}

