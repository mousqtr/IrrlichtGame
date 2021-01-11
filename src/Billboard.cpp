#include <irrlicht.h>
#include "Billboard.hpp"
#include <iostream>


using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;

/**********************************************************************************/
/****************************        BILLBOARD        *****************************/
/**********************************************************************************/

Billboard::Billboard(IrrlichtDevice* device, vector3df position, dimension2d<f32> dim, 
			path TextureName, ICameraSceneNode* camera, bool transparence)
{
    IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();


	//ajout au sein de la scene
	bill_node = smgr->addBillboardSceneNode(bill_node, dim);
	bill_node->setMaterialFlag(EMF_LIGHTING, false);
	bill_node->setMaterialTexture(0, driver->getTexture(TextureName));   
	if(transparence){
		bill_node->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
	}
	
	bill_node->setPosition(position);
	bill_node->setMaterialFlag(EMF_ZBUFFER,false);
	
	camera->addChild(bill_node);
	
}



ISceneNode* Billboard::getBillNode(){
	return bill_node;
}

void Billboard::deleteBillNode(){
	bill_node->remove();
}

