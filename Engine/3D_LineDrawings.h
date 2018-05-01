//
// Created by tristan on 9/03/18.
//

#ifndef ENGINE_3D_LINEDRAWINGS_H
#define ENGINE_3D_LINEDRAWINGS_H

#include <iostream>
#include <list>
#include <cmath>
#include "vector3d.h"
#include "Figure.h"
#include "Face.h"
#include "2D_L-systemen.h"

typedef std::list<Figure> Figures3D;
Matrix scaleFigure(const double scale);
Matrix rotateX(const double angle);
Matrix rotateY(const double angle);
Matrix rotateZ(const double angle);
Matrix translate(const Vector3D &vector);
void applyTransformation(Figure &, const Matrix &);
void toPolar(const Vector3D &point, double &theta, double &phi, double &r);
Matrix eyePointTrans(const Vector3D &eyepoint);
void applyTransformation(Figures3D &, const Matrix &);
Point2D doProjection(const Vector3D &point, const double d);
Lines2D doProjection(const Figures3D &);

#endif //ENGINE_3D_LINEDRAWINGS_H