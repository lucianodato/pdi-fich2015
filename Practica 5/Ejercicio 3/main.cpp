#include "../../funciones/funciones.h"

using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[]) {



        CImg<float> img1, img2,filtrada_espacial,filtrada_frecuencial,h;
        CImgList<float> lista1,lista2;

                // EJERCICIO ITEM 1

img1.load("../../images/Deforestacion.png");
h=mask(21);
//filtrado espacial
filtrada_espacial=img1.get_convolve(h);

filtrada_espacial.display("espacial");

//filtrado frecuencial
//aplicando el teorema de la convolucion directamente como dice la teoria(conv circular). multiplicar elemento a elemento
CImgList<float>H=h.get_FFT();
CImgList<float>F=img1.get_FFT();
CImgList<float>S(F);
cimg_forXY(F.at(0),i,j){
        S.at(0)(i,j)= H.at(0)(i,j)*F.at(0)(i,j);
        S.at(1)(i,j)= H.at(1)(i,j)*F.at(1)(i,j);
}
filtrada_frecuencial=S.get_FFT(true)[0];
filtrada_frecuencial.display();

return 0;

}
