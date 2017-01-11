//
// Created by Honzik on 29.12.16.
//

#include "DragDropListener.h"

static DragDropListener listener;

void DragDropListener::registerContainer(Rocket::Core::Element *element) {
    element->AddEventListener("dragdrop", &listener);


}

void DragDropListener::ProcessEvent(Rocket::Core::Event &event) {
    printf("event fired\n");
    if (event.GetType() == "dragdrop") {

        Rocket::Core::Element * targetContainer = event.GetCurrentElement();
        Rocket::Core::Element * draggedElement = static_cast< Rocket::Core::Element* >(event.GetParameter< void* >("drag_element", NULL));

        // remove from parent and add to the new container
        draggedElement->GetParentNode()->RemoveChild(draggedElement);
        targetContainer->AppendChild(draggedElement);
    }

}
