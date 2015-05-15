#include "funciones.h"
#include <unordered_map>
#include <functional> // For std::hash<std::string>.
#include <string>
#include <iostream>

///CImg<T>& noise	(sigma,noise_type = 0 )
///Add random noise to pixel values.
///Parameters
///sigma	Amplitude of the random additive noise. If sigma<0, it stands for a percentage of the global value range.
///noise_type	Type of additive noise (can be 0=gaussian, 1=uniform, 2=Salt and Pepper, 3=Poisson or 4=Rician).


int main()
{
    CImg<float> img,img_original,aux1,aux2;
    img_original.load("../../../../images/img.tif");
    img.load("../../../../images/img_degradada.tif");

    //img.load("../../../../images/noisy_moon.tif");
    //img.load("../../../../images/HeadCT_degradada.tif");
    CImgList<float> img_fft = fourier(img);
    (img,log(img_fft[0])).display();

    float c_x,c_y,rad;

    //La posta para localizar los picos es ver el espectro sin hacer shift y localizar las coordenadas donde se centra el ruido en el primer cuadrante

    //Centrando el notch en la frecuencia de ruido (Es mejor se elimina el ruido y no todas las altas frecuencias)
    c_x=70;
    c_y=90;
    rad=40;
    aux1 = filtrar(img,ideal_notch(img,rad,c_x,c_y,true));
    (img,aux1).display();

    //Centrando el anti-notch en la frecuencia de la imagen (Se pierde mucha definicion)
    c_x=2;
    c_y=2;
    rad=40;
    aux2 = filtrar(img,butter_notch(img,rad,3,c_x,c_y,false));
    (img,aux2).display();

    //Solo el ruido
    c_x=70;
    c_y=90;
    rad=40;
    (img,filtrar(img,ideal_notch(img,rad,c_x,c_y,false))).display();

    cout<<"Error cuadratico medio entre la original y la ruidosa: "<<img_original.MSE(img)<<endl;
    cout<<"Error cuadratico medio entre la original y filtrada por notch: "<<img_original.MSE(aux1)<<endl;
    cout<<"Error cuadratico medio entre la original y filtrada por anti-notch: "<<img_original.MSE(aux2)<<endl;

    return 0;
}

