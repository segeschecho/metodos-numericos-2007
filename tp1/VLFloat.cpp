#include "DLFloat.h"

#define MAX(a, b) (a > b) ? a : b

DLFloat :: DLFloat(int precision, long double valor){
    assert((precision < 64) && (precision > 0));
    prec = precision;
    numero = valor;
	truncar(this);
}

int DLFloat :: precision(void){
    return prec;
}

long double DLFloat :: valor(void){
    return numero;
}

DLFloat DLFloat :: operator+(const DLFloat &a){
	DLFloat res(MAX(a.prec, prec));

	res.numero = numero + a.numero;
	truncar(&res);

	return res;
}

void DLFloat :: operator++(int a){
    numero++;
}

DLFloat DLFloat :: operator-(const DLFloat &a){
	DLFloat res(MAX(a.prec, prec));

	res.numero = numero - a.numero;
	truncar(&res);

	return res;
}

DLFloat DLFloat :: operator*(const DLFloat &a){
	DLFloat res(MAX(a.prec, prec));

	res.numero = numero * a.numero;
	truncar(&res);

	return res;
}

DLFloat DLFloat :: operator/(const DLFloat &a){
	DLFloat res(MAX(a.prec, prec));

	res.numero = numero / a.numero;
	truncar(&res);

	return res;
}

DLFloat DLFloat :: operator/(long double a){
	DLFloat res(prec);

	res.numero = numero / a;
	truncar(&res);

	return res;
}

DLFloat DLFloat :: operator^(int a){
	DLFloat res(prec);
	bool neg = 0;

	if ( a < 0 ){
		a = -a;
		neg = 1;
	}

	res = numero;
	a--;

	while (a > 0){
		res.numero *= numero;
		truncar(&res);
		a--;
	}

	if (neg)
		res.numero = 1/res.numero;

	return res;
}

void DLFloat :: operator=(const DLFloat &a){
    numero = a.numero;
    truncar(this);
}

void DLFloat :: operator=(long double a){
    numero = a;
    truncar(this);
}

void truncar(DLFloat* c)
{
    //La variable bytes representara la cantidad de bytes que tenemos de mantisa
	int bytes = 8;    //"ignoramos" los 2 bytes de exponente + signo al truncar
                      //que estan en la posicion de memoria mas alta

	bytes -= (int)((c->prec)/8);
	//esto representa la cantidad de bytes enteros que voy a eliminar desde el menos significativo

	unsigned char* ch = ((unsigned char*)&(c->numero) + bytes - 1);

//	*ch += ( 1 << (7 - (c->prec % 8)) ); //con esto le sumamos 1 al primer bit que voy a truncar
                                         //con el fin de truncar
	*ch &= (255 << (8 - (c->prec % 8)) ); //255 = 1111 1111
	//ahora borramos los bytes menos significativos
	memset(&(c->numero), 0, bytes - 1);
}

ostream& operator<<(ostream &os, const DLFloat &a){
    os << a.numero;
	return os;
}
