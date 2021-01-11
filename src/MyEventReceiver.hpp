#include <irrlicht.h>
#include <iostream>
#include <map>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;




class MyEventReceiver : public IEventReceiver
{
public:

	MyEventReceiver();
	bool OnEvent(const SEvent& event);
	bool IsKeyDown(EKEY_CODE keyCode) const;

	struct SMouseState
    {
    	position2di Position;
        bool LeftButtonDown;
        SMouseState() : LeftButtonDown(false) { }
    } MouseState;

   

private:

	std::map<EKEY_CODE,bool> keys;


};

