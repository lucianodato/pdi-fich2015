#include "funciones.h"

int main()
{
    CImg<float> img_original,img_noisy,img_denoised,img_denoised2;
    img_original.load("../../../../images/sangre.jpg");
    CImg<float> img(img_original.width(),img_original.height(),1,1);

    img = img_original.RGBtoHSI().get_channel(2).get_normalize(0,255); //Img en escala de grisis. Canal Intensidad (2)

    img_noisy = img.get_noise(5,0).get_noise(5,1);//0=gaussian, 1=uniform, 2=Salt and Pepper, 3=Poisson or 4=Rician
    (img,img_noisy).display("Original - Noissy");

    //img_denoised = denoiseRGB(img_noisy,3,1);//Media Geometrica
    //img_denoised2 = denoiseRGB(img_noisy,3,2,-1);//Media Armonica
    img_denoised = denoise(img_noisy,3,1);
    img_denoised2 = denoise(img_noisy,3,2,-1);
    (img,img_denoised,img_denoised2).display("Original - Media Geometrica - Media Armonica (-1)");

    cout<<"Error cuadratico medio con la Ruidosa: "<<img.MSE(img_noisy)<<endl;
    cout<<"Error cuadratico medio con Media Geometrica: "<<img.MSE(img_denoised)<<endl;
    cout<<"Error cuadratico medio con Media Armonica: "<<img.MSE(img_denoised2)<<endl;

    return 0;
}

