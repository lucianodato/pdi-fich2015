#include <iostream>
#include "CImg.h"
#include <vector>
#include "funciones.h"

using namespace cimg_library;
using namespace std;

//Parametros de inicializacion
float c=1; //log
float cc=1,potencia=2;//potencia

using namespace std;

int main(int argc, char *argv[])
{

    CImg<unsigned char> img1,img2;
    const unsigned char white[] = { 255,255,255 };
    CImgList<unsigned char> listaImagenes;
    img1.load("../../../../images/rmn.jpg");//carga imagen en memo
       //img1.load("../PDI/Imagenes/autos.png");//carga imagen en memo
    CImg<unsigned char>  visu (img1.width(),img1.height(),1,1);
    img2=img1;
    CImg<unsigned char> lut(generar_lut_logb(c));
    img2=transformacion(img2,lut);
    listaImagenes.insert(img1);
    listaImagenes.insert(img2);
    listaImagenes.insert( visu.fill(0).draw_graph(lut.get_crop(0,0,0,0,lut.width()-1,255,0,0),white,1,1,0,255,0));
    CImgDisplay displayImagen(listaImagenes,"Logaritmica");

    listaImagenes.clear();
    img2=img1;
    CImg<unsigned char> lut2(generar_lut_expb(cc,potencia));
    img2=transformacion(img2,lut2);
    listaImagenes.insert(img1);
    listaImagenes.insert(img2);
    listaImagenes.insert( visu.fill(0).draw_graph(lut2.get_crop(0,0,0,0,lut2.width()-1,255,0,0),white,1,1,0,255,0));
    CImgDisplay displayImagen2(listaImagenes,"Correccion Gamma-Potencia Gamma");
    while (!displayImagen.is_closed()) {
        displayImagen2.wait_all();
    }



}

