

#include "jsonFile.h"

	/*int main(int argc, char *argv[])
	{
		//Carga del json 	
		jsonFileNamespace::jsonReader fileJSON;
		std::cout << "Loading json..." << std::endl;
		json::JSON fileReader = fileJSON.readFileJSONFromPath("/Users/ntamurejo/Proyectos/Json/example.json");
		std::cout << "Output file .json read:" << fileReader << std::endl;

		
		// Total de lesiones
		fileJSON.setTotalLesions(fileReader.operator[]("Lesions").length());
		int numLesions = fileJSON.getTotalLesions();
		std::cout << " Total de lesiones:" << numLesions << std::endl;

		// Extraer los datos del json
		fileJSON.readDataFromJson(fileReader);
		
		//std::cout << "resultado: " << fileReader.operator[]("lesion1") << std::endl; // solo los datos del key
		//std::cout << "obj.dump() :" << obj.dump() << std::endl; // Se extrae todo el contenido del objeto
		std::cout << "=========================================================================" << std::endl;
		return 0;
	}*/
	
	
	namespace jsonFileNamespace
	{
		jsonReader::jsonReader() :		
			m_AsimetriaLesionValue(0),
			m_EjeMayorLesionValue(0),
			m_ElipEsfericoLesionValue(0),
			m_ExcentricidadLesionValue(0),
			m_PerimetroLesionValue(0),
			m_VolumenLesionValue(0),
			m_CentroideLesionValue(0)
		{
		}
		jsonReader::~jsonReader()
		{

		}
		// Set y get
		void jsonReader::setEjeMayorLesionValue(float EM){this->m_EjeMayorLesionValue = EM;}
		float jsonReader::getEjeMayorLesionValue(){return this->m_EjeMayorLesionValue;}

		void jsonReader::setEjeMenorLesionValue(float EM) { this->m_EjeMenorLesionValue = EM; }
		float jsonReader::getEjeMenorLesionValue() { return this->m_EjeMenorLesionValue; }

		void jsonReader::setAsimetriaLesionValue(float Asimetria){this->m_AsimetriaLesionValue = Asimetria;}
		float jsonReader::getAsimetriaLesionValue(){return this->m_AsimetriaLesionValue;}

		void jsonReader::setElipEsfericoLesionValue(float Elipse){this->m_ElipEsfericoLesionValue = Elipse;}
		float jsonReader::getElipEsfericoLesionValue(){return this->m_ElipEsfericoLesionValue;}

		void jsonReader::setExcentricidadLesionValue(float excentricidad){this->m_ExcentricidadLesionValue = excentricidad;}
		float jsonReader::getExcentricidadLesionValue(){return this->m_ExcentricidadLesionValue;}

		void jsonReader::setPerimetroLesionValue(float perimetro){this->m_PerimetroLesionValue = perimetro;}
		float jsonReader::getPerimetroLesionValue(){return this->m_PerimetroLesionValue;}

		void jsonReader::setVolumenLesionValue(float volumen){this->m_VolumenLesionValue = volumen;}
		float jsonReader::getVolumenLesionValue(){return this->m_VolumenLesionValue;}

		void jsonReader::setCentroideLesionValue(float centroid)
		{
			this->m_CentroideLesionValue = centroid;
			
		}
		float jsonReader::getCentroideLesionValue()
		{
			return this->m_CentroideLesionValue;
		}

		void jsonReader::setCentroideVectorValues(std::vector<float> vectorCentroide)
		{
			for (int i = 0; i < vectorCentroide.size(); i++)
			{
				this->m_CentroideVectorValues.push_back(vectorCentroide[i]);
			}
			
		}
		std::vector<float> jsonReader::getCentroideVectorValues()
		{
			return this->m_CentroideVectorValues;
		}

		void jsonReader::setTotalLesions(int nlesiones) { this->m_TotalLesions = nlesiones; }
		int jsonReader::getTotalLesions() { return this->m_TotalLesions; }

        void jsonReader::setNumberLesion(int nlesion) { this->m_NumberLesion = nlesion; }
        int jsonReader::getNumberLesion() { return this->m_NumberLesion; }

		
		
		// Void de las funciones para leer
		//Read file .json from path
		json::JSON jsonReader::readFileJSONFromPath(std::string pathFile)
		{
            std::cout<<"Reading json..." << std::endl;
			std::string contents;
			std::ifstream input(pathFile);
			contents.reserve(input.tellg());
			input.seekg(0, std::ios::beg);

			contents.assign((std::istreambuf_iterator<char>(input)),
				std::istreambuf_iterator<char>());

			json::JSON obj = json::JSON::LoadJsonFile(contents);
			return obj;
		}
		
		// Read data from file json
		void jsonReader::readDataFromJson(json::JSON file)
		{
			int totalLesiones = this->getTotalLesions();
           this->m_CentroideVectorValues.clear();
			// Bucle para leer el eje mayor
			for (int i = 0; i < totalLesiones; i++)
			{
				int numLesion = i;
				this->setEjeMayorLesionValue(file.operator[]("Lesions").operator[](i).operator[]("MajorAxisLength").ToFloat());		
				this->setEjeMenorLesionValue(file.operator[]("Lesions").operator[](i).operator[]("MinorAxisLength").ToFloat());
				//this->setVolumenLesionValue(file.operator[]("Lesions").operator[](i).operator[]("Volume").ToFloat());
				//this->setElipEsfericoLesionValue(file.operator[]("Lesions").operator[](i).operator[]("Elipsoidal").ToFloat());
				//this->setAsimetriaLesionValue(file.operator[]("Lesions").operator[](i).operator[]("Asimentria").ToFloat());
				//this->setExcentricidadLesionValue(file.operator[]("Lesions").operator[](i).operator[]("Excentricidad").ToFloat());
				//this->setPerimetroLesionValue(file.operator[]("Lesions").operator[](i).operator[]("Perimetro").ToFloat());

				std::vector<float> centroide;
				for (int coord = 0; coord < 3; coord++)
				{
					this->setCentroideLesionValue(file.operator[]("Lesions").operator[](i).operator[]("Centroid").operator[](coord).ToFloat());			
					centroide.push_back(this->getCentroideLesionValue());
					std::cout << "centroide: " << this->getCentroideLesionValue() << std::endl;
				}
				this->setCentroideVectorValues(centroide);
				// LLamada a la funcion que rellena la tabla de qt

				std::cout << "lesion" << i << ", su eje mayor es: " << this->getEjeMayorLesionValue() << std::endl;
				std::cout << "lesion" << i << ", su eje menor es: " << this->getEjeMenorLesionValue() << std::endl;
				std::cout << "lesion" << i << ", Volumen: " << this->getVolumenLesionValue() << std::endl;
				std::cout << "lesion" << i << ", Elipse: " << this->getElipEsfericoLesionValue() << std::endl;
				std::cout << "lesion" << i << ", Asimetria: " << this->getAsimetriaLesionValue() << std::endl;
				std::cout << "lesion" << i << ", Excentricidad: " << this->getExcentricidadLesionValue() << std::endl;
				std::cout << "lesion" << i << ", Perimetro: " << this->getPerimetroLesionValue() << std::endl;
				std::cout << "lesion" << i << ", Centroide Vector: " << this->getCentroideVectorValues()[0] << "," 
																	<< this->getCentroideVectorValues()[1] << "," 
																	<< this->getCentroideVectorValues()[2] << std::endl;
           }
		}
		// Funcion para rellenar la tabla de qt con los datos extraidos de la funcion
	}
