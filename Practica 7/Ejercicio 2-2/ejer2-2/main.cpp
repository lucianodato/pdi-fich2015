#include "funciones.h"

int main()
{
    CImg<double> img, sobel,houghh;
    CImgList<double> lista;
    //hough(CImg<double> img, double angulo,int nLineasX=0,int nLineasY=0,bool inverse=false, bool activeAngle=false) {


    //img.load("../../../../images/cameraman.tif");
    img.load("../../../../images/fourier/f8.jpg");
    //img.load("../../../../images/fourier/f3.jpg");
    img=img.RGBtoHSI().get_channel(2);
    houghh=hough(img,false);
    houghh.normalize(0,255);
    lista.push_back(img);lista.push_back(houghh);
    houghh.threshold(200);
    lista.push_back(houghh);
    houghh=hough(houghh,true);
    lista.push_back(houghh);
    lista.display("img -- houghh   ----- hough umbral   ------ hough inversaa");


    lista.clear();



    //img.load("../../../../images/cameraman.tif");
    img.load("../../../../images/fourier/f8.jpg");
    //img.load("../../../../images/fourier/f3.jpg");
    img=img.RGBtoHSI().get_channel(2);
    sobel=Sobel(img,0);
    houghh=hough(sobel,false);
    houghh.normalize(0,255);
    lista.push_back(img);lista.push_back(houghh);
    houghh.threshold(200);
    lista.push_back(houghh);
    houghh=hough(houghh,true);
    lista.push_back(houghh);
    lista.display("img -- sobel --- houghh  sobel   -----sobel hough umbral   ------ sobel hough inversaa");

    return 0;
}

