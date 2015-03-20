#include <iostream>
#include "CImg.h"
using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[])
{
              CImg<unsigned char> img, copia;
              CImgList<unsigned char> listaImagenes,listaImagenes1;
              CImgDisplay displayImagen, displayImagen1;

              img.load("../../../../images/rmn.jpg");
              listaImagenes.insert(img);
              listaImagenes1.insert(img);
              for(unsigned i=0; i<5; i++){
                  copia=img;
                  //esta 2 lineas submuestreo, redimenciono 128,64,... luego la redimenciono a 256 de nuevo
                  copia.resize(img.width()/((i+1)*2), img.height()/((i+1)*2));
                  listaImagenes1.insert(copia);
                  copia.resize(img.width(), img.height());
                  listaImagenes.insert(copia);
              }
              displayImagen.assign(listaImagenes, "Normalizado a tamaño original");
              displayImagen1.assign(listaImagenes1);

              while(!displayImagen.is_closed() && !displayImagen1.is_closed()){
                  displayImagen.wait_all(); // esperamos algun evento en cualquier display
              }




    return 0;
}

