#include "funciones.h"

using namespace std;

int main()
{
    CImg<float> f1,f2,f3,f4,f5,f6,f7,f8,f9,f10;
    CImgList<float> fft_f1,fft_f2,fft_f3,fft_f4,fft_f5,fft_f6,fft_f7,fft_f8,fft_f9,fft_f10;
    f1.load("../../../../images/fourier/f1.jpg");
    f2.load("../../../../images/fourier/f2.jpg");
    f3.load("../../../../images/fourier/f3.jpg");
    f4.load("../../../../images/fourier/f4.jpg");
    f5.load("../../../../images/fourier/f5.jpg");
    f6.load("../../../../images/fourier/f6.jpg");
//    f7.load("../../../../images/fourier/f7.jpg");
//    f8.load("../../../../images/fourier/f8.jpg");
//    //f9.load("../../../../images/fourier/f9.jpg");
    //f10.load("../../../../images/fourier/f10.jpg");
    fft_f1=fourier(f1);
    fft_f2=fourier(f2);
    fft_f3=fourier(f3);
    fft_f4=fourier(f4);
    fft_f5=fourier(f5);
    fft_f6=fourier(f6);
//    fft_f7=fourier(f7);
//    fft_f8=fourier(f8);
//    fft_f9=fourier(f9);
//    fft_f10=fourier(f10);
    (f1,fft_f1[2]).display();
    (f2,fft_f2[2]).display();
    (f3,fft_f3[2]).display();
    (f4,fft_f4[2]).display();
    (f5,fft_f5[2]).display();
    (f6,fft_f6[2]).display();
//    (f7,fft_f7[2]).display();
//    (f8,fft_f8[2]).display();
//    (f9,fft_f9[2]).display();
//    (f10,fft_f10[2]).display();


    return 0;
}

