//
// Created by Honzik on 26.12.16.
//

#include "GreenHouse.h"
#include "ConstsAndTypes.h"
#include <JN/IMainGame.hpp>

int GreenHouse::getNextScreenIndex() const {
    return SCREEN_INDEX_NO_SCREEN;
}

int GreenHouse::getPrevScreenIndex() const {
    return SCREEN_MAIN_MENU;
}

void GreenHouse::build() {
    // camera init
    m_camera.init(SCREEN_W, SCREEN_H);
    m_camera.setPosition(glm::vec2(SCREEN_W / 2.0f, SCREEN_H / 2.0f));
    m_cameraGUI.init(SCREEN_W, SCREEN_H);
    m_cameraGUI.setPosition(glm::vec2(SCREEN_W / 2.0f, SCREEN_H / 2.0f));
    m_cameraGUI.flipY();

    // gui init
    m_gui.init(&m_cameraGUI, "greenhouse");
    m_controlManager = _mainGame->getControlManager();


    // spritebatch init
    m_spriteBatch.init();
    m_spriteBatchInsects.init();

    // shaders init
    m_textureProgram.addAttribute("vertexPosition");
    m_textureProgram.addAttribute("vertexColor");
    m_textureProgram.addAttribute("vertexUV");
    m_textureProgram.compileShaders("../shaders/simple.vert","../shaders/simple.frag");


    initFlowers();

    // create control window with progress bars
    m_controlWindow = m_gui.loadDocument("../gui-assets/ControlWindow.rml");
    m_controlWindowHealth.init("health", glm::vec2(150, 25), 3);
    m_controlWindowWater.init("water", glm::vec2(150, 25), 3);
    m_controlWindow->GetElementById("healthinfo")->AppendChild(m_controlWindowHealth.getGuiElement());
    m_controlWindow->GetElementById("waterinfo")->AppendChild(m_controlWindowWater.getGuiElement());


    m_controlWindowWater.setValue(0.8f);

}

void GreenHouse::onEntry() {
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f); ///< set background color

    // start injecting events to GUI
    m_controlManager->attachGui(&m_gui);

    m_controlWindow->Show();
}

void GreenHouse::update() {
    processInput();
    m_camera.update();
    m_cameraGUI.update();

    for (int i = 0; i < m_flowers.size(); i++) {
        m_flowers[i]->update(*m_controlManager, m_camera);
    }

    m_gui.update(SDL_GetTicks() / 1000.0f);

}

void GreenHouse::processInput() {
    // handle control events
    SDL_Event evnt;

    while (SDL_PollEvent(&evnt))
        _mainGame->onSDLEvent(evnt);


    if (m_controlManager->isKeyPressed(SDLK_ESCAPE)) {
        _screenState = JN::ScreenState::CHANGE_PREVIOUS;
    }

    if (m_controlManager->isMouseClicked()) {
        printf("mouse clicked!\n");
    }
    if (m_controlManager->isMouseDragged()) {
        printf("mouse dragged from %f : %f\n", m_controlManager->getDragStartCoords().x, m_controlManager->getDragStartCoords().y);
    }


}

void GreenHouse::draw() {
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); ///< clear screen to bg color

    m_textureProgram.use();

    // activate first texture slot
    glActiveTexture(GL_TEXTURE0);

    // upload uniforms to shaders
    GLint camLocation = m_textureProgram.getUniformLocation("P");
    glUniformMatrix4fv(camLocation, 1, GL_FALSE, &m_camera.getCameraMatrix()[0][0]);

    GLint textureLocation = m_textureProgram.getUniformLocation("mySampler");
    glUniform1i(textureLocation, 0);

    m_spriteBatch.begin();

    // draw background
    m_spriteBatch.draw(glm::vec4(0.0f, 0.0f, SCREEN_W, SCREEN_H),
                       glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
                       JN::ResourceManager::getTexture("../textures/bg.png").id, 1.0, JN::Color());

    // draw flowers
    for (int i = 0; i < m_flowers.size(); i++) {
        m_flowers[i]->draw(m_spriteBatch);
    }

    m_spriteBatch.end();
    m_spriteBatch.renderBatch();
    m_textureProgram.unUse();

    m_gui.draw();


    // special effects
    m_textureProgram.use();
    m_spriteBatchInsects.begin();

    m_spriteBatchInsects.end();
    m_spriteBatchInsects.renderBatch();
    m_textureProgram.unUse();
}

void GreenHouse::onExit() {

}


void GreenHouse::destroy() {

}

void GreenHouse::initFlowers() {

    // create flower containers


    m_flowerContainers.emplace_back(glm::vec2(580.0f, 390.0f), 3);
    m_flowerContainers.emplace_back(glm::vec2(580.0f, 275.0f), 3);
    m_flowerContainers.emplace_back(glm::vec2(580.0f, 165.0f), 3);
    m_flowerContainers.emplace_back(glm::vec2(330.0f, 108.0f), 3);

    m_flowerContainers.emplace_back(glm::vec2(70.0f, 390.0f), 3);
    m_flowerContainers.emplace_back(glm::vec2(70.0f, 275.0f), 3);
    m_flowerContainers.emplace_back(glm::vec2(70.0f, 165.0f), 3);


    // create flowers one on each location
    for (int i = 0; i < 7; i++){
        Flower * flower = new Flower();
        // test only
        flower->setWater(i * 0.05f);
        flower->setHealth(1.0f - i * 0.05f);
        flower->addBug();
        flower->addBug();

        m_flowerContainers[i % 7].addFlower(flower);
        m_flowers.push_back(flower);


        m_flowers.back()->doOnClick(
                // lambda to call class method - fix to only static function calls
                [this](Flower * f) {
                    this->OnFlowerClick(f);
                });

        m_flowers.back()->doOnMouseOver(
                // lambda to call class method - fix to only static function calls
                [this](Flower * f) {
                    this->OnFlowerMouseOver(f);
                });

        m_flowers.back()->doOnMouseOut(
                // lambda to call class method - fix to only static function calls
                [this](Flower * f) {
                    this->OnFlowerMouseOut(f);
                });
        m_flowers.back()->doOnMouseDrop(
                // lambda to call class method - fix to only static function calls
                [this](Flower * f) {
                    this->OnFlowerMouseDrop(f);
                });





    }

}

void GreenHouse::ProcessEvent(Rocket::Core::Event &event) {

}

void GreenHouse::OnFlowerClick(Flower *clickedFlower) {
    clickedFlower->water();
    OnFlowerMouseOver(clickedFlower);
}

void GreenHouse::OnFlowerMouseOver(Flower *clickedFlower) {
    m_controlWindowHealth.setValue(clickedFlower->getHealth());
    m_controlWindowWater.setValue(clickedFlower->getWater());
}

void GreenHouse::OnFlowerMouseOut(Flower *clickedFlower) {
    //clickedFlower->setWater(0.0f);
}

void GreenHouse::OnFlowerMouseDrop(Flower *clickedFlower) {
    printf("flower was dropped\n");
    for (int i = 0; i < m_flowerContainers.size(); i++) {
        if (m_flowerContainers[i].dropFlower(clickedFlower)) {
            return;
        }
    }
    // haven't drop into any container, restoring previous position
    clickedFlower->restorePreviousPosition();
}



