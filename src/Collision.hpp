#include <irrlicht.h>
#include <iostream>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;


/**********************************************************************************/
/****************************       COLLISION        *****************************/
/**********************************************************************************/


class Collision
{
public:

	Collision(IrrlichtDevice* device, vector3df dim1, vector3df dim2, vector3df dim3
			,ICameraSceneNode* camera, IAnimatedMeshSceneNode *model_node);
	
	Collision(IrrlichtDevice* device, 
			vector3df dim1, vector3df dim2, vector3df dim3,
			ICameraSceneNode* camera, IMeshSceneNode* mapSceneNode);


	ITriangleSelector* getTriangleDetector();

private:
	ITriangleSelector* triangleDetector = 0;
};