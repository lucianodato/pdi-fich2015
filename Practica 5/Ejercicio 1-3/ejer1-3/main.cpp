#include "funciones.h"

using namespace std;

int main()
{
    CImg<float> f1,f2,f3,f4,f5,f6;
    CImgList<float> fft_f1,fft_f2,fft_f3,fft_f4,fft_f5,fft_f6;
    f1.load("../../../../images/fourier/f1.jpg");
    f2.load("../../../../images/fourier/f2.jpg");
    f3.load("../../../../images/fourier/f3.jpg");
    f4.load("../../../../images/fourier/f4.jpg");
    f5.load("../../../../images/fourier/f5.jpg");
    f6.load("../../../../images/fourier/f6.jpg");
    fft_f1=fourier(f1);
    fft_f2=fourier(f2);
    fft_f3=fourier(f3);
    fft_f4=fourier(f4);
    fft_f5=fourier(f5);
    fft_f6=fourier(f6);
    (f1,fft_f1[2]).display();
    (f2,fft_f2[2]).display();
    (f3,fft_f3[2]).display();
    (f4,fft_f4[2]).display();
    (f5,fft_f5[2]).display();
    (f6,fft_f6[2]).display();


    return 0;
}

