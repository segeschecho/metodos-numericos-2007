#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip.h>
#include "DLFloat.h"

using namespace std;

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
DLFloat taylorMenorAMayorInv(long double valor, unsigned int n, unsigned int precision){
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
DLFloat taylorMayorAMenorInv(long double valor, unsigned int n, unsigned int precision){
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
DLFloat taylorMenorAMayor(long double valor, unsigned int n, unsigned int precision){
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
DLFloat taylorMayorAMenor(long double valor, unsigned int n, unsigned int precision){
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

int main()
{
	unsigned int p, orden;
	long double valor, e = 2.718281828459045235360287471352662497757247093699959574966967627724;
	char hacerPrueba = 's';

	while(hacerPrueba == 's')
   {
       cout << "Aproximacion de e^(-x) con presicion y orden variable" << endl;
       cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n" << endl;

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

       resultado1 = taylorMenorAMayorInv(valor, orden, p);
       resultado2 = taylorMayorAMenorInv(valor, orden, p);

       resultado1Inv = taylorMenorAMayor(valor, orden, p);
       resultado2Inv = taylorMayorAMenor(valor, orden, p);

       cout.precision(40);
       cout << "Resultado verdadero de e^(-x): " << pow(e,-valor) << endl;
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

	return EXIT_SUCCESS;
}

