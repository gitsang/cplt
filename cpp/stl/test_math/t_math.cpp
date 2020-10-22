#include <iostream>
#include <cmath>
#include <cstdio>
#include <math.h>

#define PI 3.14

void t_frexp() {
    int e = 0;
    double x = 1024;
    double fraction = frexp(x, &e);
    printf("frexp():\tx = %.2lf = %.2lf * 2^%d\n", x, fraction, e);
}

void t_ldexp() {
    int e = 3;
    double x = 0.5;
    double ret = ldexp(x, e);
    printf("ldexp():\t%f * 2^%d = %f\n", x, e, ret);
}

void t_math() {
    /* absolute value of x */
    std::cout << "abs(3.14) = " << std::abs(3.14) << '\n';
    std::cout << "fabs(3.14159) = " << std::abs(3.14159) << '\n';
    std::cout << "labs(-199999L) = " << std::abs(-199999L) << '\n';
    /* smallest integral that not less than x */
    printf("ceil(3.8) = %.1f\n", ceil(3.8));
    printf("ceil(-2.3) = %.1f\n", ceil(-2.3));
    /* value of x rounded downward */
    printf("floor(3.8) = %.1lf\n", floor(3.8));
    printf("floor(-2.3) = %.1lf\n", floor(-2.3));
    
    /* cubic root of x */
    printf("cbrt(%f) = %f\n", 27, cbrt(27));
    
    /* copy sign of y to x */
    printf("copysign(10, -1) = %f\n", copysign(10, -1));
    
    /* positive difference betwee x and y */
    printf("fdim(4.0, 1.0) = %f\n", fdim(4.0, 1.0));
    printf("fdim(1.0, 4.0) = %f\n", fdim(1.0, 4.0));

    /* fma */
    printf("fma: 10.0 * 20.1 + 30.2 = %f\n", fma(10.0, 20.1, 30.2));
    printf("fmin(-100.0, 1.0) = %f\n", fmin(-100.0, 1.0));
    printf("fmax(-100.0, -1.0) = %f\n", fmax(-100.0, -1.0));
    printf("fmod(18.5/4.2) = %f\n", fmod (18.5, 4.2));
    t_frexp();
    t_ldexp();
    /* Gauss error function */
    printf("erf(%f) = %f\n", 1, erf(1));
    printf("erfc(%f) = %f\n", 1, erfc(1));
    
}

int main() {
    t_math();

    return 0;
}
