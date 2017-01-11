//
// Created by Honzik on 06.01.17.
//

#ifndef DNAPLANTS_MAINMENU_H
#define DNAPLANTS_MAINMENU_H

#include <JN/IGameScreen.hpp>
#include <JN/GUI.h>


class MainMenu : public JN::IGameScreen, public Rocket::Core::EventListener {

public:
    int getNextScreenIndex() const override;

    int getPrevScreenIndex() const override;

    void ProcessEvent(Rocket::Core::Event &event) override;

    void build() override;

    void destroy() override;

    void onEntry() override;

    void onExit() override;

    void update() override;

    void draw() override;

private:

    JN::Camera2D m_cameraGUI;

    JN::GUI m_gui;

    JN::ControlManager *m_controlManager;

    Rocket::Core::ElementDocument * m_menuWindow;
};


#endif //DNAPLANTS_MAINMENU_H
