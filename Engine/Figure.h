//
// Created by tristan on 9/03/18.
//

#ifndef ENGINE_FIGURE_H
#define ENGINE_FIGURE_H

#include <vector>
#include "vector3d.h"
#include "Face.h"
#include "Color.h"

class Figure {
public:
    std::vector<Vector3D> points;
    std::vector<Face> faces;
    Color color;
    Color ambientReflection;
    Color diffuseReflection;
    Color specularReflection;
    double  reflectionCoefficient;
};


#endif //ENGINE_FIGURE_H
