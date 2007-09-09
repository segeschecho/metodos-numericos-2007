#ifndef _DLFloat_H
#define _DLFloat_H


#include <stdio.h>
#include <iostream>
#include <math.h>
#include <iomanip>      //para setprecision

using namespace std;

class DLFloat{
        friend ostream& operator << (ostream &o, const DLFloat &a);
        friend void truncar(DLFloat *c);

    public:

        DLFloat(int = 63, long double = 0);	//precision predefinida: 63 bits
                                            //valor predefinido: 0

        int 		precision	(void);
        long double	valor   	(void);
        DLFloat 	operator+	(const DLFloat &a);
        void     	operator++	(int);
        DLFloat 	operator-	(const DLFloat &a);
        DLFloat 	operator*	(const DLFloat &a);
        DLFloat 	operator/	(const DLFloat &a);
        DLFloat 	operator/	(long double a);
        DLFloat 	operator^	(int a);
        void 		operator=	(const DLFloat &a);
        void 		operator=	(long double a);

        ~DLFloat(){};
    private:
        int prec;
        long double numero;
};

#endif	/*_DLFloat_H*/
