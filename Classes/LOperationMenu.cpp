//
//  LOperationMenu.cpp
//  mir-mobile
//
//  出自九秒社区 http://www.9miao.com
//  Created by 栗元峰 on 14-1-2.
//
//

#include "LOperationMenu.h"
#include "LMenu.h"
#include "Player.h"
#include "GameScene.h"
//#include "Enemy.h"
#include "GameLoading.h"
#include "Direction.h"
LOperationMenu::LOperationMenu()
	:m_isHangUpAttack(false)
	,m_attackMethods(1001)
	,m_moveMethods(0)
	,m_direction(NULL)
	,m_currProgress(NULL)
	,m_operation(NULL)
{

}

LOperationMenu::~LOperationMenu()
{

}

bool LOperationMenu::init()
{
	if (!CCLayer::init())
		return false;

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	//    CCSprite* backGround = CCSprite::create("ui/direction_tray.png");
	//    CCSprite* rocker = CCSprite::create("ui/direction_head.png");
	//    Direction* dir = Direction::shareDirection(backGround, rocker);
	//	dir->setDelegate(GAME_SCENE);
	//    dir->setRadius(120);
	//    dir->setrockerRadius(40);
	//	dir->setPosition(CCPoint(120, 120));
	//    dir->setScale(0.8f);
	//	this->addChild(dir);
	//    m_direction = dir;

	m_operation = CCNode::create();
	m_operation->setPosition(CCPoint(winSize.width, 0));
	this->addChild(m_operation);

	CCSize commonAttackBtnSize = CCSize(90, 90);
	CCPoint commonAttackBtnPoint = ccpAdd(CCPoint(10, 10), commonAttackBtnSize/2);

	m_commonAttackBtn = CCControlButton::create(CCScale9Sprite::create("ui/attack_normal.png"));
	m_commonAttackBtn->setBackgroundSpriteForState(CCScale9Sprite::create("ui/attack_selected.png"), CCControlStateHighlighted);
	m_commonAttackBtn->setPreferredSize(commonAttackBtnSize);
	m_commonAttackBtn->setPosition(CCPoint(-commonAttackBtnPoint.x, commonAttackBtnPoint.y));
	m_operation->addChild(m_commonAttackBtn, 0, 0);
	m_commonAttackBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(LOperationMenu::commonAttack), CCControlEventTouchUpInside);

	CCSize skillAttackBtnSize = CCSize(75, 75);
	CCPoint skillAttackBtnPoint[3];
	skillAttackBtnPoint[0] = ccpAdd(CCPoint(120, 10), skillAttackBtnSize/2);
	skillAttackBtnPoint[1] = ccpAdd(CCPoint(110, 110), skillAttackBtnSize/2);
	skillAttackBtnPoint[2] = ccpAdd(CCPoint(10, 120), skillAttackBtnSize/2);

	for (int i=0; i<3; i++)
	{
		m_skillAttackBtn[i] = CCControlButton::create(CCScale9Sprite::create("ui/groove_normal.png"));
		m_skillAttackBtn[i]->setBackgroundSpriteForState(CCScale9Sprite::create("ui/groove_selected.png"), CCControlStateHighlighted);
		m_skillAttackBtn[i]->setPreferredSize(skillAttackBtnSize);
		m_skillAttackBtn[i]->setPosition(CCPoint(-skillAttackBtnPoint[i].x, skillAttackBtnPoint[i].y));
		m_operation->addChild(m_skillAttackBtn[i], 0, 0);
		m_skillAttackBtn[i]->addTargetWithActionForControlEvents(this, cccontrol_selector(LOperationMenu::skillAttack), CCControlEventTouchUpInside);
	}

	CCSize drugsBtnSize = CCSize(60, 60);
	CCPoint drugsBtnPoint = ccpAdd(CCPoint(210, 90), drugsBtnSize/2);

	m_drugsBtn = CCControlButton::create(CCScale9Sprite::create("ui/groove_normal.png"));
	m_drugsBtn->setBackgroundSpriteForState(CCScale9Sprite::create("ui/groove_selected.png"), CCControlStateHighlighted);
	m_drugsBtn->setPreferredSize(drugsBtnSize);
	m_drugsBtn->setPosition(CCPoint(-drugsBtnPoint.x, drugsBtnPoint.y));
	m_operation->addChild(m_drugsBtn, 0, 0);
	m_drugsBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(LOperationMenu::useDrugs), CCControlEventTouchUpInside);

	CCSize deliveryBtnSize = CCSize(60, 60);
	CCPoint deliveryBtnPoint = ccpAdd(CCPoint(10, 215), deliveryBtnSize/2);

	m_deliveryBtn = CCControlButton::create(CCScale9Sprite::create("ui/groove_normal.png"));
	m_deliveryBtn->setBackgroundSpriteForState(CCScale9Sprite::create("ui/groove_selected.png"), CCControlStateHighlighted);
	m_deliveryBtn->setPreferredSize(deliveryBtnSize);
	m_deliveryBtn->setPosition(CCPoint(-deliveryBtnPoint.x, deliveryBtnPoint.y));
	m_operation->addChild(m_deliveryBtn, 0, 0);
	m_deliveryBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(LOperationMenu::usedeliveryProp), CCControlEventTouchUpInside);

	CCControlButton* hangUpBtn = CCControlButton::create(CCLabelTTF::create("自动攻击", "fonts/Marker Felt.ttf", 15), CCScale9Sprite::create("ui/direction_head.png"));
	hangUpBtn->setPreferredSize(CCSize(95, 95));
	hangUpBtn->setPosition(CCPoint(WINSIZE.width-250, WINSIZE.height-100));
	this->addChild(hangUpBtn, 0, 0xfffffff0);
	hangUpBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(LOperationMenu::hangUpAttack), CCControlEventTouchUpInside);

	CCControlButton* moveMethodsBtn = CCControlButton::create(CCLabelTTF::create("取消跑步", "fonts/Marker Felt.ttf", 15), CCScale9Sprite::create("ui/direction_head.png"));
	moveMethodsBtn->setPreferredSize(CCSize(95, 95));
	moveMethodsBtn->setPosition(CCPoint(100, WINSIZE.height-200));
	this->addChild(moveMethodsBtn, 0);
	moveMethodsBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(LOperationMenu::moveMethods), CCControlEventTouchUpInside);

	//this->addSkillIcon(0, 1002);
	this->addSkillIcon(1, 2007);
	this->addSkillIcon(2, 2005);
	return true;
}

CCControlButton* LOperationMenu::getSkillAttackBtn(unsigned int number)
{
	if (number > 2)
		return NULL;

	return m_skillAttackBtn[number];

}

void LOperationMenu::addSkillIcon(CCControlButton* btn, int skillNumber)
{
	Player::sharePlayer()->subAttackSkill(btn->getTag());

	btn->removeChildByTag(TAG_PROGRESS_SKILL);

	for (int i=0; i<3; i++)
	{
		if (skillNumber == m_skillAttackBtn[i]->getTag())
		{
			m_skillAttackBtn[i]->removeChildByTag(TAG_PROGRESS_SKILL);
			m_skillAttackBtn[i]->setTag(0);
		}
	}

	CCString* str = CCString::createWithFormat("ui/skill/skill_%d.png",skillNumber);
	CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(str->getCString());
	if (texture)
	{
		ProgressAutomatic* progressTimer = ProgressAutomatic::create(CCSprite::createWithTexture(texture));
		progressTimer->setType(kCCProgressTimerTypeRadial);
		progressTimer->setPosition(btn->getContentSize()/2);
		btn->addChild(progressTimer, 1, TAG_PROGRESS_SKILL);
		progressTimer->setPercentage(100);

		progressTimer->setScale(1.8f);
	}

	btn->setTag(skillNumber);

	Player::sharePlayer()->addAttackSkill(skillNumber);
}

void LOperationMenu::addSkillIcon(int btnNumber, int skillNumber)
{
	CCControlButton* btn = m_skillAttackBtn[btnNumber];
	this->addSkillIcon(btn, skillNumber);
}

void LOperationMenu::addDrugs(int drugsNumber)
{
	m_drugsBtn->removeChildByTag(TAG_PROGRESS_SKILL);

	CCString* str = CCString::createWithFormat("ui/skill/skill_%d.png",drugsNumber);
	CCSprite* sprite = CCSprite::create(str->getCString());
	sprite->setPosition(m_drugsBtn->getContentSize()/2);
	m_drugsBtn->addChild(sprite, 1, TAG_PROGRESS_SKILL);
	sprite->setScale(1.2f);

	m_drugsBtn->setTag(drugsNumber);
}

void LOperationMenu::commonAttack(CCObject* sender, CCControlEvent controlEvents)
{
	m_currProgress = NULL;
	m_attackMethods = 1001;
	this->attack();
}

void LOperationMenu::skillAttack(CCObject* sender, CCControlEvent controlEvents)
{
	CCControlButton* btn = (CCControlButton*)sender;
	if (btn->getTag() == 0)
		return;
	m_currProgress = dynamic_cast<ProgressAutomatic*>(btn->getChildByTag(TAG_PROGRESS_SKILL));
	m_attackMethods = btn->getTag();
	this->attack();
}

void LOperationMenu::useDrugs(CCObject *sender, CCControlEvent controlEvents)
{
	Player::sharePlayer()->bloodReturn(5000);
	m_drugsBtn->removeChildByTag(TAG_PROGRESS_SKILL);
	m_drugsBtn->setTag(0);
}

void LOperationMenu::usedeliveryProp(cocos2d::CCObject *sender, CCControlEvent controlEvents)
{
	float r = CCRANDOM_0_1();

	if (r == 1)
		r = 0;

	GameLoading::runGameLoading(100, r * 4 + 1);
}

void LOperationMenu::skillAttackCooling(CCProgressTimer* progress)
{

}

void LOperationMenu::attack()
{
	if (GAME_SCENE->getSelected() == NULL)
	{
		//GAME_SCENE->showSelected(Player::sharePlayer()->getAgainstMeOfFirst());

	}

	Monomer* attackMonomerMajor =  GAME_SCENE->getSelected();

	if (attackMonomerMajor == NULL)
	{
		MapPoint playerPoint = MapPoint(Player::sharePlayer()->getPosition());
		CCArray* array = CCArray::create();
		CCArray* enemyKeys = GAME_SCENE->getEnemyDictionary()->allKeys();
		if (enemyKeys)
		{
			for (unsigned int i=0; i<enemyKeys->count(); i++)
			{
				//int key = ((CCInteger*)enemyKeys->objectAtIndex(i))->getValue();
				//Enemy* enemy = (Enemy*)GAME_SCENE->getEnemyDictionary()->objectForKey(key);
				//MapPoint enemyPoint = MapPoint(enemy->getPosition());
				//if (playerPoint.getDistance(enemyPoint) <= Player::sharePlayer()->getVisualRange())
				//{
				//	array->addObject(enemy);
				//}
			}
		}

		//for (unsigned int i=0; i<array->count(); i++)
		//{
		//	Enemy* enemy = (Enemy*)array->objectAtIndex(i);

		//	if (attackMonomerMajor == NULL)
		//	{
		//		attackMonomerMajor = enemy;
		//		continue;
		//	}
		//	MapPoint enemyPoint = MapPoint(enemy->getPosition());

		//	MapPoint attackMonomerPoint = MapPoint(attackMonomerMajor->getPosition());

		//	if (playerPoint.getDistance(enemyPoint) < playerPoint.getDistance(attackMonomerPoint))
		//	{
		//		attackMonomerMajor = enemy;
		//	}
		//}
		//GAME_SCENE->showSelected(attackMonomerMajor);
	}

	if (attackMonomerMajor)
	{
		Player::sharePlayer()->followAttackAndSetAttackMethods(attackMonomerMajor, m_attackMethods);
	}
}

void LOperationMenu::hangUpAttack(CCObject* sender, CCControlEvent controlEvents)
{
	bool flag = false;
	CCArray* enemyKeys = GAME_SCENE->getEnemyDictionary()->allKeys();
	if (enemyKeys)
	{
		/*for (unsigned int i=0; i<enemyKeys->count(); i++)
		{
			int key = ((CCInteger*)enemyKeys->objectAtIndex(i))->getValue();
			Enemy* enemy = (Enemy*)GAME_SCENE->getEnemyDictionary()->objectForKey(key);
			MapPoint playerPoint = MapPoint(Player::sharePlayer()->getPosition());
			MapPoint enemyPoint = MapPoint(enemy->getPosition());
			if (playerPoint.getDistance(enemyPoint) <= Player::sharePlayer()->getVisualRange())
			{
				flag = true;
				break;
			}
		}*/
	}

	do {
		CC_BREAK_IF(!flag);
		CCControlButton* menu = (CCControlButton*)sender;
		if (m_isHangUpAttack)
		{
			m_isHangUpAttack = false;
			((CCLabelTTF*)menu->getTitleLabelForState(CCControlStateNormal))->setString("自动攻击");
		}
		else
		{
			m_isHangUpAttack = true;
			this->attack();
			((CCLabelTTF*)menu->getTitleLabelForState(CCControlStateNormal))->setString("停止自动");
		}
	}
	while (0);
}

void LOperationMenu::intelligentSearch()
{
	if (m_isHangUpAttack)
	{
		CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(LOperationMenu::attack));
		CCSequence* actions = CCSequence::create(CCDelayTime::create(0.1f), callFunc, NULL);
		this->runAction(actions);

		if (Player::sharePlayer()->getBloodCap()/4 >= Player::sharePlayer()->getBlood())
		{
			Player::sharePlayer()->bloodReturn(Player::sharePlayer()->getBloodCap());
		}
	}
}

void LOperationMenu::cancelHangUP()
{
	if (m_isHangUpAttack)
	{
		this->hangUpAttack((CCObject*)this->getChildByTag(0xfffffff0), CCControlEventTouchUpInside);
	}
}

void LOperationMenu::moveMethods(cocos2d::CCObject *sender, CCControlEvent controlEvents)
{
	CCControlButton* menu = (CCControlButton*)sender;

	if (m_moveMethods == 0)
	{
		m_moveMethods = 1;
		((CCLabelTTF*)menu->getTitleLabelForState(CCControlStateNormal))->setString("取消步行");
	}
	else if (m_moveMethods == 1)
	{
		m_moveMethods = 2;
		((CCLabelTTF*)menu->getTitleLabelForState(CCControlStateNormal))->setString("取消寻路");
	}
	else if (m_moveMethods == 2)
	{
		m_moveMethods = 0;
		((CCLabelTTF*)menu->getTitleLabelForState(CCControlStateNormal))->setString("取消跑步");
	}
}

void LOperationMenu::hideOperationMenu()
{
	if (m_direction)
	{
		((Direction*)m_direction)->setTouchEnabled(false);
		m_direction->stopAllActions();

		CCMoveTo* moveTo = CCMoveTo::create(0.3f, CCPoint(-120, 120));
		CCScaleTo* scaleTo = CCScaleTo::create(0.3f, 0.8f);
		CCEaseSineOut* easeBack = CCEaseSineOut::create(CCSpawn::create(moveTo, scaleTo, NULL));
		m_direction->runAction(easeBack);
	}

	if (m_operation)
	{
		m_operation->stopAllActions();

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCMoveTo* moveTo2 = CCMoveTo::create(0.3f, CCPoint(winSize.width+300, 0));
		CCScaleTo* scaleTo2 = CCScaleTo::create(0.3f, 1.0f);
		CCEaseSineOut* easeBack2 = CCEaseSineOut::create(CCSpawn::create(moveTo2, scaleTo2, NULL));
		m_operation->runAction(easeBack2);
	}
}

void LOperationMenu::showOperationMenu()
{
	if (m_direction)
	{
		((Direction*)m_direction)->setTouchEnabled(true);
		m_direction->stopAllActions();

		CCMoveTo* moveTo = CCMoveTo::create(0.3f, CCPoint(120, 120));
		CCScaleTo* scaleTo = CCScaleTo::create(0.3f, 0.8f);
		CCEaseSineOut* easeBack = CCEaseSineOut::create(CCSpawn::create(moveTo, scaleTo, NULL));
		m_direction->runAction(easeBack);
	}

	if (m_operation)
	{
		m_operation->stopAllActions();

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCMoveTo* moveTo2 = CCMoveTo::create(0.3f, CCPoint(winSize.width, 0));
		CCScaleTo* scaleTo2 = CCScaleTo::create(0.3f, 1.0f);
		CCEaseSineOut* easeBack2 = CCEaseSineOut::create(CCSpawn::create(moveTo2, scaleTo2, NULL));
		m_operation->runAction(easeBack2);
	}
}

void LOperationMenu::joinEditState()
{
	if (m_operation)
	{
		m_operation->setPositionY(100);
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCMoveTo* moveTo2 = CCMoveTo::create(0.3f, CCPoint(winSize.width, 100));
		CCScaleTo* scaleTo2 = CCScaleTo::create(0.3f, 1.0f);
		CCEaseSineOut* easeBack2 = CCEaseSineOut::create(CCSpawn::create(moveTo2, scaleTo2, NULL));
		m_operation->runAction(easeBack2);
	}
}
