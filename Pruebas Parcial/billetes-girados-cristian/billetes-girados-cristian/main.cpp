#include "funciones.h"

using namespace std;
#define UMBRAL 245
#define VALOR_MEDIA 0.97
#define nLineas 80
#define pesoBlur 12
#define umbralTexto 0.7
#define umbralBinario 0.4

void forma1(){
    //kernels
    CImg<bool> img,mascara,se2(3,3),se1(3,3),se0(5,5,1,1,0),contorno;
    se0(0,0)=se0(1,1)=se0(2,2)=se0(3,3)=se0(4,4)=se0(5,5)=1;
    se0(1,2)=se0(2,3)=se0(3,2)=se0(2,1)=se0(4,3)=se0(3,4)=1;
    se1.fill(0,0,1,0,1,0,1,0,0);   //  Structuring element 1
    se2.fill(1);
    //imagen
    CImg<double> original,intensidad,copia;
     CImg<int> etiqueta;
    original.load("../../../../Parcial de Practica/Billetes/Billetes_Girados/3.jpg");
    original=denoise(original,3,12,0,4);
    original.display("filtrada");
    intensidad=original.get_RGBtoHSI().get_channel(2);
    mascara = intensidad.get_normalize(0,255).get_threshold(UMBRAL);//.get_dilate(se0).get_erode(se1).get_erode(se1).get_erode(se1);//.get_dilate(se1);
    (mascara,NOTimg(mascara)).display("mascara");
    mascara = apertura(NOTimg(mascara),mask(5));
    //mascara=NOTimg(mascara).erode(se2);
    (mascara,relleno_automatico(mascara)).display("mascara");
    mascara=relleno_automatico(mascara);
    //Trimeo a lo cabeza de tacho
    copia=original.get_mul(mascara);
    copia.display("copia");

    contorno = extraccion_de_contornos(relleno_automatico(mascara),mask(3));
    contorno.display();


    // Para calcular el angulo calculo la transformada de Hough y la multiplico por una imagen para pesar los angulos
      //giro la imagen de peso un poco.
            CImg<double> Hough = hough( contorno);
            //peso imagen un poco girada
            CImg<double> peso(Hough.width(),Hough.height(),1,1,"1 / (1 + 2 * (((x/w)*2)-1) * (((x/w)*2)-1))",false);
            Hough.mul( peso );

            CImgList<double> lista2( Hough.get_div(peso), peso, Hough, original-InversaHough( Hough, nLineas ) );
            lista2.display("Calcular angulo - Hough", false);

            // Para calcular el angulo de giro de la imagen tomo los "nLineas" maximos de la imagen y los promedio
            double angulo = 0;
            for(int i=0; i<nLineas; i++) {
                Pixel p = MaximoP( Hough );
                angulo += p.x;
                Hough( p.x, p.y ) = 0;
            }
            angulo /= (double)nLineas;
            angulo -= (double)(Hough.width()/2);
            angulo *= 90.0 / (double)(Hough.width()/2);
            cout<<"Angulo de giro: "<<angulo<<endl;
            copia.rotate(angulo);
            mascara.rotate(angulo);
            copia.display("rotada");
            //img=original.get_RGBtoHSI().get_channel(2).get_normalize(0,255).get_threshold(UMBRAL);
            //img.display();

           copia=trim_image(copia,mascara);
           copia.display("trimmm");
           intensidad=copia.get_RGBtoHSI().get_channel(2);
           img = intensidad.get_normalize(0,255).get_threshold(150);

           img.display("billete");

    //para determinar si el billete esta invertido o no
    double aux= img.get_crop(53,84,161,227).mean();
    if (aux<VALOR_MEDIA){
     img.rotate(180);
    }

    img.display("girado final");

    //Operacion de etiquetado
    etiqueta = label_cc(NOTimg(img.get_crop(img.width()*0.2084,img.height()*0.0278,img.width()*0.29,img.height()*0.3585)));
    etiqueta.display("Etiquetado");

    //Cuenta de la cantidad de rosas (Contar niveles de grises diferentes)
    int cant_rosas = cant_grises(etiqueta);
    vector<int> grises = grises_disponibles(etiqueta);
    switch(cant_rosas){
    case 6:
        cout<<"2 PESOS";
        break;
    case 4:
        cout<<"10 PESOS";
        break;
    case 5:
        cout<<"5 PESOS";
        break;
    case 2:
        cout<<"50 PESOS";
        break;
    case 1:
        cout<<"100 PESOS";
        break;
    case 3:
        cout<<"20 PESOS";
        break;
    }

}

 void forma2(){
    //kernels
    CImg<bool> img,mascara,se2(3,3),se1(3,3),se0(5,5,1,1,0),contorno;
    se0(0,0)=se0(1,1)=se0(2,2)=se0(3,3)=se0(4,4)=se0(5,5)=1;
    se0(1,2)=se0(2,3)=se0(3,2)=se0(2,1)=se0(4,3)=se0(3,4)=1;
    se1.fill(0,0,1,0,1,0,1,0,0);   //  Structuring element 1
    se2.fill(1);
    //imagen
    CImg<double> original,intensidad,copia;
     CImg<int> etiqueta;
    original.load("../../../../Parcial de Practica/Billetes/Billetes_Girados/3.jpg");
    original=denoise(original,3,12,0,4);
    original.display("filtrada");
    intensidad=original.get_RGBtoHSI().get_channel(2);
    mascara = intensidad.get_normalize(0,255).get_threshold(UMBRAL);//.get_dilate(se0).get_erode(se1).get_erode(se1).get_erode(se1);//.get_dilate(se1);
    //(mascara,NOTimg(mascara)).display("mascara");
    mascara = apertura(NOTimg(mascara),mask(5));
    //mascara=NOTimg(mascara).erode(se2);
    (mascara,relleno_automatico(mascara)).display("mascara");
    mascara=relleno_automatico(mascara);
    //Trimeo a lo cabeza de tacho
    copia=original.get_mul(mascara);
    //copia.display("copia miltiplicada por mascara");

    contorno = extraccion_de_contornos(relleno_automatico(mascara),mask(3));
    //contorno.display();
    // Y me quedo con una region central para evitar ser afectado por bordes
    //copia.crop(copia.width()/5, copia.height()/5, copia.width()*4/5, copia.height()*4/5);
    //copia.display();
    //mascara = extraccion_de_contornos(relleno_automatico(mascara),mask(3));
    // Y ahora aplicamos hough
    CImg<float>aux = hough(contorno);

    //buscamos el maximo pico
    double max_theta = 0;
    double max_rho_coord = 0;

    get_max_peak<double>(aux, max_theta, max_rho_coord);

    // Ahora que se donde esta el maximo pico, se cual es su inclinacion, por lo que deberia
    // rotarlo hacia 90 o hacia 0, depende cual este mas cerca
    std::cout << max_theta << std::endl;

    // Si theta es negativo, tomo consideracion especial
    max_theta = (max_theta < 0) ? 180 + max_theta : max_theta;

    // Me va dar 0 (<45), 90 (< 135), 180 (< 225), 270 (<315), o 360
    double degree_to_go = round(max_theta / 90) * 90;

    // Y lo rotamos
    //CImg<double> page_rotate(copia.get_rotate(max_theta - degree_to_go));

    //page_rotate.display("rotada");

    //trim_image(page_rotate,page_rotate).display("trimm");
    mascara.display("mascara sin rotar (la debo rotar antes de aplicar trim_image)");
    mascara.rotate(max_theta - degree_to_go);
     copia=trim_image(copia.rotate(max_theta - degree_to_go),mascara);

    copia.display("trimmm");
    intensidad=copia.get_RGBtoHSI().get_channel(2);
    img = intensidad.get_normalize(0,255).get_threshold(150);

    img.display("billete");

//para determinar si el billete esta invertido o no
double auxx= img.get_crop(53,84,161,227).mean();
if (auxx<VALOR_MEDIA){
img.rotate(180);
}

img.display("girado final");

//Operacion de etiquetado
etiqueta = label_cc(NOTimg(img.get_crop(img.width()*0.2084,img.height()*0.0278,img.width()*0.29,img.height()*0.3585)));
etiqueta.display("Etiquetado");
//Cuenta de la cantidad de rosas (Contar niveles de grises diferentes)
int cant_rosas = cant_grises(etiqueta);
vector<int> grises = grises_disponibles(etiqueta);
switch(cant_rosas){
case 6:
    cout<<"2 PESOS";
    break;
case 4:
    cout<<"10 PESOS";
    break;
case 5:
    cout<<"5 PESOS";
    break;
case 2:
    cout<<"50 PESOS";
    break;
case 1:
    cout<<"100 PESOS";
    break;
case 3:
    cout<<"20 PESOS";
    break;
}

}

int main()
{

   forma1();
   //forma2();

//la diferencia entra forma 1 y forma 2 es la forma es que se calcular el angulo con tranformada huogh
   // forma 2 con  get_max_peak, calcula el angulo en funcion de un solo maximo, el primer maximo
   //forma 1, hace un promedio entre n maximos, la cantidad de maximos a tomar para el promedio
   // se determina con el parametro nLineas.


    return 0;
}


