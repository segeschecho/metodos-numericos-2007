#include "Horno.h"


/*************************************/
/*          METODOS PUBLICOS         */
/*************************************/



Horno :: Horno(int radio, int cantAngulos, int cantRadios, int tint, int text, long double k, long double h, int* radiosLimite){
    rad = radio;
    angs = cantAngulos;
    rads = cantRadios;
    deltaR = (long double)rad/((long double)rads - 1);
    deltaT = 2*PI/(long double)angs;
    ti = tint;
    tinf = text;
    this->k = k;
    this->h = h;
	temperaturas = NULL;

	bordeInterno = new int [angs];

    // guardo los radios para cada angulo
    // asi queda definida la funcion de temperatura.
    for(int ang = 0; ang < angs; ang++)
        bordeInterno[ang] = radiosLimite[ang];

	calcular_temperaturas();
}

long double	Horno :: getTemperatura(long double radio, long double theeta) const{
	int i = (int)fabs(radio/deltaR);
	if ( i > rads - 1 )
		i = rads - 1;

	while (theeta >= 2*PI){
		theeta -= 2*PI;
	}
	int j = (int)fabs(theeta/deltaT);
	if ( j > rads - 1 )
		j = rads - 1;

	return temperaturas->ver(i, j);
}

long double Horno :: getRadio() const{
    return rad;
}

int Horno :: getCantidadAngulos() const{
    return angs;
}

int Horno :: getCantidadRadios() const{
    return rads;
}

int Horno :: getTi() const{
    return ti;
}                       //Temperatura interior

int Horno :: getTinf() const{
    return tinf;
}                     //Temperatura exterior

long double Horno :: getK() const{
    return k;
}                        //constante K

long double Horno :: getH() const{
    return h;
}                        //constante H

void Horno :: operator=(const Horno &h1){
    rad = h1.rad;
    angs = h1.angs;
    rads = h1.rads;
    deltaR = h1.deltaR;
    deltaT = h1.deltaT;         //delta Theeta
    ti = h1.ti;
    tinf = h1.tinf;
    k = h1.k;
    h = h1.h;

	delete temperaturas;
    temperaturas = new Matriz(rads, angs);
    *temperaturas = *(h1.temperaturas);

	delete [] bordeInterno;
    bordeInterno = new int[angs];
    for(int i = 0; i < angs; i++)
        bordeInterno[i] = h1.bordeInterno[i];
}

int Horno :: funcionRadio(int angulo) const{
    return bordeInterno[angulo];
}
/* Destructor */
Horno :: ~Horno(){
	delete temperaturas;
    delete [] bordeInterno;
}

/*************************************/
/*          METODOS PRIVADOS         */
/*************************************/

void Horno :: calcular_temperaturas(void){

    Matriz temp(rads*angs, rads*angs);
	Matriz b(rads*angs, 1);
	Matriz X(rads*angs, 1);

	delete temperaturas;
    temperaturas = new Matriz(rads, angs);

    int filaALlenar = 0;

	for(int r = 0; r < rads; r++){
        for(int a = 0; a < angs; a++)
        {
            if (r <= bordeInterno[a]){           //si es un punto del borde interno
			//sabemos que por la 2da ecuacion, la temperatura de los puntos
			//dentro de este borde es 5000, entonces se que el coeficiente
			//del punto en cuestion sera 1, y su correspondiente
			//resultado en b es 5000

			//ahora asigno el coeficiente en la matriz
			//viendo la matriz como un arreglo de filas,
			//dentro de la fila a llenar:
			//T[r][a] = 1
				temp.asignar(filaALlenar, r*angs + a, 1);
				b.asignar(filaALlenar, 0, ti);
            }
            else{
                if(r != rads - 1){          //si no es un punto del borde interno
                    long double coef1 = 1/(deltaR*deltaR) - 1/(r*deltaR*deltaR);
                    long double coef2 = 1/((deltaT*deltaT)*(r*r*deltaR*deltaR));
                    long double coef3 = -2/(deltaR*deltaR) + 1/(r*deltaR*deltaR) - 2/(r*deltaR*r*deltaR*deltaT*deltaT);
                    long double coef4 = 1/((r*deltaR*r*deltaR)*(deltaT*deltaT));
                    long double coef5 = 1/(deltaR*deltaR);
					//coef 1 a 5 son los 5 coeficientes de las incognitas que quedan
					//luego de la discretizacion del Laplaciano

					//ahora asigno los coeficientes en la matriz
					//viendo la matriz como un arreglo de filas,
					//dentro de la fila a llenar:
					//T[r-1][a] = coef1
					//T[r][a-1] = coef2
					//T[r][a]   = coef3
					//T[r][a+1] = coef4
					//T[r+1][a] = coef5
					temp.asignar(filaALlenar, (r - 1)*angs + a, coef1);
					temp.asignar(filaALlenar, r*angs + a - 1, coef2);
					temp.asignar(filaALlenar, r*angs + a, coef3);
					temp.asignar(filaALlenar, r*angs + a + 1, coef4);
					temp.asignar(filaALlenar, (r + 1)*angs + a, coef5);
                }
				else{	//si el punto es del borde externo
					long double coef = k/(h*deltaR);
					//coef cubre los 2 coeficientes que resultan de discretizar
					//la 3er ecuacion en cuestion

					//ahora asigno los coeficientes en la matriz
					//viendo la matriz como un arreglo de filas,
					//dentro de la fila a llenar:
					//T[r][a] = coef
					//T[r-1][a] = coef + 1
					temp.asignar(filaALlenar, r*angs + a, -coef - 1);
					temp.asignar(filaALlenar, (r - 1)*angs + a, coef);
					b.asignar(filaALlenar, 0, -tinf);
				}
            }
            //ahora avanzo en la fila
			filaALlenar++;
        }
	}

	temp.triangular(b);
	temp.resolver(X,b);

	for(int r = 0; r < rads; r++){
		for(int a = 0; a < angs; a++){
			temperaturas->asignar(r,a,X.ver(r*angs + a, 0));
		}
	}
}

/*************************************/
/*          FUNCIONES FRIEND         */
/*************************************/

void cargar(istream& archivo, Horno &h){
    char data[128];

    //agarro el comentario
    archivo.getline(data, 100);
    //agarro radio exterior
    archivo.getline(data, 100);
    h.rad = atoi(data);

    //agarro el comentario
    archivo.getline(data, 100);
    //agarro cantidad de angulos
    archivo.getline(data, 100);
    h.angs = atoi(data);

	//agarro el comentario
    archivo.getline(data, 100);
    //agarro cantidad de radios
    archivo.getline(data, 100);
    h.rads = atoi(data);

    h.deltaR = (long double)h.rad/((long double)h.rads - 1);
    h.deltaT = 2*PI/(long double)h.angs;

	//agarro el comentario
    archivo.getline(data, 100);
    //agarro temperatura interior
    archivo.getline(data, 100);
    h.ti = atoi(data);

	//agarro el comentario
    archivo.getline(data, 100);
    //agarro temperatura exterior
    archivo.getline(data, 100);
    h.tinf = atoi(data);

	//agarro comentario
    archivo.getline(data, 100);
    //agarro cosntante K
    archivo.getline(data, 100);
    h.k = atof(data);

	//agarro comentario
    archivo.getline(data, 100);
    //agarro constante H
    archivo.getline(data, 100);
    h.h = atof(data);

	//agarro comentario
    archivo.getline(data, 100);
    //agarro funcion de temperatura
	delete [] h.bordeInterno;
    h.bordeInterno = new int [h.angs];

    for(int ang = 0 ; ang < h.angs ; ang++){
        // agarro el radio para el angulo cant
        archivo.getline(data, 100);
        h.bordeInterno[ang] = atoi(data);
    }

	h.calcular_temperaturas();
}

void guardarParaGrafico(ostream &out, const Horno &h){
    Matriz m = *(h.temperaturas);

    int centroR = m.filas() - 1;             //radios

    int X = 0;
    int Y = 0;

    // guardo las X
    out << "X = [ ";

    for(int i = 0 ; i < m.filas(); i++){
        for(int j = 0 ; j < m.columnas(); j++){
            X = (int)((i*(h.rad)/(h.rads))*cos(j*2*PI/centroR));       //cuanto me muevo en "X" = Rcos(tita)

            out << " " << X;
        }
    }

    out << "]; " << endl << endl;
    // guardo las Y
    out << "Y =[ ";
    for(int i = 0 ; i < m.filas(); i++){
        for(int j = 0 ; j < m.columnas(); j++){
            Y = (int)((i*(h.rad)/(h.rads))*sin(j*2*PI/centroR));       //cuanto me muevo en "X"

            out << " " << Y;
        }
    }


    out << "]; " << endl << endl;

    //guardo los resultados del sistema
    out << *(h.temperaturas) << endl;
}
