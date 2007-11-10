#include "Misil.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    long double muestraX[4] = {1,0,1,2};
    long double muestraY[4] = {1,0,1,2};
    Misil test(0, muestraX, muestraY, 4);

    system("PAUSE");
    return 0;
}