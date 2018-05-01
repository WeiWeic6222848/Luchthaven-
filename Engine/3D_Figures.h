//
// Created by tristan on 12/03/18.
//

#ifndef ENGINE_3D_FIGURES_H
#define ENGINE_3D_FIGURES_H

#include "3D_LineDrawings.h"

Figure createCube();
Figure createTetrahedron();
Figure createOctahedron();
Figure createIcosahedron();
Figure createDodecahedron();
Figure createCylinder(const int n, const double h);
Figure createCone(const int n, const double h);
Figure createSphere(const double radius, const int n);
Figure createTorus(const double r, const double R, const int n, const int m);
Figure createBuckyball();
Figure createMengerSponge();
void generateFractal(Figure& fig, Figures3D& fractal, const int nr_iterations, const double scale,bool sponge=false);

#endif //ENGINE_3D_FIGURES_H
