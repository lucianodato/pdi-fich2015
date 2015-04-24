#include <funciones.h>
int main()
{
    CImg<float> img, copiaRGB, copiaHSI;
        CImgDisplay displayImagen, displayMascaraRGB, displayMascaraHSI;
        float r0, g0, b0;
        float radioHSI=7, radioRGB=20;
        unsigned mx, my;

        img.load("../../../../images/Busqueda_histograma/futbol.jpg");
        displayImagen.assign(img);


        copiaHSI=img;
        displayMascaraHSI.assign(copiaHSI);
        displayMascaraHSI.set_title("HSI");
        copiaRGB=img;
        displayMascaraRGB.assign(copiaRGB);
        displayMascaraRGB.set_title("RGB");

        while(!displayImagen.is_closed() && !displayMascaraRGB.is_closed() && !displayMascaraHSI.is_closed()){
            displayImagen.wait(); // esperamos algun evento en el display
            if(displayImagen.button()==1){
    //			unsigned mx, my;
                mx=displayImagen.mouse_x();
                my=displayImagen.mouse_y();
                //my=img.height()-my;
                img.RGBtoHSI();
                r0=img(mx, my, 0, 0);
                g0=img(mx, my, 0, 1);
                b0=img(mx, my, 0, 2);
                img.HSItoRGB();
                ColorMaskRGB(copiaRGB,mx,my,radioRGB);

                displayMascaraRGB.render(copiaRGB);
                displayMascaraRGB.paint();


                copiaHSI=img;
                copiaHSI.RGBtoHSI();
                ColorMaskHSI(copiaHSI, r0, g0, radioHSI);
                copiaHSI.HSItoRGB();
                displayMascaraHSI.render(copiaHSI);
                displayMascaraHSI.paint();
            }

            if(displayMascaraHSI.button()==2){
                cout<<"Ingrese el radio de la esfera HS: ";
                cin>>radioHSI;
                copiaHSI=img;
                copiaHSI.RGBtoHSI();
                ColorMaskHSI(copiaHSI, r0, g0, radioHSI);
                copiaHSI.HSItoRGB();
                displayMascaraHSI.render(copiaHSI);
                displayMascaraHSI.paint();
            }

            if(displayMascaraRGB.button()==2){
                cout<<"Ingrese el radio de la esfera RGB: ";
                cin>>radioRGB;
                copiaRGB=img;
                ColorMaskRGB(copiaRGB,mx,my,radioRGB);

                displayMascaraRGB.render(copiaRGB);
                displayMascaraRGB.paint();
            }
        }
    return 0;
}

