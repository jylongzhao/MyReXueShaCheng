#ifndef _GameScene_H_
#define _GameScene_H_

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class GameLand:public CCLayer,public CCEditBoxDelegate
{
	CCEditBox* m_accountInputBox;
	CCEditBox* m_cipherInputBox;

	virtual void editBoxReturn(CCEditBox* editBox);
public:
	static CCScene* scene();

	GameLand();

	virtual ~GameLand();

	CREATE_FUNC(GameLand);

	bool init();
private:
	void sendLand(CCObject *sender, CCControlEvent controlEvent);
	
	void joinGame();
	
	void registration(CCObject *sender, CCControlEvent controlEvent);
public:

	virtual void keyBackClicked();

	virtual void keyMenuClicked();
};
#endif