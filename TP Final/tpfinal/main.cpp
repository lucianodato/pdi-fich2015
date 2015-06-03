#include "funciones.h"

#define K1 25.0
#define K2 20.0

int main()
{
    CImg<double> imagen("../../../images/TP/aerial.tif");
    CImg<double> imagen_he =ecualizar_comun(imagen,256);
    CImg<double> imagen_bbhe =ecualizar_bbhe(imagen);
    CImg<double> imagen_clahe =ecualizar_clahe(imagen,256.0,0,255,31,0.1);
    CImg<double> imagen_acebsf =ecualizar_acebsf(imagen,K1,K2,256.0,0,255,31,0.1);

    //Seteamos los parametros k1 y k2
    //Parametros estables para k1 [10,25] - k2 [0,1]
    //double k1=15,k2=0.5

    (imagen,imagen_he,imagen_bbhe,imagen_clahe,imagen_acebsf).display();

    imagen.get_histogram(256).display_graph("Histograma de la Original");
    imagen_he.get_histogram(256).display_graph("Histograma HE");
    imagen_bbhe.get_histogram(256).display_graph("Histograma BBHE");
    imagen_clahe.get_histogram(256).display_graph("Histograma CLAHE");
    imagen_acebsf.get_histogram(256).display_graph("Histograma ACEBSF");


    return 0;
}

