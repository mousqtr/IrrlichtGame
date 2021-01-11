#include <irrlicht.h>
#include <iostream>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;



class Map
{
public:

	Map(IrrlichtDevice* device, path archiveMap, path maillageMap);
	IMeshSceneNode* getMapNode();


private:
	IMeshSceneNode *mapSceneNode = 0;;
};