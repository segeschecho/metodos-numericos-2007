#include <iostream>
#include "Matriz.h"

using namespace std;

int main(){
	Matriz mat(6,6);

	mat.asignar(0, 0, 1);
	mat.asignar(0, 1, 2);
	mat.asignar(0, 2, 3);
	mat.asignar(0, 3, 4);
	mat.asignar(0, 4, 6);
	mat.asignar(0, 5, 3);


	mat.asignar(1, 0, 7);
	mat.asignar(1, 1, 2);
	mat.asignar(1, 2, 1);
	mat.asignar(1, 3, 15);
	mat.asignar(1, 4, 0);
	mat.asignar(1, 5, 9);

	mat.asignar(2, 0, 1);
	mat.asignar(2, 1, 3);
	mat.asignar(2, 2, 13);
	mat.asignar(2, 3, 11);
	mat.asignar(2, 4, 2);
	mat.asignar(2, 5, 5);

	mat.asignar(3, 0, 21);
	mat.asignar(3, 1, 1);
	mat.asignar(3, 2, 8);
	mat.asignar(3, 3, 6);
	mat.asignar(3, 4, 17);
	mat.asignar(3, 5, 12);

	mat.asignar(4, 0, 23);
	mat.asignar(4, 1, 7);
	mat.asignar(4, 2, 6);
	mat.asignar(4, 3, 14);
	mat.asignar(4, 4, 10);
	mat.asignar(4, 5, 9);

	mat.asignar(5, 0, 1);
	mat.asignar(5, 1, 3);
	mat.asignar(5, 2, 5);
	mat.asignar(5, 3, 29);
	mat.asignar(5, 4, 8);
	mat.asignar(5, 5, 4);

	cout << mat << endl;
	mat.triangular();
	cout << mat << endl;


	system("PAUSE");
	return EXIT_SUCCESS;
}
