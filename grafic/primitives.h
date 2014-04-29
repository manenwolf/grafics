#include "EasyImage.h"
#include <list>

class vec2f{
	public:
		double x = 0;
		double y = 0;
        vec2f(float posx=0, float posy=0): x(posx), y(posy){}
};

class color{
	public:
		double red   = 0;
		double green = 0;
		double blue  = 0;
        img::Color getcolor(){
            return img::Color(red,green,blue);
        }
};

class Line{
	private:
	public:
        vec2f point1 = {0,0};
        vec2f point2 = {0,0};
        color kleur = {};
        Line(vec2f p1,vec2f p2);//:point1(p1),point2(p2){}
        void render(img::EasyImage& image);
        Line(){

        }
};

void Line::render(img::EasyImage& image){
    image.draw_line(point1.x,point1.y,
                    point2.x,point2.y,
                    kleur.getcolor());
}

typedef std::list<Line> Lines2D;

void draw2DLines(Lines2D& lines, img::EasyImage& image){
    for (Lines2D::iterator it = lines.begin(); it != lines.end(); it++){
        it->render(image);
    }
}
