#include "funciones.h"
int main()
{
    CImg<float> img,img_noisy,img_denoised1,img_denoised2,img_denoised3,img_denoised4,img_denoised5;
    img.load("../../../../images/sangre.jpg");

    img_noisy = img.get_noise(10,0).get_noise(10,2);//Cuando sigma es menor a 0 indica un porcentaje de ruido - 0 es gausseano 2 es impulsivo
    (img,img_noisy).display();

    img_denoised1 = denoiseRGB(img_noisy,3,1);//Media Geometrica
    img_denoised2 = denoiseRGB(img_noisy,3,2,-1);//Media Armonica
    img_denoised3 = denoiseRGB(img_noisy,3,3);//Mediana
    img_denoised4 = denoiseRGB(img_noisy,3,4);//Media Punto Medio
    img_denoised5 = denoiseRGB(img_noisy,3,5,0,4);//Media Alfa Recortada d = la cantidad de pixeles de la ventana que puede recortar


    cout<<"Error cuadratico medio con la Ruidosa: "<<img.MSE(img_noisy)<<endl;
    cout<<"Error cuadratico medio con Media Geometrica: "<<img.MSE(img_denoised1)<<endl;
    cout<<"Error cuadratico medio con Media Armonica: "<<img.MSE(img_denoised2)<<endl;
    cout<<"Error cuadratico medio con Media Armonica: "<<img.MSE(img_denoised3)<<endl;
    cout<<"Error cuadratico medio con Media Armonica: "<<img.MSE(img_denoised4)<<endl;
    cout<<"Error cuadratico medio con Media Armonica: "<<img.MSE(img_denoised5)<<endl;

    (img_denoised1,img_denoised2,img_denoised3,img_denoised4,img_denoised5).display();

    return 0;
}

