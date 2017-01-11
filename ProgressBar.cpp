//
// Created by Honzik on 31.12.16.
//

#include "ProgressBar.h"

void ProgressBar::init(const char *elementName, glm::vec2 dimensions, int border) {

    m_border = border;
    m_dims = dimensions;

    m_element = Rocket::Core::Factory::InstanceElement(NULL, elementName, elementName, Rocket::Core::XMLAttributes());
    m_fillElement = Rocket::Core::Factory::InstanceElement(NULL,
                                                       Rocket::Core::String(elementName) + "-fill",
                                                       Rocket::Core::String(elementName) + "-fill",
                                                       Rocket::Core::XMLAttributes());
    m_frameElement = Rocket::Core::Factory::InstanceElement(NULL,
                                                       Rocket::Core::String(elementName) + "-frame",
                                                       Rocket::Core::String(elementName) + "-frame",
                                                       Rocket::Core::XMLAttributes());

    // add child elements - frame first to be at back
    m_element->AppendChild(m_frameElement);
    m_element->AppendChild(m_fillElement);


    // set up the wrapper element
    m_element->SetProperty("position", "absolute");
    // dimensions
    m_element->SetProperty("width", Rocket::Core::Property(dimensions.x, Rocket::Core::Property::PX));
    m_element->SetProperty("height", Rocket::Core::Property(dimensions.y, Rocket::Core::Property::PX));

    // frame element's located at the origin

    // fill element is shifted by a border width
    m_fillElement->SetProperty("top", Rocket::Core::Property(float(border), Rocket::Core::Property::PX));
    m_fillElement->SetProperty("left", Rocket::Core::Property(float(border), Rocket::Core::Property::PX));

    // frame element dims
    m_frameElement->SetProperty("width", Rocket::Core::Property(dimensions.x, Rocket::Core::Property::PX));
    m_frameElement->SetProperty("height", Rocket::Core::Property(dimensions.y, Rocket::Core::Property::PX));

    // fill element dims (width gets value from m_value)
    m_fillElement->SetProperty("height", Rocket::Core::Property(m_dims.y - 2.0f * m_border, Rocket::Core::Property::PX));
    setValue(m_value);

}

Rocket::Core::Element *ProgressBar::getGuiElement() {
    return m_element;
}

void ProgressBar::setValue(float value) {
    // max value 1.0f
    if (value >= 1.0f) m_value = 1.0f;
    else m_value = value;

    m_fillElement->SetProperty("width", Rocket::Core::Property(m_value * m_dims.x - 2.0f * m_border, Rocket::Core::Property::PX));

}


void ProgressBar::setPosition(glm::vec2 position) {
    m_element->SetProperty("top", Rocket::Core::Property(position.y, Rocket::Core::Property::PX));
    m_element->SetProperty("left", Rocket::Core::Property(position.x, Rocket::Core::Property::PX));
}

