#include "funciones.h"
double angulo=0, rho=0.0;
int var_rho=sqrt(2),var_angulo=90;
int main()
{
    CImg<double> img, sobel,th,th_i,split,split_th_i;
    CImgList<double> lista;
    img.load("../../../../images/cameraman.tif");
    //img.load("../../../../images/fourier/f8.jpg");
    //img.load("../../../../images/fourier/f3.jpg");
    if (img.spectrum()!=1)
        img=img.RGBtoHSI().get_channel(2);
    sobel=Sobel(img);
    th=hough(sobel,false); //transf hough
    split=splitHough(th, angulo,rho,var_angulo,var_rho,false);//transf hough recortada
    th.normalize(0,255); // esto es indiferente me supongo, lo hago por la dudas
    split.normalize(0,255);
    lista.push_back(img);lista.push_back(sobel);lista.push_back(th);lista.push_back(split);
    th.threshold(245);
    lista.push_back(th);lista.push_back(split);
    th_i=hough(th,true);
    split_th_i=hough(th_i,true);
    lista.push_back(th_i);
    lista.push_back(split_th_i);



    lista.display("img-img filtrada(con filtro de bordes)-- th--split hough --hough umbral --hough inversaa -- inversa de la recortada");

    return 0;
}

