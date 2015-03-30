#include "funciones.h"

using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[])
{
    CImg<unsigned char> img, img2, img3;
    img.load("../../../../images/cameraman.tif");
    CImg<unsigned char> umbral, umbral_inv, umbral_tra, umbral_inv_tra, not_img, not_img2;

    //Punto 1
    umbral = img.get_threshold(125);
    umbral_inv=umbral_invertido(img,125);
    umbral_tra=umbral_por_tramos(img,100,200);
    umbral_inv_tra=umbral_invertido_por_tramos(img,100,200);
    CImgList<unsigned char> disp1(img, umbral, umbral_inv, umbral_tra, umbral_inv_tra);
    disp1.display("Original - Binaria - Invertida - Por tramos - Por tramos invertida");

//	//Punto 2
    not_img=NOTimg(umbral);
    CImgList<unsigned char> disp2(img, umbral, not_img);
    disp2.display("NOT");

    img2.load("../../../../images/cameraman.tif");
    img2.threshold(200);

    CImgList<unsigned char> disp3(umbral, img2, ANDimg(img2,umbral));
    disp3.display("AND");

    CImgList<unsigned char> disp4(umbral, img2, ORimg(umbral, img2));
    disp4.display("OR");

    //Punto 3
    img3.load("../../../../images/coins.tif");

    CImgList<unsigned char> disp5(img, img3, MAYORimg(img, img3), MAYORimg(img3,img));
    disp5.display("MAYOR -  Img1   /   Img2   /   Img1 > Img2   /   Img2 > Img1 ");

    CImgList<unsigned char> disp6(img, img3, MENORimg(img, img3), MENORimg(img3,img));
    disp6.display("MENOR -  Img1   /   Img2   /   Img1 < Img2   /   Img2 < Img1 ");

    return 0;
}
