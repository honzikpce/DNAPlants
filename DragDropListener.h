//
// Created by Honzik on 29.12.16.
//

#ifndef DNAPLANTS_DRAGDROPLISTENER_H
#define DNAPLANTS_DRAGDROPLISTENER_H

#include <Rocket/Core.h>

class DragDropListener: public Rocket::Core::EventListener {

protected:

    virtual void ProcessEvent(Rocket::Core::Event& event) override;

public :

void static registerContainer(Rocket::Core::Element * element);


};


#endif //DNAPLANTS_DRAGDROPLISTENER_H
