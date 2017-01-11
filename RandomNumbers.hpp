//
//  RandomNumbers.hpp
//  GameEngine
//
//  Created by Honzik on 22.11.16.
//  Copyright © 2016 Honzik. All rights reserved.
//

#ifndef RandomNumbers_hpp
#define RandomNumbers_hpp

#include <stdio.h>
#include <random>

class RandomNumbers {

    private :
    
    static std::random_device _rnd_dev;
    static std::mt19937 _generator;
    static std::uniform_real_distribution<float> _rnd_coords;
    
    
    public :
    RandomNumbers();
    ~RandomNumbers();
    static float getFloat(float min, float max);
    
};




#endif /* RandomNumbers_hpp */
