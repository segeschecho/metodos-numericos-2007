#include <iostream>
#include <iomanip>
#include <math.h>
#include "VLFloat.h"

using namespace std;

VLFloat factorial(unsigned int n, unsigned int p)
{
	VLFloat res(p, 1);
	VLFloat i(p, 2);

	if (n == 0)
		return res;

	while (i.valor() <= n)
	{
		res = res*i;
		i = i.valor() + 1;
	}
	return res;
}

/////////////////////////////////////////////////////////////////////////////
//Aproximacion de 1/(e^x) con taylor, sumando desde el mayor termino al menor
/////////////////////////////////////////////////////////////////////////////
VLFloat taylorMayorAMenor(long double valor, unsigned int n, unsigned int precision){
	VLFloat res(precision, 1);	//lo inicializo en 1 para no calcular el 1er termino de la serie
	VLFloat x(precision);

	x = valor;

	while (n > 0){
		res = res + (x^n)/factorial(n,precision);
		n--;
	}

	return res;
}

/////////////////////////////////////////////////////////////////////////////
//Aproximacion de 1/(e^x) con taylor, sumando desde el menor termino al mayor
/////////////////////////////////////////////////////////////////////////////
VLFloat taylorMenorAMayor(long double valor, unsigned int n, unsigned int precision){
	VLFloat res(precision, 1);	//lo inicializo en 1 para no calcular el 1er termino de la serie
	VLFloat x(precision);

	x = valor;

	unsigned int i = 1;

	while (i < n){
		res = res + (x^i)/factorial(i, precision);
		i++;
	}

    return res;
}


////////////////////////////////////////////////////////////////////////////
//Aproximacion de e^(-x) con taylor, sumando desde el mayor termino al menor
////////////////////////////////////////////////////////////////////////////
VLFloat taylorMayorAMenorInv(long double valor, unsigned int n, unsigned int precision){
	VLFloat res(precision, 1);	//lo inicializo en 1 para no calcular el 1er termino de la serie
	VLFloat x(precision);
	VLFloat neg(1, 1);

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
VLFloat taylorMenorAMayorInv(long double valor, unsigned int n, unsigned int precision){
	VLFloat res(precision, 1);	//lo inicializo en 1 para no calcular el 1er termino de la serie
	VLFloat x(precision);
	VLFloat neg(1, 1);

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

	cout << "Aproximacion de e^(-x) con presicion y orden variable" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

	cout << "\n\n\n\nsizeof(long double) = " << sizeof(long double) << " bytes";
	cout << "\n\n";

	cout << "Ingresar precision con el cual quiere trabajar el punto flotante: ";
	cin >> p;

	cout << "\n\n";

	cout << "Ingresar orden con el cual quiere aproximar a e^(-x) (0~20 recomendado): ";
	cin >> orden;

	cout << "\n\n";

	cout << "Ingresar x: ";
	cin >> valor;

	cout << "\n\n";

	VLFloat resultado1(p);
	VLFloat resultado2(p);

	VLFloat resultado1Inv(p);
	VLFloat resultado2Inv(p);

	resultado1 = taylorMayorAMenor(valor, orden, p);
	resultado2 = taylorMenorAMayor(valor, orden, p);
	resultado1 = resultado1^(-1);
	resultado2 = resultado2^(-1);

	resultado1Inv = taylorMayorAMenorInv(valor, orden, p);
	resultado2Inv = taylorMenorAMayorInv(valor, orden, p);

	cout.precision(40);
	cout << "e^(-x): " << pow(e,-valor) << endl;
	cout << "Resultado con taylor de mayor a menor 1/(e^x): " << resultado1 << endl;
	cout << "Resultado con taylor de menor a mayor 1/(e^x): " << resultado2 << endl;
	cout << "Resultado con taylor de mayor a menor e^(-x) : " << resultado1Inv << endl;
	cout << "Resultado con taylor de menor a mayor e^(-x) : " << resultado2Inv << endl;

	cout << "Error Absoluto mayor a menor 1/(e^x): " << (fabs(pow(e,-valor) - resultado1.valor())) << endl;
	cout << "Error Relativo mayor a menor 1/(e^x): " << (fabs(pow(e,-valor) - resultado1.valor()) / pow(e,-valor)) << endl << endl;
	cout << "Error Absoluto menor a mayor 1/(e^x): " << (fabs(pow(e,-valor) - resultado2.valor())) << endl;
	cout << "Error Relativo menor a mayor 1/(e^x): " << (fabs(pow(e,-valor) - resultado2.valor()) / pow(e,-valor)) << endl << endl << endl;

	cout << "Error Absoluto mayor a menor e^(-x): " << (fabs(pow(e,-valor) - resultado1Inv.valor())) << endl;
	cout << "Error Relativo mayor a menor e^(-x): " << (fabs(pow(e,-valor) - resultado1Inv.valor()) / pow(e,-valor)) << endl << endl;
	cout << "Error Absoluto menor a mayor e^(-x): " << (fabs(pow(e,-valor) - resultado2Inv.valor())) << endl;
	cout << "Error Relativo menor a mayor e^(-x): " << (fabs(pow(e,-valor) - resultado2Inv.valor()) / pow(e,-valor)) << endl << endl << endl;

	system("PAUSE");
	return EXIT_SUCCESS;
}

