#include "VLFloat.h"

#define MAX(a, b) (a > b) ? a : b

void mostrar(unsigned char c)
{
    unsigned char c0 = c + 9;
    unsigned char c1 = c + 8;
    unsigned char c2 = c + 7;
    unsigned char c3 = c + 6;
    unsigned char c4 = c + 5;
    unsigned char c5 = c + 4;
    unsigned char c6 = c + 3;
    unsigned char c7 = c + 2;
    unsigned char c8 = c + 1;
    unsigned char c9 = c;

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
    float _mantisa = 0;

    for(int i=0, pot=128; i<15; ++i)
    {
        exponente[i] = todo[i+1];
        _exponente += (exponente[i] - '0') * pot;
        pot /= 2;
    }

    float _pot = 0.5;
    for(int i=0; i<64; ++i)
    {
        mantisa[i] = todo[i+9];
        _mantisa += (mantisa[i] - '0') * _pot;
        _pot /= 2;
    }

    exponente[15] = 0;
    mantisa[64] = 0;

    printf( "signo = %c, ", signo );
    printf( "exp = %s (%d), ", exponente, _exponente );
    printf( "mant = 1.%s \n", mantisa );
//  printf( "%3.5f = %s \n", *x, todo );
}

VLFloat :: VLFloat(int precision, long double valor){
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

    cout << "mostrar" << endl;
    mostrar((unsigned char)(c->numero));
//	*ch += ( 1 << (7 - (c->prec % 8)) ); //con esto le sumamos 1 al primer bit que voy a truncar
                                         //con el fin de redondear
	*ch &= (255 << (8 - (c->prec % 8)) ); //255 = 1111 1111
	//ahora borramos los bytes menos significativos
	memset(&(c->numero), 0, bytes - 1);
    mostrar((unsigned char)(c->numero));
}

ostream& operator<<(ostream &os, const VLFloat &a){
    os << a.numero;
	return os;
}
