#include "VLFloat.h"

#define MAX(a, b) (a > b) ? a : b

VLFloat :: VLFloat(int precision, long double valor){
    prec = precision;
    numero = valor;
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

	res = numero;

	while (a > 0){
		res.numero *= numero;
		redondear(&res);
		a--;
	}

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

	if(c->numero != 1){
		cout.setf(ios_base::fixed);
		cout.precision(60);
		cout << (c->numero) << endl;
		cout << (c->numero) << endl;
	}
	*ch += ( 1 << (7 - (c->prec % 8)) ); //con esto le sumamos 5 al digito a partir del cual vamos a truncar
	*ch &= (255 << (8 - (c->prec % 8)) ); //255 = 1111 1111

	//ahora borramos los bytes menos significativos
	memset(&(c->numero), 0, bytes - 1);
}

ostream& operator << (ostream &os, const VLFloat &a){
    os << setprecision(a.prec) << a.numero << endl;
	return os;
}

VLFloat :: ~VLFloat(){
}
