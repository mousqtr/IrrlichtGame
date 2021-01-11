#include <irrlicht.h>
#include "Weapon.hpp"
#include <iostream>


using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;

/**********************************************************************************/
/****************************       ARME        *****************************/
/**********************************************************************************/

Weapon::Weapon(IrrlichtDevice* device,  vector3df position,  
			path objectName, path textureObjectName)
{
    IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();


	//Initialisation du maillage d'un personnage
	IAnimatedMesh *weapon = smgr->getMesh(objectName);

	//création du node de l'arme et ajout à la scene
	weapon_node = smgr->addAnimatedMeshSceneNode(weapon,smgr->getActiveCamera(),
                        10,
                        position,
                        vector3df(0,0,0)
                        );
	//Chargement de la texture

	ITexture *texture_weapon = driver->getTexture(textureObjectName);
	weapon_node->setMaterialTexture(0,texture_weapon);
	weapon_node->setMaterialFlag(EMF_LIGHTING,false);

	//taille de l'arme
	weapon_node->setScale(vector3df(0.3f)); 
	

}


IAnimatedMeshSceneNode* Weapon::getWeaponNode(){
	return weapon_node;
}

