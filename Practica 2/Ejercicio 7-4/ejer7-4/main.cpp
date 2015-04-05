#include "funciones.h"

using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[])
{
    const char* path = "../../../../images/cameraman.tif";
     const char* path_2 = "../../../../images/coins.tif";

    CImg<unsigned char> original;
    original.load(path);

    //Declaro las imagenes que voy a utilizar
    CImg<unsigned char>compuesta(original.width(),original.height(),1,1),binaria;

    //Cargo una imagen binaria. Puede ser cualquiera
    binaria.load(path_2);
    binaria = binario(binaria,128);

    //Descompongo la imagen original en sus 8 planos de bits
    CImgList<unsigned char> auxiliar = bitlist(original),generica;

    //Remplazo el último plano por la imagen binaria (normalizada)

    generica.push_back(binaria.get_normalize(0,1));
    for(int i =1; i<auxiliar.size();i++){
        generica.push_back(auxiliar.pop_back());
    }
    //    auxiliar.pop_back();
    //    auxiliar.push_back(binaria.normalize(0,1));

    //Sumo todos los planos de bits para componer nuevamente la imagen
    for (int k = 0 ;k<7;k++){
        compuesta+=generica[k];
    }

    //Descompongo la imagen compuesta para verificar que efectivamente se encuentra la imagen binaria en el ultimo plano
    auxiliar = bitlist(compuesta);

    //Creo una imagen nueva para verificar
    CImg <unsigned char> plano_0(auxiliar[0]);

    //Normalizo las imagenes para poder mostrar en el mismo display
    binaria.normalize(0,255);
    plano_0.normalize(0,255);

    //Cargo el listado de imagenes a mostrar
    CImgList<unsigned char> imagenes;
    imagenes.insert(original.normalize(0,255));
    imagenes.insert(binaria);
    imagenes.insert(compuesta);
    imagenes.insert(plano_0);

    //Muestro el resultado
    CImgDisplay DisplayImagen (imagenes,"Original - Binaria - Compuesta - Plano_0 (Compuesta)");

    while(!DisplayImagen.is_closed()){

        DisplayImagen.wait_all();

    }

     return 0;
}

