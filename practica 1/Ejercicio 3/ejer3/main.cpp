#include <iostream>
#include <deque>
#include "CImg.h"

using namespace cimg_library;
using namespace std;

struct point
{
    int x,y;
};

int main(int argc, char *argv[])
{
    CImg<unsigned char> image("../../../../images/cameraman.tif"), visu(500,400,1,3,0);

    //declaro color de linea para intensidad
    const unsigned char white[] = { 255,255,255 };
    int a=2;
    if (a==1){ // items 2 y 3   // um=umbral(um,50,250);
         CImgDisplay main_disp(image,"Click a point"), draw_disp(visu,"Intensity profile fila"),draw_disp1(visu,"Intensity profile columna"),draw_disp2(visu,"Intensity profile columna");
    while (!main_disp.is_closed() && !draw_disp.is_closed()) {
        main_disp.wait();
        if (main_disp.button() && main_disp.mouse_y()>=0) {
            const int y = main_disp.mouse_y();
            const int x = main_disp.mouse_x();
            //y constante-> intensidad a lo largo de una fila
            visu.fill(0).draw_graph(image.get_crop(0,y,0,0,image.width()-1,y,0,0),white,1,1,0,255,0).display(draw_disp);
            //x constante-> intensidad a lo largo de una columna
            visu.fill(0).draw_graph(image.get_crop(x,0,0,0,x,image.height()-1,0,0),white,1,1,0,255,0).display(draw_disp1);
            //x constante, y constante-> intensidad en un punto
            visu.fill(0).draw_graph(image.get_crop(x,y,0,0,x,y,0,0),white,1,1,0,255,0).display(draw_disp2);
            // Muestro por consola el valor de intensidad

        }
    }
    }
    else{ // intento que anda para atraz de item 4
         CImgDisplay main_disp(image,"Click a point"), draw_disp(visu,"Intensity profile usuario");
         deque<point> clicks;
        while (!main_disp.is_closed() && !draw_disp.is_closed()) {
                main_disp.wait();
                int x,y,xx,yy;
                if (main_disp.button()) {
                    clicks.push_front({main_disp.mouse_x(), main_disp.mouse_y()});

                            if (clicks.size() >= 2)
                            {
                                // draw a triangle using clicks[0], clicks[1] and clicks[2]
                                point point1=clicks[0];
                                x=point1.x;y=point1.y;
                                point1=clicks[1]; xx=point1.x;yy=point1.y;
                            }
                }

                            visu.fill(0).draw_graph(image.get_crop(x,y,0,0,xx-1,yy-1,0,0),white,1,1,0,255,0).display(draw_disp);

            }
    }

    return 0;
}

