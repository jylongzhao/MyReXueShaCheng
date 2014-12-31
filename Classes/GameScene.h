
#ifndef __mir_mobile__GameScene__
#define __mir_mobile__GameScene__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

#include "BgMap.h"
#include "Player.h"
#include "GameInfoUIController.h"
USING_NS_CC;
USING_NS_CC_EXT;

#define GAME_SCENE GameScene::shareGameScene()

class GameScene: public CCLayer
	, public BgMapDelegate
{

	CCPoint m_playerDirection;

	CCSprite* m_selected;

	//CCTouchMouse* m_touchMouse;

	bool m_touchProtected;

	CC_SYNTHESIZE_READONLY(bool, m_isPlayerMoveActions, PlayerMoveActions);

	CC_SYNTHESIZE(BgMap*, m_bgMap, CurrBgMap);

	CC_SYNTHESIZE_READONLY(GameInfoUIController*, m_gameInfoUIController, GameInfoUIController);

	CC_SYNTHESIZE_READONLY(CCDictionary*, m_enemyDictionary, EnemyDictionary);

	CC_SYNTHESIZE_READONLY(CCDictionary*, m_otherDictionary, OtherDictionary);

	std::map<Monomer*, int> m_gMapPoint;

	std::multimap<unsigned int, MapPoint> m_waitReincarnationEnemy;

	//std::map<int, PropIconShow*> m_gPropMap;

public:

	static CCScene* scene();

	GameScene();

	virtual ~GameScene();

	static GameScene* shareGameScene();

	static GameScene* create();

	bool init();

	void replaceBgMap(int mapID, const int born);

	//void removeEnemy(Enemy* enemy);

	void addEnemy();

	//vector<Monomer*> getMonmerVecIsLenght(CCPoint point, int lenght);

	void OutOfCombat();

	//void showSelected(Monomer* var);

	Monomer* getSelected();

	bool isPointValid(const MapPoint& point);

	std::deque<MapPoint> getPath(const MapPoint& begin, const MapPoint& end);

	std::deque<MapPoint> getPathNextRunGrid(const MapPoint& begin, const MapPoint& end);

	std::deque<MapPoint> getPathNextWalkGrid(const MapPoint& begin, const MapPoint& end);

	void insterMapPoint(Monomer* var, const MapPoint& point);

	void eraseMapPoint(Monomer* var);

	bool getMapPoint(const MapPoint& point);

	//bool insterMapPointForProp(PropIconShow* var, const MapPoint& point);

	void eraseMapPointForProp(const MapPoint& point);

	//PropIconShow* getMapPointForProp(const MapPoint& point);

protected:

	virtual void onEnterTransitionDidFinish();

	void registerWithTouchDispatcher(void);

	void unRegisterWithTouchDispatcher(void);

	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);

	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	void touchProtected();

	void untouchProtected();

	void updateImageDisplay(CCRect& showRect, CCRect& hideRect);

	void playerMovement();

	MapPoint getPlayerDirection();

public:

	void playerRunning(float delay = 0);

	virtual void beginMoveActions();

	virtual void stopMoveActions();

	virtual void AccurateMoveActions(const MapPoint& point);

public:

	virtual void keyBackClicked();

	virtual void keyMenuClicked();

	void alertCallBack(const int number);

	void log(float dt);
};


#endif /* defined(__mir_mobile__GameScene__) */
