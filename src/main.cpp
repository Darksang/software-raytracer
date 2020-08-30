#include <iostream>
#include <limits>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

#include "ray.h"
#include "hittable_list.h"
#include "raytracer.h"
#include "color.h"
#include "camera.h"
#include "material.h"
#include "mesh.h"

#include "sphere.h"
#include "triangle.h"

glm::vec3 RayColor(const Ray & r, const Hittable & World, int Depth) {
   HitRecord Rec;

   if (Depth <= 0)
      return glm::vec3(0, 0, 0);

   if (World.Hit(r, 0.001, Infinity, Rec)) {
      Ray Scattered;
      glm::vec3 Attenuation;
      
      if (Rec.MaterialPtr->Scatter(r, Rec, Attenuation, Scattered))
         return Attenuation * RayColor(Scattered, World, Depth - 1);

      return glm::vec3(0, 0, 0);
   }

   glm::vec3 UnitDirection = glm::normalize(r.Direction);
   auto t = 0.5 * (UnitDirection.y + 1.0);
   return (1.0 - t) * glm::vec3(1.0, 1.0, 1.0) + t * glm::vec3(0.5, 0.7, 1.0);
}

int main(int argc, char **argv) {
   // Image settings
   const auto AspectRatio = 16.0 / 9.0;
   const int ImageWidth = 800;
   const int ImageHeight = static_cast<int>(ImageWidth / AspectRatio);
   const int SamplesPerPixel = 100;
   const int MaxDepth = 50;

   // Camera settings
   Camera Cam(glm::vec3(-2, 2, 1), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0), 60, AspectRatio);

   // World
   HittableList World;

   auto MaterialGround = make_shared<Lambertian>(glm::vec3(0.894, 0.184, 0.384));
   auto MaterialCenter = make_shared<Lambertian>(glm::vec3(0.113, 0.768, 0.929));
   auto MaterialLeft = make_shared<Metal>(glm::vec3(0.8, 0.8, 0.8), 0.3);
   auto MaterialRight = make_shared<Metal>(glm::vec3(0.8, 0.6, 0.2), 1.0);
   auto MaterialTriangle = make_shared<Lambertian>(glm::vec3(1.0, 0.6, 0.1));

   World.Add(make_shared<Sphere>(glm::vec3(0, 0, -1), 0.5, MaterialCenter));
   World.Add(make_shared<Sphere>(glm::vec3(0, -100.5, -1), 100, MaterialGround));
   World.Add(make_shared<Sphere>(glm::vec3(-1.0, 0.0, -1), 0.5, MaterialLeft));
   World.Add(make_shared<Sphere>(glm::vec3(1.0, 0.0, -1), 0.5, MaterialRight));
   World.Add(make_shared<Triangle>(glm::vec3(-1, -1, -5), glm::vec3(1, -1, -5), glm::vec3(0, 1, -5), MaterialTriangle));

   // Rendering
   std::cout << "P3\n" << ImageWidth << " " << ImageHeight << "\n255\n";

   for (int j = ImageHeight - 1; j >= 0; --j) {
      std::cerr << "\rScanlines Remaining: " << j << ' ' << std::flush;
      for (int i = 0; i < ImageWidth; ++i) {
         glm::vec3 PixelColor(0, 0, 0);

         for (int s = 0; s < SamplesPerPixel; ++s) {
            auto u = (i + RandomDouble()) / (ImageWidth - 1);
            auto v = (j + RandomDouble()) / (ImageHeight - 1);
            Ray r = Cam.GetRay(u, v);
            PixelColor += RayColor(r, World, MaxDepth);
         }

         WriteColor(std::cout, PixelColor, SamplesPerPixel);
      }
   }

   std::cerr << "\nDone.\n";

   return 0;
}