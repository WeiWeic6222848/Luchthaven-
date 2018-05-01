//
// Created by tristan on 9/03/18.
//
#include "3D_LineDrawings.h"

Matrix scaleFigure(const double scale){
    Matrix scalingMatrix;
    for(int i=1;i<4;i++){
        scalingMatrix(i,i)=scale;
    }
    return scalingMatrix;
}
Matrix rotateX(const double angle){
    Matrix rotationMatrix;
    rotationMatrix(2,2)=std::cos(angle);
    rotationMatrix(3,3)=std::cos(angle);
    rotationMatrix(3,2)=-std::sin(angle);
    rotationMatrix(2,3)=std::sin(angle);
    return rotationMatrix;
}
Matrix rotateY(const double angle){
    Matrix rotationMatrix;
    rotationMatrix(1,1)=std::cos(angle);
    rotationMatrix(3,3)=std::cos(angle);
    rotationMatrix(1,3)=-std::sin(angle);
    rotationMatrix(3,1)=std::sin(angle);
    return rotationMatrix;
}
Matrix rotateZ(const double angle){
    Matrix rotationMatrix;
    rotationMatrix(1,1)=std::cos(angle);
    rotationMatrix(2,2)=std::cos(angle);
    rotationMatrix(2,1)=-std::sin(angle);
    rotationMatrix(1,2)=std::sin(angle);
    return rotationMatrix;
}
Matrix translate(const Vector3D &vector){
    Matrix translationMatrix;
    translationMatrix(4,1)=vector.x;
    translationMatrix(4,2)=vector.y;
    translationMatrix(4,3)=vector.z;
    return translationMatrix;
}
void applyTransformation(Figure & figuur, const Matrix & matrix){
    for(Vector3D& point:figuur.points){
        point*=matrix;
    }
}
void toPolar(const Vector3D &point, double &theta, double &phi, double &r){
    r=sqrt(pow(point.x,2)+pow(point.y,2)+pow(point.z,2));
    theta=atan2(point.y,point.x);
    phi=acos(point.z/r);
}
Matrix eyePointTrans(const Vector3D &eyepoint){
    double theta,phi,r;
    toPolar(eyepoint,theta,phi,r);
    Matrix V;
    V(1,1)=-sin(theta);
    V(1,2)=-cos(theta)*cos(phi);
    V(1,3)=cos(theta)*sin(phi);
    V(2,1)=cos(theta);
    V(2,2)=-sin(theta)*cos(phi);
    V(2,3)=sin(theta)*sin(phi);
    V(3,2)=sin(phi);
    V(3,3)=cos(phi);
    V(4,3)=-r;
    return V;
}
void applyTransformation(Figures3D & figuren, const Matrix & matrix){
    for(Figure& figuur:figuren){
        applyTransformation(figuur,matrix);
    }
}
Point2D doProjection(const Vector3D &point, const double d){
    Point2D projectie;
    projectie.x=d*point.x/(-point.z);
    projectie.y=d*point.y/(-point.z);
    return projectie;
}
Lines2D doProjection(const Figures3D & figuren){
    Lines2D projectie;
    for(const Figure& figuur:figuren){
        for(const Face& face:figuur.faces){
            for(int i=0;i<face.point_indexes.size()-1;i++){
                Line2D temp;
                temp.p1=doProjection(figuur.points[face.point_indexes[i]],1.0);
                temp.z1=figuur.points[face.point_indexes[i]].z;
                temp.p2=doProjection(figuur.points[face.point_indexes[i+1]],1.0);
                temp.z2=figuur.points[face.point_indexes[i+1]].z;
                temp.color=figuur.color;
                projectie.push_back(temp);
            }
            if(face.point_indexes.size()>2){
                Line2D temp;
                temp.p1=doProjection(figuur.points[face.point_indexes[face.point_indexes.size()-1]],1.0);
                temp.z1=figuur.points[face.point_indexes[face.point_indexes.size()-1]].z;
                temp.p2=doProjection(figuur.points[face.point_indexes[0]],1.0);
                temp.z2=figuur.points[face.point_indexes[0]].z;
                temp.color=figuur.color;
                projectie.push_back(temp);
            }

        }
    }
    return projectie;
}