#include <iostream>
#include "Matriz.h"

using namespace std;

int main(){
	Matriz mat(4,4);
	mat.asignar(0,0,20);
	mat.asignar(0,1,20);
	mat.asignar(0,2,20);
	mat.asignar(0,3,20);

	cout << mat.ver(0,0) << endl;
	mat.permutar(0,1);
	cout << mat.ver(0,0) << endl;
	cout << mat.ver(1,0) << endl;

	system("PAUSE");
	return EXIT_SUCCESS;
}
