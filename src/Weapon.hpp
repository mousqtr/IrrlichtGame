#include <irrlicht.h>
#include <iostream>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;




class Weapon
{
public:

	Weapon(IrrlichtDevice* device,  vector3df position,  
			path objectName, path textureObjectName);

	IAnimatedMeshSceneNode* getWeaponNode();


private:
	IAnimatedMeshSceneNode *weapon_node;
};