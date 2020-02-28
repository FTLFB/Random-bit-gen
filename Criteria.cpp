#include "Criteria.h"
#include "Generators.h"

//remove alfa in signature

double CharacterUniformityCriteria_1(uint64_t* stats, double alfa)
{
    
    double freqArr[256] = {};

	for(size_t i = 0; i < SIZE; ++i)
	{
		for(size_t j = 0; j < 8; ++j)
		{
			++freqArr[((stats[i] >> (8*j)) & 0b11111111)];			
		}
	}


	double X2 = 0.0;
	for(size_t i = 0; i < 256; ++i)
	{
		X2 += ( ( (freqArr[i] - 1024.0)*(freqArr[i] - 1024.0)  ) / (1024.0)   );
	}

	return X2;
}

double CharacterIndependencyCriteria_2(uint64_t* stats, double alfa)
{

	float freqArr[256+1][256+1] = {}; //declare and init with 0

    for(size_t i = 0; i < SIZE; ++i)
	{
	    /*
		for(size_t j = 0; j < 4; ++j)//j < 7
		{
		//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAaaa
			++freqArr[((stats[i] >> (8-j-1)) & 0b11111111) ][ ((stats[i] >> (8-j)) & 0b11111111) ];
		}
		*/
		++freqArr[    stats[i] & 0b11111111    ][  (stats[i] >> 8) & 0b11111111   ];
		++freqArr[    (stats[i] >> 16) & 0b11111111    ][ (stats[i] >> 24) & 0b11111111    ];
		++freqArr[    (stats[i] >> 32) & 0b11111111    ][ (stats[i] >> 40) & 0b11111111    ];
		++freqArr[    (stats[i] >> 48) & 0b11111111    ][ (stats[i] >> 56) & 0b11111111    ];
	}

	for(size_t i = 0; i < 256; ++i)
	{
		for(size_t j = 0; j < 256; ++j)
		{
			freqArr[i][256] += freqArr[i][j];
			freqArr[256][j] += freqArr[i][j];
		}
	}

	float X2 = 0.0;
	float temp1;
	float temp2;
	
	for(size_t i = 0; i < 255; ++i)
	{
		for(size_t j = 0; j < 255; ++j)
		{
		    if((freqArr[i][j] != 0) && ((freqArr[256][i] * freqArr[j][256]) != 0) )
		    {
			    X2 +=  ( ( freqArr[i][j] * freqArr[i][j] ) / ( freqArr[256][i] * freqArr[j][256] )) ;
			//    std::cout << "zn cr2  " << freqArr[256][i] * freqArr[j][256] << std::endl;
			}
		}
	}	
	--X2;
	X2 = X2 * 131072;// 4.0 ne 8.0
    	
	 
	return X2;
}



double CharacterHomoCriteria_3(uint64_t* stats, double alfa)
{
    double X2 = 0.0;
    double freqArr[16+1][256] = {}; // here can be 256+1, but we already know that length of interval is 2048*8

    for(size_t i = 0; i < 16; ++i)
    {
        for(size_t j = 0; j < 2048; ++j)
        {
            for(size_t k = 0; k < 8; ++k)
            {
                ++freqArr[i][((stats[i*2048 + j] >> (8*k)) & 0b11111111)];
            }
        }     
    }

    for(size_t i = 0; i < 16; ++i)
    {
        for(size_t j = 0; j < 256; ++j)
        {
            freqArr[16][j] += freqArr[i][j];
        }
    }


    for(size_t i = 0; i < 16; ++i)
    {
        for(size_t j = 0; j < 256; ++j)
        {
            if(freqArr[16][j] != 0)
            {
                X2 += ( ( (double)(freqArr[i][j]) * (double)(freqArr[i][j]) ) / ((double)freqArr[16][j] * (SIZE/2)) );
            }
        }        
    }
    --X2;
    X2 = X2 * SIZE * 8.0;//4.0 or 8.0

	return X2;
}




