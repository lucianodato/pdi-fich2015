#include "funciones.h"

#define UMBRAL 160

int main()
{
    //imagen
    CImg<float> original;
    original.load("../../../../images/Morfologia/Melanoma.jpg");
    //kernel para segentacion
    CImg<bool> B(3,3,1,1,1),B_CH(3,3,1,1,0),B2(8,8,1,1,1);
    B_CH.fill(1,0,0,1,0,0,1,0,0);

    //Creo la mascara y proceso la imagen original para obtener la envoltura convexa
    CImg<bool> umbral,segmentacion;
    //Umbralado
    umbral = NOTimg(original.get_RGBtoHSI().get_channel(2).get_normalize(0,255).get_threshold(UMBRAL).get_normalize(0,1));

    //Segmentacion
    segmentacion = nerode(umbral,B,5);
    segmentacion = reconstruccion_dilatacion(umbral,segmentacion);
    segmentacion = ORimg(segmentacion,relleno_automatico(segmentacion,B));
    segmentacion = relleno_automatico(segmentacion,B2);


    //segmentacion = ConvexHull(segmentacion,B_CH);

    (original,umbral,segmentacion).display("Umbralado - Segmentacion");


    return 0;
}

