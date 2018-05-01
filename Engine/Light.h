//
// Created by tristan on 26/04/18.
//

#ifndef ENGINE_LIGHT_H
#define ENGINE_LIGHT_H


#include "Color.h"
#include "vector3d.h"
#include <list>

class Light {
public:
    Color ambientLight;
    Color diffuseLight;
    Color specularLight;
    Vector3D ldVector;
    Vector3D location;
};

typedef std::list<Light> Lights3D;

#endif //ENGINE_LIGHT_H
