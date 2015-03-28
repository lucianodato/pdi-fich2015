#include <iostream>
#include "CImg.h"
#include <vector>
#include "funciones.h"

using namespace cimg_library;
using namespace std;

//Parametros de inicializacion
int alpha=-1, offset=255;

int main(int argc, char *argv[])
{

    const char* filename = cimg_option("-i","../../../../images/rmn.jpg","Image file\n");
    CImg<unsigned char> original(filename),modificada(original.width(),original.height(),1,1);
     CImg<unsigned char> lut(generar_lut_lin(alpha,offset));
     modificada=transformacion(modificada,lut);
     lut.display("Lut");

    //Display
   CImgDisplay vent0(original,"original"),draw_curve(lut,"Curva de intensidad"), vent1(modificada,"modificada");

   while(!vent0.is_closed() && !vent1.is_closed() && !draw_curve.is_closed()){
       //Esto es para que no consuma recursos cuando la ventana esta abierta
       vent0.wait_all();
       draw_curve.wait();
   }



return 0;

}
