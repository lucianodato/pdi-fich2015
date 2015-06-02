#include "funciones.h"

int main()
{
    CImg<double> image("../../../../images/futbol.jpg");
    CImg<double> img=image.get_noise(25,0);//gaussiano
    img.noise(5,2);//impulsivo

    CImg<double> imgFiltrada=denoise(img,3,10,0,4);

    cout<<"********ECM*********\n";
    cout<<"ECM limpia-degradada: "<<image.MSE(img)<<endl;
    cout<<"ECM limpia-filtrada : "<<image.MSE(imgFiltrada)<<endl<<endl;
    (image,img,imgFiltrada).display("original -- img ruidosa  -- imgFiltrada");

    return 0;
}

