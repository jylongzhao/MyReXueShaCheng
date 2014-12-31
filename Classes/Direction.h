
#include "cocos2d.h"
#include "MapPoint.h"
#include "GameScene.h"
using namespace cocos2d;
class Direction;
struct DirectionDelegate
{
	virtual void beginMoveActions() = 0;

	virtual void stopMoveActions() = 0;

	virtual void AccurateMoveActions(const MapPoint& point) = 0;
};


class Direction : public CCNode, public CCTargetedTouchDelegate
{
	CCSprite* m_backGround;

	CCSprite* m_rocker;

	CCRect m_rect;

	CCPoint m_point;

	CC_SYNTHESIZE(GameScene*, m_delegate, Delegate);

	CC_SYNTHESIZE(float, m_bgRadius, Radius);

	CC_SYNTHESIZE(float, m_rockerRadius, rockerRadius);

	CC_SYNTHESIZE(float, m_touchEnabled, TouchEnabled);

public:

	Direction();

	virtual~Direction();

	void onEnter();

	void onExit();

	static Direction* shareDirection(CCSprite* backGround, CCSprite* rocker);

	bool initWithDirection(CCSprite* backGround, CCSprite* rocker);

private:

	void registerWithTouchDispatcher(void);

	void unRegisterWithTouchDispatcher(void);

	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);

	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	void setRocker(CCPoint point);

	void readyActions(float delay = 0.0f);

	void rockerHoming();

	void touchBegin(float dt);

	void touchEnd();

};