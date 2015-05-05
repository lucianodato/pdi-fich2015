#include "funciones.h"

using namespace std;

int main()
{
    CImg<double>img("../../../../images/reunion.tif");
    CImg<double>salida=filtradoHomomorficoCompleto(img,50,0.6,1.0,1);


    //_frec_corte = 150;
    // gamma_l = 0.9;
    //gamma_h = 1.1
    // c = 1.0
    //Obtenemos un filtro gaussiano pasa altos



    (img,salida).display();

    return 0;
}

