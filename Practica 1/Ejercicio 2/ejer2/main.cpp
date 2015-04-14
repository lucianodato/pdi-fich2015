#include <iostream>
#include "CImg.h"


using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[])
{
    const char* filename = cimg_option("-i","../../../../images/cameraman.tif","Image file\n");
    //Cargo el path de la imagen
    CImg<unsigned char> img1(filename);
    //Usando el print sin stats
    img1.print("Con Print() - sin stats ",0);
    cout<<endl<<endl;
    //Usando el print con stats
    img1.print("Con Print() ");
    cout<<endl<<endl;
    //Usando display

    return 0;
}


