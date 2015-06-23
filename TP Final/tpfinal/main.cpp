#include "funciones.h"

//Ruta de la imagen
///#define RUTA "../../../images/TP/BAJO_CONTRASTE/1.tif"
///#define RUTA "../../../images/TP/MEDIO_CONTRASTE/1.tif"
#define RUTA "../../../images/TP/ALTO_CONTRASTE/1.tif"

//Parametros Ecualizacion Generales
//N_NIVELES niveles finales deseado
//N_I nivel final inferior
//N_S nivel final inferior
#define N_NIVELES 256
#define N_I 0
#define N_S 255

//Parametros CLAHE
//CLIP_LIMIT nivel limite para clipping de histograma (0-1)
//T_VENT tamaño de ventana de analisis de CLAHE (mas grande mejor)
#define CLIP_LIMIT 0.01
#define T_VENT 30

//Parametros para sigmoidea
//K c   oeficiente de mezcla (0-1)
//NC_I Nivel de corte de aplicacion inferior
//NC_S Nivel de corte de aplicacion superior
#define K 0.2
#define NC_I 50
#define NC_S 200

//HE - Histogram equalization
//BBHE - Bi-Histogram equalization
//CLAHE - Contrast-Limited Histrogram equalization
//ACEBSF - Adaptive Contrast Enhancement based on modified Sigmoid Function equalization


int main()
{
    CImg<double> imagen(RUTA);

    CImg<double> imagen_he =ecualizar_comun(imagen,N_NIVELES);
    CImg<double> imagen_bbhe =ecualizar_bbhe(imagen,N_NIVELES);
    CImg<double> imagen_clahe =ecualizar_clahe(imagen,N_NIVELES,N_I,N_S,T_VENT,CLIP_LIMIT);
    CImg<double> imagen_acebsf =ecualizar_acebsf(imagen,K,NC_I,NC_S,N_NIVELES,N_I,N_S,T_VENT,CLIP_LIMIT);

    //Muestro el resultado
    (imagen,imagen_he,imagen_bbhe,imagen_clahe,imagen_acebsf).display();

    //Guardo el resultado
    imagen_he.save_tiff("../../../images/TP/ALTO_CONTRASTE/2.tif");
    imagen_bbhe.save_tiff("../../../images/TP/ALTO_CONTRASTE/3.tif");
    imagen_clahe.save_tiff("../../../images/TP/ALTO_CONTRASTE/4.tif");
    imagen_acebsf.save_tiff("../../../images/TP/ALTO_CONTRASTE/5.tif");



    //Muestro el histograma de las ecualizaciones resultantes y luego guardo su resultado
    imagen.get_histogram(N_NIVELES).display_graph("Histograma de la Original");
    imagen_he.get_histogram(N_NIVELES).display_graph("Histograma HE");
    imagen_bbhe.get_histogram(N_NIVELES).display_graph("Histograma BBHE");
    imagen_clahe.get_histogram(N_NIVELES).display_graph("Histograma CLAHE");
    imagen_acebsf.get_histogram(N_NIVELES).display_graph("Histograma ACEBSF");

    cout<<endl<<endl;
    cout<<"       ----------Resultados MSE----------"<<endl;
    cout<<"-----------------------------------------------"<<endl;
    cout<<"El MSE con respecto a HE es: "<<imagen.MSE(imagen_he)<<endl;
    cout<<"El MSE con respecto a BBHE es: "<<imagen.MSE(imagen_bbhe)<<endl;
    cout<<"El MSE con respecto a CLAHE es: "<<imagen.MSE(imagen_clahe)<<endl;
    cout<<"El MSE con respecto a ACEBSF es: "<<imagen.MSE(imagen_acebsf)<<endl;
    cout<<"-----------------------------------------------"<<endl;
    cout<<endl<<endl;


    cout<<endl<<endl;
    cout<<"       ----------Resultados ENTROPIA DISCRETA----------"<<endl;
    cout<<"-----------------------------------------------"<<endl;
    cout<<"la ED de la imagen orginal es:"<<entropia_discreta(imagen)<<endl;
    cout<<"la ED respecto a HE es: "<<entropia_discreta(imagen_he)<<endl;
    cout<<"la ED respecto a BBHE es: "<<entropia_discreta(imagen_bbhe)<<endl;
    cout<<"la ED respecto a CLAHE es: "<<entropia_discreta(imagen_clahe)<<endl;
    cout<<"la ED respecto a ACEBSF es: "<<entropia_discreta(imagen_acebsf)<<endl;
    cout<<"-----------------------------------------------"<<endl;
    cout<<endl<<endl;

    cout<<endl<<endl;
    cout<<"       ----------Resultados INTERCEPCION ENTRE HISTOGRAMAS----------"<<endl;
    cout<<"-----------------------------------------------"<<endl;
    cout<<"la HI respecto a HE con la original es: "<<interseccion_histograma(imagen,imagen_he)<<endl;
    cout<<"la HI respecto a BBHE con la original es: "<<interseccion_histograma(imagen,imagen_bbhe)<<endl;
    cout<<"la HI respecto a CLAHE con la original es: "<<interseccion_histograma(imagen,imagen_clahe)<<endl;
    cout<<"la HI respecto a ACEBSF con la original es: "<<interseccion_histograma(imagen,imagen_acebsf)<<endl;
    cout<<"-----------------------------------------------"<<endl;
    cout<<endl<<endl;

    return 0;
}

