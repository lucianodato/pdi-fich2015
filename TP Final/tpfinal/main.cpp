#include "funciones.h"

int main()
{
    CImg<double> imagen("../../../images/camaleon.tif");
    (imagen,equalizar_comun(imagen,256)).display();

    return 0;
}

