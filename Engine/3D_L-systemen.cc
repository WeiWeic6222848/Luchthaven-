//
// Created by tristan on 15/03/18.
//

#include "3D_L-systemen.h"

Figure genereateFigure(const ini::Configuration &configuration,std::string fign){
    Figure figuur;
    LParser::LSystem3D l_system;
    std::ifstream input_stream(configuration[fign]["inputfile"]);
    input_stream >> l_system;
    input_stream.close();

    std::string initiator=l_system.get_initiator();
    std::set<char> alfabet=l_system.get_alphabet();
    int iterations=l_system.get_nr_iterations();

    std::string nieuw="";
    for(int i=0;i<iterations;i++){
        for(char a:initiator){
            for(char letter:alfabet){
                if(a==letter){
                    nieuw+=l_system.get_replacement(a);
                }
            }
            if(a=='+' ||a=='-'||a=='('||a==')'||a=='/'||a=='\\'||a=='&'||a=='^'||a=='|'){
                nieuw.push_back(a);
            }
        }
        initiator=nieuw;
        nieuw="";
    }

    Vector3D currentlocation=Vector3D::point(0,0,0);
    figuur.points.push_back(currentlocation);
    Vector3D U=Vector3D::vector(0,0,1);
    Vector3D L=Vector3D::vector(0,1,0);
    Vector3D H=Vector3D::vector(1,0,0);
    double angle=l_system.get_angle()/180.0*M_PI;

    std::vector<save> stack;
    int pointindex=1;
    int previousindex=0;
    for(char& step:initiator){
        if(step=='+'){
            Vector3D Hnew=Vector3D::vector(H.x*cos(angle)+L.x*sin(angle),H.y*cos(angle)+L.y*sin(angle),H.z*cos(angle)+L.z*sin(angle));
            Vector3D Lnew=Vector3D::vector(L.x*cos(angle)-H.x*sin(angle),L.y*cos(angle)-H.y*sin(angle),L.z*cos(angle)-H.z*sin(angle));
            H=Hnew;
            L=Lnew;
        }
        else if(step=='-'){
            Vector3D Hnew=Vector3D::vector(H.x*cos(-angle)+L.x*sin(-angle),H.y*cos(-angle)+L.y*sin(-angle),H.z*cos(-angle)+L.z*sin(-angle));
            Vector3D Lnew=Vector3D::vector(L.x*cos(-angle)-H.x*sin(-angle),L.y*cos(-angle)-H.y*sin(-angle),L.z*cos(-angle)-H.z*sin(-angle));
            H=Hnew;
            L=Lnew;
        }
        else if(step=='&'){
            Vector3D Hnew=Vector3D::vector(H.x*cos(-angle)+U.x*sin(-angle),H.y*cos(-angle)+U.y*sin(-angle),H.z*cos(-angle)+U.z*sin(-angle));
            Vector3D Unew=Vector3D::vector(U.x*cos(-angle)-H.x*sin(-angle),U.y*cos(-angle)-H.y*sin(-angle),U.z*cos(-angle)-H.z*sin(-angle));
            H=Hnew;
            U=Unew;
        }
        else if(step=='^'){
            Vector3D Hnew=Vector3D::vector(H.x*cos(angle)+U.x*sin(angle),H.y*cos(angle)+U.y*sin(angle),H.z*cos(angle)+U.z*sin(angle));
            Vector3D Unew=Vector3D::vector(U.x*cos(angle)-H.x*sin(angle),U.y*cos(angle)-H.y*sin(angle),U.z*cos(angle)-H.z*sin(angle));
            H=Hnew;
            U=Unew;
        }
        else if(step=='|'){
            H*=-1;
            L*=-1;
        }
        else if(step=='/'){
            Vector3D Lnew=Vector3D::vector(L.x*cos(-angle)-U.x*sin(-angle),L.y*cos(-angle)-U.y*sin(-angle),L.z*cos(-angle)-U.z*sin(-angle));
            Vector3D Unew=Vector3D::vector(U.x*cos(-angle)+L.x*sin(-angle),U.y*cos(-angle)+L.y*sin(-angle),U.z*cos(-angle)+L.z*sin(-angle));
            U=Unew;
            L=Lnew;
        }
        else if(step=='\\'){
            Vector3D Lnew=Vector3D::vector(L.x*cos(angle)-U.x*sin(angle),L.y*cos(angle)-U.y*sin(angle),L.z*cos(angle)-U.z*sin(angle));
            Vector3D Unew=Vector3D::vector(U.x*cos(angle)+L.x*sin(angle),U.y*cos(angle)+L.y*sin(angle),U.z*cos(angle)+L.z*sin(angle));
            U=Unew;
            L=Lnew;
        }
        else if(step=='('||step=='['){
            save currentsave={currentlocation,U,L,H,previousindex};
            stack.push_back(currentsave);
        }
        else if(step==')'||step==']'){
            save jumpback=stack.back();
            stack.pop_back();
            currentlocation=jumpback.position;
            U=jumpback.U;
            L=jumpback.L;
            H=jumpback.H;
            previousindex=jumpback.pointindex;
        }
        else{
            Vector3D nieuw=Vector3D::point(currentlocation.x+H.x,currentlocation.y+H.y,currentlocation.z+H.z);
            if(l_system.draw(step)){
                figuur.points.push_back(nieuw);
                Face vlak;
                vlak.point_indexes.push_back(previousindex);
                vlak.point_indexes.push_back(pointindex);
                figuur.faces.push_back(vlak);

            }
            currentlocation=nieuw;
            previousindex=pointindex;
            pointindex++;

        }

    }
    return  figuur;
}