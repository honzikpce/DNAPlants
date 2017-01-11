//
// Created by Honzik on 26.12.16.
//

#include "App.h"


void App::onInit() {

}

void App::addScreens() {


    // BEWARE - indexes matters!!!
    _screenList->addScreen(&m_mainMenuScreen); ///< 0

    _screenList->addScreen(&m_greenHouseScreen); ////< 1


    _screenList->setScreen(m_mainMenuScreen.getScreenIndex());


}

void App::onExit() {

}
