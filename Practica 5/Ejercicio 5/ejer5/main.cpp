#include "funciones.h"

using namespace std;
float orden=2.0;
int main()
{
    //item 1,2,4 del ejercicio 5


        CImg<float> img1,img2,img3,img4, mask,mask2,mask3;
        CImgDisplay d, m,m2,m3,o,r,t;
        CImgList<float> fft;
        img1.load("../../../../images/cameraman.tif");
        fft=fourier(img1);
        d.assign(img1, "imagen filtrada - ideal_mask");
        r.assign(img1, "imagen filtrada - butterworth_mask");
        t.assign(img1, "imagen filtrada - gauss_mask");
        o.assign(img1, "imagen original");
        m.assign(fft[0], "mascara ideal");
        m2.assign(fft[0], "mascara butter");
        m3.assign(fft[0], "mascara gauss");
        int w_2=img1.width()/2, h_2=img1.height()/2, dist;
        while(!d.is_closed() && !m.is_closed()){
            if(m.button()!=0){
                ///distancia euclidea
                //float D=sqrt(pow(i-M/2,2)+pow(j-N/2,2));
                dist=sqrt(powf(m.mouse_x()-w_2, 2)+powf(h_2-m.mouse_y(), 2));
                mask=ideal_mask(img1,(float) dist,true);
                mask2=butterworth_mask(img1,(float) dist,(float)orden,true);
                mask3=gaussian_mask(img1,(float) dist,true);
                m.render(mask.get_normalize(0,255));
                m2.render(mask2.get_normalize(0,255));
                m3.render(mask3.get_normalize(0,255));
                img2=filtrar(img1,mask);
                img3=filtrar(img1,mask2);
                img4=filtrar(img1,mask3);
                m.paint();
                m2.paint();
                m3.paint();
                d.render(img2);
                d.paint();
                r.render(img3);
                r.paint();
                t.render(img4);
                t.paint();


            }
        }

    return 0;
}

