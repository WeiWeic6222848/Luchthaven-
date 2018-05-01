//
// Created by tristan on 2/03/18.
//
#include "2D_L-systemen.h"
#include "ZBuffer.h"


int roundToInt(double d) {
    return static_cast<int>(std::round(d));
}

img::EasyImage draw2DLines(Lines2D &lines, const int size, img::Color background,bool zbuf){

    double xmin=lines.front().p1.x;
    double xmax=lines.front().p1.x;
    double ymin=lines.front().p1.y;
    double ymax=lines.front().p1.y;
    for(Line2D& line:lines){

        if(line.p1.x<xmin){xmin=line.p1.x;}
        if(line.p1.x>xmax){xmax=line.p1.x;}
        if(line.p1.y<ymin){ymin=line.p1.y;}
        if(line.p1.y>ymax){ymax=line.p1.y;}

        if(line.p2.x<xmin){xmin=line.p2.x;}
        if(line.p2.x>xmax){xmax=line.p2.x;}
        if(line.p2.y<ymin){ymin=line.p2.y;}
        if(line.p2.y>ymax){ymax=line.p2.y;}
    }
    double xrange=xmax-xmin;
    double yrange=ymax-ymin;
    double maxrange=xrange;
    if(yrange>xrange){maxrange=yrange;}

    double imagex=(double)size*(xrange/maxrange);
    double imagey=(double)size*(yrange/maxrange);

    double d=0.95*imagex/xrange;
    double dcx=d*(xmin+xmax)/2.0;
    double dcy=d*(ymin+ymax)/2.0;
    double dx=imagex/2.0-dcx;
    double dy=imagey/2.0-dcy;

    int width=roundToInt(imagex);
    int height=roundToInt(imagey);

    img::EasyImage drawing(width,height,background);

    ZBuffer buffer(width,height);
    for(Line2D& line:lines){
        line.p1.x*=d;
        line.p1.y*=d;
        line.p2.x*=d;
        line.p2.y*=d;

        line.p1.x+=dx;
        line.p1.y+=dy;
        line.p2.x+=dx;
        line.p2.y+=dy;

        int x1=roundToInt(line.p1.x);
        int y1=roundToInt(line.p1.y);
        int x2=roundToInt(line.p2.x);
        int y2=roundToInt(line.p2.y);


        img::Color kleur(roundToInt(255*line.color.red),roundToInt(255*line.color.green),roundToInt(255*line.color.blue));
        if(zbuf){
            buffer.draw_zbuf_line(buffer,drawing,x1,y1,line.z1,x2,y2,line.z2,kleur);
        }

        else{
            drawing.draw_line(x1,y1,x2,y2,kleur);
        }

    }
    return drawing;
}

Lines2D generateLines(const ini::Configuration &configuration){
    srand48(time(NULL));
    LParser::LSystem2D l_system;
    std::ifstream input_stream(configuration["2DLSystem"]["inputfile"]);
    std::vector<double> syscolor=configuration["2DLSystem"]["color"].as_double_tuple_or_die();
    input_stream >> l_system;
    input_stream.close();

    Lines2D lines;
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
            if(a=='+' ||a=='-'||a=='('||a==')'||a=='['||a==']'){
                nieuw.push_back(a);
            }
        }
        initiator=nieuw;
        nieuw="";
    }

    double angle=l_system.get_angle()/180.0*M_PI;
    double currentangle=l_system.get_starting_angle()/180.0*M_PI;
    Point2D currentlocation;
    currentlocation.x=0.0;
    currentlocation.y=0.0;
    std::vector<state> stack;
    for(char step:initiator){
        if(step=='+'){
            currentangle+=angle;
        }
        else if(step=='-'){
            currentangle-=angle;
        }
        else if(step=='('||step=='['){
            state currentstate={currentlocation,currentangle};
            stack.push_back(currentstate);
        }
        else if(step==')'||step==']'){
            state jumpback=stack.back();
            stack.pop_back();
            currentlocation=jumpback.position;
            currentangle=jumpback.angle;
        }
        else{
            Point2D nieuwpunt;
            nieuwpunt.x=currentlocation.x+std::cos(currentangle);
            nieuwpunt.y=currentlocation.y+std::sin(currentangle);
            if(l_system.draw(step)){

                Line2D line;
                line.p1=currentlocation;
                line.p2=nieuwpunt;
                line.color.red=syscolor[0];
                line.color.green=syscolor[1];
                line.color.blue=syscolor[2];
                lines.push_back(line);
            }
            currentlocation=nieuwpunt;
        }
    }
    return lines;
}
