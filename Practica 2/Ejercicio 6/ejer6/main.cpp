#include "funciones.h"

using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[])
{
    const char* path = "../../../../images/cameraman.tif";
        CImg<unsigned char> img,img_b0,img_b1,img_b2,img_b3,img_b4,img_b5,img_b6,img_b7;
        img_b0=img_b1=img_b2=img_b3=img_b4=img_b5=img_b6=img_b7=img.load(path);
        vector<int> bit;
        cimg_forXY(img,i,j){
            bit= binario(img(i,j));
            img_b0(i,j) = bit[0]*pow(2.0,0.0);

        }

        //Calculamos el error cuadratico medio de cada imagen con la original
        cout<<endl<<endl<<"Errores cuadraticos medios:"<<endl;
        cout<<"Plano de bit 0: "<<img.MSE(img_b0)<<endl;
        //para hacerlo que cambie con el teclado
     /*   while(!displayImagen.is_closed()){
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
        }*/


        CImgList<unsigned char> disp(img_b0);
        disp.display("   Original   /     Bitplanes: bit 0 al 7  ");


    return 0;
}
