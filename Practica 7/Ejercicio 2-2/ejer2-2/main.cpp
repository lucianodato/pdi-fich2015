#include "funciones.h"
int main()
{
    CImg<double> img,img_denoised,img_nueva;
    img.load("../../../../images/snowman.png");
    //img.load("../../../../images/letras1.tif");
    //img.load("../../../../images/letras2.tif");
    img_denoised = denoiseRGB(img,3,5,0,4);
    img_denoised=Sobel(img_denoised,0);
    img_nueva=img_denoised.get_threshold(16).get_RGBtoHSI().get_channel(2).get_normalize(0,1);
    CImg<double> Hough = hough( img_nueva );
    Pixel coordenadas;
    double valor_tita;
    int numeroMaximos=30;

    // Busco donde esta su maxima colinearidad
    coordenadas= MaximoP(Hough);
    valor_tita = coordenadaXY_a_rho_tita(Hough, coordenadas.x, 't'); //tita
    //splitHough(CImg<T> Hough, T angulo,T rho,int ang_tol = 0,int tolerancia_rho = 0, bool solo_max = false)
    CImg<double>acumulada(hough(splitHough(Hough, valor_tita, (double) coordenadas.y, 1, 1), true));
    acumulada.threshold(100).normalize(0,255);
    Hough(coordenadas.x,coordenadas.y)=0;//voy quedandome con los segundos maximos
    for(int i=1;i<numeroMaximos;i++){
    // Busco donde esta su maxima colinearidad
    coordenadas= MaximoP(Hough);
    valor_tita = coordenadaXY_a_rho_tita(Hough, coordenadas.x, 't'); //tita
    //splitHough(CImg<T> Hough, T angulo,T rho,int ang_tol = 0,int tolerancia_rho = 0, bool solo_max = false)
    CImg<double> linea(hough(splitHough(Hough, valor_tita, (double) coordenadas.y, 1, 1), true));
    linea.threshold(100).normalize(0,255);
    acumulada=(acumulada+linea)/2;
    acumulada.threshold(100).normalize(0,255);
    Hough(coordenadas.x,coordenadas.y)=0;//voy quedandome con los segundos maximos
    }
    (img,acumulada).display("acumulada");
return 0;
}

