#ifndef __JSONFILE_H_
#define __JSONFILE_H_

#include <stdio.h>
#include <sstream>
#include <string>
#include "json.hpp"

//#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <streambuf>
#include <vector>


//using json::JSON;

namespace jsonFileNamespace
{
	class jsonReader
	{
	public:
		jsonReader();

		~jsonReader();

		void setEjeMayorLesionValue(float EM);
		float getEjeMayorLesionValue();

		void setEjeMenorLesionValue(float EM);
		float getEjeMenorLesionValue();

		void setVolumenLesionValue(float Volumen);
		float getVolumenLesionValue();

		void setElipEsfericoLesionValue(float Elipse);
		float getElipEsfericoLesionValue();

		void setExcentricidadLesionValue(float Excentricidad);
		float getExcentricidadLesionValue();

		void setPerimetroLesionValue(float Perimetro);
		float getPerimetroLesionValue();

		void setAsimetriaLesionValue(float Asimetria);
		float getAsimetriaLesionValue();

		void setCentroideLesionValue(float Coord);
		float getCentroideLesionValue();

		void setCentroideVectorValues(std::vector<float> vectorCentroide);
		std::vector<float> getCentroideVectorValues();

		void setTotalLesions(int nlesiones);
		int getTotalLesions();

        void setNumberLesion(int nNumberLesion);
        int getNumberLesion();

        
		json::JSON readFileJSONFromPath(std::string path);
		
		void readDataFromJson(json::JSON file);
		

		

	private:

		int m_TotalLesions;
        int m_NumberLesion;

		float m_EjeMayorLesionValue;
		float m_EjeMenorLesionValue;
		float m_VolumenLesionValue;
		float m_ElipEsfericoLesionValue;
		float m_ExcentricidadLesionValue;
		float	m_PerimetroLesionValue;
		float m_AsimetriaLesionValue;
		float m_CentroideLesionValue;
		std::vector<float> m_CentroideVectorValues;

	};

	
}


#endif // __JSONFILE_H_
