#ifndef PLANE_H_
#define PLANE_H_

#include "hittable.h"
#include "AGLM.h"

class plane : public hittable {
public:
   plane() : a(0), n(0), mat_ptr(0) {}
   plane(const glm::point3& p, const glm::vec3& normal, 
      std::shared_ptr<material> m) : a(p), n(normal), mat_ptr(m) {};

   virtual bool hit(const ray& r, hit_record& rec) const override
   {
       using namespace glm;

       float len = length(r.direction());
       vec3 d = r.direction() / len;
       float den = dot(n, d);

       if (den == 0.0f) return false;

       vec3 v = a - r.origin();
       float num = dot(v, n);
       float t = num / den;
       if (t < 0) return false;
           
       rec.t = t / len;
       rec.p = r.at(rec.t);
       rec.mat_ptr = mat_ptr;
       rec.set_face_normal(r, n);

       return true;
   }

public:
   glm::vec3 a;
   glm::vec3 n;
   std::shared_ptr<material> mat_ptr;
};



#endif
