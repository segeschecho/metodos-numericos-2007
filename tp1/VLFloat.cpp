#include "VLFloat.h"

#define MAX(a, b) (a > b) ? a : b

VLFloat :: VLFloat(int precision, long double valor){
    assert((precision < 64) && (precision > 0));
    prec = precision;
    numero = valor;
	redondear(this);
}

int VLFloat :: precision(void){
    return prec;
}

long double VLFloat :: valor(void){
    return numero;
}

VLFloat VLFloat :: operator+(const VLFloat &a){
	VLFloat res(MAX(a.prec, prec));

	res.numero = numero + a.numero;
	redondear(&res);

	return res;
}

void VLFloat :: operator++(int a){
    numero++;
}

VLFloat VLFloat :: operator-(const VLFloat &a){
	VLFloat res(MAX(a.prec, prec));

	res.numero = numero - a.numero;
	redondear(&res);

	return res;
}

VLFloat VLFloat :: operator*(const VLFloat &a){
	VLFloat res(MAX(a.prec, prec));

	res.numero = numero * a.numero;
	redondear(&res);

	return res;
}

VLFloat VLFloat :: operator/(const VLFloat &a){
	VLFloat res(MAX(a.prec, prec));

	res.numero = numero / a.numero;
	redondear(&res);

	return res;
}

VLFloat VLFloat :: operator/(long double a){
	VLFloat res(prec);

	res.numero = numero / a;
	redondear(&res);

	return res;
}

VLFloat VLFloat :: operator^(int a){
	VLFloat res(prec);
	bool neg = 0;

	if ( a < 0 ){
		a = -a;
		neg = 1;
	}

	res = numero;
	a--;

	while (a > 0){
		res.numero *= numero;
		redondear(&res);
		a--;
	}

	if (neg)
		res.numero = 1/res.numero;

	return res;
}

void VLFloat :: operator=(const VLFloat &a){
    numero = a.numero;
    redondear(this);
}

void VLFloat :: operator=(long double a){
    numero = a;
    redondear(this);
}

void redondear(VLFloat* c)
{
    //La variable bytes representara la cantidad de bytes que tenemos de mantisa
	int bytes = 8;    //"ignoramos" los 2 bytes de exponente + signo al redondear
                      //que estan en la posicion de memoria mas alta

	bytes -= (int)((c->prec)/8);
	//esto representa la cantidad de bytes enteros que voy a eliminar desde el menos significativo

	unsigned char* ch = ((unsigned char*)&(c->numero) + bytes - 1);

//	*ch += ( 1 << (7 - (c->prec % 8)) ); //con esto le sumamos 1 al primer bit que voy a truncar
                                         //con el fin de redondear
	*ch &= (255 << (8 - (c->prec % 8)) ); //255 = 1111 1111
	//ahora borramos los bytes menos significativos
	memset(&(c->numero), 0, bytes - 1);
}

ostream& operator<<(ostream &os, const VLFloat &a){
    os << a.numero;
	return os;
}
