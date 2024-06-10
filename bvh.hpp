#include <pybind11/eigen.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <Eigen/Dense>
#include <vector>

#include "common.hpp"

template <size_t D>
class BoundingVolume {
  Vectorf<D> minimum = {0.0};
  Vectorf<D> maximum = {0.0};

  BoundingVolume() {}
  BoundingVolume(const Vectorf<D>& _min, const Vectorf<D>& _max) {
    minimum = _min;
    maximum = _max;
  }

  Vectorf<D> min() const { return minimum; }
  Vectorf<D> max() const { return maximum; }

  inline bool hit(const Vectorf<D>& direction, const Vectorf<D>& origin,
                  float t_min, float t_max) {
    /*
     * Method taken from Ray Tracing: The Next Week by Peter ?
     * https://raytracing.github.io/books/RayTracingTheNextWeek.html#boundingvolumehierarchies
     */
    for (int a = 0; a < D; a++) {
      auto invD = 1.0f / direction[a];
      auto t0 = (min()[a] - origin[a]) * invD;
      auto t1 = (max()[a] - origin[a]) * invD;
      if (invD < 0.0f) std::swap(t0, t1);
      t_min = t0 > t_min ? t0 : t_min;
      t_max = t1 < t_max ? t1 : t_max;
      if (t_max <= t_min) return false;
    }
    return true;
  }
};

template<size_t D>
struct BVHNode {

  BVHNode *child1;
  BVHNode *child2;

}

template<size_t D>
class BoundingVolumeHierarchy {

};
