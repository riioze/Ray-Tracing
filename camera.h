#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"

class camera {
    public:
        double aspect_ratio = 16.0/9.0;
        int image_width = 400;
        int sample_per_pixel = 10;
        int max_depth = 10;
        void render(hittable &world){
            initialize();

            std::cout<<"P3\n"<<image_width<<" "<<image_height<<"\n255\n";

            for (int j = 0; j < image_height; j++) {
                std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
                for (int i = 0; i < image_width; i++) {
                    color pixel_color(0,0,0);
                    for (int sample=0; sample<sample_per_pixel;sample++){
                        ray r = get_ray(i,j);
                        pixel_color += ray_color(r,max_depth,world);

                    }
                    write_color(std::cout, pixel_color*pixel_sample_scale);
                } 
            }
            std::clog << "\rDone.                  \n";
        }

    private:
    int image_height;
    double pixel_sample_scale;
    point3 center;
    point3 pixel00_loc;
    vec3 pixel_delta_u,pixel_delta_v;
        void initialize(){
                //calculate the height using the ratio
            image_height = int(image_width/aspect_ratio);
            image_height = (image_height<1) ? 1 : image_height; //ensure that image height >= to 1

                // Camera

            auto focal_length = 1.0;
            auto viewport_height = 2.0;
            auto viewport_width = viewport_height*(double(image_width)/image_height);

            pixel_sample_scale = 1.0/sample_per_pixel;

            center = point3(0,0,0);

            // Calculate the vectors across the horizontal and down the viewport edge
            vec3 viewport_u = vec3(viewport_width,0,0);
            vec3 viewport_v = vec3(0,-viewport_height,0);

            //calculate du and dv the delta vectors between each pixel of the camera
            pixel_delta_u = viewport_u/image_width;
            pixel_delta_v = viewport_v/image_height;

            //calculate the position of the upper left pixel
            point3 viewport_upper_left = center 
                                        -vec3(0,0,focal_length) // project from the camera to the center of the viewport
                                        -viewport_u/2 -viewport_v/2; // move top left of viewport
            
            pixel00_loc = viewport_upper_left + 0.5*(pixel_delta_u+pixel_delta_v); //move from the upperleft of the viewport to the first pixel
        }

        ray get_ray(int i, int j){
            vec3 offset = sample_square();
            point3 pixel_sample = pixel00_loc
                                + ((i+offset.x())*pixel_delta_u)
                                + ((j+offset.y())*pixel_delta_v);
            
            point3 ray_origin = center;
            vec3 ray_direction = pixel_sample-ray_origin;

            return ray(ray_origin,ray_direction);

        }

        vec3 sample_square() const {
            return vec3(random_double()-0.5,random_double()-0.5,0);
        }

        color ray_color(const ray& r,int depth, const hittable& world){

            if (depth<=0) return color(0,0,0);
        
            hit_record rec;
            if (world.hit(r,interval(0.001,infinity),rec)){
                vec3 direction = rec.normal+random_on_hemisphere(rec.normal);
                return 0.5*ray_color(ray(rec.p,direction),depth-1,world);       
            }

            
            vec3 unit_direction = unit_vector(r.direction());

            //draw the backgroud if no object is reached
            auto a = 0.5*(unit_direction.y()+1.0);
            return (1.0-a)*color(1.0,1.0,1.0) + a*color(0.5,0.7,1.0);
        }
};

#endif