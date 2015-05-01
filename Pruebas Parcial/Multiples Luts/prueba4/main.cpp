#include "funciones.h"

using namespace std;

int main()
{
    CImg<float> img,hist,img_lut;
    img.load("../../../../images/huang3.jpg");
    img.display("Original");

    hist = img.get_normalize(0,255).get_histogram(50,0,255);
    hist.display_graph();

    img_lut = transformacion(img,generar_lut_logb(float(1),true));
    img_lut.display();

    hist = img_lut.get_normalize(0,255).get_histogram(255,0,255);
    hist.display_graph();


    img_lut = transformacion(img_lut,generar_lut_logb(float(1),true));
    img_lut.display();

    hist = img_lut.get_normalize(0,255).get_histogram(255,0,255);
    hist.display_graph();

    img_lut = transformacion(img_lut,generar_lut_logb(float(1),true));
    img_lut.display();

    hist = img_lut.get_normalize(0,255).get_histogram(255,0,255);
    hist.display_graph();

    return 0;
}

