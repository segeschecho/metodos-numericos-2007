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
	truncar(&res);

	return res;
}

VLFloat VLFloat :: operator-(const VLFloat &a){
	VLFloat res(MAX(a.prec, prec));

	res.numero = numero - a.numero;
	truncar(&res);

	return res;
}

VLFloat VLFloat :: operator*(const VLFloat &a){
	VLFloat res(MAX(a.prec, prec));

	res.numero = numero * a.numero;
	truncar(&res);

	return res;
}

VLFloat VLFloat :: operator/(const VLFloat &a){
	VLFloat res(MAX(a.prec, prec));

	res.numero = numero / a.numero;
	truncar(&res);

	return res;
}

VLFloat VLFloat :: operator/(long double a){
	VLFloat res(prec);

	res.numero = numero / a;
	truncar(&res);

	return res;
}

VLFloat VLFloat :: operator^(int a){
	VLFloat res(prec);

	res = numero;

	while (a > 0){
		res.numero *= numero;
		truncar(&res);
		a--;
	}

	return res;
}

void VLFloat :: operator=(const VLFloat &a){
    numero = a.numero;
    truncar(this);
}

void VLFloat :: operator=(long double a){
    numero = a;
    truncar(this);
}

void truncar(VLFloat* c)
{
    //bytes representara la cantidad de bytes que tenemos de mantisa
	int bytes = 8;    //"ignoramos" los 2 bytes de exponente + signo al truncar
                      //que estan en la posicion de memoria mas alta

	bytes -= (int)((c->prec)/8);        //esto representa la cantidad
    memset(&(c->numero), 0, bytes - 1);	//de bytes enteros que voy a eliminar 
                                        //desde el menos significativo

	unsigned char* ch = ((unsigned char*)c + bytes - 1);
    *ch &= (255 << 8 - (c->prec % 8)); //255 = 1111 1111
}

ostream& operator << (ostream &os, const VLFloat &a){
    os << setprecision(a.prec) << a.numero << endl;
}

VLFloat :: ~VLFloat(){
}
