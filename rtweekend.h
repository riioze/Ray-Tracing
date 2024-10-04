#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>


// C++ std
using std::make_shared;
using std::shared_ptr;

//Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.141592653589732385;

// Utility funcs

inline double degrees_to_radiants(double degrees){
    return degrees * pi/ 180.0;
}

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

// Common headers
#include "color.h"
#include "ray.h"
#include "vec3.h"

#endif