#ifndef _RoleCreateLayer_H_
#define _RoleCreateLayer_H_
#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class RoleCreateLayer:public CCLayer
{
	CCObject* m_selected;
	CCArray* m_roleArray;
	UITextButton* m_textButton;
	UITextField* m_textField;
	CCString* m_nickName;
	int m_roleID;
public:
	RoleCreateLayer();
	virtual ~RoleCreateLayer();
	CREATE_FUNC(RoleCreateLayer);
	bool init();
	void joinGame();
protected:
	void runActionsForFigure(CCObject* pSender);
	void setSelector(CCObject* pSender,CCControlEvent controlEvent);
	void randomNickName(CCObject* pSender);
	void sendMessage(CCObject* pSender);
	void eventListenerTextField(CCObject* pSender,TextFiledEventType type);
	void attachWithIMEEvent(CCObject* pSender);
	void detachWithIMEEvent(CCObject* pSender);
	void insertTextEvent(CCObject* pSender);
	void deleteBackwardEvent(CCObject* pSender);
};
#endif