#include "funciones.h"

int main()
{
    //kernels
    CImg<bool> img,umbral,se0(3,3),se1(3,3);
    se0.fill(1);   //  Structuring element 1
    se1.fill(0,1,0,1,1,1,0,1,0);

    //imagen
    CImg<double> original;
    original.load("../../../../images/Morfologia/Tarjeta.jpeg");

    //Visualizo el histograma para ver el nivel de umbral
    //original.get_histogram(256,0,255).display_graph();

    //Umbralado de la imagen (negativizo porque erode y dilate trabajan sobre los blancos)
    umbral = negativo(original.get_threshold(232));
    img = umbral;

    //Aplico segmentacion erosionando fuertemente y reconstruyendo
    img = img.get_erode(se0).get_dilate(se1).get_erode(se0).get_dilate(se1).get_erode(se0);
    img = reconstruccion_dilatacion(umbral,img);//Reconstruccion es la posta


    //Visualizo
    (original,umbral,NOTimg(img)).display();


    return 0;
}
