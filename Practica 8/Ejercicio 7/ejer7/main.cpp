#include "funciones.h"

#define UMBRAL 160

int main()
{
    //imagen
    CImg<float> original;
    original.load("../../../../images/Morfologia/Melanoma.jpg");
    //kernel para segentacion
    CImg<bool> B(3,3,1,1,1),B2(8,8,1,1,1);

    //Creo la mascara y proceso la imagen original para obtener la envoltura convexa
    CImg<bool> umbral,segmentacion,chull;
    //Umbralado
    umbral = NOTimg(original.get_RGBtoHSI().get_channel(2).get_normalize(0,255).get_threshold(UMBRAL).get_normalize(0,1));

    //Segmentacion
    segmentacion = nerode(umbral,B,5);
    segmentacion = reconstruccion_dilatacion(umbral,segmentacion);
    segmentacion = ORimg(segmentacion,relleno_automatico(segmentacion,B));
    segmentacion = relleno_automatico(segmentacion,B2);

    //ConvexHull TENGO QUE TENER EN CUENTA QUE FUNCIONA PARA MASCARAS DONDE LO QUE IMPORTA ES EL BLANCO
    chull = ConvexHull(segmentacion);
    chull = extraccion_de_contornos(chull,B);

    (original,umbral,segmentacion,original.get_mul(NOTimg(chull))).display();


    return 0;
}

