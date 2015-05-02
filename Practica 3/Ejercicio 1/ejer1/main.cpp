#include <funciones.h>

using namespace std;

int main()
{

    const char* path = "../../../../images/cameraman.tif";
    CImg <unsigned char> img,img2;
    img.load(path);
    img2 = img.get_equalize(256,0,255);

    //get_histogram (nbins,mi,max)
    CImg <unsigned char> hist = img.get_histogram(50,0,255);
    CImg <unsigned char> hist2 = img2.get_histogram(50,0,255);
    //lista
    CImgList <unsigned char> lista;
    lista.push_back(img);
    lista.push_back(img2);

    lista.display();

    hist.display_graph();
    hist2.display_graph();

    return 0;
}

