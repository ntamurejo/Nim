#include <iostream>
#include "lines.h"

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkConnectedComponentImageFilter.h"
#include "itkLabelToRGBImageFilter.h"
#include "itksys/SystemTools.hxx"
#include <sstream>

typedef float  FloatPixelType;
typedef unsigned char MaskPixelType;

int main()
{
    // Read the image
    typedef signed short  PixelType;
    typedef itk::Image<PixelType, 2>     ImageType;
    typedef itk::ImageFileReader< ImageType > ImageReaderType;

    std::string mhdFile = "/Users/ntamurejo/Desktop/disec/slice2.png";//_Input_.mhd";//Cuadradonegro.jpg";
    
    ImageReaderType::Pointer reader = ImageReaderType::New();
    reader->SetFileName(mhdFile);
    ImageType::Pointer image;

    try
    {
        ///image = reader->Update();
        reader->Update();
        image = reader->GetOutput();
    }
catch (itk::ExceptionObject& e)
    {
    std::cerr << e.GetDescription() << std::endl;
    exit(1);  // You can choose to do something else, of course.
    }
    
    // Calcular la y_current;
    Lines recta;
    Lines::segment radio;
    
    ImageType::IndexType start;
    start[0] = 347;//147;
    start[1] = 489;////147;
    double grad = 30;
    double gradFinal = -grad;
    double delta = 3;
    
    double Xcurrent;// = start[0]-1;
    double Ycurrent;// = recta.ecuacionLine(start, grad, Xcurrent);
    ImageType::IndexType PixelNew;
    
    //Variables para el calculo de la media
    double avgNew = 0;
    double avgOld;
    double valueNew = 0;
    int sizeNew = 1;
    //Bucle para todos los puntos hasta que encuentre el borde
    bool first = false;
    //
    std::vector<int> vectorAverage;
    vectorAverage.clear();
    
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
   // Elegir el radio que tenga la menor intensidaD
    std::vector<int>::iterator minimo = std::min_element(std::begin(vectorAverage), std::end(vectorAverage));
    std::cout << "min element at: " << std::distance(std::begin(vectorAverage), minimo) <<"value is:" << *minimo << std::endl;
    
    // A que radio pertenece el minimo?
    int position = std::distance(std::begin(vectorAverage), minimo);
    double angleSelect = recta.m_vectorRadios.at(position).angulo;
    double mediaSelect  = recta.m_vectorRadios.at(position).averageIntensity;
    
    // Una vez elegido dibujar la linea sobre la imagen.
   for(int p = 0; p < recta.m_vectorRadios.at(position).coordVector.size(); )
    {
        ImageType::IndexType pixelRecta;
        double x = recta.m_vectorRadios.at(position).coordVector.at(p)[0];//vector_Coord.at(p)[0];
        double y = recta.m_vectorRadios.at(position).coordVector.at(p)[1];//vector_Coord.at(p)[1];
        //std::cout << "Radio: " << r << "Coordenadas:" << x <<", "<< y << std::endl;
        pixelRecta[0] = x;
        pixelRecta[1] = y;
        image->SetPixel(pixelRecta, 255);
        p = p +2;
    }
    typedef  itk::ImageFileWriter< ImageType  > WriterType;
    WriterType::Pointer writer = WriterType::New();
    
    std::stringstream radioMin;
    radioMin << "_radioMinimo_"  << ".mhd";
    writer->SetFileName(radioMin.str());
    writer->SetInput(image);
    writer->Update();

    
    //-------------------------------------------------------------
    // Dibujar linea con los pixeles que hemos metido en el vector
    //-------------------------------------------------------------
    
    for(int r = 0; r < recta.m_vectorRadios.size(); r++)
    {
        for(int p = 0; p < recta.m_vectorRadios.at(r).coordVector.size(); )
        {
            ImageType::IndexType pixelRecta;
            double x = recta.m_vectorRadios.at(r).coordVector.at(p)[0];//vector_Coord.at(p)[0];
            double y = recta.m_vectorRadios.at(r).coordVector.at(p)[1];//vector_Coord.at(p)[1];
            //std::cout << "Radio: " << r << "Coordenadas:" << x <<", "<< y << std::endl;
            pixelRecta[0] = x;
            pixelRecta[1] = y;
            
            //if(r == 6)
              //  image->SetPixel(pixelRecta, 1);
            //else
                image->SetPixel(pixelRecta, 255);
            p = p +2;
        }
        
    }
   // typedef  itk::ImageFileWriter< ImageType  > WriterType;
   // WriterType::Pointer writer = WriterType::New();

    std::stringstream ss;
    ss << "_Input_"  << ".mhd";
    writer->SetFileName(ss.str());
    writer->SetInput(image);
    writer->Update();

    return EXIT_SUCCESS;
}


