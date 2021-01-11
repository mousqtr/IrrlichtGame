#include <irrlicht.h>
#include "personnage.hpp"
#include <iostream>


using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;

/**********************************************************************************/
/****************************       PERSONNAGE        *****************************/
/**********************************************************************************/

personnage::personnage(IrrlichtDevice* device, 
			vector3df position, vector3df rotation, vector3df scale,
			path objectName, path textureObjectName, int id)
{
    IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();


	//Initialisation du maillage d'un personnage
	IAnimatedMesh *model = smgr->getMesh(objectName);

	model_node  = smgr->addAnimatedMeshSceneNode(model,0,id);
	//Chargement de la texture

	ITexture *texture = driver->getTexture(textureObjectName);
	model_node->setMaterialTexture(0,texture);
	model_node->setMaterialFlag(EMF_LIGHTING,false);





	//position initiale du perso
	model_node->setPosition(position);
	model_node->setRotation(rotation);
	model_node->setScale(scale); 

}


IAnimatedMeshSceneNode* personnage::getPersonnageNode(){
	return model_node;
}


