//
// Created by Honzik on 07.01.17.
//

#include <JN/ResourceManager.hpp>
#include "InsectBug.h"
#include "RandomNumbers.hpp"

#include <glm/gtx/rotate_vector.hpp>

InsectBug::InsectBug(glm::vec2 centerPosition)
: m_centerPosition(centerPosition), m_maxDistance(30.0f), m_position(glm::vec2()),
  m_speed(0.3f), m_texture(0), m_dims(glm::vec2(10.0f, 10.0f))
{
    m_changeFactor = RandomNumbers::getFloat(0.0001f, 0.001f);
    m_angleFactor = RandomNumbers::getFloat(-0.03f, 0.03f);
    m_speed = RandomNumbers::getFloat(0.4f, 0.9f);

    m_direction = glm::vec2(1.0f, 0.0f);
    m_texture = JN::ResourceManager::getTexture("../textures/cartoon_fly.png").id;
}

void InsectBug::draw(JN::SpriteBatch &spriteBatch) {
    if (m_position.x > 0.0f) {
        spriteBatch.draw(glm::vec4(m_centerPosition + m_position - m_dims / 2.0f, m_dims),
                         glm::vec4(0.0f, 0.0f, -1.0f, 1.0f), m_texture, 1.0f, JN::Color(255, 255, 255, 255));
    }
    else {
        spriteBatch.draw(glm::vec4(m_centerPosition + m_position - m_dims / 2.0f, m_dims),
                         glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), m_texture, 1.0f, JN::Color(255, 255, 255, 255));
    }
}

void InsectBug::update() {

    //m_angleFactor = m_angleFactor + m_changeFactor;
    m_direction = glm::rotate(m_direction, RandomNumbers::getFloat(-0.4f, 0.4f));
    m_position = m_position + m_direction * m_speed;

    if (glm::length(m_position) > m_maxDistance) {
        // bug is far away from center... lets fix the direction back to the flower
        m_direction = glm::rotate(glm::normalize(m_position), RandomNumbers::getFloat(3.1f, 3.2f));
    }


}

void InsectBug::setPosition(glm::vec2 position) {
    m_centerPosition = position;

}
