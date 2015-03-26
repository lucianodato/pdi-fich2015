#include <iostream>
#include "CImg.h"
#include "pasar_binario.h"
#include "procesar_botellas.h"

using namespace cimg_library;
using namespace std;

//Variables globales para evitar hardcoding
//Linea de evaluación de llenado
int nivel_seleccionado = 48;
int umbral_de_evaluacion = 178;
const unsigned char white[] = { 255,255,255 };

int main(int argc, char *argv[])
{
    const char* filename = cimg_option("-i","../../../../images/botellas.tif","Image file\n");
    CImg<unsigned char> original(filename), modificada(original.width(),original.height(),1,3)/*,  visu(500,400,1,1)*/;

    //Paso a binaria la original
    //binaria = pasar_binario(original,umbral);

    //Procesado de la botella
    modificada = procesar_botellas(original,umbral_de_evaluacion,nivel_seleccionado);

    //Display
    CImgDisplay vent0(original,"original")/*,draw_binary(binaria,"Binaria")*/, draw_mod(modificada,"modificada");


    //Dibujo la linea intensidad
    //visu.fill(0).draw_graph(binaria.get_crop(0,nivel_seleccionado,0,0,binaria.width()-1,nivel_seleccionado,0,0),white,1,1,0,255,0).display(draw_inten);


    while(!vent0.is_closed() && !draw_mod.is_closed() /*&& !draw_binary.is_closed()*/){
        //Esto es para que no consuma recursos cuando la ventana esta abierta
        vent0.wait();
        draw_mod.wait();
        //draw_binary.wait();
    }

    return 0;
}


