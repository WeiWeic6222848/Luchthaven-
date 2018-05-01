//
// Created by tristan on 9/04/18.
//

#include <limits>
#include "ZBuffer.h"
#include <assert.h>
#include <math.h>
#include <algorithm>
#include <cmath>

ZBuffer::ZBuffer(const int width, const int height) {
    double posInf=std::numeric_limits<double>::infinity();
    for(int x=0;x<width;x++){
        std::vector<double> rij;
        for(int y=0;y<height;y++){
            rij.push_back(posInf);
        }
        this->push_back(rij);
    }
}
void ZBuffer::swap(unsigned int & a,unsigned int & b){
    unsigned int  temp= a;
    a=b;
    b=temp;
}
void ZBuffer::draw_zbuf_line(ZBuffer & buffer, img::EasyImage & image, unsigned int x0, unsigned int y0, double z0, unsigned int x1, unsigned int y1, double z1, const img::Color &color) {

    assert(x0 < image.get_width() && y0 < image.get_height());
    assert(x1 < image.get_width() && y1 < image.get_height());
    if (x0 == x1)
    {
        //special case for x0 == x1
        int a=std::max(y0,y1)-std::min(y0,y1);
        if(y0>y1){
            double temp=z1;
            z1=z0;
            z0=temp;
        }
        for (unsigned int i = std::min(y0, y1); i <= std::max(y0, y1); i++) {
            int index = std::max(y0, y1) - i;
            double z = ((double) index / (double) a) / z0 + (1 - (double) index / (double) a) / z1;
            if(z<buffer[x0][i]){
            (image)(x0, i) = color;
            buffer[x0][i] = z;
            }

        }
    }
    else if (y0 == y1)
    {

        //special case for y0 == y1
        int a=std::max(x0,x1)-std::min(x0,x1);
        if(x0>x1){
            double temp=z1;
            z1=z0;
            z0=temp;
        }
        for (unsigned int i = std::min(x0, x1); i <= std::max(x0, x1); i++)
        {
            int index=std::max(x0,x1)-i;
            double z=((double)index/(double)a)/z0+(1-(double)index/(double)a)/z1;
            if(z<buffer[i][y0]){
                (image)(i, y0) = color;
                buffer[i][y0]=z;
            }
        }
    }
    else
    {
        if (x0 > x1)
        {
            //flip points if x1>x0: we want x0 to have the lowest value
            swap(x0,x1);
            swap(y0, y1);
            double temp=z1;
            z1=z0;
            z0=temp;
        }
        double m = ((double) y1 - (double) y0) / ((double) x1 - (double) x0);
        if (-1.0 <= m && m <= 1.0)
        {
            int a=x1-x0;
            for (unsigned int i = 0; i <= (x1 - x0); i++)
            {
                int index=a-i;
                double z=((double)index/(double)a)/z0+(1-(double)index/(double)a)/z1;
                if(z<buffer[x0+i][(unsigned int)round(y0+m*i)]){
                    (image)(x0 + i, (unsigned int) round(y0 + m * i)) = color;
                    buffer[x0+i][(unsigned int)round(y0+m*i)]=z;
                }

            }
        }
        else if (m > 1.0)
        {
            int a=y1-y0;
            for (unsigned int i = 0; i <= (y1 - y0); i++)
            {
                int index=a-i;
                double z=((double)index/(double)a)/z0+(1-(double)index/(double)a)/z1;
                if(z<buffer[(unsigned int)round(x0 + (i / m))][y0+i]){
                    (image)((unsigned int) round(x0 + (i / m)), y0 + i) = color;
                    buffer[(unsigned int)round(x0 + (i / m))][y0 + i]=z;
                }
            }
        }
        else if (m < -1.0)
        {
            int a=y0-y1;
            for (unsigned int i = 0; i <= (y0 - y1); i++)
            {
                int  index=a-i;
                double z=((double)index/(double)a)/z0+(1-(double)index/(double)a)/z1;
                if(z<buffer[(unsigned int)round(x0 - (i / m))][y0 - i]){
                    (image)((unsigned int) round(x0 - (i / m)), y0 - i) = color;
                    buffer[(unsigned int)round(x0 - (i / m))][y0 - i]=z;
                }
            }
        }
    }
}
std::vector<Face> triangulate(const Face& face){
    std::vector<Face> triangles;
    int punt1=face.point_indexes[0];
    for(int i=1;i<face.point_indexes.size()-1;i++){
        Face nieuwVlak;
        nieuwVlak.point_indexes.push_back(punt1);
        nieuwVlak.point_indexes.push_back(face.point_indexes[i]);
        nieuwVlak.point_indexes.push_back(face.point_indexes[i+1]);
        triangles.push_back(nieuwVlak);
    }
    return triangles;
}
void draw_zbuf_triag(ZBuffer& buffer, img::EasyImage& image, Vector3D const& A, Vector3D const& B, Vector3D const& C, double d, double dx, double dy, Color ambientReflection, Color diffuseReflection, Color specularReflection, double reflectionCoeff, Lights3D& lights){
    double posInf=std::numeric_limits<double>::infinity();
    double negInf=(-1.0)*std::numeric_limits<double>::infinity();

    Point2D a=doProjection(A,d);
    a.x+=dx;a.y+=dy;
    Point2D b=doProjection(B,d);
    b.x+=dx;b.y+=dy;
    Point2D c=doProjection(C,d);
    c.x+=dx;c.y+=dy;

    int min=roundToInt(std::min(std::min(a.y,b.y),c.y)+0.5);
    int max=roundToInt(std::max(std::max(a.y,b.y),c.y)-0.5);

    Vector3D u=B-A;
    Vector3D v=C-A;

    double w1=u.y*v.z-u.z*v.y;
    double w2=u.z*v.x-u.x*v.z;
    double w3=u.x*v.y-u.y*v.x;

    double k=w1*A.x+w2*A.y+w3*A.z;

    double dzdx=w1/(-d*k);double dzdy=w2/(-d*k);

    double red=0.0;
    double green=0.0;
    double blue=0.0;

    bool isItdiffuse=false;
    Vector3D l;

    Vector3D CB=B-C;
    Vector3D BA=A-B;
    Vector3D cba=Vector3D::cross(CB,BA);

    Vector3D abc=Vector3D::cross(u,v);
    Vector3D n=Vector3D::normalise(Vector3D::vector(w1,w2,w3));

    //std::cout<<"n: "<<n.x<<" "<<n.y<<" "<<n.z<<" "<<n.length()<<std::endl;

    for(Light& light:lights) {
        if(light.ldVector.x!=NULL||light.ldVector.y!=NULL||light.ldVector.z!=NULL){
            isItdiffuse=true;
            //std::cout<<"ld: "<<" "<<light.ldVector.x<<" "<<light.ldVector.y<<" "<<light.ldVector.z<<" "<<light.ldVector.length()<<std::endl;
            l=Vector3D::normalise(light.ldVector)*(-1);
            //std::cout<<"l: "<<l.x<<" "<<l.y<<" "<<l.z<<" "<<l.length()<<std::endl;
            double cos=n.x*l.x+n.y*l.y+n.z*l.z;
            //std::cout<<"cos: "<<cos<<std::endl;
            if(cos>=0){
                red+=diffuseReflection.red*light.diffuseLight.red*cos;
                green+=diffuseReflection.green*light.diffuseLight.green*cos;
                blue+=diffuseReflection.blue*light.diffuseLight.blue *cos;
            }
        }
        red += ambientReflection.red * light.ambientLight.red;
        green += ambientReflection.green * light.ambientLight.green;
        blue += ambientReflection.blue * light.ambientLight.blue;
    }
    img::Color color(roundToInt(255.0 * red), roundToInt(255.0 * green), roundToInt(255.0 * blue));

    for(int i=min;i<=max;i++){
        double xlab=posInf;double xlac=posInf;double xlbc=posInf;double xrab=negInf;double xrac=negInf;double xrbc=negInf;
        if((i-a.y)*(i-b.y)<=0 && a.y!=b.y){
            double xi=b.x+(a.x-b.x)*(i-b.y)/(a.y-b.y);
            xlab=xi;xrab=xi;
        }
        if((i-a.y)*(i-c.y)<=0 && a.y!=c.y){
            double xi=c.x+(a.x-c.x)*(i-c.y)/(a.y-c.y);
            xlac=xi;xrac=xi;
        }
        if((i-c.y)*(i-b.y)<=0 && c.y!=b.y){
            double xi=c.x+(b.x-c.x)*(i-c.y)/(b.y-c.y);
            xlbc=xi;xrbc=xi;
        }

        int xl=roundToInt(std::min(std::min(xlab,xlac),xlbc)+0.5);
        int xr=roundToInt(std::max(std::max(xrab,xrac),xrbc)-0.5);

        for(int k=xl;k<=xr;k++){
            double xg=(a.x+b.x+c.x)/3; double yg=(a.y+b.y+c.y)/3;
            double zGinvers=1/(3*A.z)+1/(3*B.z)+1/(3*C.z);

            double Zinvers=1.0001*zGinvers+((double)k-xg)*dzdx+((double)i-yg)*dzdy;

            if(Zinvers<buffer[k][i]){
                (image)(k,i)=color;
                buffer[k][i]=Zinvers;
            }
        }

    }

}