#include "easy_image.h"
#include "ini_configuration.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <cmath>

#include <stack>
#include "Line.h"
#include <list>
#include "l_parser.h"
#include "vector3d.h"
#include "Figure.h"

using namespace std;

Matrix scaleFigure(const double scale);
Matrix rotateX(const double angle);
Matrix rotateY(const double angle);
Matrix rotateZ(const double angle);
Matrix translate(const Vector3D &vector);
void applyTransformation(Figure & figure, const Matrix & matrix);
void toPolar(const Vector3D &point, double &theta, double &phi, double &r);
Matrix eyePointTrans(const Vector3D &eyepoint);
Lines doProjection(const Figures3D & figures);
Position_2D doProjection(const Vector3D &point, const double d);
void applyTransformation(Figures3D & figure, const Matrix & matrix);
Figure createTetrahedron();
Figure createCube();
Figure createOctahedron();
Figure createIcosahedron();
Figure createSphere(const double radius, const int n);
Figure createDodecaheron();
Figure createCone(const int n, const double h);

inline int roundToInt(double d)
{
    return static_cast<int>(std::round(d));
}

img::EasyImage drawlines(const Lines &lines, int size, img::Color background=img::Color(0,0,0)){
        double xmax=lines.begin().operator*().p1.X;
        double ymax=lines.begin().operator*().p1.Y;
        double xmin=lines.begin().operator*().p1.X;
        double ymin=lines.begin().operator*().p1.Y;
        for (auto i = lines.begin(); i != lines.end(); ++i) {
                const Line2D &a=*i;
                xmax=max(max(a.p1.X,a.p2.X),xmax);
                ymax=max(max(a.p1.Y,a.p2.Y),ymax);
                xmin=min(min(a.p1.X,a.p2.X),xmin);
                ymin=min(min(a.p1.Y,a.p2.Y),ymin);
        }
        // now xmaxmin and ymaxmin are found.
        double xrange=xmax-xmin;
        double yrange=ymax-ymin;
        double imagewidth=size*1.0*xrange/max(xrange,yrange);
        double imageheight=size*1.0*yrange/max(xrange,yrange);
        if (xrange==0) {xrange=1; imagewidth=1;};
        img::EasyImage image(roundToInt(imagewidth),roundToInt(imageheight),background);
        double scalefactor=0.95*imagewidth/xrange;
        double afstandX=imagewidth*1.0/2-scalefactor*(xmax+xmin)/2;
        double afstandY=imageheight*1.0/2-scalefactor*(ymax+ymin)/2;
        for (auto i = lines.begin(); i!=lines.end(); ++i){
                const Line2D &a=*i;
                image.draw_line(roundToInt(a.p1.X*scalefactor+afstandX),roundToInt(a.p1.Y*scalefactor+afstandY),roundToInt(a.p2.X*scalefactor+afstandX),roundToInt(a.p2.Y*scalefactor+afstandY),img::Color(a.color.red,a.color.green,a.color.blue));
        }

        return image;
}

/*
img::EasyImage ColorRectangle(int height, int width){
    img::EasyImage image(height,width);
    for(unsigned int j = 0; j < image.get_height(); j++)
    {
        for(unsigned int k = 0; k < image.get_width(); k++)
        {
            image(j,k).red = j;
            image(j,k).green = k;
            image(j,k).blue = (j+k)%256;
        }
    }
    return image;
}

img::EasyImage Blocks(int height,int width,int nrX, int nrY, std::vector<double> &colorw, std::vector<double> &colorb){
    double Wb=width/nrX;
    double Hb=height/nrY;
    img::EasyImage image(height,width);

    for(unsigned int j = 0; j < image.get_height(); j++)
    {
        for(unsigned int k = 0; k < image.get_width(); k++)
        {
            int Bx= j/Wb;
            int By= k/Hb;
            if ((Bx+By)%2==0){
                image(j,k).red = roundToInt(colorw[0]);
                image(j,k).green = roundToInt(colorw[1]);
                image(j,k).blue = roundToInt(colorw[2]);
            }
            else{
                image(j,k).red = roundToInt(colorb[0]);
                image(j,k).green = roundToInt(colorb[1]);
                image(j,k).blue = roundToInt(colorb[2]);
            }
        }
    }
    return image;
}


img::EasyImage Line(int height,int width,std::string figure, std::vector<double> &bc, std::vector<double> &lc, int nrl){

    img::EasyImage image(width,height);
    double Ys=height*1.0/(nrl-1);
    double Xs=width*1.0/(nrl-1);
    std::vector<std::pair<std::pair<int,int>,std::pair<int,int>>> points_to_connect;
    std::pair<int,int> firstcoor (height,width-1);
    std::pair<int,int> secondcoor (height,0);
    std::vector<std::pair<int,int>> pixeltocolor;
    for (int j=0;j<=nrl;j++){
        std::pair<std::pair<int,int>,std::pair<int,int>> tosave (firstcoor,secondcoor);
        points_to_connect.push_back(tosave);
        firstcoor.second=roundToInt(firstcoor.second-Xs);
        secondcoor.first=roundToInt(secondcoor.first-Ys);
    }

    for (auto i:points_to_connect){
        int Xverschil=abs(i.first.second-i.second.second);
        int Yverschil=i.first.first-i.second.first;
        double rico=Yverschil*1.0/Xverschil;
        int startingX=std::min(i.first.second,i.second.second);
        int startingY=i.first.second;
        if(startingX==i.first.second){
            startingY=i.first.first;
        }
        if (abs(Yverschil)>Xverschil){
            if (rico>1){
                for (int j = 0; j < Yverschil; ++j) {
                    std::pair<int,int> temp (startingX+j*1/rico,startingY+j);
                    pixeltocolor.push_back(temp);
                }
            }
            else{
                for (int j = 0; j < Yverschil; ++j) {
                    std::pair<int,int> temp (startingX-j*1/rico,startingY+j);
                    pixeltocolor.push_back(temp);
                }
            }
        }
        else{
            for (int j = 0; j < Xverschil; ++j) {
                std::pair<int,int> temp (startingX+j,startingY+j*rico);
                pixeltocolor.push_back(temp);
            }
        };
    }

    for(unsigned int j = 0; j < image.get_height(); j++)
    {
        for(unsigned int k = 0; k < image.get_width(); k++)
        {
            image(k,j).red = roundToInt(bc[0]);
            image(k,j).green = roundToInt(bc[1]);
            image(k,j).blue = roundToInt(bc[2]);
        }
    }

    for (auto i:pixeltocolor){
        if (i.first<0){
            i.first=0;
        }
        else if (i.first>=height){
            i.first=height-1;
        }
        if (i.second<0){
            i.second=0;
        }
        else if(i.second>=width){
            i.second=width-1;
        }

        image(i.second,i.first).red = roundToInt(lc[0]);
        image(i.second,i.first).green = roundToInt(lc[1]);
        image(i.second,i.first).blue = roundToInt(lc[2]);
    }
    return image;
}
*/
img::EasyImage generate_2DL(int size, std::vector<double> bc, std::vector<double> lc, LParser::LSystem2D& sysfile){
    set<char> a=sysfile.get_alphabet();
    string init=sysfile.get_initiator();
    int iter=sysfile.get_nr_iterations();
    double currentangle=sysfile.get_starting_angle();
    double angel=sysfile.get_angle();
    Position_2D currentposition(0,0);
    Lines verzameling;
    stack<pair<int,Position_2D>> haakjes;

    for (int i = 0; i < iter; ++i) {
        string tempinit="";
        for (char a:init){
            if (a!='+'&&a!='-'&&a!='('&&a!=')'){
                string qq=sysfile.get_replacement(a);
                tempinit+=qq;
            }
            else{
                tempinit+=a;
            }
        }
        init=tempinit;
    }
    for (char a:init){
        if(a=='+'){
            currentangle+=angel;
        }
        else if (a=='-'){
            currentangle-=angel;
        }
        else if(a=='('){
            haakjes.push(pair<double,Position_2D>(currentangle,currentposition));
        }
        else if(a==')'){
            pair<double,Position_2D>temp=haakjes.top();
            currentangle=temp.first;
            currentposition=temp.second;
            haakjes.pop();
        }
        else if (sysfile.draw(a)){
            Position_2D next(cos(currentangle/(360/2/M_PI))+currentposition.X,sin(currentangle/(360/2/M_PI))+currentposition.Y);
            Line2D templine(currentposition,next,img::Color(lc[0],lc[1],lc[2]));
            verzameling.push_back(templine);
            currentposition=next;
        }
    }

    return drawlines(verzameling, size,img::Color(bc[0],bc[1],bc[2]));
}


img::EasyImage generate_image(const ini::Configuration &configuration)
{
        std::string type=configuration["General"]["type"].as_string_or_die();
        if (type=="2DLSystem"){
            int size=configuration["General"]["size"].as_int_or_die();
            std::vector<double> bcolor=configuration["General"]["backgroundcolor"].as_double_tuple_or_die();
            LParser::LSystem2D lsys2d;
            string filename=configuration["2DLSystem"]["inputfile"].as_string_or_die();
            ifstream fin(filename);
            fin>>lsys2d;
            fin.close();
            std::vector<double> lcolor=configuration["2DLSystem"]["color"].as_double_tuple_or_die();
            for (int i = 0; i < 3; ++i) {
                bcolor[i]=bcolor[i]*255;
                lcolor[i]=lcolor[i]*255;
            }
            return generate_2DL(size,bcolor,lcolor,lsys2d);
        }
        else if(type=="Wireframe"){
            int size=configuration["General"]["size"].as_int_or_die();
            std::vector<double> temp=configuration["General"]["backgroundcolor"].as_double_tuple_or_die();
            img::Color bcolor(temp[0]*255,temp[1]*255,temp[2]*255);
            int nrfigures=configuration["General"]["nrFigures"].as_int_or_die();
            temp=configuration["General"]["eye"].as_double_tuple_or_die();
            Vector3D eye = Vector3D::point(temp[0],temp[1],temp[2]);


            Figures3D figurelist;
            for (int j = 0; j < nrfigures; ++j) {
                std::string type=configuration["Figure"+to_string(j)]["type"].as_string_or_die();
                Figure myfigure;
                double rX = configuration["Figure"+to_string(j)]["rotateX"].as_double_or_die();
                double rY = configuration["Figure"+to_string(j)]["rotateY"].as_double_or_die();
                double rZ = configuration["Figure"+to_string(j)]["rotateZ"].as_double_or_die();
                double scaling = configuration["Figure"+to_string(j)]["scale"].as_double_or_die();
                temp=configuration["Figure"+to_string(j)]["center"].as_double_tuple_or_die();
                Vector3D center= Vector3D::point(temp[0],temp[1],temp[2]);
                temp=configuration["Figure"+to_string(j)]["color"].as_double_tuple_or_die();
                img::Color lcolor(temp[0]*255,temp[1]*255,temp[2]*255);
                if (type=="LineDrawing"){
                    int nrpoint = configuration["Figure"+to_string(j)]["nrPoints"].as_int_or_die();
                    int nrlines = configuration["Figure"+to_string(j)]["nrLines"].as_int_or_die();
                    for (int i = 0; i < nrpoint; ++i) {
                        temp = configuration["Figure"+to_string(j)]["point"+to_string(i)].as_double_tuple_or_die();
                        Vector3D temppoint3D= Vector3D::point(temp[0],temp[1],temp[2]);
                        myfigure.points.push_back(temppoint3D);
                    }
                    for (int k = 0; k < nrlines; ++k) {
                        vector<int> tempintvector;
                        tempintvector = configuration["Figure"+to_string(j)]["line"+to_string(k)].as_int_tuple_or_die();
                        Face tempface;
                        for (int i:tempintvector){
                            tempface.point_indexes.push_back(i);
                        }
                        myfigure.faces.push_back(tempface);
                    }
                    Matrix thematrix=scaleFigure(scaling)*rotateX(rX)*rotateY(rY)*rotateZ(rZ)*translate(center);
                    applyTransformation(myfigure,thematrix);
                    myfigure.color=lcolor;
                }
                else if(type=="Cube"){
                    myfigure=createCube();
                    myfigure.color=lcolor;
                    Matrix thematrix=scaleFigure(scaling)*rotateX(rX)*rotateY(rY)*rotateZ(rZ)*translate(center);
                    applyTransformation(myfigure,thematrix);
                }
                else if(type=="Icosahedron"){
                    myfigure=createIcosahedron();
                    myfigure.color=lcolor;
                    Matrix thematrix=scaleFigure(scaling)*rotateX(rX)*rotateY(rY)*rotateZ(rZ)*translate(center);
                    applyTransformation(myfigure,thematrix);
                }
                else if(type=="Sphere"){
                    int times= configuration["Figure"+to_string(j)]["n"].as_int_or_die();
                    myfigure =createSphere(1,times);
                    myfigure.color=lcolor;
                    Matrix thematrix=scaleFigure(scaling)*rotateX(rX)*rotateY(rY)*rotateZ(rZ)*translate(center);
                    applyTransformation(myfigure,thematrix);

                }
                else if(type=="Dodecahedron"){
                    myfigure=createDodecaheron();
                    myfigure.color=lcolor;
                    Matrix thematrix=scaleFigure(scaling)*rotateX(rX)*rotateY(rY)*rotateZ(rZ)*translate(center);
                    applyTransformation(myfigure,thematrix);
                }
                else if(type=="Cone"){
                    double height=configuration["Figure"+to_string(j)]["height"].as_double_or_die();
                    int n=configuration["Figure"+to_string(j)]["n"].as_int_or_die();
                    myfigure=createCone(n,height);
                    myfigure.color=lcolor;
                    Matrix thematrix=scaleFigure(scaling)*rotateX(rX)*rotateY(rY)*rotateZ(rZ)*translate(center);
                    applyTransformation(myfigure,thematrix);
                }
                figurelist.push_back(myfigure);
            }
            Matrix eyepoint=eyePointTrans(eye);
            applyTransformation(figurelist,eyepoint);
            Lines projected=doProjection(figurelist);
            return drawlines(projected,size,bcolor);
        }
            /*
        else{
            int height=configuration["ImageProperties"]["height"].as_int_or_die();
            int width=configuration["ImageProperties"]["width"].as_int_or_die();
            if (type=="IntroColorRectangle"){
                return ColorRectangle(height,width);
            }
            else if(type=="IntroBlocks"){
                int nrXblocks=configuration["BlockProperties"]["nrXBlocks"];
                int nrYblocks=configuration["BlockProperties"]["nrYBlocks"];
                std::vector<double> colorw=configuration["BlockProperties"]["colorWhite"].as_double_tuple_or_die();
                std::vector<double> colorb=configuration["BlockProperties"]["colorBlack"].as_double_tuple_or_die();
                for (int i = 0; i < 3; ++i) {
                    colorw[i]=colorw[i]*255;
                    colorb[i]=colorb[i]*255;
                }
                bool invertcolor=configuration["BlockProperties"]["invertColors"].as_bool_or_die();
                if (invertcolor){
                    return Blocks(height,width,nrXblocks,nrYblocks,colorb,colorw);
                }
                return Blocks(height,width,nrXblocks,nrYblocks,colorw,colorb);
            }
            else if(type=="IntroLines"){
                std::string figure=configuration["LineProperties"]["figure"].as_string_or_die();
                std::vector<double> backgroundcolor=configuration["LineProperties"]["backgroundcolor"].as_double_tuple_or_die();
                std::vector<double> linecolor=configuration["LineProperties"]["lineColor"].as_double_tuple_or_die();
                for (int i = 0; i < 3; ++i) {
                    backgroundcolor[i]=backgroundcolor[i]*255;
                    linecolor[i]=linecolor[i]*255;
                }
                int x=configuration["LineProperties"]["nrLines"].as_int_or_die();
                return Line(height,width,figure,backgroundcolor,linecolor,x);
            }
        }*/
}

int main(int argc, char const* argv[])
{
        int retVal = 0;
        try
        {
                for(int i = 1; i < argc; ++i)
                {
                        ini::Configuration conf;
                        try
                        {
                                std::ifstream fin(argv[i]);
                                fin >> conf;
                                fin.close();
                        }
                        catch(ini::ParseException& ex)
                        {
                                std::cerr << "Error parsing file: " << argv[i] << ": " << ex.what() << std::endl;
                                retVal = 1;
                                continue;
                        }

                        img::EasyImage image = generate_image(conf);
                        if(image.get_height() > 0 && image.get_width() > 0)
                        {
                                std::string fileName(argv[i]);
                                std::string::size_type pos = fileName.rfind('.');
                                if(pos == std::string::npos)
                                {
                                        //filename does not contain a '.' --> append a '.bmp' suffix
                                        fileName += ".bmp";
                                }
                                else
                                {
                                        fileName = fileName.substr(0,pos) + ".bmp";
                                }
                                try
                                {
                                        std::ofstream f_out(fileName.c_str(),std::ios::trunc | std::ios::out | std::ios::binary);
                                        f_out << image;

                                }
                                catch(std::exception& ex)
                                {
                                        std::cerr << "Failed to write image to file: " << ex.what() << std::endl;
                                        retVal = 1;
                                }
                        }
                        else
                        {
                                std::cout << "Could not generate image for " << argv[i] << std::endl;
                        }
                }
        }
        catch(const std::bad_alloc &exception)
        {
    		//When you run out of memory this exception is thrown. When this happens the return value of the program MUST be '100'.
    		//Basically this return value tells our automated test scripts to run your engine on a pc with more memory.
    		//(Unless of course you are already consuming the maximum allowed amount of memory)
    		//If your engine does NOT adhere to this requirement you risk losing points because then our scripts will
		//mark the test as failed while in reality it just needed a bit more memory
                std::cerr << "Error: insufficient memory" << std::endl;
                retVal = 100;
        }
        return retVal;
}
