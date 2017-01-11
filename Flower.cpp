//
// Created by Honzik on 26.12.16.
//

#include <JN/SpriteBatch.hpp>
#include <JN/ResourceManager.hpp>
#include <JN/Errors.hpp>
#include <JN/ControlManager.hpp>
#include "Flower.h"
#include "ConstsAndTypes.h"



Flower::Flower() {
    // default values without parents
    m_parents.push_back(nullptr);
    m_parents.push_back(nullptr);

    loadTextures();

    m_onclick = new MouseEvent();
    m_onMouseOver = new MouseEvent();
    m_onMouseOut = new MouseEvent();
    m_onMouseDrop = new MouseEvent();



    // create rocket gui elements
    m_guiElement = Rocket::Core::Factory::InstanceElement(NULL, "flower", "flower", Rocket::Core::XMLAttributes());


    m_healthBar.init("health", glm::vec2(50.0f, 4.0f));
    m_healthBar.setPosition(glm::vec2(-5.0f, -15.0f));
    getGuiElement()->AppendChild(m_healthBar.getGuiElement());

    m_waterBar.init("water", glm::vec2(50.0f, 4.0f));
    m_waterBar.setPosition(glm::vec2(-5.0f, -12.0f));
    getGuiElement()->AppendChild(m_waterBar.getGuiElement());

    // register gui element for getting events
    m_guiElement->AddEventListener("click", this);
    m_guiElement->AddEventListener("mouseover", this);
    m_guiElement->AddEventListener("mouseout", this);


}

Flower::Flower(int leafType, int bloomType, JN::Color leafColor, JN::Color bloomColor) : Flower() {

    // ^^ note calling default constructor first.

    // init flower with additional params
    leafType = m_leafType;
    leafColor = m_leafColor;
    bloomType = m_bloomType;
    bloomColor = m_bloomColor;
}

Flower::Flower(Flower *parent1, Flower *parent2) {
    // generate properties from parents
    m_parents.push_back(parent1);
    m_parents.push_back(parent2);
    // TODO
}

void Flower::water() {
    setWater(m_water + 0.2f);
}

void Flower::update(JN::ControlManager &controlManager, JN::Camera2D &camera) {


    // PROCESS INPUTS AND EVENTS
    glm::vec2 mouseCoords = camera.convertScreenToWorld(controlManager.getMouseCoords());
    bool isMouseOverNow = isInBoundingBox(mouseCoords);
    // is clicked inside flower box
    if (controlManager.isMouseClicked() && isMouseOverNow) (*m_onclick)(this);

    // mouse over event
    if (isMouseOverNow && !m_isMouseOver) {
        m_isMouseOver = true;
        (*m_onMouseOver)(this);
    }

    // mouse out event
    if (m_isMouseOver && !isMouseOverNow) {
        m_isMouseOver = false;
        (*m_onMouseOut)(this);
    }

    // mouse dragging
    if (controlManager.isMouseDragged() && isInBoundingBox(camera.convertScreenToWorld(controlManager.getMouseCoords()))) {
        m_isDragged = true;
    }

    // drop event
    if (m_isDragged && controlManager.isDragFinished()) {
        m_isDragged = false;
        (*m_onMouseDrop)(this);
    }
    // set position when dragged
    if (m_isDragged) {
        setPosition(camera.convertScreenToWorld(controlManager.getMouseCoords()) - glm::vec2(0.0f, m_objectDims.y / 2.0f));
    }

    // UPDATE BUGS
    for (auto & bug : m_bugs) {
        bug.update();
    }

}

void Flower::setWater(float newValue) {
    m_water = newValue;
    m_waterBar.setValue(newValue);
}

void Flower::setHealth(float newValue) {
    m_health = newValue;
    m_healthBar.setValue(newValue);
}

void Flower::ProcessEvent(Rocket::Core::Event &event) {


    if (event.GetType() == "click") {
        (*m_onclick)(this); // calling onClick event handlers
    }
    if (event.GetType() == "mouseover") {
        (*m_onMouseOver)(this); // calling onClick event handlers
    }
    if (event.GetType() == "mouseout") {
        (*m_onMouseOut)(this); // calling onClick event handlers
    }

}

boost::signals2::connection Flower::doOnClick(const Flower::MouseEventSlotType &slot) {
    return m_onclick->connect(slot);
}

boost::signals2::connection Flower::doOnMouseOver(const Flower::MouseEventSlotType &slot) {
    return m_onMouseOver->connect(slot);
}

boost::signals2::connection Flower::doOnMouseOut(const Flower::MouseEventSlotType &slot) {
    return m_onMouseOut->connect(slot);
}

boost::signals2::connection Flower::doOnMouseDrop(const Flower::MouseEventSlotType &slot) {
    return m_onMouseDrop->connect(slot);
}

glm::vec2 Flower::getPosition() {
    return m_position;
}

void Flower::draw(JN::SpriteBatch &spriteBatch) {
    // drawing everything x center aligned

    // draw flowerpot
    spriteBatch.draw(glm::vec4(m_position.x - m_flowerpotDims.x / 2.0f, m_position.y, m_flowerpotDims.y, m_flowerpotDims.y),
                     glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), m_texturePot.id, 1.0f, JN::Color(255, 255, 255, 255));

    // DRAW BUGS
    for (auto & bug : m_bugs) {
        bug.draw(spriteBatch);
    }
}

void Flower::setPosition(glm::vec2 position) {
    m_position = position;

    for (auto & bug : m_bugs) {
        bug.setPosition(position + glm::vec2(0.0f, FLOWER_TILE_H));
    }
}

void Flower::loadTextures() {
    m_texturePot = JN::ResourceManager::getTexture("../textures/flowerpot.png");

}

bool Flower::isInBoundingBox(const glm::vec2 &point) {
    if (point.x > m_position.x - m_objectDims.x / 2.0f &&
        point.x < m_position.x + m_objectDims.x / 2.0f &&
        point.y > m_position.y &&
        point.y < m_position.y + m_objectDims.y) {
        return true;
    }
    return false;
}

void Flower::addBug() {
    m_bugs.emplace_back(m_position + glm::vec2(0.0f, m_flowerpotDims.y * 2.0f));

}


