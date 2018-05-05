#ifndef __LINES_H
#define __LINES_H

#include <utility>      // std::pair, std::make_pair
#include <iostream>
#include <sstream>
#include <vector>
//#include <math.h>

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

typedef itk::Image< unsigned char, 2 >  ImageType;



class Lines
{
	public:
    Lines(){};
    ~Lines(){};
    struct segment
    {
        std::vector<ImageType::IndexType >  coordVector;
        int angulo;
        double averageIntensity;
    };

    std::vector<segment> m_vectorRadios;
    segment computeExtrapolationMembraneToAorticWall( ImageType::Pointer image,ImageType::IndexType pixelInitial,double grados,double delta);
    double computeAverage(double valuePixel,bool first);
    int ecuacionLine(ImageType::IndexType pixelIndex,double grados,double Xcurrent);
    double gradesToRadians(double grados);
    
private:
    double m_avgNew;
    double m_avgOld;
    double m_valueNew;
    int m_sizeNew;

};

#endif //__Lines_H
