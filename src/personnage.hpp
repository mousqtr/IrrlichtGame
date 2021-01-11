#ifndef DEF_PERSONNAGE
#define DEF_PERSONNAGE

#include <irrlicht.h>
#include <iostream>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;




class personnage
{
public:

	personnage(IrrlichtDevice* device, 
			vector3df position, vector3df rotation, vector3df scale, 
			path objectName, path textureObjectName, int id);
	IAnimatedMeshSceneNode* getPersonnageNode();


private:
	IAnimatedMeshSceneNode *model_node;
};

#endif