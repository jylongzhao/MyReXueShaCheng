#ifndef _PlayerController_H_
#define _PlayerController_H_

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class PlayerController:public CCObject
{

	CC_SYNTHESIZE(unsigned int, m_playerNumber, PlayerNumber);

	CC_SYNTHESIZE(unsigned int, m_hairNumber, HairNumber);

	CC_SYNTHESIZE(unsigned int, m_weaponsNumber, WeaponsNumber);

	CC_SYNTHESIZE(std::string, m_playerName, PlayerName);

	CC_SYNTHESIZE_READONLY(int, m_playerLevel, PlayerLevel);

	CC_SYNTHESIZE_READONLY(int, m_playerShowID, PlayerShowID);

	CC_SYNTHESIZE_READONLY(int, m_playerUID, PlayerLevelUID);

	CC_SYNTHESIZE_READONLY(int, m_carryingWeaponsID, CarryingWeaponsID);
public:
	PlayerController();

	virtual ~PlayerController();

	static PlayerController* sharePlayerController();

protected:
	bool init();

	CREATE_FUNC(PlayerController);
private:
};
#endif