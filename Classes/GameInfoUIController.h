//
//  GameInfoUIController.h
//  mir9
//
//  Created by ÀõÔª·å on 14-1-14.
//
//

#ifndef __mir9__GameInfoUIController__
#define __mir9__GameInfoUIController__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "LOperationMenu.h"
//#include "GameTabBarMenu.h"
//#include "AttackEnemyInfo.h"
//#include "ChatInterface.h"
#include "MapThumbnailLayer.h"
USING_NS_CC;
USING_NS_CC_EXT;

#define GAME_UILAYER GAME_SCENE->getGameInfoUIController()

class GameInfoUIController: public CCLayer {

	CC_SYNTHESIZE_READONLY(LOperationMenu*, m_operationMenu, OperationMenu);

	//CC_SYNTHESIZE_READONLY(GameTabBarMenu*, m_gameTabBarMenu, GameTabBarMenu);

	//CC_SYNTHESIZE_READONLY(AttackEnemyInfo*, m_attackEnemyInfo, AttackEnemyInfo);

	//CC_SYNTHESIZE_READONLY(ChatInterface*, m_chatInterface, ChatInterface);

	CC_SYNTHESIZE(MapThumbnailMenu*, m_mapThumbnailMenu, MapThumbnailMenu);

	std::deque<CCNode*> m_pMenuSmall;

	CCNode* m_pMenuBig;

public:

	GameInfoUIController();

	virtual ~GameInfoUIController();

	CREATE_FUNC(GameInfoUIController);

	bool init();

	void modeSwitch(CCObject* sender = NULL);

	void updateBloodPro();

	void updateMagicPro();

	void updateLevelTTF();

	void addSmallMenu(CCNode* node);

	void addBigMenu(CCNode* node);

	void removeSmallMenu(CCNode* node);

	void removeSmallMenuAndButton(CCNode* node, CCControlEvent event = CCControlEventTouchUpInside);

	void removeBigMenuAndButton(CCNode* node = NULL, CCControlEvent event = CCControlEventTouchUpInside);

private:

	void registerWithTouchDispatcher(void);

	void initWithHeadUI();

	void initWithMapThumbnail();

	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

private:

	CCSize m_winSize;

	bool m_isShowTabBar;

	UIImageView* m_headIcon;

	UILabel* m_nickNameTTF;

	UILabelAtlas* m_levelTTF;

	UILoadingBar* m_bloodPro;

	UILoadingBar* m_magicPro;

	UIButton* m_headBtn;
};


#endif /* defined(__mir9__GameInfoUIController__) */
