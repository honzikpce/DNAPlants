//
// Created by Honzik on 29.12.16.
//

#ifndef DNAPLANTS_FLOWERCONTAINER_H
#define DNAPLANTS_FLOWERCONTAINER_H


#include <Rocket/Core/ElementDocument.h>
#include "Flower.h"

class FlowerContainer {

public :
    FlowerContainer();
    FlowerContainer(glm::vec2 position, int capacity);
    void addFlower(Flower *flower);
    void setPosition(glm::vec2 position);
    bool dropFlower(Flower * flower);
    void removeFlower(Flower * flower);


protected :
    glm::vec2 m_position;
    glm::vec2 m_dims;
    int m_capacity = 3;
    std::vector<Flower *> m_flowers;





};


#endif //DNAPLANTS_FLOWERCONTAINER_H
