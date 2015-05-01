#include "funciones.h"

using namespace std;

int main()
{
    CImg<float> img,hist,img_ap,img_eq,kernel;
    img.load("../../../../images/imagenB.tif");
    img.display("Original");

    CImgList<float> lista;

    lista.push_back(img);

    hist = img.get_normalize(0,255).get_histogram(256,0,255);
    hist.display_graph();

    //Procesamiento en cascada 1

    //Alta Potencia
    kernel = mask(3);
    img_ap = filtroAP(img,kernel,float(0));
    img.display("Alta potencia");

    hist = img_ap.get_normalize(0,255).get_histogram(256,0,255);
    hist.display_graph();

    //Ecualizacion
    img_eq = img_ap.get_equalize(256);
    img_eq.display("Ecualizando");

    hist = img_eq.get_normalize(0,255).get_histogram(256,0,255);
    hist.display_graph();

    lista.push_back(img_eq);

    //Procesamiento en cascada 2

    //Ecualizacion
    img_eq = img.get_equalize(256);
    img_eq.display("Ecualizando");

    hist = img_eq.get_normalize(0,255).get_histogram(256,0,255);
    hist.display_graph();

    //Alta Potencia
    kernel = mask(3);
    img_ap = filtroAP(img_eq,kernel,float(0));
    img.display("Alta potencia");

    hist = img_ap.get_normalize(0,255).get_histogram(256,0,255);
    hist.display_graph();

    lista.push_back(img_ap);

    lista.display();

    return 0;
}

