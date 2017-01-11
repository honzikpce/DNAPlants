//
// Created by Honzik on 26.12.16.
//

#ifndef DNAPLANTS_FLOWER_H
#define DNAPLANTS_FLOWER_H

#include <JN/SpriteBatch.hpp>
#include <JN/Vertex.h>
#include <vector>
#include <glm/vec2.hpp>
#include <Rocket/Core.h>
#include "ProgressBar.h"
#include "InsectBug.h"
#include <functional>
#include <JN/glTexture.h>
#include <boost/signals2.hpp>
#include <JN/ControlManager.hpp>


class FlowerContainer; ///< fwd declaration for having pointer to current container

class Flower : public Rocket::Core::EventListener {

    typedef boost::signals2::signal<void (Flower *)> MouseEvent;

public:

    typedef MouseEvent::slot_type MouseEventSlotType;

    Flower();
    Flower(int leafType, int bloomType, JN::Color leafColor, JN::Color bloomColor);
    Flower(Flower * parent1, Flower * parent2);

    void water();

    void update(JN::ControlManager &controlManager, JN::Camera2D &camera);

    void draw(JN::SpriteBatch &spriteBatch);

    void restorePreviousPosition() { m_position = m_positionBeforeDrag; }

    void savePosition() { m_positionBeforeDrag = m_position; }


    // setters
    void setPosition(glm::vec2 position);
    void setBloomColor(JN::Color color) { m_bloomColor = color; }
    void setWater(float newValue);
    void setHealth(float newValue);
    void setContainer(FlowerContainer * container) { m_currentContainer = container; }

    // getters
    Rocket::Core::Element * getGuiElement() { return m_guiElement; }
    float getHealth() { return m_health; }
    float getWater() { return m_water; }
    glm::vec2 getPosition();
    FlowerContainer * getContainer() { return m_currentContainer; }


    void ProcessEvent(Rocket::Core::Event &event) override;
    void addBug();

    // sets the handler for click event
    boost::signals2::connection doOnClick(const MouseEventSlotType &slot);
    boost::signals2::connection doOnMouseOver(const MouseEventSlotType &slot);
    boost::signals2::connection doOnMouseOut(const MouseEventSlotType &slot);
    boost::signals2::connection doOnMouseDrop(const MouseEventSlotType &slot);


protected:

    void loadTextures();

    bool isInBoundingBox(const glm::vec2 &point);

    // must be a pointer cause boost::signal2 uses copy deleted constructor
    MouseEvent * m_onclick;
    MouseEvent * m_onMouseOver;
    MouseEvent * m_onMouseOut;
    MouseEvent * m_onMouseDrop;

    JN::GLTexture m_texturePot;
    FlowerContainer * m_currentContainer = nullptr;
    glm::vec2 m_objectDims = glm::vec2(60.0f, 60.0f); ///<< for click events etc
    bool m_isMouseOver = false;
    bool m_isDragged = false;

    glm::vec2 m_position = glm::vec2();
    glm::vec2 m_flowerpotDims = glm::vec2(50.0f, 50.0f);
    glm::vec2 m_bloomOffset = glm::vec2();
    glm::vec2 m_positionBeforeDrag = glm::vec2();


    // leaf
    JN::Color m_leafColor = JN::Color(255,255,255,255);
    int m_leafType = 0;
    glm::vec2 m_leafDims = glm::vec2();
    GLuint m_leafTexture = 0;

    JN::Color m_bloomColor = JN::Color(255,255,255,255);
    int m_bloomType = 0;
    glm::vec2 m_bloomDims = glm::vec2();
    GLuint m_bloomTexture = 0;

    int m_growStage = 0;

    float m_water = 0;
    float m_health = 0;

    ProgressBar m_healthBar;
    ProgressBar m_waterBar;

    std::vector<InsectBug> m_bugs;
    std::vector<Flower *> m_parents;

    Rocket::Core::Element * m_guiElement;
};


#endif //DNAPLANTS_FLOWER_H
