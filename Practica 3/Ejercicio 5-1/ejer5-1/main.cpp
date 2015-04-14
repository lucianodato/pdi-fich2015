#include "funciones.h"

int main()
{
    const char* path = "../../../../images/cuadros.tif";
    CImg <float> img;
    img.load(path);

    CImg<float> mask(img.width(),img.height());
    CImg<float> eq(img.width(),img.height()),eq_global(img.width(),img.height());

    //Ecualizacion
    eq_global = img.get_equalize(256,0,255);

    //Calculo los histogramas
    CImg <float> hist_global = img.get_histogram(256,0,255);
    CImg <float> hist_eq_global = eq_global.get_histogram(256,0,255);


    //Muestro en una lista
    CImgList<float> lista_global(img,eq_global,construye_histograma(hist_global),construye_histograma(hist_eq_global));
    lista_global.display("Original - Equalizada - Hist Orig - Hist Eq");

    //Procesamiento por enmascaramiento de regiones
    //Creo la mascara en base a aislar los cuadraditos con threshold
    mask = negativo(img.get_threshold(100));

    //Ecualizo solo en los cuadrados
    eq = multiplicacion(img,mask).get_equalize(256,0,255);

    //Reemplazo los cuadraditos de la original por los ecualizados
    eq = multiplicacion(img,negativo(mask)) + eq;

    //Calculo los histogramas
    CImg <float> hist_eq = eq.get_histogram(256,0,255);

    //Muestro en una lista
    CImgList<float> lista_por_zona(img,eq,construye_histograma(hist_global),construye_histograma(hist_eq));
    lista_por_zona.display("Original - Equalizada - Hist Orig - Hist Eq Por zona");

    return 0;
}

