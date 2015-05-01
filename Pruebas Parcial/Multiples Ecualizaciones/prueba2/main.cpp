#include "funciones.h"

using namespace std;

int main()
{

    CImg<float> img,hist,img_eq;
    img.load("../../../../images/huang3.jpg");
    img.display("Original");

    hist = img.get_normalize(0,255).get_histogram(50,0,255);
    hist.display_graph();

    //Ecualizacion
    img_eq = img.get_equalize(256);
    img_eq.display("Ecualizando");

    hist = img_eq.get_normalize(0,255).get_histogram(50,0,255);
    hist.display_graph();

    //Ecualizacion
    img_eq = img_eq.get_equalize(256);
    img_eq.display("Ecualizando");

    hist = img_eq.get_normalize(0,255).get_histogram(50,0,255);
    hist.display_graph();

    //Ecualizacion
    img_eq = img_eq.get_equalize(256);
    img_eq.display("Ecualizando");

    hist = img_eq.get_normalize(0,255).get_histogram(50,0,255);
    hist.display_graph();



    return 0;
}

