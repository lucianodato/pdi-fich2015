#include "funciones.h"

using namespace cimg_library;
using namespace std;

int corrimiento=1;
//

int main(int argc, char *argv[])
{

    CImg<unsigned char> img;
    img.load("../../../../images/coins.tif");//carga imagen en memo
    CImg<unsigned char> img_neg(img.width(),img.height(),1,1);//
    CImg<unsigned char> img_emboss(img.width(),img.height(),1,1);
    img_neg = negativo(img);
    img_emboss=sumaImg(img, img_neg,corrimiento);//suma a img su negativo un poquito desplazado
    //Visualiza
    CImgList<unsigned char> disp(img, img_neg, img_emboss);
    disp.display("Original- Negativo-Filtrado Emboss");

    return 0;
}
