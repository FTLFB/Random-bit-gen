#include <iostream>
#include <random> 
#include <bitset> 
#include <gmp.h>
#include <fstream>
#include <string>

constexpr size_t SIZE = 32768;
void IdealGen(uint64_t* stats);
void StandardLanguageGen(uint64_t* stats);
void LehmerLowGen(uint64_t* stats);
void LehmerHighGen(uint64_t* stats);
void L20Gen(uint64_t* stats);
void L89Gen(uint64_t* stats);
void GeffeGen(uint64_t* stats);
void LibrarianGen(uint64_t* stats);
void WolframGen(uint64_t* stats);
void BMGen(uint64_t* stats);
void BMBytesGen(uint64_t* stats);
void BBSGen(uint64_t* stats);
void BBSBytesGen(uint64_t* stats);
