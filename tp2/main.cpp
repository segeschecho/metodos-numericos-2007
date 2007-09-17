#include <iostream>
#include "Matriz.h"

using namespace std;

int main(){
	Matriz mat(3,3);

	mat.asignar(0, 0, 2);
	mat.asignar(0, 1, 1);
	mat.asignar(0, 2, 2);
	mat.asignar(1, 0, 1);
	mat.asignar(1, 1, 2);
	mat.asignar(1, 2, 3);
	mat.asignar(2, 0, 4);
	mat.asignar(2, 1, 1);
	mat.asignar(2, 2, 2);

	cout << mat << endl;
	mat.triangular();
	cout << mat << endl;
	system("PAUSE");
	return EXIT_SUCCESS;
}
