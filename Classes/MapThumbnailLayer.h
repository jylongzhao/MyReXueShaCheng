#ifndef _MapThumbnailLayer_H_
#define _MapThumbnailLayer_H_

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class MapThumbnailLayer;
class MapThumbnailMenu:public CCSprite,public CCTargetedTouchDelegate
{
public:
	MapThumbnailMenu();
	~MapThumbnailMenu();
	static MapThumbnailMenu* create();
	bool initWithFile(const char *pszFilename);
	virtual void onEnter();
	virtual void onExit();
	
protected:
	CCSprite* m_playerIndicator;

	CCDictionary* m_enemyDic;

	vector<int> keyVec;

	CCLabelTTF* m_pCoordinateTTF;
protected:
	void update(float delta);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);

	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
private:
};
class MapThumbnailScrollView;
class MapThumbnailLayer:public CCLayer
{
public:
	CREATE_FUNC(MapThumbnailLayer);
	bool init();
protected:
	MapThumbnailScrollView* m_nMap;
	void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
private:
};

class MapThumbnailScrollView:
	public CCScrollView
{

	bool m_bIsMoved;

	CCSprite* m_playerIndicator;

	CCSprite* m_pEndPoint;

	void update(float delay);

	CCPoint m_beginPoint;

public:

	MapThumbnailScrollView();

	~MapThumbnailScrollView();

	static MapThumbnailScrollView* create();

	void initWithMap();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);

	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

};

#endif