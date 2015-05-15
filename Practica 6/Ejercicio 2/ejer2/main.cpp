#include "funciones.h"

int main()
{
    CImg<float> img,img_noisy,img_denoised,img_denoised2;
    img.load("../../../../images/sangre.jpg");

    img_noisy = img.get_noise(10,0).get_noise(10,2);//0=gaussian, 1=uniform, 2=Salt and Pepper, 3=Poisson or 4=Rician
    (img,img_noisy).display();

    img_denoised = denoiseRGB(img_noisy,3,1);//Media Geometrica
    img_denoised2 = denoiseRGB(img_noisy,3,2,-1);//Media Armonica
    (img_denoised,img_denoised2).display();


    cout<<"Error cuadratico medio con la Ruidosa: "<<img.MSE(img_noisy)<<endl;
    cout<<"Error cuadratico medio con Media Geometrica: "<<img.MSE(img_denoised)<<endl;
    cout<<"Error cuadratico medio con Media Armonica: "<<img.MSE(img_denoised2)<<endl;

    return 0;
}

