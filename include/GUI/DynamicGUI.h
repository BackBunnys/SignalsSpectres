#ifndef DYNAMICGUI_H
#define DYNAMICGUI_H

#include "GUI.h"

class DynamicGUI: public GUI
{
    public:
        virtual void update() = 0;
        virtual ~DynamicGUI() {}
};


#endif // DYNAMICGUI_H
