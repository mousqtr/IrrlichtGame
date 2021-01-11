#include <irrlicht.h>
#include <iostream>
#include "ennemis.hpp"

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;




class Vague
{
public:

	Vague(IrrlichtDevice* device, int num_vague, ICameraSceneNode *camera, 
	ennemis* liste_ennemis, IAnimatedMeshSceneNode *model_node, int nombre_drones, 
	int nb, int t_debut_vague3, int nb2, std::vector<int> liste_id, int helico_vie);

	ISceneNode* getVagueNode(int num_vague);
	ISceneNode* getLabelNode(int num_vague);

private:
	ISceneNode* vague_node = 0;
	ISceneNode* label_node = 0;
};