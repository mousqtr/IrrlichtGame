#ifndef DEF_ENNEMIS
#define DEF_ENNEMIS

#include <irrlicht.h>
#include <iostream>
#include <string>
#include <vector>


using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace gui;



 
class ennemis
{
    public:
 
	ennemis(IrrlichtDevice *device, int Nb_drones, std::vector<int> liste_id);
	
	// accesseur - mutateur
	std::vector<IAnimatedMeshSceneNode*> getEnnemisNode();
	std::vector<IAnimatedMeshSceneNode*> getDronesNode();
	std::vector<IAnimatedMeshSceneNode*> getRobotsNode();
	std::vector<IAnimatedMeshSceneNode*> getMissileNode();


	void deplacementEnnemis(IrrlichtDevice *device);
	void deplacementDrones(IrrlichtDevice *device, int Nb_drones);

	int nb_ennemis(IrrlichtDevice *device);
	int nb_drones(IrrlichtDevice *device, int Nb_drones);

	int nb_ennemis_contact(IrrlichtDevice *device);
	int nb_impact_drones(IrrlichtDevice *device, int Nb_drones);
	int nb_impact_missiles(IrrlichtDevice *device);

	void envoie_missile(IrrlichtDevice *device, std::vector<int> liste_id);

    private:

 	std::vector<IAnimatedMeshSceneNode*>  liste_ennemis;
 	std::vector<IAnimatedMeshSceneNode*>  liste_drones;
 	std::vector<IAnimatedMeshSceneNode*>  liste_robots;
 	std::vector<IAnimatedMeshSceneNode*>  liste_missile;
 	int nb_missiles = 0;



};
 
#endif