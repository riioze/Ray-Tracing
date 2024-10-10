#include "rtweekend.h"

#include "sphere.h"
#include "hittable.h"
#include "hittable_list.h"



color ray_color(const ray& r, const hittable& world){
    
    hit_record rec;
    if (world.hit(r,interval(0,infinity),rec)){
        return 0.5*(rec.normal + color(1,1,1));        
    }

    
    vec3 unit_direction = unit_vector(r.direction());

    //draw the backgroud if no object is reached
    auto a = 0.5*(unit_direction.y()+1.0);
    return (1.0-a)*color(1.0,1.0,1.0) + a*color(0.5,0.7,1.0);
}

int main(){
    auto aspect_ratio = 16.0/9.0;
    int image_width = 400;

    //calculate the height using the ratio
    int image_height = int(image_width/aspect_ratio);
    image_height = (image_height<1) ? 1 : image_height; //ensure that image height >= to 1


    // World
    hittable_list world;

    world.add(make_shared<sphere>(point3(0,0,-1),0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1),100));


    // Camera

    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height*(double(image_width)/image_height);
    point3 camera_center = point3(0,0,0);

    // Calculate the vectors across the horizontal and down the viewport edge
    vec3 viewport_u = vec3(viewport_width,0,0);
    vec3 viewport_v = vec3(0,-viewport_height,0);

    //calculate du and dv the delta vectors between each pixel of the camera
    vec3 pixel_delta_u = viewport_u/image_width;
    vec3 pixel_delta_v = viewport_v/image_height;

    //calculate the position of the upper left pixel
    point3 viewport_upper_left = camera_center 
                                -vec3(0,0,focal_length) // project from the camera to the center of the viewport
                                -viewport_u/2 -viewport_v/2; // move top left of viewport
    
    point3 pixel00_loc = viewport_upper_left + 0.5*(pixel_delta_u+pixel_delta_v); //move from the upperleft of the viewport to the first pixel

    
    //render

    std::cout<<"P3\n"<<image_width<<" "<<image_height<<"\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) { 
            point3 pixel_center = pixel00_loc + (i*pixel_delta_u) + (j*pixel_delta_v);
            vec3 ray_direction = pixel_center-camera_center;
            ray r(camera_center,ray_direction);

            color pixel_color = ray_color(r,world);
            write_color(std::cout, pixel_color);
        } 
    }
    std::clog << "\rDone.                  \n";
}