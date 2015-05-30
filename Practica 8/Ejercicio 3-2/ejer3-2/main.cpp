#include "funciones.h"

int main()
{
    //kernels
    CImg<bool> img,img2,umbral,se0(3,3),se1(3,3);
    se0.fill(1);   //  Structuring element 1
    se1.fill(0,1,0,1,1,1,0,1,0);

    //imagen
    CImg<double> original;
    original.load("../../../../images/Morfologia/Caracteres.jpeg");

    //Visualizo el histograma para ver el nivel de umbral
    //original.get_histogram(256,0,255).display_graph();

    //Umbralado de la imagen (negativizo porque erode y dilate trabajan sobre los blancos)
    umbral = negativo(original.get_threshold(232));
    img = img2 =umbral;

    //Aplico segmentacion - Para las letras grandes
    img = img.get_erode(se0).get_dilate(se1).get_erode(se0).get_dilate(se1).get_erode(se0);
    img = reconstruccion_dilatacion(umbral,img);//Reconstruccion es la posta

    //Aplico diferencia con la umbralada - Para las letras chicas
    img2 = DIFERENCIAimg(umbral,img);

    //Visualizo
    (original,umbral,NOTimg(img),NOTimg(img2)).display();


    return 0;
}
