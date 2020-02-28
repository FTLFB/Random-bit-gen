#include "Generators.h"
#include "Support.h"
#include <bitset>

void IdealGen(uint64_t* stats)
{
    
    uint8_t buffer = 0;


    for(size_t i = 0; i < SIZE; ++i)
    {
        for(size_t j = 0; j < 8; ++j)
        {
                stats[i] = (stats[i] << 8) ^ buffer;
                ++buffer;
        }
    }

}

void StandardLanguageGen(uint64_t* stats)
{
	std::random_device devUrandom;
	std::mt19937_64 generator(devUrandom());
	SetNullStats(stats);
	
	for(uint16_t i = 0; i < SIZE; ++i)
	{
		stats[i] = generator();
//		std::cout << std::bitset<64>(stats[i]) << std::endl;
	}
}



void LehmerLowGen(uint64_t* stats)
{
    std::random_device devUrandom;
    std::mt19937 generator(devUrandom());
        SetNullStats(stats);

	uint32_t a = 0b1;
	a = (a << 16) + 1;
    uint32_t c =18939337; 
	uint32_t container = 0;
	while(container == 0)
	{
        container = generator();
	}
	for(size_t i = 0 ; i < SIZE; ++i)
	{
		for(size_t j = 0; j < 8; ++j)
		{
			container = container*a + c ;
			stats[i] = ((stats[i] << 8 ) | ((container >> 20) & 0b11111111 ) ) ;

		}
	}
	
	
//LehmerMidGen poluchilsya; ya vse delala po metode no ona ne rabotaet	
}


void LehmerHighGen(uint64_t* stats)
{
    std::random_device devUrandom;
    std::mt19937_64 generator(devUrandom());
        SetNullStats(stats);

	uint64_t m = 0b1;
	m = m << 32;
	uint64_t a = 0b1;
	a = (a << 16) + 1;
	
	const uint64_t c = 172619; 

	uint64_t container = generator();
	for(size_t i = 0 ; i < SIZE; ++i)
	{
		for(size_t j = 0; j < 8; ++j)
		{
			container = (a*container + c) % m;
			stats[i] = ((stats[i] << 8 ) | (container >> 24) ) ; // LemerHighGen
		}
	}
	
	
	
}

void L20Gen(uint64_t* stats) // 2^20 - 1 ~ 10^6; we need 2*10^6, 

{
    SetNullStats(stats);
    std::random_device devUrandom;
    std::mt19937 generator(devUrandom());

    for(size_t half = 0; half != SIZE; half += (SIZE/2))
    {
        while(stats[half] == 0)
        {
            stats[half] = generator();
//            std::cout << "HALF " << std::bitset<64>(stats[half]) << std::endl;
        }
    
        for(size_t i = 0; i < 44; ++i)//we have 20 randomed bits, here we get 44 more bits
        {
            stats[half] = (stats[half] << 1) | ( ( ( stats[half] >> 19)^(stats[half] >> 8)^(stats[half] >> 4)^(stats[half] >> 2) ) &1 );
        }

        for(size_t i = 1 ; i < (SIZE/2) ; ++i)
        {
            stats[i+half] = stats[i-1+half];
            for(size_t j = 0; j < 64; ++j)
            {
                stats[i+half] = (stats[i+half] << 1) | ( ( ( stats[i+half] >> 19)^(stats[i+half] >> 8)^(stats[i+half] >> 4)^(stats[i+half] >> 2) ) &1 );
            }
        }
    
    }

}

void L89Gen(uint64_t* stats)
{
    
    std::random_device devUrandom;
    std::mt19937_64 generator(devUrandom());

    SetNullStats(stats);
    uint64_t state1 = 0;
    uint64_t state2 = 0;

    while(state1 == 0 || (state2 << 39) == 0)
    {
        state1 = generator();
        state2 = generator();
    }

    for(size_t i = 0; i < SIZE; ++i)
    {
        for(size_t j = 0; j < 64; ++j)
        {
            stats[i] = ( (stats[i] << 1) | ( ( (state1 >> 37) ^ (state2 >> 24) ) & 0b1) );
            state2 = ( (state2 << 1) | (state1 >> 63) ); // hope we don't need & 0b1 here, because of unsigned int shift properties
            state1 = ( state1 << 1 ) | (stats[i] & 0b1) ;   
        }
    }

}

void GeffeGen(uint64_t* stats)
{
    std::random_device devUrandom;
    std::mt19937_64 generator(devUrandom());

    SetNullStats(stats);

    uint64_t L11_l1 = 0;
    uint64_t L9_l2  = 0;
    uint64_t L10_l3 = 0;

    while(L11_l1 == 0 || L9_l2 == 0 || L10_l3 == 0)
    {
        L11_l1 = generator();
        L9_l2  = generator();
        L10_l3 = generator();
    }

    SetNullStats(stats);


    for(size_t i = 0; i < SIZE; ++i)
    {
        for(size_t j = 0; j < 64; ++j)
        {
            L11_l1 = ( (L11_l1 << 1) | ( ( ( L11_l1 >> 10)^(L11_l1 >> 8) ) & 0b1) );
            L9_l2  = ( (L9_l2  << 1) | ( ( ( L9_l2  >> 8 )^(L9_l2  >> 7)^(L9_l2 >> 5)^(L9_l2 >> 4)) & 0b1  ));
            L10_l3 = ( (L10_l3 << 1) | ( ( ( L10_l3 >> 9 )^(L10_l3 >> 6) ) & 0b1) );
            
            stats[i] = ( (stats[i] << 1) | ( ( (L11_l1 & L10_l3 )^((0b1 ^ L10_l3) & L9_l2) ) & 0b1 ) );
        }
    }
}


void LibrarianGen(uint64_t* stats)//each time, this function gets the exact same sequence of bits
{
    std::ifstream text_stream("/home/ftl/as1/text/TH1.txt");
    SetNullStats(stats);
    

    
    std::string temp, cont;
    while(!text_stream.eof() && (cont.length() < 262144))
    {
        getline(text_stream, temp);
        if(temp != "\0")
        {
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            cont +=temp;
        }
        temp = " ";

    }


    size_t in = 0;
    for(size_t i = 0; i < SIZE; ++i)
    {
        for(size_t j = 0; j < 8; ++j)
        {
            
            stats[i] = ((stats[i] << 8) | cont[in] );
            ++in;
        }
    }




    text_stream.close();
}


void WolframGen(uint64_t* stats)
{
    std::random_device devUrandom;
    std::mt19937_64 generator(devUrandom());
        
    SetNullStats(stats);

    uint64_t ri = 0;
    while(ri == 0)
    {
        ri = generator();
    }

    for(size_t i = 0; i < SIZE; ++i)
    {
        for(size_t j = 0; j < 64; ++j)
        {
            ri = ( (ri  << 1 ) |  (ri >> 63)  ) ^ ( ri | ( ( ri >> 1 ) | ( ri << 63 )  ) );    
            stats[i] = (stats[i] << 1) | (ri & 0b1);
        }
    }
}

void BMGen(uint64_t* stats)
{
    SetNullStats(stats);
    
    std::random_device devUrandom;
    std::mt19937_64 generator(devUrandom());
    uint64_t small_t = generator();

    mpz_t p, a, q, t;
    mpz_init_set_str(p, "CEA42B987C44FA642D80AD9F51F10457690DEF10C83D0BC1BCEE12FC3B6093E3", 16);
    mpz_init_set_str(a, "5B88C41246790891C095E2878880342E88C79974303BD0400B090FE38A688356", 16);
    mpz_init_set_str(q, "675215CC3E227D3216C056CFA8F8822BB486F788641E85E0DE77097E1DB049F1", 16);//(p-1)/2
    mpz_init_set_ui(t, small_t);

    for(size_t i = 0; i < SIZE; ++i)
    {
        for(size_t j = 0; j < 64; ++j)
        {
            mpz_powm(t, a, t, p);
            if(mpz_cmp(t, q) >= 0 )
            {
                stats[i] = stats[i] << 1; // sets last bit 0
            }
            else
            {
                stats[i] = ( (stats[i] << 1) | (0b1) ); //sets last bit 1
            }

        }
    }

    


    mpz_clear(p);
    mpz_clear(a);
    mpz_clear(q);
    mpz_clear(t);
}

void BMBytesGen(uint64_t* stats) //fix while in future and remove kost
{
    SetNullStats(stats);
    
    std::random_device devUrandom;
    std::mt19937_64 generator(devUrandom());
    uint64_t small_t = generator();

    mpz_t p, a, q, t;
    mpz_init_set_str(p, "CEA42B987C44FA642D80AD9F51F10457690DEF10C83D0BC1BCEE12FC3B6093E3", 16);
    mpz_init_set_str(a, "5B88C41246790891C095E2878880342E88C79974303BD0400B090FE38A688356", 16);
    mpz_init_set_str(q, "675215CC3E227D3216C056CFA8F8822BB486F788641E85E0DE77097E1DB049F1", 16);//(p-1)/2
    mpz_init_set_ui(t, small_t);

    mpz_t* preCalc = new mpz_t[256]; // all possible k-s 0 - 256;

    mpz_div_ui(q, q, (uint64_t)128);









    for(size_t i = 0 ; i < 256; ++i)
    {
        mpz_init(preCalc[i]);
    }
    for(size_t i = 0; i < 256; ++i)
    {
        mpz_mul_ui(preCalc[i], q, (uint64_t)i);
    }

    uint64_t step = 0;
    uint64_t count = 0;//kost
    for(size_t i = 0; i < SIZE; ++i)
    {
        for(size_t j = 0; j < 8; ++j)
        {
            mpz_powm(t, a, t, p);
            step = 0;
            while( !( (mpz_cmp(t, preCalc[step]) == 1 ) && (mpz_cmp(t, preCalc[ (step+1) % 256]) <= 0) )   )
            {
                ++step;
                if(step == 256)
                {  
                    ++count;
                    break;
                }

            }
            if(step == 256)
            {
                if(count % 2)
                {
                    stats[i] = (stats[i] << 8) | 0b11111111;
                }
                else
                {
                    stats[i] = (stats[i] << 8) | 0b100000000;
                }
            }
            else
            {
                stats[i] = (stats[i] << 8) | (step);
            }
        

        }
    }

    
    for(size_t i = 0; i < 256; ++i)
    {
        mpz_clear(preCalc[i]);
    }
    delete[]preCalc;


    mpz_clear(p);
    mpz_clear(a);
    mpz_clear(q);
    mpz_clear(t);
}





void BBSGen(uint64_t* stats)
{
    std::random_device devUrandom;
    std::mt19937_64 generator(devUrandom());
    SetNullStats(stats);



    uint64_t holder = 0;
    while(holder < 2)
    {
        holder = generator();
    }
    
    mpz_t p, q, n, ri;
    mpz_init_set_str(p, "D5BBB96D30086EC484EBA3D7F9CAEB07", 16);
    mpz_init_set_str(q, "425D2B9BFDB25B9CF6C416CC6E37B59C1F", 16);
    mpz_init_set_str(n, "1", 16);
    mpz_init_set_ui(ri, holder);
    mpz_mul(n, p, q);
    
    
    for(size_t i = 0 ; i < SIZE; ++i)
    {
        for(size_t j = 0; j < 64; ++j)
        {
            mpz_powm_ui(ri, ri, 2, n);
            holder = mpz_get_ui(ri);
            stats[i] = ((stats[i] << 1) | (holder & 0b1)) ;
        }
    }
        


    mpz_clear(p);
    mpz_clear(q);
    mpz_clear(n);
    mpz_clear(ri);

}

void BBSBytesGen(uint64_t* stats)
{
    std::random_device devUrandom;
    std::mt19937_64 generator(devUrandom());
    SetNullStats(stats);

    uint64_t holder = 0;
    while(holder < 2)
    {
        holder = generator();
    }
    
    mpz_t p, q, n, ri;
    mpz_init_set_str(p, "D5BBB96D30086EC484EBA3D7F9CAEB07", 16);
    mpz_init_set_str(q, "425D2B9BFDB25B9CF6C416CC6E37B59C1F", 16);
    mpz_init_set_str(n, "1", 16);
    mpz_init_set_ui(ri, holder);
    mpz_mul(n, p, q);
    
    
    for(size_t i = 0 ; i < SIZE; ++i)
    {
        for(size_t j = 0; j < 8; ++j)
        {
            mpz_powm_ui(ri, ri, 2, n);
            holder = mpz_get_ui(ri);
            stats[i] = ((stats[i] << 8) | (holder & 0b11111111)) ;
        }
    }
        


    
    mpz_clear(p);
    mpz_clear(q);
    mpz_clear(n);
    mpz_clear(ri);

}

