#include "funciones.h"
double angulo=0, rho=0.0;
int var_rho=sqrt(2),var_angulo=90;
int main()
{
<<<<<<< HEAD
<<<<<<< HEAD
    CImg<double> img, sobel,houghh;
    CImgList<double> lista;
    //hough(CImg<double> img, double angulo,int nLineasX=0,int nLineasY=0,bool inverse=false, bool activeAngle=false) {


    img.load("../../../../images/cameraman.tif");
    //img.load("../../../../images/fourier/f8.jpg");
    //img.load("../../../../images/fourier/f3.jpg");
    //img=img.RGBtoHSI().get_channel(2);
    houghh=hough(img,false);
    houghh.normalize(0,255);
    lista.push_back(img);lista.push_back(houghh);
    houghh.threshold(255);
    lista.push_back(houghh);
    houghh=hough(houghh,true);
    lista.push_back(houghh);
    lista.display("img -- houghh   ----- hough umbral   ------ hough inversaa");


    lista.clear();



    img.load("../../../../images/cameraman.tif");
    //img.load("../../../../images/fourier/f8.jpg");
    //img.load("../../../../images/fourier/f3.jpg");
    //img=img.RGBtoHSI().get_channel(2);
    sobel=Sobel(img,0);
    houghh=hough(sobel,false);
    houghh.normalize(0,255);
    lista.push_back(img);lista.push_back(houghh);
    houghh.threshold(255);
    lista.push_back(houghh);
    houghh=hough(houghh,true);
    lista.push_back(houghh);
    lista.display("img -- sobel --- houghh  sobel   -----sobel hough umbral   ------ sobel hough inversaa");
=======
=======
>>>>>>> fa5707e9a01065279bf312ec0c5f30621c2526e6
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
<<<<<<< HEAD
>>>>>>> solo un detalle:no me segmenta en color ejer3, ver funcion ComposeHSI, ejercicio 2.2: si empiezo de cero ?
=======
>>>>>>> fa5707e9a01065279bf312ec0c5f30621c2526e6

    return 0;
}

