//
// Created by Honzik on 26.12.16.
//

#ifndef DNAPLANTS_GREENHOUSE_H
#define DNAPLANTS_GREENHOUSE_H


#include <JN/IGameScreen.hpp>
#include <JN/Camera2D.hpp>
#include <JN/GUI.h>
#include <JN/SpriteBatch.hpp>
#include <JN/ControlManager.hpp>
#include <JN/GLSLProgram.hpp>
#include "FlowerContainer.h"
#include "InsectBug.h"


class GreenHouse: public JN::IGameScreen, public Rocket::Core::EventListener {
public:

    int getNextScreenIndex() const override;

    int getPrevScreenIndex() const override;

    void build() override;

    void destroy() override;

    void onEntry() override;

    void onExit() override;

    void update() override;

    void draw() override;



private:

    void OnFlowerClick(Flower *clickedFlower);

    void OnFlowerMouseOver(Flower *clickedFlower);

    void OnFlowerMouseOut(Flower *clickedFlower);

    void OnFlowerMouseDrop(Flower *clickedFlower);

    void ProcessEvent(Rocket::Core::Event &event) override;

    void processInput();

    void initFlowers();

    JN::Camera2D m_camera;
    JN::Camera2D m_cameraGUI;

    JN::GUI m_gui;

    JN::SpriteBatch m_spriteBatch;
    JN::SpriteBatch m_spriteBatchInsects;

    JN::ControlManager *m_controlManager;

    JN::GLSLProgram m_textureProgram;

    Flower * m_testFlower = nullptr;

    std::vector<FlowerContainer> m_flowerContainers;
    std::vector<Flower *> m_flowers;

    Rocket::Core::ElementDocument * m_controlWindow = nullptr;
    ProgressBar m_controlWindowHealth;
    ProgressBar m_controlWindowWater;

};


#endif //DNAPLANTS_GREENHOUSE_H
