#ifndef _VLFloat_H
#define _VLFloat_H


#include <stdio.h>
#include <iostream>
#include <math.h>
#include <iomanip>      //para setprecision

using namespace std;

class VLFloat{
        friend ostream& operator << (ostream &o, const VLFloat &a);
        friend void redondear(VLFloat *c);

    public:

        VLFloat(int = 64, long double = 0);	//presicion predefinida: 64 bits

        int 		precision	(void);
        long double	valor   	(void);
        VLFloat 	operator+	(const VLFloat &a);
        VLFloat 	operator-	(const VLFloat &a);
        VLFloat 	operator*	(const VLFloat &a);
        VLFloat 	operator/	(const VLFloat &a);
        VLFloat 	operator/	(long double a);
        VLFloat 	operator^	(int a);
        void 		operator=	(const VLFloat &a);
        void 		operator=	(long double a);

        ~VLFloat(){};
    private:
        int prec;
        long double numero;
};

#endif	/*_VLFloat_H*/
