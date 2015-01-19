//
//  GameInfoUIController.cpp
//  mir9
//
//  出自九秒社区 http://www.9miao.com
//  Created by 栗元峰 on 14-1-14.
//
//

#include "GameInfoUIController.h"
//#include "LMenu.h"
#include "PlayerController.h"
#include "Player.h"
GameInfoUIController::GameInfoUIController()
	:m_operationMenu(NULL)
	,m_isShowTabBar(true)
	,m_headIcon(NULL)
	,m_headBtn(NULL)
	,m_levelTTF(NULL)
	,m_nickNameTTF(NULL)
	,m_bloodPro(NULL)
	,m_magicPro(NULL)
	//,m_gameTabBarMenu(NULL)
	//,m_attackEnemyInfo(NULL)
	//,m_chatInterface(NULL)
	,m_pMenuBig(NULL)
{

}

GameInfoUIController::~GameInfoUIController()
{

}

void GameInfoUIController::registerWithTouchDispatcher()
{
	CCTouchDispatcher* touchDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	touchDispatcher->addTargetedDelegate(this, 100, true);
}

bool GameInfoUIController::init()
{
	if (!CCLayer::init())
		return false;

	m_winSize = CCDirector::sharedDirector()->getWinSize();

	this->initWithHeadUI();

	m_mapThumbnailMenu = MapThumbnailMenu::create();
	m_mapThumbnailMenu->setPosition(ccpSub(m_winSize, CCPoint(100, 100)));
	this->addChild(m_mapThumbnailMenu);

	m_operationMenu = LOperationMenu::create();
	this->addChild(m_operationMenu);

	//m_attackEnemyInfo = AttackEnemyInfo::create();
	//m_attackEnemyInfo->setPosition(CCPoint(m_winSize.width/2-125, m_winSize.height-110));
	//this->addChild(m_attackEnemyInfo);
	//m_attackEnemyInfo->hide();

	//m_chatInterface = ChatInterface::create();
	//m_chatInterface->setPosition(CCPoint(220, 0));
	//this->addChild(m_chatInterface);

	//m_gameTabBarMenu = GameTabBarMenu::create();
	//m_gameTabBarMenu->setPosition(CCPoint(m_winSize.width-960, -100));
	//this->addChild(m_gameTabBarMenu);

	return true;
}

void GameInfoUIController::initWithHeadUI()
{
	UILayer* layer = UILayer::create();
	layer->setScale(1.0f);
	layer->setPosition(CCPoint(-480*(1-layer->getScale()), m_winSize.height-320));
	this->addChild(layer);

	UILayout* widget = dynamic_cast<UILayout*>(GUIReader::shareReader()->widgetFromJsonFile("ui/head_UI/head_UI.json"));
	if (widget)
	{
		layer->addWidget(widget);
	}

	const char* nickName = PlayerController::sharePlayerController()->getPlayerName().c_str();
	m_nickNameTTF = dynamic_cast<UILabel*>(layer->getWidgetByName("nickName"));
	if (m_nickNameTTF)
	{
		m_nickNameTTF->setText(nickName);
	}

	m_headIcon = dynamic_cast<UIImageView*>(layer->getWidgetByName("ImageView"));
	if (m_headIcon)
	{
		m_headIcon->setTouchEnabled(true);
	}

	m_levelTTF = dynamic_cast<UILabelAtlas*>(layer->getWidgetByName("level"));
	if (m_levelTTF)
	{
		m_levelTTF->setStringValue("3");
	}

	m_bloodPro = dynamic_cast<UILoadingBar*>(layer->getWidgetByName("redBar"));
	if (m_bloodPro)
	{
		m_bloodPro->setPercent(100);
	}

	m_magicPro = dynamic_cast<UILoadingBar*>(layer->getWidgetByName("blueBar"));
	if (m_magicPro)
	{
		m_magicPro->setPercent(100);
	}

	m_headBtn = dynamic_cast<UIButton*>(layer->getWidgetByName("head"));
	if (m_headBtn)
	{
		m_headBtn->setTouchEnabled(true);
		m_headBtn->addReleaseEvent(this, coco_releaseselector(GameInfoUIController::modeSwitch));
	}

}

void GameInfoUIController::modeSwitch(cocos2d::CCObject *sender)
{
	/*if (this->getActionByTag(0xacff))
		return;

	if (m_isShowTabBar)
	{
		m_isShowTabBar = false;
		m_operationMenu->hideOperationMenu();
		m_chatInterface->hideChatInterface();

		CCDelayTime* delay = CCDelayTime::create(0.3f);
		CCCallFunc* finish = CCCallFunc::create(m_gameTabBarMenu, callfunc_selector(GameTabBarMenu::showGameTabBarMenu));
		CCSequence* actions = CCSequence::create(delay, finish, NULL);
		actions->setTag(0xacff);
		this->runAction(actions);
	}
	else
	{
		m_isShowTabBar = true;
		m_gameTabBarMenu->hideGameTabBarMenu();

		CCDelayTime* delay = CCDelayTime::create(0.3f);
		CCCallFunc* finish = CCCallFunc::create(m_operationMenu, callfunc_selector(LOperationMenu::showOperationMenu));
		CCCallFunc* finish2 = CCCallFunc::create(m_chatInterface, callfunc_selector(ChatInterface::showChatInterface));
		CCSequence* actions = CCSequence::create(delay, finish, finish2, NULL);
		actions->setTag(0xacff);
		this->runAction(actions);
	}*/
}

void GameInfoUIController::updateBloodPro()
{
	m_bloodPro->setPercent(100*Player::sharePlayer()->getBlood()/Player::sharePlayer()->getBloodCap());
}

void GameInfoUIController::updateMagicPro()
{
	m_bloodPro->setPercent(100*Player::sharePlayer()->getMagic()/Player::sharePlayer()->getMagicCap());
}

void GameInfoUIController::updateLevelTTF()
{

}

void GameInfoUIController::addSmallMenu(cocos2d::CCNode *node)
{
	this->removeBigMenuAndButton();

	for (std::deque<CCNode*>::iterator itr=m_pMenuSmall.begin(); itr!=m_pMenuSmall.end(); itr++)
	{
		if (typeid(*node) == typeid(**itr))
			return;
	}

	if (m_pMenuSmall.size() >= 2)
	{
		m_pMenuSmall.at(0)->removeFromParent();
		m_pMenuSmall.pop_front();
		m_pMenuSmall.at(0)->setPosition(CCPoint(m_winSize.width/4, (m_winSize.height+80)/2));
	}

	node->setPosition(CCPoint(m_winSize.width/4 * (m_pMenuSmall.size()*2+1), (m_winSize.height+80)/2));
	this->addChild(node);
	m_pMenuSmall.push_back(node);

	this->setTouchEnabled(true);
}

void GameInfoUIController::removeSmallMenu(cocos2d::CCNode *node)
{
	if (node == NULL)
		return;

	std::deque<CCNode*>::iterator* pItr = NULL;
	for (std::deque<CCNode*>::iterator itr=m_pMenuSmall.begin(); itr!=m_pMenuSmall.end(); itr++)
	{
		if (node->isEqual(*itr))
		{
			pItr = &itr;
			break;
		}
	}

	if (pItr)
	{
		m_pMenuSmall.erase(*pItr);
		node->removeFromParent();
	}

	if (m_pMenuSmall.size() > 0)
	{
		m_pMenuSmall.at(0)->setPosition(CCPoint(m_winSize.width/4, (m_winSize.height+80)/2));
	}
	else
	{
		this->setTouchEnabled(false);
	}
}

void GameInfoUIController::removeSmallMenuAndButton(cocos2d::CCNode *node, CCControlEvent event)
{
	this->removeSmallMenu(node->getParent());
}

void GameInfoUIController::addBigMenu(cocos2d::CCNode *node)
{
	this->removeBigMenuAndButton();

	if (m_pMenuSmall.size() > 0)
	{
		for (std::deque<CCNode*>::iterator itr=m_pMenuSmall.begin(); itr!=m_pMenuSmall.end(); itr++)
			(*itr)->removeFromParent();

		m_pMenuSmall.clear();
	}


	node->setPosition(CCPoint(m_winSize.width/2, (m_winSize.height+80)/2));
	this->addChild(node);
	m_pMenuBig = node;

	this->setTouchEnabled(true);
}

void GameInfoUIController::removeBigMenuAndButton(CCNode* node, CCControlEvent event)
{
	if (m_pMenuBig)
	{
		m_pMenuBig->removeFromParent();
		m_pMenuBig = NULL;
	}
	this->setTouchEnabled(false);
}

bool GameInfoUIController::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}