#include <irrlicht.h>
#include <iostream>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;




class Billboard
{
public:

	Billboard(IrrlichtDevice* device, vector3df position, dimension2d<f32> dim, 
		io::path TextureName, ICameraSceneNode* camera, bool transparence);

	ISceneNode* getBillNode();
	void deleteBillNode();


private:
	ISceneNode *bill_node = 0;
};