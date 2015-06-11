#include "funciones.h"

#define PATH "../../../Imagenes parcial/algo.jpg"

int main()
{
    //Carga de imagen a procesar
    CImg<float> original;
    original.load(PATH);
    original.display();

    return 0;
}

