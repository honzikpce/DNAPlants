//
// Created by Honzik on 31.12.16.
//

#ifndef DNAPLANTS_PROGRESSBAR_H
#define DNAPLANTS_PROGRESSBAR_H

#include <Rocket/Core.h>
#include <glm/vec2.hpp>

class ProgressBar {


public:

    void init(const char * elementName, glm::vec2 dimensions, int border = 1);

    void setValue(float value);
    float getValue() const { return m_value; }
    Rocket::Core::Element * getGuiElement();

    void setPosition(glm::vec2 position);


protected:
    float m_value = 1.0f;
    int m_border = 1;
    Rocket::Core::Element * m_element = nullptr;
    Rocket::Core::Element * m_fillElement = nullptr;
    Rocket::Core::Element * m_frameElement = nullptr;
    glm::vec2 m_dims;
};


#endif //DNAPLANTS_PROGRESSBAR_H
