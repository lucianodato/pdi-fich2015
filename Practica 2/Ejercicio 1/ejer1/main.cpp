#include <iostream>
#include <stdlib.h>
#include "CImg.h"
#include <vector>
#include "funciones.h"
#include <cmath>

using namespace cimg_library;
using namespace std;

//Parametros de inicializacion
float alpha=1, offset=0;
unsigned char white[] = {255,255,255};
int cantclick=0;
vector<punto> puntos;
vector<float> pendientes;


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
        vent0.wait();
        vent_intensidad.wait();
        vent1.wait();

        if (vent_intensidad.button() && vent_intensidad.mouse_y()>=0 && vent_intensidad.mouse_x()>=0) {

            pendientes.clear();

            //Cargo los puntos intermedios cuidando que quede ultimo el ultimo
            punto click;
            puntos.pop_back();
            click.x =vent_intensidad.mouse_x();
            click.y = abs(255-vent_intensidad.mouse_y());//coloco coord "y" abajo
            puntos.push_back(click);
            puntos.push_back(fin);
            // con cero click tengo . Inicial, Final
            // con un click tengo tres coordenadas. Inicial, punto1, Final
            //con dos click tengo n coordenadas. Inicial, punto1, punto2,..., punto N, Final
            //ordenar puntos  segun distancia al origen (0,0)
            puntos=ordenarCoordenadas(puntos);
            for(int i=1;i<puntos.size();i++)//m= y2-y1/x2-x1
                pendientes.push_back(abs(puntos[i].y-puntos[i-1].y)/abs(puntos[i].x-puntos[i-1].x));//las coordenadas estan ordenadas
            //cout<<"m: "<<(puntos[i].y-puntos[i-1].y)/(puntos[i].x-puntos[i-1].x)<<endl;

            for(int i=0;i<pendientes.size();i++)
                cout<<i<<": "<<pendientes[i]<<endl;
            //   cout<<"size pendiente: "<<pendientes.size()<<"size puntos: "<<puntos.size()<<endl;

            //generar luts

            //el primer tramo de la curva bien
            //luego o pego mal las luts o calculo mal las pendientes revisar estos dos for
            CImgList<unsigned char>listLut;
            for(int i=0;i<pendientes.size();i++){
                // CImg<unsigned char> lut_aux(1,puntos[i+1].x-puntos[i].x,1,1);
                // cout<<"offset: "<<puntos[i].y<<"punto x: "<<puntos[i].x<<"puntox +1: "<<puntos[i+1].x<<endl;
                //   cout<<i<<": "<<pendientes[i]<<endl;
                listLut.push_back(generar_lut(pendientes[i],puntos[i].y,puntos[i].x,puntos[i+1].x));
            }

            //pegar luts-- no pega bien!!
            for(int i=0;i<pendientes.size();i++){
                CImg<unsigned char> lut_aux=listLut[i];
                for(int j=puntos[i].x;j<(puntos[i+1].x);j++){
                    lut(1,j)=lut_aux(1,j);
                }
            }

            //lut.display();
            //lut.clear();
            //cantclick++;
            //aplico nuevo mapeo de lut
            modificada=transformacion(modificada,lut);
            //Redibujo las nuevas ventanas
            draw_curva.fill(0).draw_graph(lut.get_crop(0,0,0,0,lut.width()-1,255,0,0),white,1,1,0,255,0);
            vent_intensidad.assign(draw_curva,"curva de intensidad").render(draw_curva);
            vent1.assign(modificada).render(modificada);

        }

        //        if (vent_intensidad.is_keyC()){
        //            //Quiero empezar de nuevo, limpio todo

        //            CImg<unsigned char> lut(calcular_lut(alpha,offset,0,255));
        //            modificada=transformacion(modificada,lut);

        //            draw_curva.fill(0).draw_graph(lut.get_crop(0,0,0,0,lut.width()-1,255,0,0),white,1,1,0,255,0);
        //            vent_intensidad.assign(draw_curva,"curva de intensidad").render(draw_curva);
        //            vent1.assign(modificada).render(modificada);

        //        }


    }
    return 0;
}
