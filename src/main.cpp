#include <irrlicht.h>
#include <math.h>
#include "driverChoice.h"
#include "MyEventReceiver.hpp"
#include "personnage.hpp"
#include "Weapon.hpp"
#include "Map.hpp"
#include "Camera.hpp"
#include "Billboard.hpp"
#include "Collision.hpp"
#include "ennemis.hpp"
#include "Vague.hpp"


using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace gui;
using namespace io;


int main()
{

	/**********************************************************************************/
	/***********************    INITIALISATION  GLOBALE   *****************************/
	/**********************************************************************************/

	//Choix du driver
	E_DRIVER_TYPE driverType=driverChoiceConsole();
	if (driverType==video::EDT_COUNT)
		return 1;


	//Création du receiver permettant de récupérer la gestion d'évenement
	MyEventReceiver receiver;

	//Création du device
	IrrlichtDevice* device = createDevice(driverType,
			dimension2d<u32>(1200, 600), 16, false, false, false, &receiver);
	if (device == 0)
		return 1; 

	//On créer des racourcis correspondant aux pointeurs vers la gestion de scene, de video et de l'interface
    IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* env = device->getGUIEnvironment();

	//Initialisation du node de la scene
	ISceneNode* node = 0;


	//On masque la souris
	device->getCursorControl()->setVisible(false);


/**********************************************************************************/
/****************************            MAP          *****************************/
/**********************************************************************************/

	Map* map1 = new Map(device,"../media/orichalciane.pk3","orichalciane.bsp");
	scene::IMeshSceneNode* mapSceneNode = map1->getMapNode();


/**********************************************************************************/
/****************************       CAMERA        *********************************/
/**********************************************************************************/

	Camera* camera1 = new Camera(device);
	ICameraSceneNode *camera = camera1->getCameraNode();


/**********************************************************************************/
/****************************       PERSONNAGE        *****************************/
/**********************************************************************************/		

	personnage* perso1 = new personnage(device,vector3df(-707,40,463),
		vector3df(0,190,0),vector3df(1.5f), "../media/sydney.md2","../media/sydney.bmp",1);
	IAnimatedMeshSceneNode *model_node = perso1->getPersonnageNode();
	model_node->removeAnimators();


/**********************************************************************************/
/****************************       ENNEMIS        *****************************/
/**********************************************************************************/		

	int nombre_drones = 20; 
	std::vector<int> liste_id = {1,2,3,4,5};
	ennemis* liste_ennemis = new ennemis(device, nombre_drones,  liste_id);
	std::vector<IAnimatedMeshSceneNode*> ennemis_node = liste_ennemis->getEnnemisNode();
	std::vector<IAnimatedMeshSceneNode*> drones_node = liste_ennemis->getDronesNode();
	std::vector<IAnimatedMeshSceneNode*> robots_node = liste_ennemis->getRobotsNode();

	//points de vie
	int pt_vies_ennemis = 30;
	int pt_vies_drones = 5;
	int pt_vies_missiles = 5;


/**********************************************************************************/
/****************************       HELICOPTERE        ****************************/
/**********************************************************************************/		

	personnage* helicoptere = new personnage(device,vector3df(-120,20,340),
		vector3df(0,0,0),vector3df(0.6f), "../media/N916MU.obj","../media/N916MU.tga",1);
	IAnimatedMeshSceneNode *helico_node = helicoptere->getPersonnageNode();

	//points de vie
	int helico_vie = 1000;

/**********************************************************************************/
/****************************       LUMIERES      *********************************/
/**********************************************************************************/		

	ILightSceneNode * light = smgr->addLightSceneNode(0, vector3df(400,50,400),
		SColorf(255.0f,0.0f,0.0f,0.1f), 600.0f);


	ISceneNode* highlightedSceneNode = 0;

/**********************************************************************************/
/****************************       COLLISION       *******************************/
/**********************************************************************************/

	//gestionnaire de collision
	ISceneCollisionManager* collison = smgr->getSceneCollisionManager();

	//collision avec le personnage secondaire
	Collision* collision_model = new Collision(device,
		vector3df(30,50,30),vector3df(0,0,0), vector3df(0,30,0),
			camera, model_node);

	//colission avec la carte
	Collision* collision_map = new Collision(device,
		vector3df(30,50,30),vector3df(0,-10,0), vector3df(0,30,0),
			camera, mapSceneNode);

	//collision avec l'hélicoptère
	Collision* collision_helico = new Collision(device,
		vector3df(30,50,30),vector3df(0,0,0), vector3df(0,30,0),
			camera, helico_node);
	
	//collision avec les robots
	for(IAnimatedMeshSceneNode* i : ennemis_node ){
		Collision* collision_ennemis = new Collision(device,
		vector3df(30,50,30),vector3df(0,0,0), vector3df(0,30,0),
			camera, i);
	}

	//collision avec les drones
	for(IAnimatedMeshSceneNode* i : drones_node ){
		Collision* collision_drones = new Collision(device,
		vector3df(30,50,30),vector3df(0,0,0), vector3df(0,30,0),
			camera, i);
	}

	//collision avec les grosses machines
	for(IAnimatedMeshSceneNode* i : robots_node ){
		Collision* collision_robots = new Collision(device,
		vector3df(30,50,30),vector3df(0,0,0), vector3df(0,30,0),
			camera, i);
	}


/**********************************************************************************/
/****************************       ARME        ***********************************/
/**********************************************************************************/		
	
	path SKIN = "../media/AK_diffuse.jpg";
	path skin_classique = "../media/AK_diffuse.jpg";
	path skin_violet = "../media/AK_normal.jpg";

	Weapon* weapon1 = new Weapon(device, vector3df(10,-20,0), "../media/AK.obj",SKIN );
	IAnimatedMeshSceneNode *weapon_node = weapon1->getWeaponNode();


/**********************************************************************************/
/****************************       CROSSHAIR        ******************************/
/**********************************************************************************/

	Billboard* crosshair_green = new Billboard(device, vector3df(0,0,150), dimension2d<f32>(25, 25),
	"../media/crosshair.png",camera,true);
	ISceneNode *crosshair_green_node = crosshair_green->getBillNode();

/**********************************************************************************/
/****************************   INDICATIONS  TOUCHES         **********************/
/**********************************************************************************/

	Billboard* touches = new Billboard(device, vector3df(180,80,150), dimension2d<f32>(70, 50),
	"../media/touches.png",camera,false);
	ISceneNode *touches_node = touches->getBillNode();

/**********************************************************************************/
/****************************      BARRE DE VIE         ***************************/
/**********************************************************************************/
	
	Billboard* jauge_vie1 = new Billboard(device, vector3df(0,96,150), dimension2d<f32>(150, 20),
	"../media/health_bar/6_6.png",camera,true);
	ISceneNode *pt_vie = jauge_vie1->getBillNode();
 
 	Billboard* helico_icon = new Billboard(device, vector3df(-85,96,150), dimension2d<f32>(20, 20),
	"../media/helico.png",camera,true);

/**********************************************************************************/
/****************************       VARIABLES GLOBALES            *****************/
/**********************************************************************************/

 	//textes avant chaque vague
	ISceneNode* label1_node = 0;
	ISceneNode* label2_node = 0;
	ISceneNode* label3_node = 0;

	//label vague en haut à gauche pour chaque vague
	ISceneNode* vague1_node = 0;
	ISceneNode* vague2_node = 0;
	ISceneNode* vague3_node = 0;

	//les differentes barres de vie successives
	Billboard* jauge_vie2 = 0;
	Billboard* jauge_vie3 = 0;
	Billboard* jauge_vie4 = 0;
	Billboard* jauge_vie5 = 0;
	int jauge = 5;

	//variables liees au timer
	u32 t0 = device->getTimer()->getTime();
	const f32 MOVEMENT_SPEED = 40.f;
	f32 time_weapon_position = 0;
	int nb2 = 0;

	//variables liees aux ennemis
	int nombre_contact;
	int nombre_impact_drone;
	int nombre_impact_missiles;
	int degats = 0;
	int degats_missiles = 0;
	int nombre_ennemi;
	int nombre_drone;

	//variables liees aux vagues
	int vague = 0;
	bool vague1_reussi = 0;
	bool vague2_reussi = 0;
	int t_debut_vague3 = 0;
	

/*********************************************************************************/
/**************************      BOUCLE PRINCIPALE        ************************/
/*********************************************************************************/


	while(device->run())
	{
		if (device->isWindowActive())
		{

		/*****************************************************************/
		/**************************    TOUCHES  **************************/
		/*****************************************************************/

			//Bouton quitter
			if(receiver.IsKeyDown(KEY_ESCAPE)){
				exit(0);
			}

			//Fermer informations touches
			if(receiver.IsKeyDown(KEY_KEY_V)){
				touches->deleteBillNode();
			}

		/*****************************************************************/
		/*****************     GESTION DU TEMPS          *****************/
		/*****************************************************************/

	        const u32 t1 = device->getTimer()->getTime();
			const f32 dt = (f32)(t1 - t0) / 1000.f; 
			int nb = floor(dt);

		/*****************************************************************/
		/*****************     SUCCESSION DES VAGUES     *****************/
		/*****************************************************************/

			//etat initial
			if(vague == 0){
				Vague* vague0 = new Vague(device, vague, camera, liste_ennemis, model_node, nombre_drones, nb, t_debut_vague3, nb2, liste_id, helico_vie);
				label1_node = vague0->getLabelNode(vague);
				vague = -1;
			}

			//lancement de la premiere vague
			if(receiver.IsKeyDown(KEY_KEY_C)&&(vague==-1)){
				label1_node->remove();
				Vague* vague1 = new Vague(device, vague, camera, liste_ennemis, model_node, nombre_drones, nb, t_debut_vague3, nb2, liste_id, helico_vie);
				vague1_node = vague1->getVagueNode(vague);
				vague = 1;
				model_node->removeAnimators();
				model_node->setPosition(vector3df(0,-500,0));
			}

			//premiere vague reussi
			if((vague==1)&&(vague1_reussi==1)){
				vague1_node->remove();
				Vague* vague10 = new Vague(device, vague, camera, liste_ennemis, model_node, nombre_drones, nb, t_debut_vague3, nb2, liste_id, helico_vie);
				label2_node = vague10->getLabelNode(vague);	
				vague = -2;
			}

			//lancement de la deuxieme vague
			if(receiver.IsKeyDown(KEY_KEY_C)&&(vague==-2)){
				label2_node->remove();
				Vague* vague2 = new Vague(device, vague, camera, liste_ennemis, model_node, nombre_drones, nb, t_debut_vague3, nb2, liste_id, helico_vie);
				vague2_node = vague2->getVagueNode(vague);			
				vague = 2;
			}

			//deuxieme vague reussi
			if((vague2_reussi==1)&&(vague==2)){
				vague2_node->remove();
				Vague* vague20 = new Vague(device, vague, camera, liste_ennemis, model_node, nombre_drones, nb, t_debut_vague3, nb2, liste_id, helico_vie);
				label3_node = vague20->getLabelNode(vague);	
				vague = -3;
			}

			//lancement de la troisieme vague
			if(receiver.IsKeyDown(KEY_KEY_C)&&(vague==-3)){
				label3_node->remove();
				Vague* vague3 = new Vague(device, vague, camera, liste_ennemis, model_node, nombre_drones, nb, t_debut_vague3, nb2, liste_id, helico_vie);
				vague3_node = vague3->getVagueNode(vague);	
				vague = 3;
				t_debut_vague3 = floor(dt);
			}
			
			//troisieme vague en cours
			if(vague == 3){
				if((nb%5 == 0)&&((nb-t_debut_vague3)<30)&&(nb!=nb2)){
					nb2 = nb;
					liste_ennemis->envoie_missile(device , liste_id);
					std::vector<IAnimatedMeshSceneNode*> missile_node = liste_ennemis->getMissileNode();
					for(IAnimatedMeshSceneNode* i : missile_node ){
					Collision* collision_missile = new Collision(device,
					vector3df(30,50,30),vector3df(0,0,0), vector3df(0,30,0),
						camera, i);
					}
				}

				//victoire lors que la troisieme vague
				if(((nb-t_debut_vague3)>32)&&(helico_vie>0)){
					Billboard* helico_icon = new Billboard(device, vector3df(0,0,150), dimension2d<f32>(100, 100),
					"../media/you_win.png",camera,true);
					camera->setPosition(vector3df(0,1000,0));
					camera->setRotation(vector3df(30,0,0));
				}
	}
			


			/**********************************************************************************/
			/*******************        DETECTION DES ENNEMIS           ***********************/
			/**********************************************************************************/
			
			//eclairage de la scene
			if (highlightedSceneNode)
			{
				highlightedSceneNode->setMaterialFlag(video::EMF_LIGHTING, false);
				highlightedSceneNode = 0;
			}

			//en cas de clique sur le bouton gauche
			if(receiver.MouseState.LeftButtonDown){
				
				/****************************       Recul de l'arme        ********************/

				weapon_node->setRotation(vector3df(-5,0,0));
				time_weapon_position = dt;
			
				/**********************  Détection de l'ennemi par ray-cast      **************/
							
				core::line3d<f32> ray;
				ray.start = camera->getPosition();
				ray.end = ray.start + (camera->getTarget() - ray.start).normalize() * 1000.0f;

				core::vector3df intersection;
				core::triangle3df hitTriangle;

				scene::ISceneNode * selectedSceneNode =
					collison->getSceneNodeAndCollisionPointFromRay(
							ray,
							intersection, 
							hitTriangle, 	
							0); 

				if(selectedSceneNode)
				{
					if((selectedSceneNode->getID()  == 2)&&(vague==1))//robots
					{
						pt_vies_ennemis -=1;
						if(pt_vies_ennemis == 0){									
							selectedSceneNode->removeAnimators();
							selectedSceneNode->setPosition(vector3df(0,-500,0));
							pt_vies_ennemis = 10;
						}else{
							highlightedSceneNode = selectedSceneNode;
							highlightedSceneNode->setMaterialFlag(EMF_LIGHTING, true);
						}
					}
					else if((selectedSceneNode->getID()  == 3)&&(vague==2))//drones
					{
						pt_vies_drones -=1;
						if(pt_vies_drones == 0){									
							selectedSceneNode->removeAnimators();
							selectedSceneNode->setPosition(vector3df(0,-500,0));
							pt_vies_drones = 10;
						}else{
							highlightedSceneNode = selectedSceneNode;
							highlightedSceneNode->setMaterialFlag(EMF_LIGHTING, true);
						}
					}
					else if((selectedSceneNode->getID()  == 4)&&(vague==3))//misiles des machines
					{
						pt_vies_missiles -=1;
						if(pt_vies_missiles == 0){									
							selectedSceneNode->removeAnimators();
							selectedSceneNode->setPosition(vector3df(0,-500,0));
							pt_vies_missiles = 10;
						}else{
							highlightedSceneNode = selectedSceneNode;
							highlightedSceneNode->setMaterialFlag(EMF_LIGHTING, true);
						}
					}
				}

			}//fin tirer
			

			/****************************    Fin  du recul de l'arme        ********************/
			
			if (dt>time_weapon_position+0.1){
				weapon_node->setRotation(vector3df(5,0,0));
				time_weapon_position = 0;	
			}

			/* **********************************************************************************  */
			/* *************************      DEGATS DES ENNEMIS      ***************************  */
			/* **********************************************************************************  */

			nombre_contact = liste_ennemis->nb_ennemis_contact(device);
			nombre_impact_drone = liste_ennemis->nb_impact_drones(device,nombre_drones );
			nombre_impact_missiles = liste_ennemis->nb_impact_missiles(device);
			

			helico_vie -= 0.5*nombre_contact;

			if (nombre_impact_drone > degats){
				helico_vie -= 150;
			}
			degats = nombre_impact_drone;


			if (nombre_impact_missiles > degats_missiles){
				helico_vie -= 200;
			}
			degats_missiles = nombre_impact_missiles;

			/* **********************************************************************************  */
			/* *************************      ELIMINATION DES ENNEMIS      **********************  */
			/* **********************************************************************************  */
			
			nombre_ennemi = liste_ennemis->nb_ennemis(device);
			nombre_drone = liste_ennemis->nb_drones(device, nombre_drones);
			

			if(nombre_ennemi == 0){
				vague1_reussi = 1;
			}

			if((nombre_drone - nombre_impact_drone) == 0){
				vague2_reussi = 1;
			}

			/* **********************************************************************************  */
			/* *************************      GESTION DE VIE DE L'HELICO    *********************  */
			/* **********************************************************************************  */

			if((helico_vie<830)&&(helico_vie>660)&&(jauge == 5)){
				jauge_vie1->deleteBillNode();
				jauge_vie5 = new Billboard(device, vector3df(0,96,150), dimension2d<f32>(150, 20),
				"../media/health_bar/5_6.png",camera,true);	
				jauge = 4;
			}
			else if((helico_vie<660)&&(helico_vie>490)&&(jauge == 4)){
				jauge_vie5->deleteBillNode();
				jauge_vie4 = new Billboard(device, vector3df(0,96,150), dimension2d<f32>(150, 20),
				"../media/health_bar/4_6.png",camera,true);
				jauge = 3;
			}
			else if((helico_vie<490)&&(helico_vie>320)&&(jauge == 3)){
				jauge_vie4->deleteBillNode();
				jauge_vie3  = new Billboard(device, vector3df(0,96,150), dimension2d<f32>(150, 20),
				"../media/health_bar/3_6.png",camera,true);
				jauge = 2;
			}
			else if((helico_vie<320)&&(helico_vie>160)&&(jauge == 2)){
				jauge_vie3->deleteBillNode();
				jauge_vie2  = new Billboard(device, vector3df(0,96,150), dimension2d<f32>(150, 20),
				"../media/health_bar/2_6.png",camera,true);
				jauge = 1;
			}
			else if((helico_vie<160)&&(helico_vie>0)&&(jauge == 1)){
				jauge_vie2->deleteBillNode();
				jauge_vie1 = new Billboard(device, vector3df(0,96,150), dimension2d<f32>(150, 20),
				"../media/health_bar/1_6.png",camera,true);
				jauge = 0;
			}
			else if((helico_vie<=0)&&(jauge == 0)){
				jauge_vie1->deleteBillNode();
				Billboard* jauge_vie0 = new Billboard(device, vector3df(0,96,150), dimension2d<f32>(150, 20),
				"../media/health_bar/0.png",camera,true);
				helico_node->setRotation(vector3df(0,0,90));
				helico_node->setPosition(vector3df(0,100,340));
				
				Billboard* helico_icon = new Billboard(device, vector3df(0,0,150), dimension2d<f32>(100, 100),
				"../media/you_lose.png",camera,true);
				jauge = -1;
			}

			//vector3df position = camera->getPosition();
			//std::cout << position.X << "     "   << position.Z << std::endl;


			driver->beginScene(true, true, 0);
			smgr->drawAll();//Affiche les éléments de la scene
			env->drawAll();
			driver->endScene();

		}
		else
			device->yield();
	}



	device->drop();
	return 0;
}



