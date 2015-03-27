#include <iostream>
#include "CImg.h"
#include <vector>
#include "funciones.h"

using namespace cimg_library;
using namespace std;

//Parametros de inicializacion
int alpha=1, offset=0;

int main(int argc, char *argv[])
{

    const char* filename = cimg_option("-i","../../../../images/botellas.tif","Image file\n");
    CImg<unsigned char> original(filename),modificada(original.width(),original.height(),1,1),imagen_lut,intensidad(256,256,1,1);




    //genero la LUT y reemplazo en la imagen
    imagen_lut = lut(alpha,offset);

    cimg_forXY(modificada,i,j)
    modificada(i,j) = imagen_lut(1,(int)*original.data(i,j,0,0));


    //Display
   CImgDisplay vent0(original,"original"),draw_curve(intensidad,"Curva de intensidad"), vent1(modificada,"modificada");

   while(!vent0.is_closed() && !vent1.is_closed() && !draw_curve.is_closed()){
       //Esto es para que no consuma recursos cuando la ventana esta abierta
       vent0.wait();
       vent1.wait();
       draw_curve.wait();
   }



return 0;

}
