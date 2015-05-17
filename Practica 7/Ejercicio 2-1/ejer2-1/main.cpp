#include "funciones.h"

int main()
{
    CImg<double> hough0,hough1,hough2,hough3,hough4,hough5,hough6;
    hough0.load("../../../../images/hough/hough0.png");
    hough1.load("../../../../images/hough/hough1.png");
    hough2.load("../../../../images/hough/hough2.png");
    hough3.load("../../../../images/hough/hough3.png");
    hough4.load("../../../../images/hough/hough4.png");
    hough5.load("../../../../images/hough/hough5.png");
    hough6.load("../../../../images/hough/hough6.png");

    //Transformada directa de Hough

    CImg<double> th_0 = hough(hough0);
    CImg<double> th_1 = hough(hough1);
    CImg<double> th_2 = hough(hough2);
    CImg<double> th_3 = hough(hough3);
    CImg<double> th_4 = hough(hough4);
    CImg<double> th_5 = hough(hough5);
    CImg<double> th_6 = hough(hough6);

    //Transformada inversa de Hough
    //Con la imagenes originales

    CImg<double> thi_0_img = hough(hough0,true);
    CImg<double> thi_1_img = hough(hough1,true);
    CImg<double> thi_2_img = hough(hough2,true);
    CImg<double> thi_3_img = hough(hough3,true);
    CImg<double> thi_4_img = hough(hough4,true);
    CImg<double> thi_5_img = hough(hough5,true);
    CImg<double> thi_6_img = hough(hough6,true);

    //Con la transformada de las imagenes (antitransformo)

   CImg<double> thi_0 = hough(th_0,true);
   CImg<double> thi_1 = hough(th_1,true);
   CImg<double> thi_2 = hough(th_2,true);
   CImg<double> thi_3 = hough(th_3,true);
   CImg<double> thi_4 = hough(th_4,true);
   CImg<double> thi_5 = hough(th_5,true);
   CImg<double> thi_6 = hough(th_6,true);

   (hough0,th_0, thi_0,  thi_0_img).display("imagen --    Transformada directa de Hough - antitranformada(inversa) -transformada(inversa) de la imagen Orginal");
   (hough1,th_1, thi_1,  thi_1_img).display("imagen --    Transformada directa de Hough - antitranformada(inversa) - transformada(inversa) de la imagen Orginal");
   (hough2,th_2, thi_2,  thi_2_img).display("imagen --    Transformada directa de Hough - antitranformada(inversa) - transformada(inversa) de la imagen Orginal");
   (hough3,th_3, thi_3,  thi_3_img).display("imagen --    Transformada directa de Hough - antitranformada(inversa) - transformada(inversa) de la imagen Orginal");
   (hough4,th_4, thi_4,  thi_4_img).display("imagen --    Transformada directa de Hough - antitranformada(inversa) - transformada(inversa) de la imagen Orginal");
   (hough5,th_5, thi_5,  thi_5_img).display("imagen --    Transformada directa de Hough - antitranformada(inversa) - transformada(inversa) de la imagen Orginal");
   (hough6,th_6, thi_6,  thi_6_img).display("imagen --    Transformada directa de Hough - antitranformada(inversa) - transformada(inversa) de la imagen Orginal");


/// MAS EJEMPLOS
CImg<double> hough10(256,256,1,1,0);
CImg<double> hough11(256,256,1,1,0);
CImg<double> hough12(256,256,1,1,0);
CImg<double> hough13(256,256,1,1,0);
CImg<double> hough14(256,256,1,1,0);
hough10(0,0)=1;
hough11(255,0)=1;
hough12(255,255)=1;
hough13(0,255)=1;
hough14(128,128)=1;
//Transformada directa de Hough

CImg<double> th_10 = hough(hough0);
CImg<double> th_11 = hough(hough1);
CImg<double> th_12 = hough(hough2);
CImg<double> th_13 = hough(hough3);
CImg<double> th_14 = hough(hough4);
//inversa
CImg<double> thi_10 = hough(th_10,true);
CImg<double> thi_11 = hough(th_11,true);
CImg<double> thi_12 = hough(th_12,true);
CImg<double> thi_13 = hough(th_13,true);
CImg<double> thi_14 = hough(th_14,true);

(hough10,th_0, thi_10).display("imagen --    Transformada directa de Hough - antitranformada(inversa) ");
(hough11,th_1, thi_11).display("imagen --    Transformada directa de Hough - antitranformada(inversa)");
(hough12,th_2, thi_12).display("imagen --    Transformada directa de Hough - antitranformada(inversa) ");
(hough13,th_3, thi_13).display("imagen --    Transformada directa de Hough - antitranformada(inversa) ");
(hough14,th_4, thi_14).display("imagen --    Transformada directa de Hough - antitranformada(inversa) ");




    return 0;
}
