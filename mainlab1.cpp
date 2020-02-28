#include "Support.h"
#include "Generators.h"
#include "Criteria.h"

//compile flags : -lgmp -lgmpxx -std=c++17
//use std::array or std::vector instead of raw arrays.... mb rewrite whole lab later


int main()
{
    std::string_view path    = "/home/ftl/as1/text/outputFile";
    std::string_view pathCSV = "/home/ftl/as1/results.csv";

    uint64_t* stats = new uint64_t[SIZE]{};
    
    MakeCSV(pathCSV, stats);
    PrintInFile(path, stats);

return 0;
}

