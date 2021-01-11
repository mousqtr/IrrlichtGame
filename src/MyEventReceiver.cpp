#include <irrlicht.h>
#include "MyEventReceiver.hpp"
#include <iostream>
#include <map>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;



MyEventReceiver::MyEventReceiver()
{
	
	
	keys[KEY_ESCAPE] = 0;
	keys[KEY_KEY_C] = 0;
	keys[KEY_KEY_V] = 0;


}



bool MyEventReceiver::OnEvent(const SEvent& event)
{

	if (event.EventType == EET_KEY_INPUT_EVENT){
		keys[event.KeyInput.Key] = event.KeyInput.PressedDown;
	}
	if (event.EventType == EET_MOUSE_INPUT_EVENT){  
        switch(event.MouseInput.Event)
        {
        case EMIE_LMOUSE_PRESSED_DOWN:
            MouseState.LeftButtonDown = true;
            break;

        case EMIE_LMOUSE_LEFT_UP:
            MouseState.LeftButtonDown = false;
            break;

        case EMIE_MOUSE_MOVED:
            MouseState.Position.X = event.MouseInput.X;
            MouseState.Position.Y = event.MouseInput.Y;
            break;

        default:
            // We won't use the wheel
            break;
        }
		
	}

	return false;
}


bool MyEventReceiver::IsKeyDown(EKEY_CODE keyCode) const
{
	return keys.find(keyCode)->second;
}









