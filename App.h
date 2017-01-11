//
// Created by Honzik on 26.12.16.
//

#ifndef DNAPLANTS_APP_H
#define DNAPLANTS_APP_H

#include <JN/IMainGame.hpp>
#include <JN/IGameScreen.hpp>
#include "GreenHouse.h"
#include "MainMenu.h"

class App: public JN::IMainGame {

public:

private:
    void onInit() override;

    void addScreens() override;

    void onExit() override;

    GreenHouse m_greenHouseScreen;
    MainMenu m_mainMenuScreen;



};


#endif //DNAPLANTS_APP_H
