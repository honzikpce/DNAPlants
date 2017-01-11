//
// Created by Honzik on 06.01.17.
//

#include "MainMenu.h"
#include "ConstsAndTypes.h"
#include <JN/IMainGame.hpp>

int MainMenu::getNextScreenIndex() const {
    return SCREEN_GREENHOUSE;
}

int MainMenu::getPrevScreenIndex() const {
    return SCREEN_INDEX_NO_SCREEN;
}

void MainMenu::build() {

    m_cameraGUI.init(SCREEN_W, SCREEN_H);
    m_cameraGUI.setPosition(glm::vec2(SCREEN_W / 2.0f, SCREEN_H / 2.0f));
    m_cameraGUI.flipY();

    // gui init
    m_gui.init(&m_cameraGUI, "mainmenu");
    m_controlManager = _mainGame->getControlManager();


    m_menuWindow = m_gui.loadDocument("../gui-assets/MainMenu.rml");
    m_menuWindow->AddEventListener("click", this);

}

void MainMenu::destroy() {

}

void MainMenu::onEntry() {
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f); ///< set background color

    // start injecting events to GUI
    m_controlManager->attachGui(&m_gui);

    m_menuWindow->Show();
}

void MainMenu::onExit() {

}

void MainMenu::update() {

    SDL_Event evnt;

    while (SDL_PollEvent(&evnt))
        _mainGame->onSDLEvent(evnt);

    m_cameraGUI.update();

    m_gui.update(SDL_GetTicks() / 1000.0f);
}

void MainMenu::draw() {

    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); ///< clear screen to bg color


    m_gui.draw();
}

void MainMenu::ProcessEvent(Rocket::Core::Event &event) {

    if (event.GetType() == "click") {
        Rocket::Core::Element * clickedElement = event.GetTargetElement();
        if (clickedElement->GetId() == "start") {
            _screenState = JN::ScreenState::CHANGE_NEXT;
        }
        if (clickedElement->GetId() == "exit") {
            _screenState = JN::ScreenState::EXIT_APPLICATION;
        }
    }
}
