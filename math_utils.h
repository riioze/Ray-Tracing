#ifndef MATH_UTILS_H
#define MATH_UTILS_H

double fast_inverse_sqrt(double number){
    double y = number;
    double x2 = y * 0.5;
    long long int i = *(long long int *) &y;
    // The magic number is for doubles is from https://cs.uwaterloo.ca/~m32rober/rsqrt.pdf
    i = 0x5fe6eb50c7b537a9 - (i >> 1);
    y = *(double *) &i;
    y = y * (1.5 - (x2 * y * y));   // 1st iteration
    //      y  = y * ( 1.5 - ( x2 * y * y ) );   // 2nd iteration, this can be removed
    return y;
}

#endif