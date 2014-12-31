#ifndef _TextureController_H_
#define _TextureController_H_

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;
using namespace std;

typedef enum
{
	TexturePathFigure = 1,
	TexturePathMonster = 2,
	TexturePathHair = 3,
	TexturePathWeapon = 4,
	TexturePathSkillCaster = 5,
	TexturePathSkillLocus = 6,
	TexturePathSkillExplosion = 7
}TexturePathType;

class TextureController {

public:

	static string getTextureRoute(TexturePathType type, unsigned int number);

	static string getTexturePath(TexturePathType type, unsigned int number);

	static void addSpriteFrames(TexturePathType type, unsigned int number, CCObject *target = NULL, SEL_CallFunc selector = NULL);

	static void subSpriteFrames(TexturePathType type, unsigned int number);

	static void removeAllSpriteFrames();

};

#endif /* defined(__mir_mobile__TextureController__) */
