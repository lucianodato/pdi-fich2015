#include "funciones.h"

//K parametro de mezcla de la sigmoidea (0-1)
#define K 0.5
#define N_I 56
#define N_S 200


int main()
{
    CImg<double> imagen("../../../images/TP/aerial.tif");
    CImg<double> imagen_he =ecualizar_comun(imagen,256);
    CImg<double> imagen_bbhe =ecualizar_bbhe(imagen);
    CImg<double> imagen_clahe =ecualizar_clahe(imagen,256.0,0,255,31,0.01);
    CImg<double> imagen_acebsf =ecualizar_acebsf(imagen,K,N_I,N_S,256.0,0,255,31,0.01);

    //Seteamos los parametros k1 y k2
    //Parametros estables para k1 [10,25] - k2 [0,1]
    //double k1=15,k2=0.5

    (imagen,imagen_he,imagen_bbhe,imagen_clahe,imagen_acebsf).display();

    imagen.get_histogram(256).display_graph("Histograma de la Original");
    imagen_he.get_histogram(256).display_graph("Histograma HE");
    imagen_bbhe.get_histogram(256).display_graph("Histograma BBHE");
    imagen_clahe.get_histogram(256).display_graph("Histograma CLAHE");
    imagen_acebsf.get_histogram(256).display_graph("Histograma ACEBSF");

    //(imagen,transformacion(imagen,lut_sigmoidea(K))).display();


    return 0;
}

