#include <iostream>
#include "Matriz.h"

using namespace std;

int main(){
	Matriz mat(10, 10);
	cout << mat.ver(1,1) << endl;
	mat.asignar(1,1,20);
	cout << mat.ver(1,1) << endl;

	system("PAUSE");
	return EXIT_SUCCESS;
}
