#include "funciones.h"

int main()
{
    CImg<double> image("../../../../images/futbol.jpg");
    CImg<double> img=image.get_noise(25,0);
    img.noise(20,2);
    CImg<double> img_noisy=img;
    CImg<double> imgR=filter(img.get_channel(0),4,10);
    CImg<double> imgB=filter(img.get_channel(1),4,10);
    CImg<double> imgG=filter(img.get_channel(2),4,10);

    CImg<double> imgFiltrada;
    ComposeRGB(imgFiltrada,imgR,imgG,imgB);

    cout<<"********ECM*********\n";
    cout<<"ECM limpia-degradada: "<<image.MSE(img_noisy)<<endl;
    cout<<"ECM limpia-filtrada : "<<image.MSE(img)<<endl<<endl;
    //CImgDisplay v1(img_noisy),v2(img);
    (image,img_noisy,imgFiltrada).display("original -- img_noisy  -- imgFiltrada");

    return 0;
}

