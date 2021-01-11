#include <irrlicht.h>
#include <iostream>
#include <random>
#include "ennemis.hpp"
#include "personnage.hpp"
#include <vector>
#include <math.h>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace gui;




ennemis::ennemis(IrrlichtDevice *device, int Nb_drones, std::vector<int> liste_id){

	/**********************************************************************************/
	/****************************       DRONES            *****************************/
	/**********************************************************************************/		


		std::default_random_engine generator_pos{};


		std::uniform_int_distribution<int> delta_x(-2000,2000);
		std::uniform_int_distribution<int> delta_y(300,2000);
		std::uniform_int_distribution<int> delta_z(-2000,2000);
		std::uniform_int_distribution<int> delta(0,360);

		for (int i=0;i<Nb_drones;i++){
		
		
			int x = delta_x(generator_pos); 
			int y = delta_y(generator_pos); 
			int z = delta_z(generator_pos);
			int orientation = delta(generator_pos);

			personnage* perso2 = new personnage(device,vector3df(x,y,z),
			vector3df(0,orientation,0),vector3df(9.0f), "../media/drone/drone.obj","../media/drone/images.jpeg", liste_id[2]);
			IAnimatedMeshSceneNode *model_node2 = perso2->getPersonnageNode();
			liste_drones.push_back(model_node2);
		}


	/**********************************************************************************/
	/****************************       ROBOTS           ***************************/
	/**********************************************************************************/
	

		std::vector<int> pos_x = {-466,-659,-445,-205,326,518,273,61};
		std::vector<int> pos_z = {-82,204,731,863,725,427,22,-101};
		std::vector<int> orientation_y = {30,75,-230,150,220,270,310,-30};

		for (int i=0; i<8; i++){
		
			//std::cout << "x : " << x1 << ",   z : "  <<  x2 << std::endl;

			int x = pos_x[i]; 
			int z = pos_z[i]; 
			int o_y = orientation_y[i]; 

			personnage* perso2 = new personnage(device,vector3df(x,100,z),
			vector3df(0,o_y,0),vector3df(20.0f), "../media/robot.obj","../media/blue_robot.png", liste_id[1]);
			IAnimatedMeshSceneNode *model_node2 = perso2->getPersonnageNode();
			liste_ennemis.push_back(model_node2);
		}


	/**********************************************************************************/
	/****************************       MACHINES           ***************************/
	/**********************************************************************************/
	IVideoDriver* driver = device->getVideoDriver();

	std::vector<int> pos_machine_x = {-1250,920};
	std::vector<int> pos_machine_z = {571,548};
	std::vector<int> machine_orientation = {181,-10};

	for (int i=0;i<2;i++){
	

		int x = pos_machine_x[i]; 
		int z = pos_machine_z[i];
		int o =  machine_orientation[i];

		personnage* machine1 = new personnage(device,vector3df(x,-50,z),
		vector3df(0,o,0),vector3df(200.0f), "../media/Gun_Bot.3ds","../media/GB_C.jpg",liste_id[4]);
		IAnimatedMeshSceneNode *machine1_node = machine1->getPersonnageNode();
		
		ITexture *texture = driver->getTexture("../media/GB_D.jpg");
		machine1_node->setMaterialTexture(0,texture);
		ITexture *texture2 = driver->getTexture("../media/GB_N.jpg");
		machine1_node->setMaterialTexture(0,texture2);
		liste_robots.push_back(machine1_node);
	}



}




std::vector<IAnimatedMeshSceneNode*> ennemis::getEnnemisNode(){
	return liste_ennemis;
}

std::vector<IAnimatedMeshSceneNode*> ennemis::getDronesNode(){
	return liste_drones;
}

std::vector<IAnimatedMeshSceneNode*> ennemis::getRobotsNode(){
	return liste_robots;
}

void ennemis::deplacementEnnemis(IrrlichtDevice *device){

		ISceneManager* smgr = device->getSceneManager();

		std::vector<int> pos_x = {-218,-290,-254,-149,44,84,47,-42};
		std::vector<int> pos_z = {203,331,513,601,516,380,210,152};

		int vitesse = 8000;

		for (int i=0;i<8;i++){
	

			IAnimatedMeshSceneNode *ennemi = liste_ennemis[i];
			vector3df position_ennemi = ennemi->getPosition();

			int x = pos_x[i]; 
			int z = pos_z[i]; 

			scene::ISceneNodeAnimator* anim =
			smgr->createFlyStraightAnimator(core::vector3df(position_ennemi.X,position_ennemi.Y,position_ennemi.Z),
			core::vector3df(x,100,z), vitesse, false);
			if (anim)
			{
				ennemi->addAnimator(anim);
				anim->drop();
			}

			vitesse += 2000;

		}
}



void ennemis::deplacementDrones(IrrlichtDevice *device, int Nb_drones){

		ISceneManager* smgr = device->getSceneManager();

		int cpt = 10000;

		for (int i=0;i<Nb_drones;i++){
		
	
			IAnimatedMeshSceneNode *drone = liste_drones[i];
			vector3df position_drone = drone->getPosition();


			scene::ISceneNodeAnimator* anim =
			smgr->createFlyStraightAnimator(core::vector3df(position_drone.X,position_drone.Y,position_drone.Z),
			core::vector3df(-135,80,395), cpt , false);
			if (anim)
			{
				drone->addAnimator(anim);
				anim->drop();
			}
			cpt += 2000;

		}
		
}

int ennemis::nb_ennemis_contact(IrrlichtDevice *device){

	ISceneManager* smgr = device->getSceneManager();

	int nb = 0;
	std::vector<int> pos_x = {-218,-290,-254,-149,44,84,47,-42};
	std::vector<int> pos_z = {203,331,513,601,516,380,210,152};

	for (int i=0;i<8;i++){
		IAnimatedMeshSceneNode *ennemi = liste_ennemis[i];
		vector3df pos = ennemi->getPosition();
		if ((pos.X==pos_x[i])&&(pos.Z==pos_z[i])){
			nb += 1;
		}
	}

	return nb;
}



int ennemis::nb_impact_drones(IrrlichtDevice *device, int Nb_drones){

	ISceneManager* smgr = device->getSceneManager();

	int nb = 0;

	for (int i=0 ; i<Nb_drones ; i++){
		IAnimatedMeshSceneNode *drone = liste_drones[i];
		vector3df pos = drone->getPosition();
		if ((pos.X == -135)&&(pos.Z == 395)){
			nb += 1;
		}
	}
	return nb;
}


int ennemis::nb_impact_missiles(IrrlichtDevice *device){

	ISceneManager* smgr = device->getSceneManager();

	vector3df pos;
	int nb = 0;
	for( IAnimatedMeshSceneNode* missile : liste_missile){
		pos = missile->getPosition();
		if ((pos.X == -135)&&(pos.Z == 395)){
			nb += 1;
		}
	}

	return nb;
}

int ennemis::nb_ennemis(IrrlichtDevice *device){

	ISceneManager* smgr = device->getSceneManager();

	int nb = 8;
	
	for (int i=0;i<8;i++){
		IAnimatedMeshSceneNode *ennemi = liste_ennemis[i];
		vector3df pos = ennemi->getPosition();
		if (pos.Y < -100){
			nb -= 1;
		}
	}

	return nb;
}


int ennemis::nb_drones(IrrlichtDevice *device, int Nb_drones){

	ISceneManager* smgr = device->getSceneManager();

	int nb = Nb_drones;
	
	for (int i=0;i<Nb_drones;i++){
		IAnimatedMeshSceneNode *drone = liste_drones[i];
		vector3df pos = drone->getPosition();
		if (pos.Y < -100){
			nb -= 1;
		}
	}

	return nb;
}


void ennemis::envoie_missile(IrrlichtDevice *device , std::vector<int> liste_id){

	ISceneManager* smgr = device->getSceneManager();

	std::vector<int> pos_machine_x = {-1250,920};
	std::vector<int> pos_machine_z = {571,548};
	std::vector<int> machine_orientation = {181,-10};
	nb_missiles = 0;

	for (int i=0;i<2;i++){
	

		int x = pos_machine_x[i]; 
		int z = pos_machine_z[i];
		int o =  machine_orientation[i];

		personnage* missile = new personnage(device,vector3df(x,150,z),
		vector3df(0,o,0),vector3df(10.0f), "../media/ball.obj","../media/ball.jpg",liste_id[3]);
		IAnimatedMeshSceneNode *missile_node = missile->getPersonnageNode();

		scene::ISceneNodeAnimator* anim =
		smgr->createFlyStraightAnimator(core::vector3df(x,150,z),
		core::vector3df(-135,80,395), 3000 , false);
		if (anim)
		{
			missile_node->addAnimator(anim);
			anim->drop();
		}
		nb_missiles += 1;
		liste_missile.push_back(missile_node);

	}

}

std::vector<IAnimatedMeshSceneNode*> ennemis::getMissileNode(){
	return liste_missile;
}
