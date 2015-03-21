#include <iostream>
#include "CImg.h"
using namespace cimg_library;
using namespace std;

int main()
{


    CImg<unsigned char> imgOrig, imgQuant;
        CImgDisplay displayImagen;
        unsigned nBits=8;
        unsigned nLevels; // maxima cantidad de niveles segun el tipo de dato usado
        char window_title[50];

        imgOrig.load("../../../../images/huang2.jpg");
        imgQuant=imgOrig;
        displayImagen.assign(imgQuant);

        while(!displayImagen.is_closed()){
            displayImagen.wait(); // esperamos algun evento en el display
            if(displayImagen.is_keyARROWUP()){nBits+=1;}
            if(displayImagen.is_keyARROWDOWN()){nBits-=1;}
            if(nBits>8) nBits=8;
            if(nBits<1) nBits=1;
            nLevels=pow(2, nBits);


            imgQuant=imgOrig;
            imgQuant.quantize(nLevels);
            displayImagen.render(imgQuant);
            sprintf(window_title,"Quant %i bits",nBits);
            displayImagen.set_title(window_title);
            displayImagen.paint();
        }



    return 0;
}

