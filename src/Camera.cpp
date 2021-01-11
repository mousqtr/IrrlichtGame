#include <irrlicht.h>
#include "Camera.hpp"
#include <iostream>


using namespace irr;
using namespace core;
using namespace video;
using namespace scene;

/**********************************************************************************/
/****************************       CAMERA            *****************************/
/**********************************************************************************/

Camera::Camera(IrrlichtDevice* device)
{
    IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();


	//Création de la map contenant les mouvements de bases de la camera en vue FPS
	SKeyMap keyMap[5];
	keyMap[0].Action = EKA_MOVE_FORWARD;   // avancer
	keyMap[0].KeyCode = KEY_KEY_Z;
	keyMap[1].Action = EKA_MOVE_BACKWARD;  // reculer
	keyMap[1].KeyCode = KEY_KEY_S;
	keyMap[2].Action = EKA_STRAFE_LEFT;    // a gauche
	keyMap[2].KeyCode = KEY_KEY_Q;
	keyMap[3].Action = EKA_STRAFE_RIGHT;   // a droite
	keyMap[3].KeyCode = KEY_KEY_D;
	keyMap[4].Action = EKA_JUMP_UP;        // saut
	keyMap[4].KeyCode = KEY_SPACE;

	//place la cmamera en vue FPS
	camera_node = smgr ->addCameraSceneNodeFPS(0, 100, 0.3, 0, keyMap, 8,false,4.0f);
	
	camera_node->setPosition(vector3df(-778,82.0,510));
	//direction initiale de la camera
	camera_node->setTarget(vector3df(0,0,283));


}


ICameraSceneNode* Camera::getCameraNode(){
	return camera_node;
}