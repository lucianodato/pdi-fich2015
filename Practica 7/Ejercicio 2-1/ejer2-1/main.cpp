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

    th_0.display();
    th_1.display();
    th_2.display();
    th_3.display();
    th_4.display();
    th_5.display();
    th_6.display();

    //Transformada inversa de Hough

    //Con la imagenes originales
    CImg<double> thi_0 = hough(hough0,true);
    CImg<double> thi_1 = hough(hough1,true);
    CImg<double> thi_2 = hough(hough2,true);
    CImg<double> thi_3 = hough(hough3,true);
    CImg<double> thi_4 = hough(hough4,true);
    CImg<double> thi_5 = hough(hough5,true);
    CImg<double> thi_6 = hough(hough6,true);

    thi_0.display();
    thi_1.display();
    thi_2.display();
    thi_3.display();
    thi_4.display();
    thi_5.display();
    thi_6.display();

    //Con la transformada de las imagenes

    thi_0 = hough(th_0,true);
    thi_1 = hough(th_1,true);
    thi_2 = hough(th_2,true);
    thi_3 = hough(th_3,true);
    thi_4 = hough(th_4,true);
    thi_5 = hough(th_5,true);
    thi_6 = hough(th_6,true);

    thi_0.display();
    thi_1.display();
    thi_2.display();
    thi_3.display();
    thi_4.display();
    thi_5.display();
    thi_6.display();

    return 0;
}

