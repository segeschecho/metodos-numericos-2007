#ifndef _VLFloat_H
#define _VLFloat_H


#include <stdio.h>
#include <iostream>
#include <math.h>
#include <iomanip>      //para setprecision

using namespace std;

class VLFloat{
        friend ostream& operator << (ostream &o, const VLFloat &a);
        friend void truncar(VLFloat *c);

    public:

        VLFloat(int = 63, long double = 0);	//precision predefinida: 63 bits
                                            //valor predefinido: 0

        int 		precision	(void);
        long double	valor   	(void);
        VLFloat 	operator+	(const VLFloat &a);
        void     	operator++	(int);
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
