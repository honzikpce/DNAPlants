//
// Created by Honzik on 07.01.17.
//

#ifndef DNAPLANTS_INSECTBUG_H
#define DNAPLANTS_INSECTBUG_H


#include <glm/vec2.hpp>
#include <JN/SpriteBatch.hpp>

class InsectBug {

public:

    InsectBug(glm::vec2 centerPosition);
    void draw(JN::SpriteBatch &spriteBatch);
    void setPosition(glm::vec2 position);
    void update();


private:

    // movement stuff
    glm::vec2 m_position;
    float m_speed = 0.3f;
    glm::vec2 m_direction;
    glm::vec2 m_centerPosition;
    float m_maxDistance;
    float m_changeFactor = 0.02f;
    float m_angleFactor = 0.02f;

    // graphic stuff
    GLuint m_texture;
    glm::vec2 m_dims;

};


#endif //DNAPLANTS_INSECTBUG_H
