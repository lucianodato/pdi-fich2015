#include <funciones.h>
float thresh = 20.0;

int main()
{
    const char* path = "../../../../images/rio.jpg";
    CImg<float> img,hist;
    img.load(path);


    //Muestro el histograma
    hist = img.get_histogram(256,0,255);
    //hist.display_graph();

    //Creo una imagen resutado con los canales rgb iguales a la imagen original
    CImg<float> result(img.width(),img.height(),img.depth(),3);

    cimg_forXYZ(img,i,j,k){
        result(i,j,k,0) = img(i,j,k,0);
        result(i,j,k,1) = img(i,j,k,0);
        result(i,j,k,2) = img(i,j,k,0);
    }

    //Recorro original la imagen y en funcion de la intesidad coloreo la imagen resultado
    cimg_forXYZ(img,i,j,k){
        if(img(i,j) <= thresh){
            //Amarillo es 255,255,0 en los canales rgb
            result(i,j,k,0) = 255.0;
            result(i,j,k,1) = 255.0;
            result(i,j,k,2) = 0.0;
        }
    }

    result.display();

    return 0;
}

