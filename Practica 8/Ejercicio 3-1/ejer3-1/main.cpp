#include "funciones.h"

int main()
{
    //kernels
    CImg<bool> img,umbral,se0(3,3),se1(4,4),se3(3,3),se4(3,1);
    se0.fill(0,1,0,1,1,1,0,1,0);   //  Structuring element 1
    se1.fill(1);
    se3.fill(1,1,1,1,1,1,1,1,1);
    se4.fill(1,1,1);

    //imagen
    CImg<double> original;
    original.load("../../../../images/Morfologia/Tarjeta.jpeg");

    //Visualizo el histograma para ver el nivel de umbral
    //original.get_histogram(256,0,255).display_graph();

    //Umbralado de la imagen (negativizo porque erode y dilate trabajan sobre los blancos)
    umbral = negativo(original.get_threshold(232));
    img = umbral;

    //Aplico segmentacion
    img = apertura(img,se1);
    img = DIFERENCIAimg(umbral,img);

//    img = apertura(img,se3);
//    img = img.erode(se4);
//    img = img.erode(se4.rotate(90));


    //Visualizo
    (original,umbral,img).display();

    return 0;
}
