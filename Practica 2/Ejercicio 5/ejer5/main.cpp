#include "funciones.h"

using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[])
{
    CImg<unsigned char> img, img2, img3;
    img.load("../../../../images/cameraman.tif");
    CImg<unsigned char> umbral, umbral_inv, umbral_tra, umbral_inv_tra, not_img, umbral2;

//    //Punto 1
//    //Pregunta: Es recomendable normalizar antes de aplicar cualquier operacion de umbral??
      umbral = img.get_threshold(128);
      umbral_inv=transformacion(umbral,generar_lut(-1,255,0,255)).normalize(0,1);
//    umbral_tra=umbral_por_tramos(img,40,160);
//    umbral_inv_tra=transformacion(umbral_tra,generar_lut(-1,255,0,255)).normalize(0,1);
//    CImgList<unsigned char> disp1(img, umbral, umbral_inv, umbral_tra, umbral_inv_tra);
//    disp1.display("Original - Binaria - Invertida - Por tramos - Por tramos invertida");

    //Punto 2

    //EL NOT es lo mismo que el negativo de la binaria
      not_img=transformacion(umbral,generar_lut(-1,255,0,255)).normalize(0,1);
      CImgList<unsigned char> disp2(img,umbral,not_img);
      disp2.display("NOT");

      img2.load("../../../../images/cameraman.tif");
      umbral2=transformacion(img2.get_threshold(128),generar_lut(-1,255,0,255)).normalize(0,1);

     CImgList<unsigned char> disp3(umbral, umbral2, ANDimg(umbral,umbral2));
     disp3.display("AND");

     img.load("../../../../images/carlock1.png");
     img2.load("../../../../images/carlock2.png");

     CImgList<unsigned char> disp4(img.get_threshold(128),  img2.get_threshold(128) , img.get_threshold(128) | img2.get_threshold(128) ); //correcto??-> revisar
     disp4.display("OR");

     CImgList<unsigned char> disp10(img.get_threshold(128) ,  img2.get_threshold(128) , img.get_threshold(128) ^ img2.get_threshold(128)); // correcto??->revisar
     disp10.display("XOR");


     ////Punto 3
     img.load("../../../../images/cameraman.tif");
     img2.load("../../../../images/cameraman.tif");
     img3.load("../../../../images/coins.tif");


     CImgList<unsigned char> disp5(img, img3, MAYORimg(img, img3), MAYORimg(img3,img));
     disp5.display("MAYOR -  Img1   /   Img2   /   Img1 > Img2   /   Img2 > Img1 ");

     CImgList<unsigned char> disp6(img, img3, MENORimg(img, img3), MENORimg(img3,img));
     disp6.display("MENOR -  Img1   /   Img2   /   Img1 < Img2   /   Img2 < Img1 ");

     return 0;
}
