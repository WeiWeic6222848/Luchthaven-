//
// Created by tristan on 15/03/18.
//

#ifndef ENGINE_3D_L_SYSTEMEN_H
#define ENGINE_3D_L_SYSTEMEN_H

#include "3D_Figures.h"
typedef struct save{Vector3D position; Vector3D U;Vector3D L;Vector3D H;int pointindex;};
Figure genereateFigure(const ini::Configuration &configuration,std::string fign);

#endif //ENGINE_3D_L_SYSTEMEN_H
