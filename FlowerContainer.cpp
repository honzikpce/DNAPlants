//
// Created by Honzik on 29.12.16.
//

#include <Rocket/Core/Factory.h>
#include "FlowerContainer.h"
#include "ConstsAndTypes.h"

FlowerContainer::FlowerContainer(glm::vec2 position, int capacity) {
    m_position = position;
    m_flowers.resize((size_t)capacity);
    for (int i = 0; i < m_capacity; i++) {
        m_flowers[i] = nullptr; // init all members just for safety
    }
    m_dims = glm::vec2(m_capacity * (FLOWER_TILE_W + FLOWER_TILE_MARGIN), FLOWER_TILE_H);

}

void FlowerContainer::addFlower(Flower *flower) {
    for (int i = 0; i < m_capacity; i++) {
        if (m_flowers[i] == nullptr) {
            // empty spot found, insert flower here
            m_flowers[i] = flower;
            flower->setContainer(this);
            flower->setPosition(glm::vec2(m_position.x + i * (FLOWER_TILE_W + FLOWER_TILE_MARGIN), m_position.y));
            flower->savePosition();
            return;
        }
    }
}

FlowerContainer::FlowerContainer() {

}

void FlowerContainer::setPosition(glm::vec2 position) {
    m_position = position;
}

bool FlowerContainer::dropFlower(Flower * flower) {
    glm::vec2 point = flower->getPosition() + glm::vec2(FLOWER_TILE_W / 2.0f, FLOWER_TILE_H / 2.0f);

    // check if drop coords are in the container's rect
    if (!(point.x > m_position.x &&
        point.x < m_position.x + m_dims.x &&
        point.y > m_position.y &&
        point.y < m_position.y + m_dims.y)) return false; ///< not in this rectangle

    int cellNum = (point.x - m_position.x) / (int)(FLOWER_TILE_W + FLOWER_TILE_MARGIN);
    if (m_flowers[cellNum]== nullptr) {
        // insert flower
        m_flowers[cellNum] = flower;
        flower->getContainer()->removeFlower(flower); ///< remove from the old one
        flower->setContainer(this); ///< add to this one
        flower->setPosition(glm::vec2(m_position.x + cellNum * (FLOWER_TILE_W + FLOWER_TILE_MARGIN), m_position.y));
        flower->savePosition();
        return true; ///< successfully added
    }
    else return false; ///< the slot is not empty

}

void FlowerContainer::removeFlower(Flower *flower) {
    for (int i = 0; i < m_capacity; i++) {
        if (m_flowers[i] == flower)
            m_flowers[i] = nullptr; ///< removing the flower
    }
}
