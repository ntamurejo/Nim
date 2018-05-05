#include "lines.h"
#define PI 3.14159265



int Lines::ecuacionLine(ImageType::IndexType pixelIndex, double grados,double Xcurrent)
{
    ImageType::IndexType pointInitial = pixelIndex;
    pointInitial[0] = pixelIndex[0];
    pointInitial[1] = pixelIndex[1];
    //std::cout <<"Punto de inicio:" << pointInitial[0] <<","<< pointInitial[1] << std::endl;

    double grados_iniciales = grados;
    int x_current = Xcurrent;
    int y_current = 0;
    double radians = gradesToRadians(grados_iniciales);
    double tang = std::tan(radians);
    y_current = pointInitial[1] + tang * (x_current-pointInitial[0]);
    
    return y_current;
}

double Lines::gradesToRadians(double grados)
{
    double radians = (grados * PI)/180;
    
    return radians;
}

/*segment computeExtrapolationMembraneToAorticWall( ImageType::Pointer image,ImageType::IndexType pixelInitial,double grados,double delta)
{
    while(grad!= gradFinal)
    {   //El punto central de la imagen es nuestra punto inicial para tirar los rayos
        Xcurrent = start[0]-1;
        Ycurrent = recta.ecuacionLine(start, grad, Xcurrent);
        PixelNew[0] = Xcurrent;
        PixelNew[1] = Ycurrent;
        
        //Rayo
        while(image->GetPixel(PixelNew)!= 255)
        {
            std::cout <<"Grados:" << grad << std::endl;
            //Calcular la media de intensidad del radio que estamos recorriendo.
            if(!first)
            {
                avgOld = image->GetPixel(PixelNew);
                valueNew = avgOld;
                sizeNew = 1;
                avgNew = avgOld + (valueNew-avgOld)/sizeNew;
                avgOld = avgNew;
                first = true;
            }
            else
            {
                valueNew = image->GetPixel(PixelNew);
                sizeNew +=1;
                avgNew = avgOld + (valueNew-avgOld)/sizeNew;
                avgOld = avgNew;
            }
            //Meter el pixel new en el vector con las coordenadas
            radio.coordVector.push_back(PixelNew);
            Xcurrent = Xcurrent -1;
            // Calcular la ecuacion de la recta->obtenemos el valor de Ycurrent
            double Ycurrent = recta.ecuacionLine(start, grad, Xcurrent);
            // Metemos Xcurrent e Ycurrent en un IndexPixel
            PixelNew[0] = Xcurrent;
            PixelNew[1] = Ycurrent;
            // Se volvera a ejecutar el while
        }
        vectorAverage.push_back(avgNew);
        radio.averageIntensity = avgNew;
        radio.angulo = grad;
        recta.m_vectorRadios.push_back(radio);
        //Reseteamos los valores para el nuevo radio.
        radio.coordVector.clear(); //Reseteamos el radio para hacer el proximo y no acumular
        
        
        grad = grad-delta;
        first = false;
    }
}*/


