//
// Created by tristan on 2/03/18.
//

#ifndef ENGINE_2D_L_SYSTEMEN_H
#define ENGINE_2D_L_SYSTEMEN_H

#include "Line2D.h"
#include <list>
#include "easy_image.h"
#include <cmath>
#include "ini_configuration.h"
#include "l_parser.h"
#include <fstream>
#include <string>

typedef std::list<Line2D> Lines2D;
typedef struct state{Point2D position; double angle;};
int roundToInt(double d);
img::EasyImage draw2DLines(Lines2D &lines, const int size, img::Color background,bool zbuf=false);
Lines2D generateLines(const ini::Configuration &configuration);

#endif //ENGINE_2D_L_SYSTEMEN_H
