#ifndef _GameLoading_H_
#define _GameLoading_H_

#include "cocos2d.h"

USING_NS_CC;

class GameLoading:public CCSprite,public CCTargetedTouchDelegate
{
	int m_mapID;
	int m_born;

	CCSprite* m_sprite;

public:
	GameLoading(const int mapID,const int born);

	virtual ~GameLoading();

	static GameLoading* runGameLoading(int mapID,const int born);

	void setOpacity(GLubyte opacity);
protected:
	void onEnter();

	void onExit();

	bool init();

	void initGameScene(float delay = 0);

	void updateBgMap(float delay = 0);

	void updateFinish();

	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
};
#endif