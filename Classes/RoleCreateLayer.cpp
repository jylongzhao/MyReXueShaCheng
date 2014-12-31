#include "RoleCreateLayer.h"
#include "Figure.h"
#include "GameLoading.h"
#include "GameSocket.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
const char* font_UITextFieldTest ="Marker Felt";
#else
const char* font_UITextFieldTest ="cocosgui/Marker Felt.ttf";
#endif

RoleCreateLayer::RoleCreateLayer():m_textButton(NULL),m_textField(NULL),m_nickName(NULL),m_selected(NULL){
	m_roleArray=new CCArray();
}

RoleCreateLayer::~RoleCreateLayer(){
	CC_SAFE_DELETE(m_roleArray);
	CCTextureCache::sharedTextureCache()->removeAllTextures();
}

bool RoleCreateLayer::init(){

	if(!CCLayer::init()){
		return false;
	}
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();

	CCLayerColor* layerColor=CCLayerColor::create(ccc4(140,150,180,255),winSize.width,winSize.height);
	this->addChild(layerColor,-1);

	UILayer* layer=UILayer::create();
	layer->setPosition(ccpSub(winSize,CCPoint(860,640))/2);
	layer->scheduleUpdate();
	this->addChild(layer);

	UILayout* widget=dynamic_cast<UILayout*>(GUIReader::shareReader()->widgetFromJsonFile("ui/role_create/role_create.json"));
	if(widget){
		layer->addWidget(widget);
	}
	m_textButton=dynamic_cast<UITextButton*>(layer->getWidgetByName("TextButton"));
	if(m_textButton){
		m_textButton->setColor(ccc3(127,127,127));
		m_textButton->addReleaseEvent(this,coco_releaseselector(RoleCreateLayer::sendMessage));
	}

	UIButton* button10 = dynamic_cast<UIButton*>(layer->getWidgetByName("Button_10"));
	if (button10)
	{
		button10->setTouchEnabled(true);
		button10->addReleaseEvent(this, coco_releaseselector(RoleCreateLayer::randomNickName));
	}

	UITextArea* textAreaTitle = dynamic_cast<UITextArea*>(layer->getWidgetByName("TextTitle"));
	if (textAreaTitle)
	{
		textAreaTitle->setText("傲来国");
	}

	m_textField = dynamic_cast<UITextField*>(layer->getWidgetByName("TextField"));
	if (m_textField)
	{
		m_textField->setFontName(font_UITextFieldTest);
		m_textField->setTouchEnable(true);
		m_textField->setTouchEnabled(true);
		 m_textField->setTouchSize(CCSize(200, 40));
		m_textField->addEventListenerTextField(this, textfieldeventselector(RoleCreateLayer::eventListenerTextField));
		m_textField->addAttachWithIMEEvent(this, coco_TextField_AttachWithIME_selector(RoleCreateLayer::attachWithIMEEvent));
		m_textField->addDetachWithIMEEvent(this, coco_TextField_DeleteBackward_selector(RoleCreateLayer::detachWithIMEEvent));
		m_textField->addInsertTextEvent(this, coco_TextField_DeleteBackward_selector(RoleCreateLayer::insertTextEvent));
		m_textField->addDeleteBackwardEvent(this, coco_TextField_DeleteBackward_selector(RoleCreateLayer::detachWithIMEEvent));
	}

	for (unsigned int i =0; i < 6; i++)
	{
		CCString* string = CCString::createWithFormat("FIGURE_%d",i);
		UIPanel* panel = dynamic_cast<UIPanel*>(layer->getWidgetByName(string->getCString()));
		if (panel)
		{
			CCControlButton* button = CCControlButton::create();
			button->setHighlighted(false);
			button->setPreferredSize(CCSize(120, 200));
			button->setPosition(ccpAdd(layer->getPosition(), panel->getPosition()));
			this->addChild(button);
			button->setTag(panel->getTag());
			button->addTargetWithActionForControlEvents(this, cccontrol_selector(RoleCreateLayer::setSelector), CCControlEventTouchDown);

			Figure* monomer = Figure::create(TexturePathFigure, panel->getTag());
			monomer->setHair(panel->getTag() / 10 - 100);
			monomer->setWeapon(1000);
			monomer->setPosition(button->getContentSize()/2);
			monomer->setColor(ccc3(127, 127, 127));
			button->addChild(monomer);
			m_roleArray->addObject(monomer);

			//CCCallFunc* finish = CCCallFunc::create(monomer, callfunc_selector(Monomer::stop));
			//CCCallFunc* finish2 = CCCallFunc::create(monomer->getWeaponSprite(), callfunc_selector(CCSprite::stopAllActions));
			//CCSequence* actions = CCSequence::create(CCDelayTime::create(0.15f), finish, finish2, NULL);
			//monomer->runAction(actions);
		}
	}
	return true;
}

void RoleCreateLayer::runActionsForFigure(CCObject *pSender){
	Figure* monomer=(Figure*)pSender;
	monomer->setFigureState(FStateAttack,FDirDown);

	CCDelayTime* delayTime=CCDelayTime::create(2.0f);
	CCCallFuncO* finish=CCCallFuncO::create(this,callfuncO_selector(RoleCreateLayer::runActionsForFigure),monomer);
	CCSequence* actions=CCSequence::create(delayTime,finish,NULL);
	monomer->runAction(actions);
}

void RoleCreateLayer::setSelector(CCObject* pSender,CCControlEvent controlEvent){
	CCControlButton* btn = dynamic_cast<CCControlButton*>(pSender);
	if (btn)
	{
		m_roleID = btn->getTag();
		if (m_selected)
		{
			Figure* monomer = (Figure*)m_selected;
			CCControlButton* button = (CCControlButton*)monomer->getParent();
			monomer->setFigureState(FStateStand, FDirDown);
			monomer->setColor(ccc3(127, 127, 127));
			CCScaleTo* scaleTo = CCScaleTo::create(0.15f, 1.0f);
		//r	CCCallFunc* finish = CCCallFunc::create(monomer, callfunc_selector(Monomer::stopAllActions));
			CCCallFunc* finish2 = CCCallFunc::create(monomer->getWeaponSprite(), callfunc_selector(CCSprite::stopAllActions));
			CCSequence* actions = CCSequence::create(scaleTo, finish2, NULL);
			monomer->runAction(actions);
			button->setTouchEnabled(true);
		}

		for (int i=0; i<m_roleArray->count(); i++)
		{
			Figure* monomer = (Figure*)m_roleArray->objectAtIndex(i);
			CCControlButton* button = (CCControlButton*)monomer->getParent();
			if (btn->isEqual(button))
			{
				button->setTouchEnabled(false);
				CCScaleTo* scaleTo = CCScaleTo::create(0.15, 1.2);
				monomer->runAction(scaleTo);
				monomer->setColor(ccWHITE);
				this->runActionsForFigure(monomer);
				m_selected = monomer;
			}
		}
	}

	if (m_textButton)
	{
		m_textButton->setColor(ccWHITE);
		m_textButton->setTouchEnable(true);
	}
}

void RoleCreateLayer::randomNickName(CCObject* pSender){
	if(m_textField){
		int num=CCRANDOM_0_1()*0xffffff;
		char str[20];
		sprintf(str,"随机%d",num);
		m_textField->setText(str);
	}
}

void RoleCreateLayer::sendMessage(CCObject* pSender){
	if (0 == strcmp(m_textField->getStringValue(), ""))
	{
		CCMessageBox("提示", "您还没有取名哦!");
		return;
	}
	GameSocket::sendRoleCreate(this, m_roleID, m_textField->getStringValue());//SOCKET
	//m_textField->setTouchEnable(false);
	//joinGame();
}

void RoleCreateLayer::eventListenerTextField(CCObject* pSender,TextFiledEventType type)
{

}

void RoleCreateLayer::attachWithIMEEvent(CCObject* pSender)
{

}

void RoleCreateLayer::detachWithIMEEvent(CCObject* pSender)
{

}


void RoleCreateLayer::insertTextEvent(CCObject* pSender)
{

}


void RoleCreateLayer::deleteBackwardEvent(CCObject* pSender)
{

}

void RoleCreateLayer::joinGame()
{
	GameLoading::runGameLoading(200, 1);
	this->removeFromParent();
}
