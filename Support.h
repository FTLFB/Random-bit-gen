#include <iostream>
#include <random> 
#include <bitset> 
#include <gmp.h>
#include <fstream>
#include <string>
#include <functional>


void PrintInFile(std::string_view path, uint64_t* stats);
void SetNullStats(uint64_t* stats);
void PrintInTerm(uint64_t* stats);
void MakeCSV(std::string_view pathCSV, uint64_t* stats);
