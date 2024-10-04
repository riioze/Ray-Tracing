#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"
#include "ray.h"
#include "color.h"

class sphere{
    public:
        sphere(const point3& center, double radius, color sphere_color) : cent(center), rad(radius), col(sphere_color){}

        const point3 center() const {return cent;}
        const double radius() const {return rad;}
        const color sphere_color() const {return col;} 

        bool hit(const ray& r){
            // resolving at2 + bt + c = 0 if there is solution(s) then the ray hit the sphere at t1 and t2
            vec3 oc = cent-r.origin();
            double a = dot(r.direction(),r.direction());
            double b = -2.0 * dot(r.direction(), oc);
            double c = dot(oc,oc) - rad*rad;
            double discriminant = b*b - 4*a*c;
            return discriminant>=0;
        }
    private:
        point3 cent;
        double rad;
        color col;
            
};

#endif