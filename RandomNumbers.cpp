//
//  RandomNumbers.cpp
//  GameEngine
//
//  Created by Honzik on 22.11.16.
//  Copyright © 2016 Honzik. All rights reserved.
//

#include "RandomNumbers.hpp"

// static members init
std::random_device RandomNumbers::_rnd_dev;
std::mt19937 RandomNumbers::_generator = std::mt19937(_rnd_dev());
std::uniform_real_distribution<float> RandomNumbers::_rnd_coords;

RandomNumbers::RandomNumbers(){
    
    
}


RandomNumbers::~RandomNumbers(){
    
    
}


float RandomNumbers::getFloat(float min, float max) {
    _rnd_coords = std::uniform_real_distribution<float>(min,max);
    return _rnd_coords(_rnd_dev);
}
