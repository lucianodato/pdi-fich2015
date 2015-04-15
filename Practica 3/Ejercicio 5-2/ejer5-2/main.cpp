#include "funciones.h"

int c=1;
double A=3;

int main()
{
    CImg<double> img;
    img.load("../../../../images/esqueleto.tif");
    CImg<double> lut(generar_lut_logb(c));
    img.channel(0);
    CImg<double> mask(3,3); //filtro
    mask.fill(1,1,1,
             1,-8,1,
             1,1,1);
    // hb = imagen alta frec
    //hb= A*img-PB(IMG)

    // pasa alto->filtro suma 0: altas frecuencias eliminando las bajas(zonas homogeneas)
    CImg<double> f_realze_3x3a_sum0(3,3);
    f_realze_3x3a_sum0.fill(-1,-1,-1,-1,8,-1,-1,-1,-1);
    //f_realze_3x3a_sum0.fill(0,0.125,0,0.125,0.5,0.125,0,0.125,0);

    //filtro de promediado (de suma 1)
    CImg<double> filtro_suav_5x5(5,5);
    filtro_suav_5x5=mask(5.0);


    //CImg<double> imgHigFrec=img.get_convolve(f_realze_3x3a_sum0);
    CImg<double> imgHigFrec=((A-1)*img + img.get_convolve(f_realze_3x3a_sum0)).normalize(0,255);
    CImg<double> imgSobel=Sobel(img).normalize(0,255);
    CImg<double> imgSobel1=Sobel(img).get_convolve(filtro_suav_5x5).normalize(0,255);
    //imgRealzada1
    CImg<double> imgRealzada1=(img+imgHigFrec).normalize(0,255);
    //imgRealzada2= producto de "img+imgHigFrec" y imgSobel pasada por un filtro de promediado 5x5
    CImg<double> imgRealzada2=multiplicacion(imgRealzada1, imgSobel1).normalize(0,255);
    CImg<double> imgRealzada3=(img+imgRealzada2).normalize(0,255);
    CImg<double> imgRealzada4=transformacion(imgRealzada3,lut).normalize(0,255);
    (img,imgHigFrec,imgRealzada1,imgSobel,imgSobel1,imgRealzada2,imgRealzada3,imgRealzada4).display("img(a) -imgHigFrec(b) - imgRealzada1(c=a+b) - imgSobel(d) - imgSobel1(e) - imgRealzada2(f=c*e) - imgRealzada3(g=a+f) -imgRealzada4(h)");

    ///page 139 Gonzales & Wood
    return 0;
}

