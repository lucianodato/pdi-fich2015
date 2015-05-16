#include "funciones.h"
int main()
{
    CImg<float> img,img_noisy,img_denoised1,img_denoised2,img_denoised3,img_denoised4,img_denoised5,img_denoised_mediana_punto_medio;
    img.load("../../../../images/sangre.jpg");

    img_noisy = img.get_noise(10,0).get_noise(10,2);//Cuando sigma es menor a 0 indica un porcentaje de ruido - 0 es gausseano 2 es impulsivo
    (img,img_noisy).display("original - ruidosa");

    img_denoised1 = denoiseRGB(img_noisy,3,1);//Media Geometrica
    img_denoised2 = denoiseRGB(img_noisy,3,2,-1);//Media Armonica
    img_denoised3 = denoiseRGB(img_noisy,3,3);//Mediana
    img_denoised4 = denoiseRGB(img_noisy,3,4);//Media Punto Medio
    img_denoised5 = denoiseRGB(img_noisy,3,5,0,4);//Media Alfa Recortada d = la cantidad de pixeles de la ventana que puede recortar
    img_denoised_mediana_punto_medio = denoiseRGB(img_denoised3,3,4);//aplico primero mediana luego al resultado aplico punto medio

    cout<<"Error cuadratico medio con la Ruidosa: "<<img.MSE(img_noisy)<<endl;
    cout<<"Error cuadratico medio con Media Geometrica: "<<img.MSE(img_denoised1)<<endl;
    cout<<"Error cuadratico medio con Media Armonica: "<<img.MSE(img_denoised2)<<endl;
    cout<<"Error cuadratico medio con Media Mediana: "<<img.MSE(img_denoised3)<<endl;
    cout<<"Error cuadratico medio con Media punto medio: "<<img.MSE(img_denoised4)<<endl;
    cout<<"Error cuadratico medio con Media alfa refortado: "<<img.MSE(img_denoised5)<<endl;
    cout<<"Error cuadratico medio con 1ro:mediana 2do:punto medio en cadena : "<<img.MSE(img_denoised5)<<endl;

    (img,img_denoised1,img_denoised2,img_denoised3,img_denoised4,img_denoised5,img_denoised_mediana_punto_medio).display("original - mGeometrica - mArmonica - mMediana - mPuntoMedio - mAlfaRecortado");

    return 0;
}

