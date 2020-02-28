#include "Support.h"
#include "Criteria.h"
#include "Generators.h"
#include <functional>
#include <map>
#include <iterator>

void PrintInFile(std::string_view path, uint64_t* stats) //std::string_view does not work here with std::ofstream :(
{
    
    std::ofstream FileStream(path.data());

    for(size_t i = 0; i < SIZE; ++i)
    {
        FileStream << std::bitset<64>(stats[i]) << std::endl;
    }

    FileStream.close();
}

void SetNullStats(uint64_t* stats)
{
    for(size_t i = 0; i < SIZE; ++i)
    {
        stats[i] = 0;
    }
}

void PrintInTerm(uint64_t* stats)
{
    for(size_t i = 0; i < SIZE; ++i)
    {
    std::cout << std::bitset<64>(stats[i]) << std::endl;
    }
}


void MakeCSV(std::string_view pathCSV, uint64_t* stats)
{
    std::ofstream CSVStream(pathCSV.data());
    
    std::function<double(uint64_t*, double)> criteriaArray[3] = {};
    criteriaArray[0] = CharacterUniformityCriteria_1;
    criteriaArray[1] = CharacterIndependencyCriteria_2;
    criteriaArray[2] = CharacterHomoCriteria_3;

  
    //because of map container, order of generators in CSV file may be confusing :)
    std::map<std::string, std::function<void(uint64_t*)>> m = {{ "StandardLanguage", StandardLanguageGen}, 
                                    {"LehmerLow", LehmerLowGen }, {"LehmerHigh", LehmerHighGen}, {"L20", L20Gen}, 
                                    {"L89", L89Gen}, {"Geffe", GeffeGen}, {"Librarian", LibrarianGen}, {"Wolfram", WolframGen },
                                    {"BM", BMGen}, {"BMBytes", BMBytesGen}, {"BBS", BBSGen}, {"BBSBytes", BBSBytesGen}};
  

    const double alfaArray[3] = { 0.01, 0.05, 0.1};
    //rename theoreticX2Array
    const double theoreticAlfaArray[3][3] = { { 307.618808424, 292.149330411, 281.648151906}, {65863.93, 65618.17, 65487.15}, 
                                              {4027.91713, 3951.8232 , 3928.20785 }};


   

                    /*
                    //блок 1 
    SetNullStats(stats);

    //StandardLanguageGen(stats);
    //LehmerLowGen(stats);
    //LehmerHighGen(stats);
    //L20Gen(stats);
    //L89Gen(stats);
    //GeffeGen(stats);
    LibrarianGen(stats);
    //WolframGen(stats);
    //BMGen(stats);
    //BMBytesGen(stats);
    //BBSGen(stats);
    //BBSBytesGen(stats);

    std::cout << "cr1 : " << CharacterUniformityCriteria_1(stats, 0.01) << std::endl;
    std::cout << "cr2 : " << criteriaArray[1](stats, 0.01) << std::endl;
    std::cout << "cr3 : " << criteriaArray[2](stats, 0.01) << std::endl;
    PrintInFile("/home/ftl/as1/BMbytes", stats);
                    //блок 1 
                    */
			
			
                    /*        //блок 2 
                           
   std::string outArr[3] = {};
    
    for(size_t i = 0 ; i < 3; ++i)
    {
        outArr[i] = "Generator_type, alfa, ";
        outArr[i] += std::to_string(theoreticAlfaArray[0][i]) + ",,       " + std::to_string(theoreticAlfaArray[1][i]) +
                     ",,     " + std::to_string(theoreticAlfaArray[2][i]) + ",\n";
    }

  
  for(auto i = m.begin(); i != m.end(); ++i)
    {
        i->second(stats);
        for(size_t k = 0; k < 3; ++k)
        {
            outArr[k] += i->first;
            outArr[k] += ",     ";
            outArr[k] += std::to_string(alfaArray[k]);
            outArr[k] += ",     ";
            for(size_t j = 0; j < 3; ++j)
            {
		double x = criteriaArray[j](stats, alfaArray[k]);
                outArr[k] += std::to_string(x);
                outArr[k] += ",     ";
		if (x < theoreticAlfaArray[j][0] )
                	outArr[k] += "PASS,     ";
		else
                	outArr[k] += "FAIL,     ";
            }
            outArr[k] += "\n";
        }
    }

    for(size_t i = 0; i < 3; ++i)
    {
        outArr[i] += "\n\n";
        //std::cout << outArr[i];
        std::cout << "DONE, check result.csv please" << std::endl;
        CSVStream << outArr[i];
    }

                                //блок 2 
*/





                                  
    							//блок 3 
    							
	double mark = 0.0;
    for(size_t k = 0; k < 3; ++k)
    {
	    CSVStream << "generator_type" << ",     " << "alfa" << ",       " << theoreticAlfaArray[0][k] << ",,     " <<
	                                                                         theoreticAlfaArray[1][k] << ",,     " <<
	                                                                         theoreticAlfaArray[2][k] << ",     " << '\n';
        for(/*std::unordered_map<std::string, std::function<void(uint64_t*)>>::iterator*/ auto i = m.begin(); i != m.end(); ++i)
        {
            i->second(stats);
            CSVStream << i->first << ",     " << alfaArray[k] << ",     ";
         
            for(size_t j = 0; j < 3; ++j)
            {
               // CSVStream <<  criteriaArray[j](stats, alfaArray[k]) << ",     ";
               mark = criteriaArray[j](stats, alfaArray[k]);
               CSVStream << mark << ",   ";
           
                if(mark>theoreticAlfaArray[j][k])
                      {
                   CSVStream << "Fail,  ";
                }
                  else 
                     {
                       CSVStream << "PASS,  ";
                  }
             }
   
            CSVStream <<  "\n";
        }
        CSVStream << "\n\n";
      
        std::cout << "DONE, check result.csv please" << std::endl;
        
    }
                                //блок 3 
                                


    CSVStream.close();
}
