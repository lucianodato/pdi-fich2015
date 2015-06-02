#include "funciones.h"

int main()
{
    CImg<double> image("../../../../images/futbol.jpg");
    CImg<double> img=image.get_noise(25,0);//gaussiano
    img.noise(5,2);//impulsivo

//    CImg<double> imgFiltrada=denoise(img,3,10,0,4);

//    cout<<"********ECM*********\n";
//    cout<<"ECM limpia-degradada: "<<image.MSE(img)<<endl;
//    cout<<"ECM limpia-filtrada : "<<image.MSE(imgFiltrada)<<endl<<endl;
//    (image,img,imgFiltrada).display("original -- img ruidosa  -- imgFiltrada");


    //Pruebo el pseudoinverso
    img = filtrar3(image,gaussian_mask(image,25.0));
    CImg<double> imgArreglada = filtrado_pseudoinverso3(img,gaussian_mask(image,25.0),0.0000001);

    cout<<"********ECM*********\n";
    cout<<"ECM limpia-degradada: "<<image.MSE(img)<<endl;
    cout<<"ECM limpia-filtrada : "<<image.MSE(imgArreglada)<<endl<<endl;
    (image,img,imgArreglada).display("original -- img desenfocada  -- imgFiltrada");


    return 0;
}

