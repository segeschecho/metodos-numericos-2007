#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include "VLFloat.h"

using namespace std;

VLFloat factorial(unsigned int n, unsigned int p)
{
	VLFloat res(p, 1);
	VLFloat i(p, 2);
	//i lo hice VLFloat por la linea: res = res*i; que viene luego

	if (n == 0)
		return res;

	while (i.valor() <= n)
	{
		res = res*i;
	    cout << "res = " << res << endl;
	    cout << "res.precision() = " << res.precision() << endl;
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
        for(int j = 1; j <= 170; j++){
            cout << setprecision(20) << taylorMenorAMayor(x, j, i) << " ";
            archivo << setprecision(20) << taylorMenorAMayor(x, j, i) << " ";
        }
    }

    archivo << " ]" << endl << endl;
    cout << " ]" << endl << endl;

    archivo << "B = [ ";
    cout << "B = [ ";

    for(int i = 1; i < 64; i++){
        for(int j = 1; j <= 170; j++){
            archivo << setprecision(20) << taylorMenorAMayorInv(x, j, i) << " ";
            cout << setprecision(20) << taylorMenorAMayorInv(x, j, i) << " ";
        }
    }

    archivo << " ]" << endl << endl;
    cout << " ]" << endl << endl;

    x = 5;

/*    while( x < 20 )
    {
        archivo << "x = " << x << endl;
        archivo << "~~~~~" << endl << endl;

        archivo << "A = [ ";

        cout << "x = " << x << endl;
        cout << "~~~~~" << endl << endl;

        cout << "A = [ ";

        for(int i = 1; i < 64; i++){
            for(int j = 1; j <= 170; j++){
                archivo << setprecision(20) << taylorMenorAMayor(x, j, i) << " ";
                cout << setprecision(20) << taylorMenorAMayor(x, j, i) << " ";
            }
        }

        archivo << " ]" << endl << endl;

        archivo << "B = [ ";

        cout << " ]" << endl << endl;

        cout << "B = [ ";

        for(int i = 1; i < 64; i++){
            for(int j = 1; j <= 170; j++){
                archivo << setprecision(20) << taylorMenorAMayorInv(x, j, i) << " ";
                cout << setprecision(20) << taylorMenorAMayorInv(x, j, i) << " ";
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
        for(int j = 1; j < 170; j++){
            archivo << setprecision(20) << taylorMayorAMenor(x, j, i) << " ";
            cout << setprecision(20) << taylorMayorAMenor(x, j, i) << " ";
        }
    }

    archivo << " ]" << endl << endl;

    archivo << "B = [ ";

    cout << " ]" << endl << endl;

    cout << "B = [ ";

    for(int i = 1; i < 64; i++){
        for(int j = 1; j < 170; j++){
            archivo << setprecision(20) << taylorMayorAMenorInv(x, j, i) << " ";
            cout << setprecision(20) << taylorMayorAMenorInv(x, j, i) << " ";
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
            for(int j = 1; j < 170; j++){
                archivo << setprecision(20) << taylorMayorAMenor(x, j, i) << " ";
                cout << setprecision(20) << taylorMayorAMenor(x, j, i) << " ";
            }
        }

        archivo << " ]" << endl << endl;

        archivo << "B = [ ";

        cout << " ]" << endl << endl;

        cout << "B = [ ";

        for(int i = 1; i < 64; i++){
            for(int j = 1; j < 170; j++){
                archivo << setprecision(20) << taylorMayorAMenorInv(x, j, i) << " ";
                cout << setprecision(20) << taylorMayorAMenorInv(x, j, i) << " ";
            }
        }

        archivo << " ]" << endl << endl;
        cout << " ]" << endl << endl;
        x += 5;
    }
*/
    archivo.close();
}

int main()
{
//  ofstream a ("grafico.txt");
//  imprimirValores(a);
	unsigned int p, orden;
	long double valor, e = 2.718281828459045235360287471352662497757247093699959574966967627724;

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

