#include "funciones.h"
int main()
{
    //DEFINICION Y CARGA DE IMAGEN
    int M=256,N=256;
    CImg<double>img("../../../../images/huang3_movida.tif");
    img.resize(M,N);
    img.display("imagen");


    //DEFINICION DE FILTRO
    //double T=0.11;
    double pi=3.14159265;
    double a=0.7;
    double b=0.9;

    int P=2*M;
    int Q=2*N;

    CImg<double>U(P,Q,1,1),V(P,Q,1,1);
    CImg<double>D(P,Q,1,1);
    CImg<double> Hi(P,Q,1,1);
    CImg<double> Hr(P,Q,1,1);
    std::complex<double> val,J(0.0,1.0);
    for (int i=0;i<P;i++){
        for (int j=0;j<Q;j++){
            //Variables de frecuencia U y V:
            U(i,j)=-1.+i*2./P;
            V(i,j)=-1.+j*2./Q;
            //FILTRO
            val=(1/(pi*(U(i,j)*a+V(i,j)*b)))*sin(pi*(U(i,j)*a+V(i,j)*b))*exp(J*pi*(U(i,j)*a+V(i,j)*b));
            Hr(i,j)=real(val);
            Hi(i,j)=imag(val);
        }
    }



    //OBTENER MAGNITUD Y FASE DE H
    //Definicion de la constante imaginaria I=sqrt(-1):
    complex<double>I(0.,1.);
    CImg<double>magnitudH(P,Q,1,1);
    CImg<double>faseH(P,Q,1,1);
    for (int i=0;i<P;i++){
        for (int j=0;j<Q;j++){
            magnitudH(i,j)=sqrt(pow(Hr(i,j),2)+pow(Hi(i,j),2));
            complex<double>complejo=Hr(i,j)+I*Hi(i,j);
            faseH(i,j)=arg(complejo);
        }
    }

    magnitudH.display("magnitud H");


    //APLICACION DE ZERO PADDING A LA IMAGEN CARCGADA
    img.resize(P,Q,-100,-100,0);
    img.display("IMAGEN ORIGINAL CON ZPADDING");




    //Transformada directa y obtencion de las partes real e imaginaria
    CImgList<double>TDF_img=img.get_FFT();
    cimglist_apply(TDF_img,shift)(P/2,Q/2,0,0,2);
    CImg<double>TDF_real=TDF_img[0];
    CImg<double>TDF_imaginaria=TDF_img[1];



    //OBTENER MAGNITUD Y FASE
    //Definicion de la constante imaginaria I=sqrt(-1):

    CImg<double>magnitud(P,Q,1,1);
    CImg<double>fase(P,Q,1,1);
    for (int i=0;i<P;i++){
        for (int j=0;j<Q;j++){
            magnitud(i,j)=sqrt(pow(TDF_real(i,j),2)+pow(TDF_imaginaria(i,j),2));
            complex<double>complejo=TDF_real(i,j)+I*TDF_imaginaria(i,j);
            fase(i,j)=std::arg(complejo);
        }
    }
    CImg<double> muestra_magnitud=magnitud;
(muestra_magnitud+0.001).get_log().display("magnitud Espectro Frecuencias img zeroPadding");

    //SE LLEVA A CABO EL FILTRADO
    CImg<double> magnitud_filtrada(P,Q,1,1);
    CImg<double> fase_filtrada(P,Q,1,1);
    cimg_forXY(magnitud,x,y){


            magnitud_filtrada(x,y)=(double)magnitud(x,y)/(double)magnitudH(x,y);
        fase_filtrada(x,y)=fase(x,y)-faseH(x,y);
    }



    //PASAR DE MAGNITUD Y FASE A FORMA BINOMIAL USANDO LA MAGNITUD FILTRADA
    CImg<double>real(P,Q,1,1);
    CImg<double>imaginaria(P,Q,1,1);
    for (int i=0;i<P;i++){
        for (int j=0;j<Q;j++){
            real(i,j)=std::real(magnitud_filtrada(i,j)*exp(I*fase_filtrada(i,j)));
            imaginaria(i,j)=std::imag(magnitud_filtrada(i,j)*exp(I*fase_filtrada(i,j)));
        }
    }

    (magnitud_filtrada+0.0001).get_log().display("magnitud filtrada");

    //RECUPERAR IMAGEN FILTRADA A PARTIR DE SU TRANSFORMADA FILTRADA
    CImgList<double> TDF_img_filtrada=(real,imaginaria);
    cimglist_apply(TDF_img_filtrada,shift)(-P/2,-Q/2,0,0,2);


    CImg<double> img_filtrada=TDF_img_filtrada.get_FFT(true)[0];




    img_filtrada.display("IMAGEN FILTRADA"); //NO ANDAAAAAAAA WTFFFFF!!!





    system("pause");
    return 0;
}

