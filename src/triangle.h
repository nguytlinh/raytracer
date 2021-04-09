#ifndef TRIANGLE_H_
#define TRIANGLE_H_


#include "hittable.h"
#include "AGLM.h"

class triangle : public hittable {
public:
   triangle() : a(0), b(0), c(0), mat_ptr(0) {}
   triangle(const glm::point3& v0, const glm::point3& v1, const glm::point3& v2, 
      std::shared_ptr<material> m) : a(v0), b(v1), c(v2), mat_ptr(m) {};

   virtual bool hit(const ray& r, hit_record& rec) const override
   {
       using namespace glm;
       float eps = 0.0001f;
       vec3 e1 = b - a;
       vec3 e2 = c - a;
       vec3 nor = cross(e1, e2);
       float len = length(r.direction());
       vec3 d = r.direction() / len;
       
       vec3 q = cross(d, e2);
       float a1 = dot(e1, q);

       if (fabs(a1) < eps) return false;

       float f = 1 / a1;
       vec3 s = r.origin() - a;
       float u = f * (dot(s, q));
       if (u < 0.0) return false;

       vec3 r1 = cross(s, e1);
       float v = f * (dot(d, r1));
       if (v < 0.0 || (u + v) > 1.0) return false;

       float t = f * (dot(e2, r1));

       rec.t = t;
       rec.p = r.at(t);
       rec.mat_ptr = mat_ptr;
       rec.set_face_normal(r, nor);


       return false;
   }

public:
   glm::point3 a;
   glm::point3 b;
   glm::point3 c;
   std::shared_ptr<material> mat_ptr;
};

#endif
