#include <funciones.h>
int main()
{
        CImg<float> img, maskRGB, maskHSI,complemento;
        CImgDisplay displayImagen, displayMascaraRGB, displayMascaraHSI;
        float radioHSI=7, radioRGB=20;
        unsigned mx, my;

        img.load("../../../../images/futbol.jpg");


        complemento=complemento_color(img);
        img=complemento;
        displayImagen.assign(img);

        displayMascaraHSI.assign(img);
        displayMascaraHSI.set_title("HSI");
        displayMascaraRGB.assign(img);
        displayMascaraRGB.set_title("RGB");

        while(!displayImagen.is_closed() && !displayMascaraRGB.is_closed() && !displayMascaraHSI.is_closed()){
            displayImagen.wait(); // esperamos algun evento en el display
            if(displayImagen.button()==1){
                mx=displayImagen.mouse_x();
                my=displayImagen.mouse_y();

                //segmentacion de color RGB
                maskRGB=ColorMaskRGB(img,mx,my,radioRGB);
                displayMascaraRGB.render(maskRGB);
                displayMascaraRGB.paint();

                //segmentacion de color HSI
                maskHSI=ColorMaskHSI(img,mx,my,radioHSI);
                displayMascaraHSI.render(maskHSI);
                displayMascaraHSI.paint();
            }


        }
    return 0;
}

