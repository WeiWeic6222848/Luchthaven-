//
// Created by tristan on 12/03/18.
//

#include "3D_Figures.h"

Figure createCube(){
    Figure figuur;
    Vector3D punt1=Vector3D::point(1,-1,-1);
    Vector3D punt2=Vector3D::point(-1.0,1.0,-1.0);
    Vector3D punt3=Vector3D::point(1.0,1.0,1.0);
    Vector3D punt4=Vector3D::point(-1.0,-1.0,1.0);
    Vector3D punt5=Vector3D::point(1.0,1.0,-1.0);
    Vector3D punt6=Vector3D::point(-1.0,-1.0,-1.0);
    Vector3D punt7=Vector3D::point(1.0,-1.0,1.0);
    Vector3D punt8=Vector3D::point(-1.0,1.0,1.0);
    figuur.points.push_back(punt1);
    figuur.points.push_back(punt2);
    figuur.points.push_back(punt3);
    figuur.points.push_back(punt4);
    figuur.points.push_back(punt5);
    figuur.points.push_back(punt6);
    figuur.points.push_back(punt7);
    figuur.points.push_back(punt8);
    Face vlak1;
    vlak1.point_indexes.push_back(0);
    vlak1.point_indexes.push_back(4);
    vlak1.point_indexes.push_back(2);
    vlak1.point_indexes.push_back(6);
    Face vlak2;
    vlak2.point_indexes.push_back(4);
    vlak2.point_indexes.push_back(1);
    vlak2.point_indexes.push_back(7);
    vlak2.point_indexes.push_back(2);
    Face vlak3;
    vlak3.point_indexes.push_back(1);
    vlak3.point_indexes.push_back(5);
    vlak3.point_indexes.push_back(3);
    vlak3.point_indexes.push_back(7);
    Face vlak4;
    vlak4.point_indexes.push_back(5);
    vlak4.point_indexes.push_back(0);
    vlak4.point_indexes.push_back(6);
    vlak4.point_indexes.push_back(3);
    Face vlak5;
    vlak5.point_indexes.push_back(6);
    vlak5.point_indexes.push_back(2);
    vlak5.point_indexes.push_back(7);
    vlak5.point_indexes.push_back(3);
    Face vlak6;
    vlak6.point_indexes.push_back(0);
    vlak6.point_indexes.push_back(5);
    vlak6.point_indexes.push_back(1);
    vlak6.point_indexes.push_back(4);

    figuur.faces.push_back(vlak1);
    figuur.faces.push_back(vlak2);
    figuur.faces.push_back(vlak3);
    figuur.faces.push_back(vlak4);
    figuur.faces.push_back(vlak5);
    figuur.faces.push_back(vlak6);

    return figuur;

}
Figure createTetrahedron(){
    Figure figuur;
    Vector3D punt1=Vector3D::point(1.0,-1.0,-1.0);
    Vector3D punt2=Vector3D::point(-1.0,1.0,-1.0);
    Vector3D punt3=Vector3D::point(1.0,1.0,1.0);
    Vector3D punt4=Vector3D::point(-1.0,-1.0,1.0);
    figuur.points.push_back(punt1);
    figuur.points.push_back(punt2);
    figuur.points.push_back(punt3);
    figuur.points.push_back(punt4);
    Face vlak1;
    for(int i=3;i>0;i--){
        vlak1.point_indexes.push_back(i);
    }
    Face vlak2;
    vlak2.point_indexes.push_back(2);
    vlak2.point_indexes.push_back(3);
    vlak2.point_indexes.push_back(1);
    Face vlak3;
    vlak3.point_indexes.push_back(3);
    vlak3.point_indexes.push_back(1);
    vlak3.point_indexes.push_back(0);
    Face vlak4;
    vlak4.point_indexes.push_back(3);
    vlak4.point_indexes.push_back(2);
    vlak4.point_indexes.push_back(0);

    figuur.faces.push_back(vlak1);
    figuur.faces.push_back(vlak2);
    figuur.faces.push_back(vlak3);
    figuur.faces.push_back(vlak4);

    return figuur;
}
Figure createOctahedron(){
    Figure figuur;
    Vector3D punt1=Vector3D::point(1,0,0);
    Vector3D punt2=Vector3D::point(0,1,0);
    Vector3D punt3=Vector3D::point(-1,0,0);
    Vector3D punt4=Vector3D::point(0,-1,0);
    Vector3D punt5=Vector3D::point(0,0,-1);
    Vector3D punt6=Vector3D::point(0,0,1);
    figuur.points.push_back(punt1);
    figuur.points.push_back(punt2);
    figuur.points.push_back(punt3);
    figuur.points.push_back(punt4);
    figuur.points.push_back(punt5);
    figuur.points.push_back(punt6);
    Face vlak1;
    vlak1.point_indexes.push_back(0);
    vlak1.point_indexes.push_back(1);
    vlak1.point_indexes.push_back(5);

    Face vlak2;
    vlak2.point_indexes.push_back(1);
    vlak2.point_indexes.push_back(2);
    vlak2.point_indexes.push_back(5);

    Face vlak3;
    vlak3.point_indexes.push_back(2);
    vlak3.point_indexes.push_back(3);
    vlak3.point_indexes.push_back(5);

    Face vlak4;
    vlak4.point_indexes.push_back(3);
    vlak4.point_indexes.push_back(0);
    vlak4.point_indexes.push_back(5);

    Face vlak5;
    vlak5.point_indexes.push_back(1);
    vlak5.point_indexes.push_back(0);
    vlak5.point_indexes.push_back(4);

    Face vlak6;
    vlak6.point_indexes.push_back(2);
    vlak6.point_indexes.push_back(1);
    vlak6.point_indexes.push_back(4);

    Face vlak7;
    vlak7.point_indexes.push_back(3);
    vlak7.point_indexes.push_back(2);
    vlak7.point_indexes.push_back(4);

    Face vlak8;
    vlak8.point_indexes.push_back(0);
    vlak8.point_indexes.push_back(3);
    vlak8.point_indexes.push_back(4);

    figuur.faces.push_back(vlak1);
    figuur.faces.push_back(vlak2);
    figuur.faces.push_back(vlak3);
    figuur.faces.push_back(vlak4);
    figuur.faces.push_back(vlak5);
    figuur.faces.push_back(vlak6);
    figuur.faces.push_back(vlak7);
    figuur.faces.push_back(vlak8);

    return figuur;
}
Figure createIcosahedron(){
    Figure figuur;
    Vector3D punt1=Vector3D::point(0,0,sqrt(5)/2);
    figuur.points.push_back(punt1);
    for(int i=0;i<5;i++){
        Vector3D punt2=Vector3D::point(cos((i-2)*2*M_PI/5),sin((i-2)*2*M_PI/5),0.5);
        figuur.points.push_back(punt2);
    }
    for(int i=0;i<5;i++){
        Vector3D punt3=Vector3D::point(cos(M_PI/5+(i-7)*2*M_PI/5),sin(M_PI/5+(i-7)*2*M_PI/5),-0.5);
        figuur.points.push_back(punt3);
    }
    Vector3D punt4=Vector3D::point(0,0,-sqrt(5)/2);
    figuur.points.push_back(punt4);
    Face vlak1;
    vlak1.point_indexes.push_back(0);
    vlak1.point_indexes.push_back(1);
    vlak1.point_indexes.push_back(2);

    Face vlak2;
    vlak2.point_indexes.push_back(0);
    vlak2.point_indexes.push_back(2);
    vlak2.point_indexes.push_back(3);

    Face vlak3;
    vlak3.point_indexes.push_back(0);
    vlak3.point_indexes.push_back(3);
    vlak3.point_indexes.push_back(4);

    Face vlak4;
    vlak4.point_indexes.push_back(0);
    vlak4.point_indexes.push_back(4);
    vlak4.point_indexes.push_back(5);

    Face vlak5;
    vlak5.point_indexes.push_back(0);
    vlak5.point_indexes.push_back(5);
    vlak5.point_indexes.push_back(1);

    Face vlak6;
    vlak6.point_indexes.push_back(1);
    vlak6.point_indexes.push_back(6);
    vlak6.point_indexes.push_back(2);

    Face vlak7;
    vlak7.point_indexes.push_back(2);
    vlak7.point_indexes.push_back(6);
    vlak7.point_indexes.push_back(7);

    Face vlak8;
    vlak8.point_indexes.push_back(2);
    vlak8.point_indexes.push_back(7);
    vlak8.point_indexes.push_back(3);

    Face vlak9;
    vlak9.point_indexes.push_back(3);
    vlak9.point_indexes.push_back(7);
    vlak9.point_indexes.push_back(8);

    Face vlak10;
    vlak10.point_indexes.push_back(3);
    vlak10.point_indexes.push_back(8);
    vlak10.point_indexes.push_back(4);

    Face vlak11;
    vlak11.point_indexes.push_back(4);
    vlak11.point_indexes.push_back(8);
    vlak11.point_indexes.push_back(9);

    Face vlak12;
    vlak12.point_indexes.push_back(4);
    vlak12.point_indexes.push_back(9);
    vlak12.point_indexes.push_back(5);

    Face vlak13;
    vlak13.point_indexes.push_back(5);
    vlak13.point_indexes.push_back(9);
    vlak13.point_indexes.push_back(10);

    Face vlak14;
    vlak14.point_indexes.push_back(5);
    vlak14.point_indexes.push_back(10);
    vlak14.point_indexes.push_back(1);

    Face vlak15;
    vlak15.point_indexes.push_back(1);
    vlak15.point_indexes.push_back(10);
    vlak15.point_indexes.push_back(6);

    Face vlak16;
    vlak16.point_indexes.push_back(11);
    vlak16.point_indexes.push_back(7);
    vlak16.point_indexes.push_back(6);

    Face vlak17;
    vlak17.point_indexes.push_back(11);
    vlak17.point_indexes.push_back(8);
    vlak17.point_indexes.push_back(7);

    Face vlak18;
    vlak18.point_indexes.push_back(11);
    vlak18.point_indexes.push_back(9);
    vlak18.point_indexes.push_back(8);

    Face vlak19;
    vlak19.point_indexes.push_back(11);
    vlak19.point_indexes.push_back(10);
    vlak19.point_indexes.push_back(9);

    Face vlak20;
    vlak20.point_indexes.push_back(11);
    vlak20.point_indexes.push_back(6);
    vlak20.point_indexes.push_back(10);

    figuur.faces.push_back(vlak1);
    figuur.faces.push_back(vlak2);
    figuur.faces.push_back(vlak3);
    figuur.faces.push_back(vlak4);
    figuur.faces.push_back(vlak5);
    figuur.faces.push_back(vlak6);
    figuur.faces.push_back(vlak7);
    figuur.faces.push_back(vlak8);
    figuur.faces.push_back(vlak9);
    figuur.faces.push_back(vlak10);
    figuur.faces.push_back(vlak11);
    figuur.faces.push_back(vlak12);
    figuur.faces.push_back(vlak13);
    figuur.faces.push_back(vlak14);
    figuur.faces.push_back(vlak15);
    figuur.faces.push_back(vlak16);
    figuur.faces.push_back(vlak17);
    figuur.faces.push_back(vlak18);
    figuur.faces.push_back(vlak19);
    figuur.faces.push_back(vlak20);

    return figuur;
}
Figure createDodecahedron(){
    Figure icosahedron=createIcosahedron();
    Figure figuur;
    for(Face vlak:icosahedron.faces){
        Vector3D A=icosahedron.points[vlak.point_indexes[0]];
        Vector3D B=icosahedron.points[vlak.point_indexes[1]];
        Vector3D C=icosahedron.points[vlak.point_indexes[2]];
        Vector3D punt=Vector3D::point((A.x+B.x+C.x)/3,(A.y+B.y+C.y)/3,(A.z+B.z+C.z)/3);
        figuur.points.push_back(punt);
    }
    Face vlak;
    vlak.point_indexes.push_back(0);vlak.point_indexes.push_back(1);vlak.point_indexes.push_back(2);vlak.point_indexes.push_back(3);vlak.point_indexes.push_back(4);
    figuur.faces.push_back(vlak);
    vlak.point_indexes.clear();
    vlak.point_indexes.push_back(0);vlak.point_indexes.push_back(5);vlak.point_indexes.push_back(6);vlak.point_indexes.push_back(7);vlak.point_indexes.push_back(1);
    figuur.faces.push_back(vlak);
    vlak.point_indexes.clear();
    vlak.point_indexes.push_back(1);vlak.point_indexes.push_back(7);vlak.point_indexes.push_back(8);vlak.point_indexes.push_back(9);vlak.point_indexes.push_back(2);
    figuur.faces.push_back(vlak);
    vlak.point_indexes.clear();
    vlak.point_indexes.push_back(2);vlak.point_indexes.push_back(9);vlak.point_indexes.push_back(10);vlak.point_indexes.push_back(11);vlak.point_indexes.push_back(3);
    figuur.faces.push_back(vlak);
    vlak.point_indexes.clear();
    vlak.point_indexes.push_back(3);vlak.point_indexes.push_back(11);vlak.point_indexes.push_back(12);vlak.point_indexes.push_back(13);vlak.point_indexes.push_back(4);
    figuur.faces.push_back(vlak);
    vlak.point_indexes.clear();
    vlak.point_indexes.push_back(4);vlak.point_indexes.push_back(13);vlak.point_indexes.push_back(14);vlak.point_indexes.push_back(5);vlak.point_indexes.push_back(0);
    figuur.faces.push_back(vlak);
    vlak.point_indexes.clear();
    vlak.point_indexes.push_back(19);vlak.point_indexes.push_back(18);vlak.point_indexes.push_back(17);vlak.point_indexes.push_back(16);vlak.point_indexes.push_back(15);
    figuur.faces.push_back(vlak);
    vlak.point_indexes.clear();
    vlak.point_indexes.push_back(19);vlak.point_indexes.push_back(14);vlak.point_indexes.push_back(13);vlak.point_indexes.push_back(12);vlak.point_indexes.push_back(18);
    figuur.faces.push_back(vlak);
    vlak.point_indexes.clear();
    vlak.point_indexes.push_back(18);vlak.point_indexes.push_back(12);vlak.point_indexes.push_back(11);vlak.point_indexes.push_back(10);vlak.point_indexes.push_back(17);
    figuur.faces.push_back(vlak);
    vlak.point_indexes.clear();
    vlak.point_indexes.push_back(17);vlak.point_indexes.push_back(10);vlak.point_indexes.push_back(9);vlak.point_indexes.push_back(8);vlak.point_indexes.push_back(16);
    figuur.faces.push_back(vlak);
    vlak.point_indexes.clear();
    vlak.point_indexes.push_back(16);vlak.point_indexes.push_back(8);vlak.point_indexes.push_back(7);vlak.point_indexes.push_back(6);vlak.point_indexes.push_back(15);
    figuur.faces.push_back(vlak);
    vlak.point_indexes.clear();
    vlak.point_indexes.push_back(15);vlak.point_indexes.push_back(6);vlak.point_indexes.push_back(5);vlak.point_indexes.push_back(14);vlak.point_indexes.push_back(19);
    figuur.faces.push_back(vlak);
    vlak.point_indexes.clear();

    return figuur;
}
Figure createCylinder(const int n, const double h){
    Figure figuur;
    Face bovenvlak;
    Face grondvlak;
    for(double i=0.0;i<n;i++){
        Vector3D punt1=Vector3D::point(cos(2.0*i*M_PI/(double)n),sin(2.0*i*M_PI/(double)n),0.0);
        Vector3D punt2=Vector3D::point(cos(2.0*i*M_PI/(double)n),sin(2.0*i*M_PI/(double)n),h);
        figuur.points.push_back(punt1);
        figuur.points.push_back(punt2);
    }
    for(int i=0;i<2*n;i+=2){
        Face vlak;
        vlak.point_indexes.push_back(i);
        grondvlak.point_indexes.push_back(i);
        vlak.point_indexes.push_back((i+1)%(2*n));
        vlak.point_indexes.push_back((i+3)%(2*n));
        bovenvlak.point_indexes.push_back((i+3)%(2*n));
        vlak.point_indexes.push_back((i+2)%(2*n));
        figuur.faces.push_back(vlak);
    }
    figuur.faces.push_back(grondvlak);
    figuur.faces.push_back(bovenvlak);
    return figuur;
}
Figure createCone(const int n, const double h){
    Figure figuur;
    for(int i=0;i<n;i++){
        Vector3D punt=Vector3D::point(cos(2*i*M_PI/n),sin(2*i*M_PI/n),0);
        figuur.points.push_back(punt);
    }
    Vector3D punt=Vector3D::point(0,0,h);
    figuur.points.push_back(punt);

    for(int i=0;i<n;i++){
        Face vlak;
        vlak.point_indexes.push_back(i);
        vlak.point_indexes.push_back((i+1)%n);
        vlak.point_indexes.push_back(n);
        figuur.faces.push_back(vlak);
    }
    Face vlak;
    for(int i=0;i<n;i++){
        vlak.point_indexes.push_back(i);
    }
    figuur.faces.push_back(vlak);
    return figuur;

}
void divideTriangles(Figure & figuur){
    Figure res;
    int i=0;
    for(Face vlak:figuur.faces){
        Vector3D A=figuur.points[vlak.point_indexes[0]];
        Vector3D B=figuur.points[vlak.point_indexes[1]];
        Vector3D C=figuur.points[vlak.point_indexes[2]];
        Vector3D D=Vector3D::point((A.x+B.x)/2,(A.y+B.y)/2,(A.z+B.z)/2);
        Vector3D E=Vector3D::point((A.x+C.x)/2,(A.y+C.y)/2,(A.z+C.z)/2);
        Vector3D F=Vector3D::point((C.x+B.x)/2,(C.y+B.y)/2,(C.z+B.z)/2);
        res.points.push_back(A);res.points.push_back(B);res.points.push_back(C);res.points.push_back(D);res.points.push_back(E);res.points.push_back(F);
        Face nieuw;
        nieuw.point_indexes.push_back(0+i);nieuw.point_indexes.push_back(3+i);nieuw.point_indexes.push_back(4+i);
        res.faces.push_back(nieuw);
        nieuw.point_indexes.clear();
        nieuw.point_indexes.push_back(1+i);nieuw.point_indexes.push_back(5+i);nieuw.point_indexes.push_back(3+i);
        res.faces.push_back(nieuw);
        nieuw.point_indexes.clear();
        nieuw.point_indexes.push_back(2+i);nieuw.point_indexes.push_back(4+i);nieuw.point_indexes.push_back(5+i);
        res.faces.push_back(nieuw);
        nieuw.point_indexes.clear();
        nieuw.point_indexes.push_back(3+i);nieuw.point_indexes.push_back(5+i);nieuw.point_indexes.push_back(4+i);
        res.faces.push_back(nieuw);

        i+=6;
    }
    figuur=res;
}
Figure createSphere(const double radius, const int n){
    Figure figuur=createIcosahedron();

    for(int i=0;i<n;i++){
        divideTriangles(figuur);
    }
    for(Vector3D & punt:figuur.points){
        double lengte=punt.length();
        punt.x/=lengte*radius;
        punt.y/=lengte*radius;
        punt.z/=lengte*radius;

    }
    return figuur;
}
Figure createTorus(const double r, const double R, const int n, const int m){
    Figure figuur;
    for(int i=0;i<n;i++){
        double u=2.0*(1.0*i)*M_PI/(1.0*n);
        for(int j=0;j<m;j++){
            double v=2.0*(1.0*j)*M_PI/(1.0*m);
            double x=(R+r*cos(v))*cos(u);
            double y=(R+r*cos(v))*sin(u);
            double z=r*sin(v);
            Vector3D punt=Vector3D::point(x,y,z);
            figuur.points.push_back(punt);
            Face vlak;
            vlak.point_indexes.push_back(i*m+j);
            vlak.point_indexes.push_back(((i+1)*m)%(n*m)+j);
            vlak.point_indexes.push_back(((i+1)*m)%(n*m)+(j+1)%m);
            vlak.point_indexes.push_back(i*m+(j+1)%m);
            figuur.faces.push_back(vlak);

        }
    }
    return figuur;

}
Figure createBuckyball(){
    Figure ico=createIcosahedron();
    Figure buckyball;
    int index=0;
    for(Face vlak:ico.faces){
        Vector3D A=ico.points[vlak.point_indexes[0]];
        Vector3D B=ico.points[vlak.point_indexes[1]];
        Vector3D C=ico.points[vlak.point_indexes[2]];

        Vector3D length1=(B-A)/3;
        Vector3D length2=(C-B)/3;
        Vector3D length3=(C-A)/3;

        Face zeshoek;

        Vector3D point1=A+length1;
        Vector3D point2=B+length2;
        Vector3D point3=A+length3;

        buckyball.points.push_back(point1);
        Vector3D point4=A+length1*2;
        buckyball.points.push_back(point4);
        buckyball.points.push_back(point2);
        Vector3D point5=B+length2*2;
        buckyball.points.push_back(point5);
        Vector3D point6=A+length3*2;
        buckyball.points.push_back(point6);
        buckyball.points.push_back(point3);

        for(int i=0;i<6;i++){
            zeshoek.point_indexes.push_back(index+i);
        }
        buckyball.faces.push_back(zeshoek);
        index+=6;
    }
    Face vijfhoek;
    for(int i=0;i<5;i++){
        vijfhoek.point_indexes.push_back(buckyball.faces[i].point_indexes[0]);
    }
    Face vijfhoek1;
    vijfhoek1.point_indexes.push_back(buckyball.faces[0].point_indexes[1]);
    vijfhoek1.point_indexes.push_back(buckyball.faces[0].point_indexes[2]);
    vijfhoek1.point_indexes.push_back(buckyball.faces[5].point_indexes[0]);
    vijfhoek1.point_indexes.push_back(buckyball.faces[14].point_indexes[0]);
    vijfhoek1.point_indexes.push_back(buckyball.faces[4].point_indexes[3]);
    Face vijfhoek2;
    vijfhoek2.point_indexes.push_back(buckyball.faces[0].point_indexes[3]);
    vijfhoek2.point_indexes.push_back(buckyball.faces[1].point_indexes[1]);
    vijfhoek2.point_indexes.push_back(buckyball.faces[1].point_indexes[2]);
    vijfhoek2.point_indexes.push_back(buckyball.faces[7].point_indexes[0]);
    vijfhoek2.point_indexes.push_back(buckyball.faces[6].point_indexes[0]);
    Face vijfhoek3;
    vijfhoek3.point_indexes.push_back(buckyball.faces[1].point_indexes[4]);
    vijfhoek3.point_indexes.push_back(buckyball.faces[7].point_indexes[4]);
    vijfhoek3.point_indexes.push_back(buckyball.faces[7].point_indexes[3]);
    vijfhoek3.point_indexes.push_back(buckyball.faces[9].point_indexes[0]);
    vijfhoek3.point_indexes.push_back(buckyball.faces[9].point_indexes[5]);
    Face vijfhoek4;
    vijfhoek4.point_indexes.push_back(buckyball.faces[2].point_indexes[3]);
    vijfhoek4.point_indexes.push_back(buckyball.faces[2].point_indexes[4]);
    vijfhoek4.point_indexes.push_back(buckyball.faces[3].point_indexes[2]);
    vijfhoek4.point_indexes.push_back(buckyball.faces[10].point_indexes[5]);
    vijfhoek4.point_indexes.push_back(buckyball.faces[10].point_indexes[0]);
    Face vijfhoek5;
    vijfhoek5.point_indexes.push_back(buckyball.faces[4].point_indexes[1]);
    vijfhoek5.point_indexes.push_back(buckyball.faces[4].point_indexes[2]);
    vijfhoek5.point_indexes.push_back(buckyball.faces[12].point_indexes[5]);
    vijfhoek5.point_indexes.push_back(buckyball.faces[12].point_indexes[0]);
    vijfhoek5.point_indexes.push_back(buckyball.faces[3].point_indexes[3]);
    Face vijfhoek6;
    vijfhoek6.point_indexes.push_back(buckyball.faces[5].point_indexes[1]);
    vijfhoek6.point_indexes.push_back(buckyball.faces[5].point_indexes[2]);
    vijfhoek6.point_indexes.push_back(buckyball.faces[15].point_indexes[3]);
    vijfhoek6.point_indexes.push_back(buckyball.faces[15].point_indexes[4]);
    vijfhoek6.point_indexes.push_back(buckyball.faces[14].point_indexes[3]);
    Face vijfhoek7;
    vijfhoek7.point_indexes.push_back(buckyball.faces[7].point_indexes[1]);
    vijfhoek7.point_indexes.push_back(buckyball.faces[7].point_indexes[2]);
    vijfhoek7.point_indexes.push_back(buckyball.faces[16].point_indexes[3]);
    vijfhoek7.point_indexes.push_back(buckyball.faces[16].point_indexes[4]);
    vijfhoek7.point_indexes.push_back(buckyball.faces[15].point_indexes[2]);

    Face vijfhoek8;
    vijfhoek8.point_indexes.push_back(buckyball.faces[9].point_indexes[1]);
    vijfhoek8.point_indexes.push_back(buckyball.faces[9].point_indexes[2]);
    vijfhoek8.point_indexes.push_back(buckyball.faces[17].point_indexes[3]);
    vijfhoek8.point_indexes.push_back(buckyball.faces[17].point_indexes[4]);
    vijfhoek8.point_indexes.push_back(buckyball.faces[16].point_indexes[2]);
    Face vijfhoek9;
    vijfhoek9.point_indexes.push_back(buckyball.faces[17].point_indexes[1]);
    vijfhoek9.point_indexes.push_back(buckyball.faces[17].point_indexes[2]);
    vijfhoek9.point_indexes.push_back(buckyball.faces[11].point_indexes[1]);
    vijfhoek9.point_indexes.push_back(buckyball.faces[11].point_indexes[2]);
    vijfhoek9.point_indexes.push_back(buckyball.faces[18].point_indexes[3]);
    Face vijfhoek10;
    vijfhoek10.point_indexes.push_back(buckyball.faces[18].point_indexes[1]);
    vijfhoek10.point_indexes.push_back(buckyball.faces[18].point_indexes[2]);
    vijfhoek10.point_indexes.push_back(buckyball.faces[13].point_indexes[1]);
    vijfhoek10.point_indexes.push_back(buckyball.faces[13].point_indexes[2]);
    vijfhoek10.point_indexes.push_back(buckyball.faces[19].point_indexes[3]);
    Face vijfhoek11;
    for(int i=0;i<5;i++){
        vijfhoek11.point_indexes.push_back(buckyball.faces[i+15].point_indexes[0]);
    }

    buckyball.points=buckyball.points;
    buckyball.faces.push_back(vijfhoek);
    buckyball.faces.push_back(vijfhoek1);
    buckyball.faces.push_back(vijfhoek2);
    buckyball.faces.push_back(vijfhoek3);
    buckyball.faces.push_back(vijfhoek4);
    buckyball.faces.push_back(vijfhoek5);
    buckyball.faces.push_back(vijfhoek6);
    buckyball.faces.push_back(vijfhoek7);
    buckyball.faces.push_back(vijfhoek8);
    buckyball.faces.push_back(vijfhoek9);
    buckyball.faces.push_back(vijfhoek10);
    buckyball.faces.push_back(vijfhoek11);

    return buckyball;
}
Figure createMengerSponge(){
    Figure sponge;
    sponge=createCube();
    return sponge;
}
void generateFractal(Figure& fig, Figures3D& fractal, const int nr_iterations, const double scale,bool sponge){
    if(nr_iterations==0){
        fractal.push_back(fig);
        return;
    }
    if(sponge){
        for(int i=0;i<fig.faces.size()-2;i++){
            for(int j=0;j<fig.faces[i].point_indexes.size()-1;j++){
                Vector3D A=fig.points[fig.faces[i].point_indexes[j]];
                Vector3D B=fig.points[fig.faces[i].point_indexes[j+1]];
                fig.points.push_back((B-A)/2+A);
            }
        }
    }

    Matrix resize=scaleFigure(1/scale);
    for(int i=0;i<fig.points.size();i++){
        Figure* fract=new Figure(fig);
        applyTransformation(*fract,resize);
        Vector3D trans=fig.points[i]-fract->points[i];
        Matrix move=translate(trans);
        applyTransformation(*fract,move);
        if(nr_iterations<=1){
            fractal.push_back(*fract);
        }
        else{
            generateFractal(*fract,fractal,nr_iterations-1,scale);
        }
        delete(fract);
    }
}