#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
			unsigned long long w[5] = {0, 0, 0, 0, 0};
			int x = 4; 

		//loop through in revere order - in groups of 6
			for(int i = k.size()-6; i >= 0; i-=6){
				std::string substring = k.substr(i,6); // make substring of 6 
				for (int j = 0; j < 6; j++){
						w[x] *= 36; // base 36
						w[x] += letterDigitToNumber(substring[j]); // convert using helper 
				}
				x--; 
		}

// would not form a 6 char block
		if(k.size() % 6 != 0){ // if k is not a multiple of 6
			std::string rest = k.substr(0, k.size() - (6 * (4 - x))); // beginning values
			for (int k = 0; k < int(rest.size()); k++){ // repeat from above 
        w[x] *= 36;
        w[x] += letterDigitToNumber(rest[k]);
      }
		}

		HASH_INDEX_T hashes = 0; // hash it 
    for(int y = 0; y < 5; y++){
      hashes += rValues[y] * w[y];
    }
    return hashes;

		}
 

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
				HASH_INDEX_T converted; 
				 
				if (letter >='a' && letter <= 'z'){ // if lowecase 
          converted = (int)letter - 97;
				}
        else if (letter >= 'A' && letter <= 'Z'){ // if capital
          converted = (int)letter - 65;
				}
        else if (letter >= '0' && letter <= '9'){ // if number 
          converted = (int)letter - 22;
				}

        return converted;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
