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
    //Creo la mascara en base a las posiciones de los recuadros
    mask.fill(0);

    //Creo los puntos que definen cada cuadradito
    punto a,b,c,d,e,f,g,h,i,j;
    a.x=12;
    a.y=12;

    b.x=136;
    b.y=136;

    c.x=374;
    c.y=12;

    d.x=498;
    d.y=136;

    e.x=194;
    e.y=194;

    f.x=318;
    f.y=318;

    g.x=12;
    g.y=376;

    h.x=136;
    h.y=500;

    i.x=374;
    i.y=376;

    j.x=498;
    j.y=500;

    //Lleno la mascara con 0 en las posiciones de los cuadrados
    llenado_puntos(mask,a,b,true);//Cuadradito 1
    llenado_puntos(mask,c,d,true);//Cuadradito 2
    llenado_puntos(mask,e,f,true);//Cuadradito 3
    llenado_puntos(mask,g,h,true);//Cuadradito 4
    llenado_puntos(mask,i,j,true);//Cuadradito 5

    //mask.display();

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

