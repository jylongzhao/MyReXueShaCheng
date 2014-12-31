#pragma once
#ifndef _Figure_H_
#define _Figure_H_


#include "cocos2d.h"
#include "TextureController.h"

#define TAG_ANIMATE 0xfffffff0

using namespace cocos2d;

typedef enum
{
	FDirUp              = 8,
	FDirLeftAndUp       = 7,
	FDirLeft            = 6,
	FDirDownAndLeft     = 5,
	FDirDown            = 4,
	FDirRightAndDown    = 3,
	FDirRight           = 2,
	FDirUpAndRight      = 1,
	FDirNone            = 0
}FigureDirectionType;

typedef enum
{
	FStateDeath     = 7,
	FStateHurt      = 6,
	FStateCaster    = 5,
	FStateAttack    = 4,
	FStateRun       = 3,
	FStateWalk      = 2,
	FStateStand     = 1,
	FStateNone      = 0
}FigureStateType;

class Figure;
class FigureDelegate
{
public:

	virtual void attacking() = 0;

	virtual void attackCompleted() = 0;

	virtual void underAttack() = 0;

	virtual void deathActionFinish() = 0;

	void removeDelegate(Figure* var);
};

class Figure: public CCSprite
{

	float m_frameRate;

	unsigned int m_figureNumber;

	unsigned int m_hairNumber;

	unsigned int  m_weaponNumber;

	TexturePathType m_pathType;

	FigureDelegate* m_pDelegate;

public:

	Figure(TexturePathType type, unsigned int figureNumber);

	virtual ~Figure();

	virtual void onEnter();

	virtual void onExit();

	static Figure* create(TexturePathType type, unsigned int figureNumber);

	bool init();

	void setHair(unsigned int hairNumber);

	void setWeapon(unsigned int weaponNumber);

	void setFigureState(FigureStateType stateType, FigureDirectionType directionType);

	void setDelegate(FigureDelegate* delegate);

	CC_SYNTHESIZE_READONLY(FigureStateType, m_stateType, StateType);

	CC_SYNTHESIZE_READONLY(FigureDirectionType, m_directionType, DirectionType);

	CC_SYNTHESIZE_READONLY(CCSprite*, m_hairSprite, HairSprite);

	CC_SYNTHESIZE_READONLY(CCSprite*, m_weaponSprite, WeaponSprite);

	CCPoint getAnchorPointWithFoot();

	CCPoint getAnchorPointWithHand();

	CCPoint getAnchorPointCenter();

	void setOpacity(GLubyte opacity);

private:

	void updateFigure();

	void runActions();

	CCActionInterval* getRunActionsFromSprite(CCSprite* sprite, std::string& path);

	void attackCompleted();

	void hurtCompleted();

	void deathCompleted();

	void attacking();

};


#endif