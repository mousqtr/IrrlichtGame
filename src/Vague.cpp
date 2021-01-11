#include <irrlicht.h>
#include "Vague.hpp"
#include "ennemis.hpp"
#include "Billboard.hpp"
#include "Collision.hpp"
#include <iostream>


using namespace irr;
using namespace core;
using namespace video;
using namespace scene;

Vague::Vague(IrrlichtDevice* device, int num_vague, ICameraSceneNode *camera, 
	ennemis* liste_ennemis, IAnimatedMeshSceneNode *model_node, int nombre_drones, 
	int nb, int t_debut_vague3, int nb2, std::vector<int> liste_id, int helico_vie)
{
	IVideoDriver* driver = device->getVideoDriver();
    ISceneManager* smgr = device->getSceneManager();

    if(num_vague == 0){
		label_node = smgr->addBillboardSceneNode(label_node, dimension2d<f32>(250, 50));
		label_node->setMaterialFlag(EMF_LIGHTING, false);
		label_node->setMaterialTexture(0, driver->getTexture("../media/label1.jpeg"));   
		label_node->setPosition(vector3df(0,-80,150));
		label_node->setMaterialFlag(EMF_ZBUFFER,false);
		camera->addChild(label_node);
    }
    

    if(num_vague == -1){
		vague_node = smgr->addBillboardSceneNode(vague_node, dimension2d<f32>(40, 20));
		vague_node->setMaterialFlag(EMF_LIGHTING, false);
		vague_node->setMaterialTexture(0, driver->getTexture("../media/vague_1.png"));   
		vague_node->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
		vague_node->setPosition(vector3df(-160,96,150));
		vague_node->setMaterialFlag(EMF_ZBUFFER,false);
		camera->addChild(vague_node);
		liste_ennemis->deplacementEnnemis(device);
	}

	if(num_vague == 1){
		//affichage de label 2
		label_node = smgr->addBillboardSceneNode(label_node, dimension2d<f32>(250, 50));
		label_node->setMaterialFlag(EMF_LIGHTING, false);
		label_node->setMaterialTexture(0, driver->getTexture("../media/label2.jpeg"));   
		label_node->setPosition(vector3df(0,-80,150));
		label_node->setMaterialFlag(EMF_ZBUFFER,false);
		camera->addChild(label_node);

	}

    if(num_vague == -2){
		//affichage vague 2
		vague_node = smgr->addBillboardSceneNode(vague_node, dimension2d<f32>(40, 20));
		vague_node->setMaterialFlag(EMF_LIGHTING, false);
		vague_node->setMaterialTexture(0, driver->getTexture("../media/vague_2.png"));   
		vague_node->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
		vague_node->setPosition(vector3df(-165,96,150));
		vague_node->setMaterialFlag(EMF_ZBUFFER,false);
		camera->addChild(vague_node);
		//lancement du deplament ennemi
		liste_ennemis->deplacementDrones(device, nombre_drones);
    }

    if(num_vague == 2){
		//affichage de label 2
		label_node = smgr->addBillboardSceneNode(label_node, dimension2d<f32>(250, 50));
		label_node->setMaterialFlag(EMF_LIGHTING, false);
		label_node->setMaterialTexture(0, driver->getTexture("../media/label3.jpeg"));   
		label_node->setPosition(vector3df(0,-80,150));
		label_node->setMaterialFlag(EMF_ZBUFFER,false);
		camera->addChild(label_node);
    }

    if(num_vague == -3){
		vague_node = smgr->addBillboardSceneNode(vague_node, dimension2d<f32>(40, 20));
		vague_node->setMaterialFlag(EMF_LIGHTING, false);
		vague_node->setMaterialTexture(0, driver->getTexture("../media/vague_3.png"));   
		vague_node->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
		vague_node->setPosition(vector3df(-165,96,150));
		vague_node->setMaterialFlag(EMF_ZBUFFER,false);
		camera->addChild(vague_node);
	}



}

ISceneNode* Vague::getVagueNode(int num_vague){
	return vague_node;
}

ISceneNode* Vague::getLabelNode(int num_vague){
	return label_node;
}