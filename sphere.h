#ifndef SPHERE_H
#define SPHERE_H


#include "hittable.h"

class sphere : public hittable{
    public:
        sphere(const point3& center, double radius) : center(center), radius(radius), col(){}
        sphere(const point3& center, double radius, color sphere_color) : center(center), radius(radius), col(sphere_color){}

        const color sphere_color() const {return col;} 

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override{
            // resolving at2 + bt + c = 0 if there is solution(s) then the ray hit the sphere at t1 and t2
            vec3 oc = center-r.origin();
            double a = dot(r.direction(),r.direction());
            double h = dot(r.direction(), oc);
            double c = dot(oc,oc) - radius*radius;
            double discriminant = h*h - a*c;
            if (discriminant<0){
                return false;
            }
            double sqrtd = std::sqrt(discriminant);



            double root = (h-sqrtd)/a;
            if (!ray_t.surronds(root)){
                root = (h+sqrtd)/a;
                if (!ray_t.surronds(root)){
                    return false;
                }
            }

            rec.t = root;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p-center)/radius;
            rec.set_face_normal(r,outward_normal);

            return true;

        }
    private:
        point3 center;
        double radius;
        color col;
            
};

#endif