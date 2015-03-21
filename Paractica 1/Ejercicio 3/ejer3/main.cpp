#include <iostream>
#include "CImg.h"

using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[])
{
    bool diagonal = 0;
    const int y,y_ant,x,x_ant;
    vector<unsigned int> auxiliar;
    const unsigned char white[] = { 255,255,255 };

    CImg<unsigned char> image("../../../../images/cameraman.tif"), visu(500,400,1,3,0);
    CImgDisplay main_disp(image,"Click a point"), draw_disp(visu,"Intensity profile");
    //declaro color de linea para intensidad


    //Mientras que no se cierre la ventana
    while (!main_disp.is_closed() && !draw_disp.is_closed()) {
        main_disp.wait();
        if (!diagonal){
            //Para que devuelva la informacion de una fila
            if (main_disp.button() && main_disp.mouse_y()>=0) {
                y = main_disp.mouse_y();
                visu.fill(0).draw_graph(image.get_crop(0,y,0,0,image.width()-1,y,0,0),white,1,1,0,255,0).display(draw_disp);
                // Muestro por consola el valor de intensidad
                cout<< "Cantidad de canales: "<< image.spectrum()<<endl;
                cout<< "valor de intensidad en el punto:"<< (int)image(main_disp.mouse_x(),main_disp.mouse_y(),0,0)<<endl;
            }
        }
        else
        {
            //Para que devuelva la informacion en cualquier direccion de la imagen
            if (main_disp.button() && main_disp.mouse_y()>=0) {
                y_ant = y;
                y = main_disp.mouse_y();
                x_ant = x;
                x = main_disp.mouse_x();

                for (int i = )

                visu.fill(0).draw_graph().display(draw_disp);
                // Muestro por consola el valor de intensidad
                cout<< "Cantidad de canales: "<< image.spectrum()<<endl;
                cout<< "valor de intensidad en el punto:"<< (int)image(main_disp.mouse_x(),main_disp.mouse_y(),0,0)<<endl;
            }
        }
    }
    return 0;
}

