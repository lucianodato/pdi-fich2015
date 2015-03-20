#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    const char* filename = cimg_option("-i","../../../../images/cameraman.tif","Image file\n");
    //Imagen color, 8 bits de profundidad por componente.
    //Asigna 0 a todos los pıxeles
    //Visualiza
    CImg<unsigned char> img1(filename);

    //Carga de disco
    CImgDisplay vent1(img1,"original");

    //Encontrar los pixeles de a cara del fotografo (version de libreria)
    CImg<unsigned char> img2 = img1.get_crop(94,38,130,80);
    CImgDisplay vent2(img2,"recortada");
}

