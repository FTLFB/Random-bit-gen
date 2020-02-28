#include <iostream>
#include <random> 
#include <bitset> 
#include <gmp.h>
#include <fstream>
#include <string>


double CharacterUniformityCriteria_1(uint64_t* stats, double alfa);
double CharacterIndependencyCriteria_2(uint64_t* stats, double alfa);
double CharacterHomoCriteria_3(uint64_t* stats, double alfa);
