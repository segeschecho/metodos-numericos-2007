#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <time.h>
#include "DLFloat.h"

using namespace std;
/*
void mostrar(short int *x)
{
    unsigned char c0 = *((char*)x + 1);
    unsigned char c1 = *((char*)x);

    unsigned char pot = 128;
    for(int i=0; i<8; ++i)
    {
        cout << (char)('0' + (c0 / pot) % 2);
        pot /= 2;
    }

    pot = 128;
    for(int i=8; i<16; ++i)
    {
        cout << (char)('0' + (c1 / pot) % 2);
        pot /= 2;
    }

    cout << endl;
}

void mostrar(long double *x)
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

    char todo[81];

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
    char exponente[16];
    char mantisa[65];

    int _exponente = 0;
    float _mantisa = 1.0;

    for(int i=0, pot=128; i<16; ++i)
    {
        exponente[i] = todo[i+1];
        _exponente += (exponente[i] - '0') * pot;
        pot /= 2;
    }

    float _pot = 0.5;
    for(int i=0; i<65; ++i)
    {
        mantisa[i] = todo[i+16];
        _mantisa += (mantisa[i] - '0') * _pot;
        _pot /= 2;
    }

    exponente[15] = 0;
    mantisa[64] = 0;

    printf( "signo = %c, ", signo );
    printf( "exp = %s (%d), ", exponente, _exponente );
    printf( "mant = %s \n", mantisa);
//  printf( "%3.5f = %s \n", *x, todo );
}

void redondear(long double c, int prec)
{
    //La variable bytes representara la cantidad de bytes que tenemos de mantisa
	int bytes = 8;    //"ignoramos" los 2 bytes de exponente + signo al redondear
                      //que estan en la posicion de memoria mas alta

	bytes -= (int)(prec/8);
	//esto representa la cantidad de bytes enteros que voy a eliminar desde el menos significativo

	unsigned char* ch = ((unsigned char*)&c + bytes - 1);

    cout << "mostrar(Precision = " << prec << ")" << endl;
    mostrar(&c);
    c += pow(2, -prec + 1); //con esto le sumamos 1 al primer bit que voy a truncar
                        //con el fin de redondear
    mostrar(&c);
	*ch &= (255 << (8 - (prec % 8)) ); //255 = 1111 1111
	//ahora borramos los bytes menos significativos
	memset(&c, 0, bytes - 1);
    mostrar(&c);
    cout << c << endl;
	ch = ((unsigned char*)&c + 7);
    *ch += 128;
    mostrar(&c);
    cout << c << endl;
}
*/
DLFloat factorial(unsigned int n, unsigned int p)
{
	DLFloat res(p, 1);
	DLFloat i(p, 2);
	//i lo hice DLFloat por la linea: res = res*i; que viene luego

	if (n == 0)
		return res;

	while (i.valor() <= n){
		res = res*i;
		i++;
	}
	return res;
}

/////////////////////////////////////////////////////////////////////////////
//Aproximacion de 1/(e^x) con taylor, sumando desde el mayor termino al menor
/////////////////////////////////////////////////////////////////////////////
DLFloat taylorMayorAMenor(long double valor, unsigned int n, unsigned int precision){
	DLFloat res(precision, 1);	//lo inicializo en 1 para no calcular el 1er termino de la serie
	DLFloat x(precision);

	x = valor;

	while (n > 0){
		res = res + (x^n)/factorial(n,precision);
		n--;
	}

	return res^(-1);
}

/////////////////////////////////////////////////////////////////////////////
//Aproximacion de 1/(e^x) con taylor, sumando desde el menor termino al mayor
/////////////////////////////////////////////////////////////////////////////
DLFloat taylorMenorAMayor(long double valor, unsigned int n, unsigned int precision){
	DLFloat res(precision, 1);	//lo inicializo en 1 para no calcular el 1er termino de la serie
	DLFloat x(precision);

	x = valor;

	unsigned int i = 1;

	while (i < n){
		res = res + (x^i)/factorial(i, precision);
		i++;
	}

    return res^(-1);
}


////////////////////////////////////////////////////////////////////////////
//Aproximacion de e^(-x) con taylor, sumando desde el mayor termino al menor
////////////////////////////////////////////////////////////////////////////
DLFloat taylorMayorAMenorInv(long double valor, unsigned int n, unsigned int precision){
	DLFloat res(precision, 1);	//lo inicializo en 1 para no calcular el 1er termino de la serie
	DLFloat x(precision);
	DLFloat neg(1, 1);

	x = valor;

	while (n > 0){
		neg = pow(-1,n%2);
		res = res + neg*((x^n)/factorial(n,precision));
		n--;
	}

	return res;
}

////////////////////////////////////////////////////////////////////////////
//Aproximacion de e^(-x) con taylor, sumando desde el menor termino al mayor
////////////////////////////////////////////////////////////////////////////
DLFloat taylorMenorAMayorInv(long double valor, unsigned int n, unsigned int precision){
	DLFloat res(precision, 1);	//lo inicializo en 1 para no calcular el 1er termino de la serie
	DLFloat x(precision);
	DLFloat neg(1, 1);

	x = valor;

	unsigned int i = 1;

	while (i < n){
		neg = pow(-1,i%2);
		res = res + neg*((x^i)/factorial(i, precision));
		i++;
	}

    return res;
}

void imprimirValores(ofstream& archivo)
{

    archivo << "TAYLOR MENOR A MAYOR" << endl;
    archivo << "~~~~~~~~~~~~~~~~~~~~\n\n" << endl;
    cout << "TAYLOR MENOR A MAYOR" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~\n\n" << endl;
    int x = 1;

    archivo << "x = 1" << endl;
    archivo << "~~~~~" << endl << endl;
    archivo << "A = [ ";

    cout << "x = 1" << endl;
    cout << "~~~~~" << endl << endl;
    cout << "A = [ ";
    for(int i = 1; i < 64; i++){
        for(int j = 1; j <= 15; j++){
            archivo << setprecision(20) << taylorMenorAMayor(x, j, i) << " ";
        }
    }

    archivo << " ]" << endl << endl;
    cout << " ]" << endl << endl;

    archivo << "B = [ ";
    cout << "B = [ ";

    for(int i = 1; i < 64; i++){
        for(int j = 1; j <= 15; j++){
            archivo << setprecision(20) << taylorMenorAMayorInv(x, j, i) << " ";
        }
    }

    archivo << " ]" << endl << endl;
    cout << " ]" << endl << endl;

    x = 5;

    while( x < 20 )
    {
        archivo << "x = " << x << endl;
        archivo << "~~~~~" << endl << endl;

        archivo << "A = [ ";

        cout << "x = " << x << endl;
        cout << "~~~~~" << endl << endl;

        cout << "A = [ ";

        for(int i = 1; i < 64; i++){
            for(int j = 1; j <= 15; j++){
                archivo << setprecision(20) << taylorMenorAMayor(x, j, i) << " ";
            }
        }

        archivo << " ]" << endl << endl;

        archivo << "B = [ ";

        cout << " ]" << endl << endl;

        cout << "B = [ ";

        for(int i = 1; i < 64; i++){
            for(int j = 1; j <= 15; j++){
                archivo << setprecision(20) << taylorMenorAMayorInv(x, j, i) << " ";
            }
        }

        archivo << " ]" << endl << endl;
        cout << " ]" << endl << endl;
        x += 5;
    }

    archivo << "\n\n\n\n";

    archivo << "TAYLOR MAYOR A MENOR" << endl;
    archivo << "~~~~~~~~~~~~~~~~~~~~\n\n" << endl;
    cout << "\n\n\n\n";

    cout << "TAYLOR MAYOR A MENOR" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~\n\n" << endl;
    x = 1;

    archivo << "x = 1" << endl;
    archivo << "~~~~~" << endl << endl;
    archivo << "A = [ ";

    cout << "x = 1" << endl;
    cout << "~~~~~" << endl << endl;
    cout << "A = [ ";

    for(int i = 1; i < 64; i++){
        for(int j = 1; j < 15; j++){
            archivo << setprecision(20) << taylorMayorAMenor(x, j, i) << " ";
        }
    }

    archivo << " ]" << endl << endl;

    archivo << "B = [ ";

    cout << " ]" << endl << endl;

    cout << "B = [ ";

    for(int i = 1; i < 64; i++){
        for(int j = 1; j < 15; j++){
            archivo << setprecision(20) << taylorMayorAMenorInv(x, j, i) << " ";
        }
    }

    archivo << " ]" << endl << endl;
    cout << " ]" << endl << endl;

    x = 5;

    while( x < 20 )
    {
        archivo << "x = " << x << endl;
        archivo << "~~~~~" << endl << endl;

        archivo << "A = [ ";

        cout << "x = " << x << endl;
        cout << "~~~~~" << endl << endl;

        cout << "A = [ ";

        for(int i = 1; i < 64; i++){
            for(int j = 1; j < 15; j++){
                archivo << setprecision(20) << taylorMayorAMenor(x, j, i) << " ";
            }
        }

        archivo << " ]" << endl << endl;

        archivo << "B = [ ";

        cout << " ]" << endl << endl;

        cout << "B = [ ";

        for(int i = 1; i < 64; i++){
            for(int j = 1; j < 15; j++){
                archivo << setprecision(20) << taylorMayorAMenorInv(x, j, i) << " ";
            }
        }

        archivo << " ]" << endl << endl;
        cout << " ]" << endl << endl;
        x += 5;
    }

    archivo.close();
}

void imprimirValores2(ofstream& archivo)
{
    int cantTerminos = 50;
    long double valor = 1, e = 2.718281828459045235360287471352662497757247093699959574966967627724;

    cout << "Guardando error relativo de e^(-x) en funcion de la presicion en bits";
    cout << "en X = " << valor << " y cantidad de terminos = " << cantTerminos << endl;

    archivo << "Guardando error relativo de e^(-x) en funcion de la presicion en bits: ";
    archivo << "En X = " << valor << " y cantidad de terminos = " << cantTerminos << endl << endl;

    /* imprimo los X */
    archivo << "[ ";
    for(int precision = 1; precision < 64; precision++)
        archivo << 1 << " ";

    archivo << " ]" << endl << endl;

    /* imprimo la cantidad de terminos */
    archivo << "[ ";
    for(int precision = 1; precision < 64; precision++)
        archivo << 50 << " ";

    archivo << " ]" << endl << endl;

    /* taylor mayor a menor*/
    archivo << "taylor mayor a menor:" << endl << endl;
    archivo << "[ ";
    for(int precision = 1; precision < 64; precision++){
		  DLFloat res(precision);
		  res = taylorMayorAMenor(valor, cantTerminos, precision);
        archivo << setprecision(20) << (fabs(pow(e,-valor) - res.valor()) / pow(e,-valor)) << " ";
    }
    archivo << " ]" << endl << endl;

    /* taylor mayor a menor inv */
    archivo << "taylor mayor a menor INV:" << endl << endl;
    archivo << "[ ";
    for(int precision = 1; precision < 64; precision++){
		  DLFloat res(precision);
		  res = taylorMayorAMenorInv(valor, cantTerminos, precision);
        archivo << setprecision(20) << (fabs(pow(e,-valor) - res.valor()) / pow(e,-valor)) << " ";
    }

    archivo << " ]" << endl << endl;

    /* taylor menor a mayor */
    archivo << "taylor menor a mayor:" << endl << endl;
    archivo << "[ ";
    for(int precision = 1; precision < 64; precision++){
		  DLFloat res(precision);
		  res = taylorMenorAMayor(valor, cantTerminos, precision);
        archivo << setprecision(20) << (fabs(pow(e,-valor) - res.valor()) / pow(e,-valor)) << " ";
    }

    archivo << " ]" << endl << endl;

    /* taylor menor a mayor */
    archivo << "taylor menor a mayor INV:" << endl << endl;
    archivo << "[ ";
    for(int precision = 1; precision < 64; precision++){
		  DLFloat res(precision);
		  res = taylorMenorAMayorInv(valor, cantTerminos, precision);
        archivo << setprecision(20) << (fabs(pow(e,-valor) - res.valor()) / pow(e,-valor)) << " ";
    }

    archivo << " ]" << endl << endl;


    int precision = 50;

    cout << "Guardando error relativo de e^(-x) en funcion del orden de Taylor";
    cout << "en X = " << valor << " y precision = " << cantTerminos << endl;

    archivo << "Guardando error relativo de e^(-x) en funcion del orden de Taylor: ";
    archivo << "En X = " << valor << " y precision = " << cantTerminos << endl << endl;

    /* imprimo los X */
    archivo << "[ ";
    for(int cantTerminos = 1; cantTerminos < 50; cantTerminos++)
        archivo << 1 << " ";

	 archivo << " ]" << endl << endl;

    /* imprimo la cantidad de terminos */
    archivo << "[ ";
    for(int cantTerminos = 1; cantTerminos < 50; cantTerminos++)
        archivo << 50 << " ";

    archivo << " ]" << endl << endl;

    /* taylor mayor a menor*/
    archivo << "taylor mayor a menor:" << endl << endl;
    archivo << "[ ";
    for(int cantTerminos = 1; cantTerminos < 50; cantTerminos++){
		  DLFloat res(precision);
		  res = taylorMayorAMenor(valor, cantTerminos, precision);
        archivo << setprecision(20) << (fabs(pow(e,-valor) - res.valor()) / pow(e,-valor)) << " ";
    }

    archivo << " ]" << endl << endl;

    /* taylor mayor a menor inv */
    archivo << "taylor mayor a menor INV:" << endl << endl;
    archivo << "[ ";
    for(int cantTerminos = 1; cantTerminos < 50; cantTerminos++){
		  DLFloat res(precision);
		  res = taylorMayorAMenorInv(valor, cantTerminos, precision);
        archivo << setprecision(20) << (fabs(pow(e,-valor) - res.valor()) / pow(e,-valor)) << " ";
    }

    archivo << " ]" << endl << endl;

    /* taylor menor a mayor */
    archivo << "taylor menor a mayor:" << endl << endl;
    archivo << "[ ";
    for(int cantTerminos = 1; cantTerminos < 50; cantTerminos++){
		  DLFloat res(precision);
		  res = taylorMenorAMayor(valor, cantTerminos, precision);
        archivo << setprecision(20) << (fabs(pow(e,-valor) - res.valor()) / pow(e,-valor)) << " ";
    }

    archivo << " ]" << endl << endl;

    /* taylor menor a mayor */
    archivo << "taylor menor a mayor INV:" << endl << endl;
    archivo << "[ ";
    for(int cantTerminos = 1; cantTerminos < 50; cantTerminos++){
		  DLFloat res(precision);
		  res = taylorMenorAMayorInv(valor, cantTerminos, precision);
        archivo << setprecision(20) << (fabs(pow(e,-valor) - res.valor()) / pow(e,-valor)) << " ";
    }

    archivo << " ]" << endl << endl;

    archivo.close();
}

int main()
{
/*    long double e = 2.718281828459045235360287471352662497757247093699959574966967627724;
    short int i = 255;

    mostrar(&i);
    unsigned char *c1 = ((unsigned char*)&i);
    i += pow(2,6);
    mostrar(&i);

    for(int i = 0; i < 64; i++){
        redondear(e, i);
        cout << endl << endl;
        system("PAUSE");
   }
*/
/*	 unsigned int comienzo = time(NULL);
    ofstream a ("grafico2.txt");
    imprimirValores2(a);
	 cout << "\n\nEl algoritmo tardo: " << time(NULL) - comienzo << " segundos.\n\n";*/

	unsigned int p, orden;
	long double valor, e = 2.718281828459045235360287471352662497757247093699959574966967627724;
    char hacerPrueba = 's';

    while(hacerPrueba == 's')
    {
        cout << "Aproximacion de e^(-x) con presicion y orden variable" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

        cout << "\n\n\n\nsizeof(long double) = " << sizeof(long double) << " bytes";
        cout << "\n\n";

        cout << "Ingresar precision con el cual quiere trabajar el punto flotante: ";
        cin >> p;

        cout << "\n\n";

        cout << "Ingresar orden con el cual quiere aproximar a e^(-x) (1~170): ";
        cin >> orden;

        cout << "\n\n";

        cout << "Ingresar x: ";
        cin >> valor;

        cout << "\n\n";

        DLFloat resultado1(p);
        DLFloat resultado2(p);

        DLFloat resultado1Inv(p);
        DLFloat resultado2Inv(p);

        resultado1 = taylorMayorAMenor(valor, orden, p);
        resultado2 = taylorMenorAMayor(valor, orden, p);

        resultado1Inv = taylorMayorAMenorInv(valor, orden, p);
        resultado2Inv = taylorMenorAMayorInv(valor, orden, p);

        cout.precision(40);
        cout << "e^(-x): " << pow(e,-valor) << endl;
        cout << "Resultado con taylor de mayor a menor 1/(e^x): " << resultado1 << endl;
        cout << "Resultado con taylor de menor a mayor 1/(e^x): " << resultado2 << endl;
        cout << "Resultado con taylor de mayor a menor e^(-x) : " << resultado1Inv << endl;
        cout << "Resultado con taylor de menor a mayor e^(-x) : " << resultado2Inv << endl << endl;

        cout << "Error Absoluto mayor a menor 1/(e^x): " << (fabs(pow(e,-valor) - resultado1.valor())) << endl;
        cout << "Error Relativo mayor a menor 1/(e^x): " << (fabs(pow(e,-valor) - resultado1.valor()) / pow(e,-valor)) << endl << endl;
        cout << "Error Absoluto menor a mayor 1/(e^x): " << (fabs(pow(e,-valor) - resultado2.valor())) << endl;
        cout << "Error Relativo menor a mayor 1/(e^x): " << (fabs(pow(e,-valor) - resultado2.valor()) / pow(e,-valor)) << endl << endl << endl;

        cout << "Error Absoluto mayor a menor e^(-x): " << (fabs(pow(e,-valor) - resultado1Inv.valor())) << endl;
        cout << "Error Relativo mayor a menor e^(-x): " << (fabs(pow(e,-valor) - resultado1Inv.valor()) / pow(e,-valor)) << endl << endl;
        cout << "Error Absoluto menor a mayor e^(-x): " << (fabs(pow(e,-valor) - resultado2Inv.valor())) << endl;
        cout << "Error Relativo menor a mayor e^(-x): " << (fabs(pow(e,-valor) - resultado2Inv.valor()) / pow(e,-valor)) << endl << endl << endl;
        cout << endl << endl;
        cout << "Desea realizar otra prueba? (s/n)" << endl;
        cin >> hacerPrueba;
    }
	system("PAUSE");
	return EXIT_SUCCESS;
}

