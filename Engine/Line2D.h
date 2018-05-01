//
// Created by tristan on 1/03/18.
//

#ifndef ENGINE_LINE2D_H
#define ENGINE_LINE2D_H


#include "Point2D.h"
#include "Color.h"

class Line2D {
public:
    Point2D p1;
    Point2D p2;
    Color color;

    double z1;
    double z2;
};


#endif //ENGINE_LINE2D_H
