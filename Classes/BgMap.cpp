//  出自九秒社区 http://www.9miao.com
//
//  BgMap.cpp
//  mir-mobile
//
//  Created by 栗元峰 on 13-12-16.
//
//

#include "BgMap.h"
#include <iostream>
#include <fstream>
#include <math.h>

#include "GameScene.h"
#include "GameLoading.h"
#include "SimpleAudioEngine.h"
using namespace std;

#define RADIUS_PASSAGEWAY 64

#define TYPE_PROTAL 100
#define TYPE_BORN_POINT 101
#define TYPE_NPC 200
#define TYPE_ENEMY 300
#define TYPE_BACKGROUND_MUSIC 400

#pragma -
#pragma JSON

#pragma -
#pragma BgMap

void BgMap::readGirdData()
{
	CSJson::Reader reader;
	CSJson::Value json;

	CCString* jsonPath = CCString::createWithFormat("map/s%d/data_gird_%d.json", m_mapID, m_mapID);
	std::string absolutePath = CCFileUtils::sharedFileUtils()->fullPathForFilename(jsonPath->getCString());
	CCString* filePath = CCString::createWithContentsOfFile(absolutePath.c_str());

	//ifstream filePath(file.c_str(), ios::in);

	CCAssert(filePath, "file is open fail!");
	if (!reader.parse(filePath->getCString(), json, false))
	{
		CCAssert(false, "Json::Reader Parse error!");
	}

	unsigned int width = json["mapW"].asInt();
	unsigned int height = json["mapH"].asInt();
	m_bgSize = CCSize(width, height);

	unsigned int gWidth = json["mapGridW"].asInt();
	unsigned int gHeight = json["mapGridH"].asInt();
	m_gridSize = CCSize(gWidth, gHeight);
	MapPoint::setGridSize(m_gridSize);
	m_gridRow = (unsigned int)ceilf(width/m_gridSize.width);
	m_gridCol = (unsigned int)ceilf(height/m_gridSize.height);

	CSJson::Value arr = json["mapFlagArr"];
	this->initGridData(arr);

	unsigned int iWidth = json["divideBlockW"].asInt();
	unsigned int iHeight = json["divideBlockH"].asInt();
	m_imageSize = CCSize(iWidth, iHeight);
	m_imageRow = (unsigned int)ceilf(width/m_imageSize.width);
	m_imageCol = (unsigned int)ceilf(height/m_imageSize.height);
}

void BgMap::readGoodsData()
{
	CSJson::Reader reader;
	CSJson::Value json;

	CCString* jsonPath = CCString::createWithFormat("map/s%d/data_goods_%d.json", m_mapID, m_mapID);
	std::string absolutePath = CCFileUtils::sharedFileUtils()->fullPathForFilename(jsonPath->getCString());
	CCString* filePath = CCString::createWithContentsOfFile(absolutePath.c_str());

	CCAssert(filePath, "file is open fail!");
	if (!reader.parse(filePath->getCString(), json, false))
	{
		CCAssert(false, "Json::Reader Parse error!");
	}

	unsigned int size = json["items"].size();
	for (unsigned int i=0; i<size; i++)
	{
		CSJson::Value goods = json["items"][i];

		switch (goods["itemType"].asInt())
		{
		case TYPE_PROTAL:
			{
				int key = goods["itemSN"].asInt();
				int mapID = goods["portalToMap"].asInt();
				int born = goods["portalToPos"].asInt();
				CCPoint point = CCPoint(goods["itemPosX"].asFloat(), goods["itemPosY"].asFloat());
				PortalInformation p={key, mapID, born, point};
				m_mapPassageway.push_back(p);
			}
			break;
		case TYPE_BORN_POINT:
			{
				int born = goods["itemSN"].asInt();
				CCPoint point = CCPoint(goods["itemPosX"].asFloat(), goods["itemPosY"].asFloat());
				m_mapBornPoint[born] = point;
			}
			break;
		case TYPE_NPC:
			{
				//int key = goods["itemSN"].asInt();
				//NPCDirectionType direction = (NPCDirectionType)goods["npcDirection"].asInt();
				//CCPoint point = CCPoint(goods["itemPosX"].asFloat(), goods["itemPosY"].asFloat());
				//m_npcInfoVec.push_back((NpcInformation){key, direction, point});
			}
			break;
		case TYPE_ENEMY:
			{
				unsigned int key = goods["itemSN"].asUInt();
				CCPoint point = CCPoint(goods["itemPosX"].asFloat(), goods["itemPosY"].asFloat());
				m_enemyMap.insert(std::multimap<unsigned int, MapPoint>::value_type(key, MapPoint(point)));
			}
			break;
		case TYPE_BACKGROUND_MUSIC:
			{
				unsigned int key = goods["itemSN"].asUInt();
				char s[20];
				sprintf(s, "music/400/%d.mp3", key);
				m_backGroundMusic = s;
			}
			break;
		default:
			break;
		}
	}
}

BgMap::BgMap(int mapID)
	:m_grid(NULL)
	,m_gridRow(0)
	,m_gridCol(0)
	,m_gridSize(CCSizeZero)
	,m_imageRow(0)
	,m_imageCol(0)
	,m_imageSize(CCSizeZero)
	,m_bgSize(CCSizeZero)
	,m_mapID(mapID)
	,m_playerLead(NULL)
	,m_delegate(NULL)
{
	this->readGirdData();
	this->readGoodsData();
}

BgMap::~BgMap()
{
	for (unsigned int i=0; i<m_gridCol; i++)
	{
		delete[] m_grid[i];
	}
	delete[] m_grid;

	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

BgMap* BgMap::createWithPath(int mapID)
{
	BgMap* map = new BgMap(mapID);
	if (map && map->init())
	{
		map->autorelease();
		return map;
	}
	CC_SAFE_DELETE(map);
	return NULL;
}

bool BgMap::init()
{
	if (!CCNode::init())
		return false;

	char str[24];
	sprintf(str, "map/s%d/min_s%d.jpg", m_mapID, m_mapID);
	m_sMap = CCSprite::create(str);
	m_sMap->setAnchorPoint(CCPointZero);
	this->addChild(m_sMap, BgMap::getZOrderZero(this));
	m_sMap->setScale(10/3.0f);

	this->initBgMapFloorTile();

	this->initBgMapPassagewayImage();

	this->initNpcFigure();

	this->updateImageDisplay();

	if (m_backGroundMusic.compare("") != 0)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(m_backGroundMusic.c_str(), true);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.2f);
	}

	return true;
}

void BgMap::initGridData(CSJson::Value& arr)
{
	m_grid = new unsigned char*[m_gridCol];
	for (unsigned int i=0; i<m_gridCol; i++)
	{
		m_grid[i] = new unsigned char[m_gridRow];
	}

	int size = arr.size();
	for (unsigned int i=0; i<size; i++)
	{
		m_grid[i/m_gridRow][i%m_gridRow] = arr[i].asInt();
	}
}

void BgMap::initBgMapFloorTile()
{
	for (unsigned int i=0; i<m_imageCol; i++)
	{
		for (unsigned int j=0; j<m_imageRow; j++)
		{
			BgMapFloorTile* floorTile = BgMapFloorTile::create();
			floorTile->setFloorTileFileName(CCString::createWithFormat("map/s%d/s%d_%d_%d.jpg", m_mapID, m_mapID, i, j));

			floorTile->setPosition(CCPoint(m_imageSize.width*j, m_imageSize.height*i));
			this->addChild(floorTile, BgMap::getZOrderZero(this));//z轴
			m_floorTileVec.push_back(floorTile);
		}
	}
}

void BgMap::initBgMapPassagewayImage()
{
	vector<struct PortalInformation>::iterator itr;
	for (itr=m_mapPassageway.begin(); itr!=m_mapPassageway.end(); itr++)
	{
		CCPoint point = MapPoint((*itr).point).getCCPointValue();

		//生成传送门
		float value = BgMap::getZOrder(point);//z轴

		//PortalSprite* sprite = PortalSprite::createWithPortalSprite("trans-");
		//sprite->setPosition(point);
		//this->addChild(sprite, value);
	}
}

void BgMap::initNpcFigure()
{
	vector<struct NpcInformation>::iterator itr;
	for (itr=m_npcInfoVec.begin(); itr!=m_npcInfoVec.end(); itr++)
	{
		//NpcFigure* npc = NpcFigure::create(itr->key, itr->directionType);
		//npc->setPosition(itr->point);
		//this->addChild(npc, this->getZOrder(npc->getPosition()));

		//m_npcFigureVec.push_back(npc);
	}
}

void BgMap::updateImageDisplay()
{
	CCRect rect = this->getShowRect();

	CCRect rect2 = this->getHideRect();

	std::vector<BgMapFloorTile*>::iterator itr;
	for (itr=m_floorTileVec.begin(); itr!=m_floorTileVec.end(); itr++)
	{
		(*itr)->IntelligentDisplay(rect, rect2);
	}

	//std::vector<NpcFigure*>:: iterator itr2;
	//for (itr2=m_npcFigureVec.begin(); itr2!=m_npcFigureVec.end(); itr2++)
	//{
	//	(*itr2)->IntelligentDisplay(rect, rect2);
	//}

	if (m_delegate)
	{
		m_delegate->updateImageDisplay(rect, rect2);
	}

	CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

void BgMap::updateMapPosition(float delay)
{
	if (m_playerLead == NULL)
		return;

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pMap = ccpSub(winSize/2, m_playerLead->getPosition());

	pMap.x = MAX(pMap.x, WINSIZE.width-this->getBgSize().width);
	pMap.y = MAX(pMap.y, WINSIZE.height-this->getBgSize().height);
	pMap.x = MIN(pMap.x, 0);
	pMap.y = MIN(pMap.y, 0);

	this->setPosition(pMap);

	this->updateImageDisplay();
}

unsigned char BgMap::getCurrentGridValue(const MapPoint& point)
{
	M_INT row = point.x;
	M_INT col = point.z;
	unsigned char relust = 1;

	if (1 < col && col < m_gridCol-1 && 1 < row &&row < m_gridRow-1)
	{
		relust = m_grid[col][row];
	}

	return relust;
}

PortalInformation BgMap::isMapPassageway(cocos2d::CCNode *node)
{
	vector<struct PortalInformation>::iterator itr;
	for (itr=m_mapPassageway.begin(); itr!=m_mapPassageway.end(); itr++)
	{
		struct PortalInformation mapPassageway = *itr;
		CCPoint point = mapPassageway.point;
		if (ccpDistance(point, node->getPosition()) <= RADIUS_PASSAGEWAY)
		{
			return mapPassageway;
		}
	}
	return PortalInformationZero;
}

std::multimap<unsigned int, MapPoint>& BgMap::getEnemeyMap()
{
	return m_enemyMap;
}

void BgMap::addChildPlayerLead(CCNode* node, int bornPoint)
{
	map<int, CCPoint>::iterator itr = m_mapBornPoint.find(bornPoint);
	CCPoint point = MapPoint((*itr).second).getCCPointValue();
	this->addChildPlayerLead(node, point);
}

void BgMap::addChildPlayerLead(CCNode* node, CCPoint point)
{
	float value = BgMap::getZOrder(this->getPosition());//z轴
	m_playerLead = node;
	m_playerLead->setPosition(MapPoint(point).getCCPointValue());
	this->addChild(m_playerLead, value);
	this->updateMapPosition();
}

CCRect BgMap::getShowRect()
{
	CCRect rect = CCRectZero;
	rect.origin = ccpSub(CCPointZero, OFF_SIZE);
	rect.origin = ccpSub(rect.origin, this->getPosition());
	rect.size = ccpAdd(WINSIZE, OFF_SIZE * 2);
	return rect;
}

CCRect BgMap::getHideRect()
{
	CCRect rect = CCRectZero;
	rect.origin = ccpSub(CCPointZero, OFF_SIZE * 2);
	rect.origin = ccpSub(rect.origin, this->getPosition());
	rect.size = ccpAdd(WINSIZE, OFF_SIZE * 4);
	return rect;
}