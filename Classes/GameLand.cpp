#include "GameLand.h"
#include "GameConfig.h"
#include "RoleCreateLayer.h"
CCScene* GameLand::scene(){
	CCScene* scene=CCScene::create();
	GameLand* layer=GameLand::create();
	//RoleCreateLayer* layer=RoleCreateLayer::create();
	scene->addChild(layer);
	return scene;
}

GameLand::GameLand():m_accountInputBox(NULL),m_cipherInputBox(NULL){

}

GameLand::~GameLand(){
	CCTextureCache::sharedTextureCache()->removeAllTextures();
}

bool GameLand::init(){
	if(!CCLayer::init()){
		return false;
	}
	CCSize winSize =CCDirector::sharedDirector()->getWinSize();

#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	this->setKeypadEnabled(true);
#endif

	CCLayerColor* layerColor=CCLayerColor::create(ccc4(200,200,200,200),winSize.width,winSize.height);
	this->addChild(layerColor);
	CCString account="ÇëÊäÈëÄãµÄÕÊºÅ";
	CCString cipher="ÇëÊäÈëÄãµÄÃÜÂë";
	//std::string account="ÇëÊäÈëÄãµÄÕÊºÅ";
	//std::string cipher="ÇëÊäÈëÄúµÄÃÜÂë";

	CCSize inputBoxSize=CCSize(360,50);

	m_accountInputBox=CCEditBox::create(inputBoxSize,CCScale9Sprite::create());
	m_accountInputBox = CCEditBox::create(inputBoxSize, CCScale9Sprite::create());
	m_accountInputBox->setPlaceHolder(account.getCString());
	m_accountInputBox->setPlaceholderFontColor(ccc3(0, 0, 0));
	m_accountInputBox->setInputMode(kEditBoxInputModeAny);
	m_accountInputBox->setMaxLength(12);
	m_accountInputBox->setReturnType(kKeyboardReturnTypeDone);
	m_accountInputBox->setPosition(ccpAdd(winSize/2, CCPoint(0, 100)));
	m_accountInputBox->setDelegate(this);
	this->addChild(m_accountInputBox);

	m_cipherInputBox = CCEditBox::create(inputBoxSize, CCScale9Sprite::create());
	m_cipherInputBox->setPlaceHolder(cipher.getCString());
	m_cipherInputBox->setPlaceholderFontColor(ccc3(0, 0, 0));
	m_cipherInputBox->setInputMode(kEditBoxInputModeAny);
	m_cipherInputBox->setInputFlag(kEditBoxInputFlagPassword);
	m_cipherInputBox->setMaxLength(12);
	m_cipherInputBox->setReturnType(kKeyboardReturnTypeDone);
	m_cipherInputBox->setPosition(ccpAdd(winSize/2, CCPoint(0, 30)));
	m_cipherInputBox->setDelegate(this);
	this->addChild(m_cipherInputBox);

	CCLayerColor* accountBg = CCLayerColor::create(ccc4(100, 100, 200, 200), inputBoxSize.width, inputBoxSize.height);
	accountBg->setPosition(ccpSub(m_accountInputBox->getPosition(), m_accountInputBox->getContentSize()/2));
	this->addChild(accountBg, -1);

	CCLayerColor* cipherBg = CCLayerColor::create(ccc4(100, 100, 200, 200), inputBoxSize.width, inputBoxSize.height);
	cipherBg->setPosition(ccpSub(m_cipherInputBox->getPosition(), m_cipherInputBox->getContentSize()/2));
	this->addChild(cipherBg, -1);

	CCControlButton* btnLand = CCControlButton::create("Login", MAIN_FONT_NAME, 50);
	btnLand->setPosition(ccpSub(winSize/2, CCPoint(80, 60)));
	this->addChild(btnLand);
	btnLand->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLand::sendLand), CCControlEventTouchUpInside);

	CCControlButton* btnReg = CCControlButton::create("register", MAIN_FONT_NAME, 50);
	btnReg->setPosition(ccpSub(winSize/2, CCPoint(-80, 60)));
	this->addChild(btnReg);
	btnReg->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLand::registration), CCControlEventTouchUpInside);

	return true;
}

void GameLand::sendLand(CCObject *sender, CCControlEvent controlEvent){
	joinGame();
}

void GameLand::joinGame(){
	RoleCreateLayer* layer = RoleCreateLayer::create();
	CCDirector::sharedDirector()->getRunningScene()->addChild(layer);
	this->removeFromParent();
}


void GameLand::registration(CCObject *sender, CCControlEvent controlEvent)
{
	for (int i=0; i<8; i++)
	{
		float angle = i * 45 * M_PI / 180;
		CCLog("xxxxx:%d, %f, %f",i, cosf(angle), sinf(angle));
	}

}

#pragma mark -
#pragma mark inputBoxDelegate

void GameLand::editBoxReturn(CCEditBox* editBox)
{

}

#pragma mark -
#pragma mark androidKeyMenu

void GameLand::keyBackClicked()
{

}

void GameLand::keyMenuClicked()
{

}