#include <iostream>
#include "CImg.h"
#include <vector>
#include "funciones.h"

using namespace cimg_library;
using namespace std;

//Parametros de inicializacion
float alpha=1, offset=0;
unsigned char white[] = {255,255,255};
vector<punto> puntos;


int main(int argc, char *argv[])
{

    const char* filename = cimg_option("-i","../../../../images/rmn.jpg","Image file\n");
    CImg<unsigned char> original(filename),modificada(original.width(),original.height(),1,1),draw_curva(256,256,1,1);

    //Agrego los puntos inicial y final (Cabeza style)
    punto ini,fin;
    ini.x=0;
    ini.y=0;
    fin.x=255;
    fin.y=255;
    puntos.push_back(ini);
    puntos.push_back(fin);

    //Paso por los parametros de la funcion inicial. a,c e ini y fin
    CImg<unsigned char> lut(1,256,1,1);
    lut = generar_curva(lut,puntos);
    modificada=transformacion(modificada,lut);

    //Display
    draw_curva.fill(0).draw_graph(lut.get_crop(0,0,0,0,lut.width()-1,255,0,0),white,1,1,0,255,0);
    CImgDisplay vent0(original,"original"), vent1(modificada,"modificada"),vent_intensidad(draw_curva,"Curva Intensidad");

    while(!vent0.is_closed() && !vent1.is_closed() && !vent_intensidad.is_closed()){
        //Esto es para que no consuma recursos cuando la ventana esta abierta
        vent0.wait_all();

        if (vent_intensidad.button() && vent_intensidad.mouse_y()>=0) {
            //Cargo los puntos intermedios cuidando que quede ultimo el ultimo
            punto click;
            puntos.pop_back();
            click.x =abs(255-vent_intensidad.mouse_x());
            click.y = abs(255-vent_intensidad.mouse_y());
            puntos.push_back(click);
            puntos.push_back(fin);


            //Regenero la lut con los nuevos puntos
            lut = generar_curva(lut,puntos);
            //modificada=transformacion(modificada,lut);

            //Redibujo las nuevas ventanas
            draw_curva.fill(0).draw_graph(lut.get_crop(0,0,0,0,lut.width()-1,255,0,0),white,1,1,0,255,0);//Esto aca esta bien????
            vent_intensidad.assign(draw_curva,"curva de intensidad").render(draw_curva);
            //vent1.assign(modificada).render(modificada);

        }

        if (vent_intensidad.is_keyC()){
            //Quiero empezar de nuevo, limpio todo

            CImg<unsigned char> lut(calcular_lut(alpha,offset,0,255));
            modificada=transformacion(modificada,lut);

            draw_curva.fill(0).draw_graph(lut.get_crop(0,0,0,0,lut.width()-1,255,0,0),white,1,1,0,255,0);
            vent_intensidad.assign(draw_curva,"curva de intensidad").render(draw_curva);
            vent1.assign(modificada).render(modificada);

        }


    }



    return 0;

}
