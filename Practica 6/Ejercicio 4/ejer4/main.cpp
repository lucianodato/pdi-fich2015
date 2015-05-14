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
    CImg<float> img;
    img.load("../../../../images/img_degradada.tif");
    //CImgList<float> img_fft = fourier(img);
    //(img,img_fft[2]).display();

    (gaussian_notch(img,float(20),float(50),float(50),true)).display();

    return 0;
}

