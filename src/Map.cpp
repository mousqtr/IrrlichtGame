#include <irrlicht.h>
#include "Map.hpp"
#include <iostream>


using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;

/**********************************************************************************/
/****************************       MAP               *****************************/
/**********************************************************************************/

Map::Map(IrrlichtDevice* device, path archiveMap, path maillageMap )
{
    IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();


	//Ouverture de l'archive
	device->getFileSystem()->addFileArchive(archiveMap);
	//Lecture du maillage
	IAnimatedMesh* mapMaillage = smgr->getMesh(maillageMap);


	//ajout de la map à la scene
	mapSceneNode = smgr->addOctreeSceneNode(mapMaillage->getMesh(0));


	//on place le maillage du monde
	mapSceneNode->setPosition(core::vector3df(0,0,0));
	mapSceneNode->setRotation(core::vector3df(0,-30,0));


}


IMeshSceneNode* Map::getMapNode(){
	return mapSceneNode;
}

