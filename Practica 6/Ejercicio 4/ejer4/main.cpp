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
//        CImg<float> img1, img2,img1b,img2b, copia_fase;
//        CImgList<float> fft1, fft2,fft1b,fft2b;
//        // cargamos 1 imagen
//        img1.load("../../../../images/img_degradada.tif");
//        // le calculamos la FFT
//        fft1=fourier(img1);
//filtro_notch2(CImg<double> img,bool pasabajo=1,int n=4,double D0=0.12,double U0=0.2,double V0=0)
//        //CImg<double>img_fil=filtro_notch2(img1,1,4,0.12,0.2,0);

//        (img1, fft1[2],img_fil).display("imagen original -- transformada");






    CImg<double> img1;
        img1.load("../../../../images/noisy_moon.jpg");
    //    img1.load("../../../../images/img_degradada.tif");
        CImgList<double> l=fourier(img1);
        l[2].display("magnitud");
            int x[3]={256*2,246*2,216*2};
            int y[3]={236*2,256*2,216*2};
            int w[3]={70,70,70};
    //	int x[2]={84*2,167*2};
    //	int y[2]={167*2,84*2};
    //	int w[2]={20,20};
        CImg<double> filtrada=filtro_notch(img1,x,y,w,2,3,false,20 );
        filtrada.normalize(0,255);
        (img1,filtrada).display("original -- filtrada");
        l=fourier(filtrada);
        l[2].display("magnitud");
        filtrada.display();


    return 0;
}

