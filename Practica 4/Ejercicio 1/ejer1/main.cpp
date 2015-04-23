#include "funciones.h"

using namespace std;

int main()
{
    const char* path = "../../../../images/patron.tif";
    CImg <float> img_rgb,img_hsi,hue;
    img_rgb.load(path);
    img_hsi = img_rgb.get_RGBtoHSI();

    //a)

    CImgList<float> lista(img_rgb.get_channel(0),img_rgb.get_channel(1),img_rgb.get_channel(2),img_hsi.get_channel(0),img_hsi.get_channel(1),img_hsi.get_channel(2));
    //lista.display();

//    //b)

//    img_hsi.get_HSItoRGB().display();


//    hue = img_hsi.get_channel(0);

//    //Normalizo
//    cimg_forXY(hue,i,j)
//            hue(i,j) = hue(i,j)*255.0/360.0;


//    //Rotamos los colores azules
//    cimg_forXY(hue,i,j)
//            if(hue(i,j) > 170.0 && hue(i,j) < 190.0)
//            hue(i,j) += 100.0;

//    //Desnormalizo
//    cimg_forXY(hue,i,j)
//            hue(i,j) = hue(i,j)*360.0/255.0;

//    //Copio hue modificado al canal hue de la imagen
//    cimg_forXY(hue,i,j)
//        *img_hsi.channel(0).data(i,j) = hue(i,j);

//    img_hsi.get_HSItoRGB().display();


    //c)
//    //Modificamos el brillo y la saturacion para cada pixel para maximizalos
//    cimg_forXY(img_hsi,i,j){
//            //img_hsi.channel(1)(i,j) = 1.0;//Saturacion al maximo
//            img_hsi.channel(2)(i,j) = 1.0;//Brillo al maximo
//    }

//    img_hsi.channel(2).display();

    //2)
    //Realizamos los cambios en cada pixel
    cimg_forXY(img_hsi,i,j){
            img_hsi.channel(0)(i,j) -= 180;//Roto hacia los complementarios
            img_hsi.channel(2)(i,j) = negativo(img_hsi.channel(2)(i,j));
    }

    //Desnormalizo
    cimg_forXY(hue,i,j)
            hue(i,j) = hue(i,j)*360.0/255.0;




    return 0;
}

