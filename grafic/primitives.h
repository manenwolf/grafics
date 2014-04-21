#include "EasyImage.h"
#include <list>
#include <iostream>
#include <algorithm>

class vec2f{
	public:
		double x = 0;
		double y = 0;
        vec2f(float posx=0, float posy=0): x(posx), y(posy){}
};

class Color{
	public:
    Color(double r,double g,double b): red(r*255),green(g*255),blue(b*255){}
    Color(std::vector<double> rgb);
        int red   = 0;
        int green = 0;
        int blue  = 0;
        img::Color getcolor(){
            return img::Color(red,green,blue);
        }
};
Color::Color(std::vector<double> rgb){
    if(rgb.size()!=3){
        std::cout << "incorect collor" << std::endl;

    }else{
        red = rgb[0]*255;
        green = rgb[1]*255;
        blue = rgb[2]*255;
    }

}
class Line{
	private:
	public:
        vec2f point1 = {0,0};
        vec2f point2 = {0,0};
        Color kleur = Color(1,1,1);
        Line(vec2f p1,vec2f p2):point1(p1),point2(p2){}
        void render(img::EasyImage& image);
        Line(){

        }
};

void Line::render(img::EasyImage& image){
    image.draw_line(point1.x,point1.y,
                    point2.x,point2.y,
                    kleur.getcolor());
}

void setBackground(Color color, img::EasyImage& image){
    for(unsigned int i=0;i < image.get_height();i++){
        for(unsigned int j =0; j < image.get_width();j++ ){
            image(i,j).red = color.red;
            image(i,j).green = color.green;
            image(i,j).blue = color.blue;
        }
    }
}

typedef std::list<Line> Lines2D;

void draw2DLines(Lines2D& lines, img::EasyImage& image){
    if(lines.size()==0){
        std::cout << "drawing empty line list" << std::endl;
    }else{

        //declaring of the min and max point valeus
        double Xmin = lines.begin()->point1.x;
        double Xmax = lines.begin()->point1.x;
        double Ymin = lines.begin()->point1.y;
        double Ymax = lines.begin()->point1.y;

        //calculating Xmin, Xmax, Ymin and Ymax
        for (Lines2D::iterator it = lines.begin(); it != lines.end(); it++){
            if( it->point1.x < Xmin ){
                Xmin = it->point1.x;
            }
            if( it->point2.x < Xmin){
                Xmin = it->point2.x;
            }
            if( it->point1.x > Xmax){
                Xmax = it->point1.x;
            }
            if( it->point2.x > Xmax){
                Xmax = it->point2.x;
            }
            if( it->point1.y < Ymin){
                Ymin = it->point1.y;
            }
            if( it->point2.y < Ymin){
                Ymin = it->point2.y;
            }
            if( it->point1.y > Ymax){
                Ymax = it->point1.y;
            }
            if( it->point2.y > Ymax){
                Ymax = it->point2.y;
            }
        }

        std::cout << Xmin << ' ' << Xmax << ' ' << Ymin << ' ' << Ymax << std::endl;

        //calculating of ranges, Imagesizes and the scale factor d
        double Xrange = Xmax - Xmin;
        double Yrange = Ymax - Ymin;

        double image_x = image.get_width()*(Xrange/std::max(Xrange,Yrange));
        double image_y = image.get_height()*(Yrange/std::max(Xrange,Yrange));

        double d = 0.95*(image_x/Xrange);

        double DCx = d*(Xmin+Xmax)/2;
        double DCy = d*(Ymin+Ymax)/2;



        for (Lines2D::iterator it = lines.begin(); it != lines.end(); it++){
            std::cout << it->point1.x << std::endl;
            std::cout << it->point1.y << std::endl;

            std::cout << it->point2.x << std::endl;
            std::cout << it->point2.y << std::endl;

            std::cout << "____________" << std::endl;

            it->point1.x=it->point1.x*d + image_x/2-DCx;
            it->point1.y=it->point1.y*d + image_y/2-DCy;
            it->point2.x=it->point2.x*d + image_x/2-DCx;
            it->point2.y=it->point2.y*d + image_y/2-DCy;

            std::cout << it->point1.x << std::endl;
            std::cout << it->point1.y << std::endl;

            std::cout << it->point2.x << std::endl;
            std::cout << it->point2.y << std::endl;
            it->render(image);
        }
    }
}
