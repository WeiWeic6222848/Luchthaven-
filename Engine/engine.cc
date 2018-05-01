#include "easy_image.h"
#include "ini_configuration.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include "2D_L-systemen.h"
#include "3D_LineDrawings.h"
#include "3D_Figures.h"
#include "3D_L-systemen.h"
#include "ZBuffer.h"

img::EasyImage generate_image(const ini::Configuration &configuration){
    std::string type=configuration["General"]["type"].as_string_or_die();
    std::vector<double> kleur;
    Lines2D lines;
    kleur=configuration["General"]["backgroundcolor"].as_double_tuple_or_die();
    for(double &a:kleur){
        a*=255;
    }
    img::Color background(roundToInt(kleur[0]),roundToInt(kleur[1]), roundToInt(kleur[2]));
    if(type=="2DLSystem"){
        lines=generateLines(configuration);
    }
    if(type=="Wireframe"||type=="ZBufferedWireframe"||type=="ZBuffering"||type=="LightedZBuffering"){
        Figures3D space;
        bool isItFractal=false;
        Lights3D lights;

        if(type=="LightedZBuffering"){
            int nrLights=configuration["General"]["nrLights"].as_int_or_die();
            for(int i=0;i<nrLights;i++){
                std::string naam="Light"+std::to_string(i);
                Light light;
                if(configuration[naam]["infinity"].exists()){
                    if(configuration[naam]["infinity"].as_bool_or_die()){
                        std::vector<double> richting=configuration[naam]["direction"];
                        light.ldVector=Vector3D::vector(richting[0],richting[1],richting[2]);
                    }
                    else{
                        std::vector<double> location=configuration[naam]["location"];
                        light.location=Vector3D::point(location[0],location[1],location[2]);

                    }
                    std::vector<double> diffuse=configuration[naam]["diffuseLight"].as_double_tuple_or_die();
                    light.diffuseLight.red=diffuse[0];light.diffuseLight.green=diffuse[1];light.diffuseLight.blue=diffuse[2];
                }
                std::vector<double> ambient=configuration[naam]["ambientLight"].as_double_tuple_or_die();
                light.ambientLight.red=ambient[0];light.ambientLight.green=ambient[1];light.ambientLight.blue=ambient[2];

                lights.push_back(light);
            }
        }
        else if(type=="ZBuffering"){
            Light light;
            light.ambientLight.red=1.0;light.ambientLight.green=1.0;light.ambientLight.blue=1.0;
            light.specularLight.red=0.0;light.specularLight.green=0.0;light.specularLight.blue=0.0;
            light.diffuseLight.red=0.0;light.diffuseLight.green=0.0;light.diffuseLight.blue=0.0;
            lights.push_back(light);
        }

        int nrFigures=configuration["General"]["nrFigures"].as_int_or_die();
        for(int i=0;i<nrFigures;i++){
            Figure figuur;
            std::string naam="Figure"+std::to_string(i);
            std::string typefig=configuration[naam]["type"].as_string_or_die();

            if(typefig=="Cube"||typefig=="FractalCube"){
                figuur=createCube();
            }
            else if(typefig=="Tetrahedron"||typefig=="FractalTetrahedron"){
                figuur=createTetrahedron();
            }
            else if(typefig=="Octahedron"||typefig=="FractalOctahedron"){
                figuur=createOctahedron();
            }
            else if(typefig=="Icosahedron"||typefig=="FractalIcosahedron"){
                figuur=createIcosahedron();
            }
            else if(typefig=="Dodecahedron"||typefig=="FractalDodecahedron"){
                figuur=createDodecahedron();
            }
            else if(typefig=="BuckyBall"||typefig=="FractalBuckyBall"){
                figuur=createBuckyball();
            }
            else if(typefig=="MengerSponge"||typefig=="FractalMengerSponge"){
                figuur=createMengerSponge();
            }
            else if(typefig=="Sphere"){
                int n=configuration[naam]["n"].as_int_or_die();
                figuur=createSphere(1.0,n);
            }
            else if(typefig=="Cone"){
                double height=configuration[naam]["height"].as_double_or_die();
                int n=configuration[naam]["n"].as_int_or_die();
                figuur=createCone(n,height);
            }
            else if(typefig=="Cylinder"){
                double height=configuration[naam]["height"].as_double_or_die();
                int n=configuration[naam]["n"].as_int_or_die();
                figuur=createCylinder(n,height);
            }
            else if(typefig=="Torus"){
                int n=configuration[naam]["n"].as_int_or_die();
                int m=configuration[naam]["m"].as_int_or_die();
                double r=configuration[naam]["r"].as_double_or_die();
                double R=configuration[naam]["R"].as_double_or_die();
                figuur=createTorus(r,R,n,m);
            }
            else if(typefig=="3DLSystem"){
                figuur=genereateFigure(configuration,naam);
            }
            else if(typefig=="LineDrawing"){
            int nrpoints=configuration[naam]["nrPoints"].as_int_or_die();
            for(int j=0;j<nrpoints;j++){
                std::string puntNaam="point"+std::to_string(j);
                std::vector<double> coord=configuration[naam][puntNaam].as_double_tuple_or_die();
                Vector3D punt=Vector3D::point(coord[0],coord[1],coord[2]);
                figuur.points.push_back(punt);
            }
                int nrFaces=configuration[naam]["nrLines"].as_int_or_die();
                for(int j=0;j<nrFaces;j++){
                    std::string faceName="line"+std::to_string(j);
                    std::vector<int> punten=configuration[naam][faceName].as_int_tuple_or_die();
                    Face face;
                    for(int punt:punten){
                        face.point_indexes.push_back(punt);
                    }
                    figuur.faces.push_back(face);
                }
            }
            std::string check=typefig.substr(0,7);
            if(check=="Fractal"||typefig=="MengerSponge"){
                isItFractal=true;
                const int iterations=configuration[naam]["nrIterations"].as_int_or_die();
                Figures3D opgesplitst;
                if(typefig=="MengerSponge"){
                    generateFractal(figuur,opgesplitst,iterations,3,true);
                }
                else{
                    const double scale=configuration[naam]["fractalScale"].as_double_or_die();
                    generateFractal(figuur,opgesplitst,iterations,scale);
                }
                for(Figure& part:opgesplitst){
                    if(type=="ZBuffering"||type=="LightedZBuffering"){
                        std::vector<Face> updatedFaces;
                        for(Face face:part.faces){
                            std::vector<Face> driehoeken=triangulate(face);
                            for(Face face:driehoeken){
                                updatedFaces.push_back(face);
                            }
                        }
                        part.faces=updatedFaces;

                    }
                    if(type=="LightedZBuffering"){
                        std::vector<double> ambient=configuration[naam]["ambientReflection"].as_double_tuple_or_die();
                        part.ambientReflection.red=ambient[0];part.ambientReflection.green=ambient[1];part.ambientReflection.blue=ambient[2];
                        std::vector<double> diffuse=configuration[naam]["diffuseReflection"].as_double_tuple_or_die();
                        part.diffuseReflection.red=diffuse[0];part.diffuseReflection.green=diffuse[1];part.diffuseReflection.blue=diffuse[2];
                    }
                    else if(type=="ZBuffering"){
                        std::vector<double> kleur=configuration[naam]["color"].as_double_tuple_or_die();
                        part.ambientReflection.red=kleur[0];
                        part.ambientReflection.green=kleur[1];
                        part.ambientReflection.blue=kleur[2];
                    }
                    else{
                        std::vector<double> kleur=configuration[naam]["color"].as_double_tuple_or_die();
                        part.color.red=kleur[0];
                        part.color.green=kleur[1];
                        part.color.blue=kleur[2];
                    }
                    Matrix schaal=scaleFigure(configuration[naam]["scale"].as_double_or_die());
                    Matrix xrot=rotateX(configuration[naam]["rotateX"].as_double_or_die()/180*M_PI);
                    Matrix yrot=rotateY(configuration[naam]["rotateY"].as_double_or_die()/180*M_PI);
                    Matrix zrot=rotateZ(configuration[naam]["rotateZ"].as_double_or_die()/180*M_PI);
                    std::vector<double> center=configuration[naam]["center"].as_double_tuple_or_die();
                    Vector3D translatiepunt=Vector3D::point(center[0],center[1],center[2]);
                    Matrix trans=translate(translatiepunt);
                    Matrix transformatie=schaal*xrot*yrot*zrot*trans;
                    applyTransformation(part,transformatie);
                    space.push_back(part);
                }
            }
            if(!isItFractal){
                if(type=="ZBuffering"||type=="LightedZBuffering"){
                    std::vector<Face> updatedFaces;
                    for(Face face:figuur.faces){
                        std::vector<Face> driehoeken=triangulate(face);
                        for(Face face:driehoeken){
                            updatedFaces.push_back(face);
                        }
                    }
                    figuur.faces=updatedFaces;

                }
                if(type=="LightedZBuffering"){
                    std::vector<double> ambient=configuration[naam]["ambientReflection"].as_double_tuple_or_die();
                    figuur.ambientReflection.red=ambient[0];figuur.ambientReflection.green=ambient[1];figuur.ambientReflection.blue=ambient[2];
                    std::vector<double> diffuse=configuration[naam]["diffuseReflection"].as_double_tuple_or_die();
                    figuur.diffuseReflection.red=diffuse[0];figuur.diffuseReflection.green=diffuse[1];figuur.diffuseReflection.blue=diffuse[2];
                }
                else if(type=="ZBuffering"){
                    std::vector<double> kleur=configuration[naam]["color"].as_double_tuple_or_die();
                    figuur.ambientReflection.red=kleur[0];
                    figuur.ambientReflection.green=kleur[1];
                    figuur.ambientReflection.blue=kleur[2];
                }
                else{
                    std::vector<double> kleur=configuration[naam]["color"].as_double_tuple_or_die();
                    figuur.color.red=kleur[0];
                    figuur.color.green=kleur[1];
                    figuur.color.blue=kleur[2];
                }
                Matrix schaal=scaleFigure(configuration[naam]["scale"].as_double_or_die());
                Matrix xrot=rotateX(configuration[naam]["rotateX"].as_double_or_die()/180*M_PI);
                Matrix yrot=rotateY(configuration[naam]["rotateY"].as_double_or_die()/180*M_PI);
                Matrix zrot=rotateZ(configuration[naam]["rotateZ"].as_double_or_die()/180*M_PI);
                std::vector<double> center=configuration[naam]["center"].as_double_tuple_or_die();
                Vector3D translatiepunt=Vector3D::point(center[0],center[1],center[2]);
                Matrix trans=translate(translatiepunt);
                Matrix transformatie=schaal*xrot*yrot*zrot*trans;
                applyTransformation(figuur,transformatie);
                space.push_back(figuur);
            }
        }
        std::vector<double> eyecoord=configuration["General"]["eye"].as_double_tuple_or_die();
        Vector3D eye=Vector3D::point(eyecoord[0],eyecoord[1],eyecoord[2]);
        Matrix eyepoint=eyePointTrans(eye);
        applyTransformation(space,eyepoint);

        lines=doProjection(space);

        if(type=="ZBuffering"||type=="LightedZBuffering"){
            int size=configuration["General"]["size"].as_int_or_die();
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

            for(Figure figuur:space){
                double refl;
                for(Face face:figuur.faces){
                    draw_zbuf_triag(buffer,drawing,figuur.points[face.point_indexes[0]],figuur.points[face.point_indexes[1]],figuur.points[face.point_indexes[2]],d,dx,dy,figuur.ambientReflection,figuur.diffuseReflection,figuur.specularReflection,refl,lights);
                }
            }
            return drawing;
        }

        if(type=="ZBufferedWireframe"){
            return draw2DLines(lines,configuration["General"]["size"],background,true);
        }
    }
    return draw2DLines(lines,configuration["General"]["size"],background);
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
