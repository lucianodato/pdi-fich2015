#include "funciones.h"
#define RADIO 30
#define UMBRAL_ALTO 200
#define UMBRAL_BAJO 58
#define RADIO_CIRCULOS 30
#define NERODE 5
int main()
{
    CImg<float> img,final;
    CImg<int> etiqueta;
    CImg<float> intensidad;
    CImg<bool> mascara,se1(3,3),se2(5,5),segmentacion;
    int mx,my;
    //vent.fill(0,1,0,1,1,1,0,1,0);
    se1.fill(1);
    se2.fill(1);
    const char* path = "../../../../Parcial de Practica/Piletas/google4.png";
    img.load(path);
    mascara.assign(img.width(),img.height(),1,1);
    intensidad.assign(img.width(),img.height(),1,1);
    final.assign(img);
    //Color Slicing

    CImgDisplay v1(img,"Presione sobre el color deseado"),v2(img,"Resultado");

    while(!v1.is_closed() || !v2.is_closed()){
        v1.wait();
        if(v1.button()==1){

            mx=v1.mouse_x();
            my=v1.mouse_y();

            intensidad = ColorMaskHSI(img,mx,my,RADIO);

            v2.render(intensidad);
            v2.paint();
        }
    }


    //Proceso la mascara para dejarla binaria
    intensidad = intensidad.get_RGBtoHSI().get_channel(2).get_normalize(0,255);
   // intensidad.display("grices");
    mascara=umbral_por_tramos_bool(intensidad,UMBRAL_BAJO,UMBRAL_ALTO);//este umbral es para recortar si hay techos con mucho brillo
    //smascara=NOTimg(mascara);
    //mascara=intensidad.get_threshold(40);
   //(img,mascara,intensidad.get_threshold(40),img.get_mul(mascara)).display("markara");

    //Estrategia para limpiar la mugre

//    //Operacion 1 - Erosion y dilatacionmascara=nerode(mascara,se2,4);
    segmentacion=nerode(mascara,se1,NERODE);
    //(img,segmentacion).display("operaciones nerode");

   segmentacion = reconstruccion_dilatacion(mascara,segmentacion);
   (img,segmentacion).display("segmentacion");

   //segmentacion=relleno_automatico(segmentacion);
  (img,segmentacion).display("relleno auto");
   //   (img,mascara, img.get_mul(mascara)).display("Erosion y Dilatacion");
     // (img,segmentacion).display("erode");
//    //Operacion de etiquetado
      etiqueta = label_cc(segmentacion);
      etiqueta.display("Etiquetado");

//    //Cuenta de la cantidad de rosas (Contar niveles de grises diferentes)
    int cant_rosas = cant_grises(etiqueta);
//    vector<int> grises = grises_disponibles(etiqueta);
//    vector<int> contar;int contador=0;
//    for (int i=0;i<grises.size();i++){
//        cimg_forXY(etiqueta,i,j)
//                if(etiqueta(i,j)==grises.at(i))
//                contador++;
//    contar.push_back(contador);
//    contador=0;
//    }

//     for (int i=0;i<contar.size();i++)
//         cout<<contar.at(i)<<endl;



    cout<<"La cantidad total de Piletas es: "<<cant_rosas<<endl;

//    //Dibujar un circulo rojo encima de cada rosa
//    //Armo la macara encontrando los centros de cada rosa y el diametro minimo en el cuadrado que la encierra
//    CImg<float> masc(etiqueta.width(),etiqueta.height(),1,1,0);

//    //Recorro el vector de grises
//    for(int g=0;g<grises.size();g++){
//        //Primero encuentro las coordenadas maximas y minimas
//        int max_x=0,max_y=0,min_x=etiqueta.width(),min_y=etiqueta.height(),radio,centro_x,centro_y;
//        cimg_forXY(etiqueta,i,j){
//            if(etiqueta(i,j)==grises.at(g)){
//                //Estoy en un pixel del gris buscado - actualizo los maximos y los minimos
//                i>max_x ? max_x=i:max_x=max_x;
//                j>max_y ? max_y=j:max_y=max_y;
//                i<min_x ? min_x=i:min_x=min_x;
//                j<min_y ? min_y=j:min_x=min_x;
//            }
//        }
//        //Calculo el radio del circulo y el pixel medio
//        radio=min((max_x-min_x),(max_y-min_y))-12;//El -12 es para achicar un poco los circulos (a ojo)
//        centro_x=min_x + ((max_x-min_x)/2);
//        centro_y=min_y + ((max_y-min_y)/2);
//        //Creo una mascara a partir del ciculo
//        masc.draw_circle(centro_x,centro_y,radio,white);
//    }
//    masc.display("Mascara de circulos");

//    //Pinto la imagen original con los circulos rojos (en realidad hago un balance de color con un aumento grande)
//    final = balancecolorRGB(final,0,300).get_mul(masc) + final.get_mul(negativo(masc));

//    final.display("Coloreando");
    return 0;
}



