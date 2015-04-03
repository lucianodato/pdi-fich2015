#include "funciones.h"

using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[])
{
    const char* path = "../../../../images/cameraman.tif";
    int nBits = 7;
    char window_title[50];

    CImg<unsigned char> img;
    img.load(path);

    CImgList<unsigned char> disp = bitlist(img);
    //disp.display("   Original   /     Bitplanes: bit 0 al 7  ");

    //Calculamos el error cuadratico medio de cada imagen con la original
    //cout<<endl<<endl<<"Errores cuadraticos medios:"<<endl;
    //cout<<"Plano de bit 0: "<<img.MSE(img_b0)<<endl;
    //para hacerlo que cambie con el teclado

    CImgDisplay displayImagen;
    CImg<unsigned char> auxiliar(img);
    //auxiliar.fill(0);
    displayImagen.assign(auxiliar);


    while(!displayImagen.is_closed()){
        displayImagen.wait(); // esperamos algun evento en el display
        if(displayImagen.is_keyARROWUP()){
           auxiliar.fill(0);
            nBits+=1;
            if(nBits>7) nBits=7;
            if(nBits<0) nBits=0;
            for (int k = 7 ;k>nBits;k--){
                auxiliar+=disp[k];
            }
        }
        if(displayImagen.is_keyARROWDOWN()){
            auxiliar.fill(0);
            nBits-=1;
            if(nBits>7) nBits=7;
            if(nBits<0) nBits=0;
            for (int k = 7 ;k>nBits;k--){
                auxiliar+=disp[k];
            }

        }

        displayImagen.render(auxiliar);
        sprintf(window_title," %i bits",nBits+1);
        displayImagen.set_title(window_title);
        displayImagen.paint();
        //auxiliar.fill(0);
    }


    return 0;
}
