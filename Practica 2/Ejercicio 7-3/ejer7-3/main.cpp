#include "funciones.h"

using namespace cimg_library;
using namespace std;

const char* path1 = "../../../../images/blister_incompleto.jpg";
//const char* path2 = "../../../../images/blister_incompleto.jpg";
int c=1,corteUmbral=210;
int main(int argc, char *argv[])
{

    cimg_usage("Ejercicio ");
    CImg<unsigned char> img;
    img.load(path1).channel(0);
    //pre- procesado: mejoro contraste(opcional) y aplico umbral
    CImg<unsigned char> lut(generar_lut_logb(c));
    img=transformacion(img,lut);
    img.threshold(corteUmbral);
    //aplico funcion blister
    vector<punto> vectorcoor=blister(img);
    if (vectorcoor.empty())
        cout<<"Blister Completo"<<endl;
              else {
              for (vector<punto>::iterator it = vectorcoor.begin();it != vectorcoor.end();++it)
                cout<<"Falta Pastilla en--> x:"<<(*it).x<<"--> y: "<<(*it).y<<endl;
}

    img.display("Imagen Blister");


    return 0;
}

