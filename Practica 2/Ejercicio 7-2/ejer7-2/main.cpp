#include "funciones.h"

using namespace cimg_library;
using namespace std;

//Coordenadas de los puntos para aplicar la mascara (la saque con gimp)
int m1_x = 197,m1_y= 98, m2_x = 246, m2_y = 153;
int tamanio_de_mediana = 1;

const char* path1 = "../../../../images/a7v600-SE(RImpulsivo).gif";
const char* path2 = "../../../../images/a7v600-SE.gif";
const char* path3 = "../../../../images/a7v600-X(RImpulsivo).gif";
const char* path4 = "../../../../images/a7v600-X.gif";


//Establecer una forma de identificar cada imagen (Por ejemplo con el valor medio de pixel de los disipadores)
CImg<unsigned char> img1,img2;
const double placa1 = img1.load(path2).get_crop(m1_x,m1_y,m2_x,m2_y).mean();
const double placa2 = img1.load(path4).get_crop(m1_x,m1_y,m2_x,m2_y).mean();

int main()
{
    //Carga de la imagen
    CImgList<unsigned char> imagenes;
    CImg<unsigned char> img;
    CImg<unsigned char> img_mask;
    img.load(path4);
    imagenes.push_back(img);

    //Limpiar ruido impulsivo
    CImg<unsigned char> img_limpia = img.get_blur_median(tamanio_de_mediana);//Filtro anti salt and pepper
    imagenes.push_back(img_limpia);

    //Enmascarar la imagen en la parte de los disipadores
    img_mask = img.get_crop(m1_x,m1_y,m2_x,m2_y);

    cout<<"El promedio de pixel arrojado es "<<img_mask.mean()<<endl<<endl;
    cout<<"El promedio de valor de pixel de a7v600-SE es "<<placa1<<endl;
    cout<<"El promedio de valor de pixel de a7v600-X es "<<placa2<<endl<<endl;

    //Comparar la imagen con los datos
    if (img_mask.mean() >= placa1){
        cout<<"La placa identificada es a7v600-SE"<<endl;
    }
    else
    {
        cout<<"La placa identificada es a7v600-X"<<endl;
    }

    //Mostrar los resultados
    imagenes.display();
    return 0;
}

