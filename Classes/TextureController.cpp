#include "TextureController.h"

#define FIGURE_PATH "char_"
#define MONSTER_PATH "monster_"
#define HAIR_PATH "hair_"
#define WEAPON_PATH "weapon_"
#define SKILL_CASTER_PATH "caster_"
#define SKILL_LOCUS_PATH "locus_"
#define SKILL_EXPLOSION_PATH "explosion_"

#define FIGURE_ROUTE "texture_figure/"
#define MONSTER_ROUTE "texture_monster/"
#define HAIR_ROUTE "texture_figure/"
#define WEAPON_ROUTE "texture_weapon/"
#define SKILL_ROUTE "texture_skill/"
#define OTHER_ROUTE "texture_set/"

static std::map<std::string,int> textureMap;

const char* textureSuffix = ".plist";
const char* texturePngSuffix = ".png";

class TextureAsync : public CCObject
{
	string m_texturePath;

	CCObject* m_pTarget;

	SEL_CallFunc m_pSelector;

	void addSpriteFrames(CCTexture2D* texture)
	{
		std::string completePath = m_texturePath + textureSuffix;

		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(completePath.c_str(), texture);

		this->isFinish();
	}

	void addImageAsync()
	{
		std::string completePath = m_texturePath + texturePngSuffix;
		CCTextureCache::sharedTextureCache()->addImageAsync(completePath.c_str(), this, callfuncO_selector(TextureAsync::addSpriteFrames));
	}

	void WaitForFinish()
	{
		CCDirector::sharedDirector()->getScheduler()->unscheduleAllForTarget(this);
		if (textureMap[m_texturePath] > 0)
		{
			this->isFinish();
		}
		else
		{
			CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(TextureAsync::WaitForFinish), this, 0.1f, false);
		}
	}

	void isFinish()
	{
		textureMap[m_texturePath]++;
		//CCLog("texture::path=%s,count=%d",m_texturePath.c_str(),textureMap[m_texturePath]);
		if (m_pTarget && m_pSelector)
		{
			(m_pTarget->*m_pSelector)();
		}
		delete this;
	}

public:

	TextureAsync(string& path, CCObject *target, SEL_CallFunc selector)
		:m_texturePath(path) ,m_pTarget(target) ,m_pSelector(selector){;}

	~TextureAsync(){;}

	static void addSpriteFramesAsync(string& path, CCObject *target = NULL, SEL_CallFunc selector = NULL)
	{
		if (path.compare("") == 0)
			return;

		std::map<std::string, int>::iterator itr;
		itr = textureMap.find(path);

		if (itr == textureMap.end())
		{
           // if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC || GAME_SCENE == NULL)
			if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC || true)
			{
				std::string completePath = path + textureSuffix;
				CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(completePath.c_str());
				if (target && selector)
				{
					(target->*selector)();
				}
				textureMap.insert(std::map<std::string, int>::value_type(path, 1));

				//CCLog("texture::AddPath=%s", completePath.c_str());
			}
			else
			{
				TextureAsync* async = new TextureAsync(path, target ,selector);
				async->addImageAsync();
				textureMap.insert(std::map<std::string, int>::value_type(path, 0));
			}
		}
		else
		{
			TextureAsync* async = new TextureAsync(path, target ,selector);
			async->WaitForFinish();
		}
	}

	static void subSpriteFramesAsync(string& path)
	{
		if (path.compare("") == 0)
			return;

		std::map<std::string, int>::iterator itr;
		itr = textureMap.find(path);
		if (itr != textureMap.end())
		{
			(itr->second)--;
			//CCLog("texture::path=%s,count=%d",itr->first.c_str(),itr->second);
			if (itr->second <= 0)
			{
				std::string completePath = path + textureSuffix;
				CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(completePath.c_str());

				std::string pngPath = path + texturePngSuffix;
				CCTextureCache::sharedTextureCache()->removeTextureForKey(pngPath.c_str());

				textureMap.erase(itr);

				//CCLog("texture::RemovePath=%s", completePath.c_str());
			}

		}
	}

	static void removeAllSpriteFrames()
	{
		std::map<std::string, int>::iterator itr;
		for (itr=textureMap.begin(); itr!=textureMap.end(); itr++)
		{
			std::string completePath = itr->first + textureSuffix;

			CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(completePath.c_str());
		}
		textureMap.clear();

		CCTextureCache::sharedTextureCache()->removeAllTextures();
	}
};


string TextureController::getTextureRoute(TexturePathType type, unsigned int number)
{
	string path;

	switch (type)
	{
	case TexturePathFigure:
		{
			path = string(FIGURE_ROUTE) + FIGURE_PATH;
			break;
		}
	case TexturePathMonster:
		{
			path = string(MONSTER_ROUTE) + MONSTER_PATH;
			break;
		}
	case TexturePathHair:
		{
			path = string(HAIR_ROUTE) + HAIR_PATH;
			break;
		}
	case TexturePathWeapon:
		{
			path = string(WEAPON_ROUTE) + WEAPON_PATH;
			break;
		}
	case TexturePathSkillCaster:
		{
			path = string(SKILL_ROUTE) + SKILL_CASTER_PATH;
			break;
		}
	case TexturePathSkillLocus:
		{
			path = string(SKILL_ROUTE) + SKILL_LOCUS_PATH;
			break;
		}
	case TexturePathSkillExplosion:
		{
			path = string(SKILL_ROUTE) + SKILL_EXPLOSION_PATH;
			break;
		}
	default:
		{
			path = "";
			break;
		}
	}

	if (path.compare("") != 0)
	{
		//      string str;
		//      stringstream ss;
		//      ss << number;
		//      ss >> str;
		char str[6];
		sprintf(str, "%d",number);

		path += str;
	}

	return path;
}

string TextureController::getTexturePath(TexturePathType type, unsigned int number)
{
	string path;

	switch (type)
	{
	case TexturePathFigure:
		{
			path = FIGURE_PATH;
			break;
		}
	case TexturePathMonster:
		{
			path = MONSTER_PATH;
			break;
		}
	case TexturePathHair:
		{
			path = HAIR_PATH;
			break;
		}
	case TexturePathWeapon:
		{
			path = WEAPON_PATH;
			break;
		}
	case TexturePathSkillCaster:
		{
			path = SKILL_CASTER_PATH;
			break;
		}
	case TexturePathSkillLocus:
		{
			path = SKILL_LOCUS_PATH;
			break;
		}
	case TexturePathSkillExplosion:
		{
			path = SKILL_EXPLOSION_PATH;
			break;
		}
	default:
		{
			path = "";
			break;
		}
	}

	if (path.compare("") != 0)
	{
		//      string str;
		//      stringstream ss;
		//      ss << number;
		//      ss >> str;
		char str[6];
		sprintf(str, "%d",number);

		path += str;
	}

	return path;
}

void TextureController::addSpriteFrames(TexturePathType type, unsigned int number, CCObject *target, SEL_CallFunc selector)
{
	do
	{
		CC_BREAK_IF(number == 0);
		string path = getTextureRoute(type, number);
		CC_BREAK_IF(path.compare("") == 0);
		TextureAsync::addSpriteFramesAsync(path, target, selector);
	}
	while (0);
}

void TextureController::subSpriteFrames(TexturePathType type, unsigned int number)
{
	do
	{
		CC_BREAK_IF(number == 0);
		string path = getTextureRoute(type, number);
		CC_BREAK_IF(path.compare("") == 0);
		TextureAsync::subSpriteFramesAsync(path);
		CCTextureCache::sharedTextureCache()->removeUnusedTextures();
	}
	while (0);
}

void TextureController::removeAllSpriteFrames()
{
	TextureAsync::removeAllSpriteFrames();
	CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}