#include "funciones.h"

using namespace std;

int main()
{
    CImg<double> img,img_denoised,img_nueva;
   //img.load("../../../../images/corrientes_ruidogris.jpg");
    img.load("../../../../Parcial de Practica/Monedas/01_Monedas.jpg");
   // //denoise(img.get_channel(0),sizew,tipofiltro,Q,d);
    img_denoised = denoise(img,3,3);
    img_denoised = denoise(img,3,5,0,4);//Media Alfa Recortada d = la cantidad de pixeles de la ventana que puede recortar

    img_denoised.display("imagen denoise");
    double A=1.3;//medio
    img_nueva=(A *  img_denoised -  img_denoised.get_convolve(mask(6)));//alta potencia

    (img_nueva).display("alta potencia");
    img_nueva=Sobel(img_nueva,0);
    (img_nueva).display("sobel");
    img_nueva.threshold(70);//.erode(3).dilate(3);
    img_nueva.display("umbral");

    CImg<double> Hough = HoughCirculos(img_nueva,20);
    Hough.display("hough");
    CImg<double> linea = InversaHough(Hough,3);

    linea.normalize(0,255);
    linea.display("linea");
    CImg<double> resultado=sumaImg(linea.normalize(0,255),img_denoised.normalize(0,255));
    CImgList<double> lista( /*original, filtrada,*/ img_nueva, /*Hough,*/  resultado );
    lista.display("Pista", false);
    return 0;
}

