#include <funciones.h>

using namespace std;

int main()
{
    const char* path = "../../../../images/cameraman.tif";
    CImg <double> img,img_aux,res_ab,res_ba,res_multi;
    CImg <double> mask1(1,3,1,1),mask2(3,1,1,1),mask3(1,1,1,1);
    img.load(path);

    //Llamo a la mascara para que me la arme, es mas sencillo
    //mask1=mask(3);
    //mask2=mask(3);
    mask3=mask(3);

    mask1.fill(0);
    mask2.fill(0);
    mask3.fill(0);

    //Mascara horizontal

    mask1(0,0)=0.25;
    mask1(0,1)=0.5;
    mask1(0,2)=0.25;

    //mascara Vertical

    mask2(0,0)=0.25;
    mask2(1,0)=0.5;
    mask2(2,0)=0.25;

    //Mascara producto mask1 y mask2

    mask3(0,1)= mask2(1,0);
    mask3(1,0)= mask1(1,0);
    mask3(1,1)= mask1(1,0)*mask2(0,1);
    mask3(1,2)= mask1(0,2);
    mask3(2,1)= mask2(2,0);

    //Filtro por mascara 1 y dsp 2

    img_aux=img.get_convolve(mask1);
    res_ab=img_aux.get_convolve(mask2);

    //Filtro por mascara 2 y dsp 1

    img_aux=img.get_convolve(mask2);
    res_ba=img_aux.get_convolve(mask1);

    //Filtro por el producto de las dos marcaras (LSI)

    res_multi = img.get_convolve(mask3);

    (img,res_ab,res_ba,res_multi).display("Original - Mask_ab - Mask_ba - Mask_Producto");


    return 0;

}

