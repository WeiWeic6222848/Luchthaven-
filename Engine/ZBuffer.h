//
// Created by tristan on 9/04/18.
//

#ifndef ENGINE_ZBUFFER_H
#define ENGINE_ZBUFFER_H

#include <vector>
#include "easy_image.h"
#include "2D_L-systemen.h"
#include "3D_LineDrawings.h"
#include "Light.h"

class ZBuffer: public std::vector<std::vector<double>>{
public:
    ZBuffer(const int width, const int height);
    void swap(unsigned int & a,unsigned int & b);
    void draw_zbuf_line(ZBuffer &,img::EasyImage &, unsigned int x0,
                        const unsigned int y0, const double z0, unsigned int x1,
                        const unsigned int y1, const double z1, const img::Color& color);
};
std::vector<Face> triangulate(const Face& face);
void draw_zbuf_triag(ZBuffer& buffer, img::EasyImage& image, Vector3D const& A, Vector3D const& B, Vector3D const& C,
                     double d, double dx, double dy, Color ambientReflection,
                     Color diffuseReflection, Color specularReflection, double reflectionCoeff,
                     Lights3D& lights);

#endif //ENGINE_ZBUFFER_H
