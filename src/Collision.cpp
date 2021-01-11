#include <irrlicht.h>
#include "Collision.hpp"
#include <iostream>


using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;

/**********************************************************************************/
/****************************       COLLISION        *****************************/
/**********************************************************************************/

Collision::Collision(IrrlichtDevice* device, 
			vector3df dim1, vector3df dim2, vector3df dim3,
			ICameraSceneNode* camera, IAnimatedMeshSceneNode *model_node )
{
	ISceneManager* smgr = device->getSceneManager();

	triangleDetector = smgr->createOctreeTriangleSelector(model_node->getMesh(), model_node, 128);
	model_node->setTriangleSelector(triangleDetector);

	//gestion de la collision avec la map
	if (triangleDetector)
	{
		ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
			triangleDetector, 
			camera, 
			dim1,
			dim2, 
			dim3);
		triangleDetector->drop(); 
		camera->addAnimator(anim);
		anim->drop();  

	}

}




Collision::Collision(IrrlichtDevice* device, 
			vector3df dim1, vector3df dim2, vector3df dim3,
			ICameraSceneNode* camera, IMeshSceneNode* mapSceneNode)
{
	ISceneManager* smgr = device->getSceneManager();

	triangleDetector = smgr->createOctreeTriangleSelector(mapSceneNode->getMesh(), mapSceneNode, 128);
	mapSceneNode->setTriangleSelector(triangleDetector);

	//gestion de la collision avec la map
	if (triangleDetector)
	{
		ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
			triangleDetector, 
			camera, 
			dim1,
			dim2, 
			dim3);
		triangleDetector->drop(); 
		camera->addAnimator(anim);
		anim->drop();  

	}

}


ITriangleSelector* Collision::getTriangleDetector(){
	return triangleDetector;
}

