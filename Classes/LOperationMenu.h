//
//  LOperationMenu.h
//  mir-mobile
//
//  Created by ÀõÔª·å on 14-1-2.
//
//

#ifndef __mir_mobile__LOperationMenu__
#define __mir_mobile__LOperationMenu__

#include <iostream>
#include "ProgressAutomatic.h"

#define TAG_PROGRESS_SKILL 0xfffffff

class LOperationMenu: public CCLayer {

	bool m_isHangUpAttack;

	int m_attackMethods;

	CCNode* m_direction;

	CCNode* m_operation;

	CCControlButton* m_commonAttackBtn;

	CCControlButton* m_skillAttackBtn[3];

	CC_SYNTHESIZE_READONLY(CCControlButton*, m_drugsBtn, DrugsBtn);

	CC_SYNTHESIZE_READONLY(CCControlButton*, m_deliveryBtn, DeliveryBtn);

	CC_SYNTHESIZE_READONLY(ProgressAutomatic*, m_currProgress, CurrProgress);

	CC_SYNTHESIZE_READONLY(int, m_moveMethods, MoveMethods);

public:

	LOperationMenu();

	virtual ~LOperationMenu();

	CREATE_FUNC(LOperationMenu);

	bool init();

	void attack();

	void hangUpAttack(CCObject* sender, CCControlEvent controlEvents);

	void moveMethods(CCObject* sender = NULL, CCControlEvent controlEvents = NULL);

	void intelligentSearch();

	void cancelHangUP();

	void hideOperationMenu();

	void showOperationMenu();

	void joinEditState();

	void commonAttack(CCObject* sender = NULL, CCControlEvent controlEvents = NULL);

	void skillAttack(CCObject* sender = NULL, CCControlEvent controlEvents = NULL);

	void useDrugs(CCObject* sender = NULL, CCControlEvent controlEvents = NULL);

	void usedeliveryProp(CCObject* sender = NULL, CCControlEvent controlEvents = NULL);

	CCControlButton* getSkillAttackBtn(unsigned int number);

	void addSkillIcon(CCControlButton* btn, int skillNumber);

	void addSkillIcon(int btnNumber, int skillNumber);

	void addDrugs(int drugsNumber);

	void skillAttackCooling(CCProgressTimer* progress);

};

#endif /* defined(__mir_mobile__LOperationMenu__) */
