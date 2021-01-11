#include <irrlicht.h>
#include <iostream>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;




class Camera
{
public:

	Camera(IrrlichtDevice* device);
	ICameraSceneNode* getCameraNode();


private:
	ICameraSceneNode *camera_node;
};