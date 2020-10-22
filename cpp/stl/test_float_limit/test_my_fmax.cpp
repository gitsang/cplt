#include <stdio.h>
#include <stdlib.h> //abs()

#include <math.h> //pow()

float my_fmax(float a, float b) {
    if(abs(a-b) <= 1e-6) {
        return 0; 
    }
    return a > b ? a : b;
}

int main() {
    float a = 0.1f;
    float b = 0.01f;
    printf("%.8lf\n", my_fmax(pow(a, 2), a * a));

    return 0;
}
