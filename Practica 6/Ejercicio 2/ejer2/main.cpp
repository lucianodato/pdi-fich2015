#include "funciones.h"

int main()
{
    CImg<float> img,img_noisy,img_denoised,img_denoised2;
    img.load("../../../../images/sangre.jpg");

    img_noisy = img.get_noise(10,0).get_noise(10,2);//Cuando sigma es menor a 0 indica un porcentaje de ruido - 0 es gausseano 2 es impulsivo
    (img,img_noisy).display();

    img_denoised = denoiseRGB(img_noisy,10,1);//Media Geometrica
    img_denoised2 = denoiseRGB(img_noisy,10,2,-1);//Media Armonica
    (img_denoised,img_denoised2).display();


    cout<<"Error cuadratico medio con Media Geometrica: "<<img.MSE(img_denoised);
    cout<<"Error cuadratico medio con Media Armonica: "<<img.MSE(img_denoised2);

    return 0;
}

