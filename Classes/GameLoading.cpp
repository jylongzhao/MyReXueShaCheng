#include "GameLoading.h"
#include "GameScene.h"
GameLoading* _gameLoading = NULL;

GameLoading::GameLoading(const int mapID,const int born):m_mapID(mapID),m_born(born){

}

GameLoading::~GameLoading(){
	_gameLoading=NULL;
}

void GameLoading::onEnter(){
	CCSprite::onEnter();
	CCTouchDispatcher* touchDispatchar=CCDirector::sharedDirector()->getTouchDispatcher();
	touchDispatchar->addTargetedDelegate(this,kCCMenuHandlerPriority-999,true);

	if(GAME_SCENE==NULL){
		this->scheduleOnce(schedule_selector(GameLoading::initGameScene),0.5f);
	}
	this->scheduleOnce(schedule_selector(GameLoading::updateBgMap),1.0f);
}

void GameLoading::onExit(){
	CCSprite::onExit();
	CCTouchDispatcher* touchDispatcher=CCDirector::sharedDirector()->getTouchDispatcher();
	touchDispatcher->removeDelegate(this);
}

GameLoading* GameLoading::runGameLoading(int mapID,const int born){
	if(_gameLoading==NULL){
		_gameLoading=new GameLoading(mapID,born);
		_gameLoading->init();
		CCDirector::sharedDirector()->getRunningScene()->addChild(_gameLoading,100);
		_gameLoading->release();
	}
	return _gameLoading;
}

bool GameLoading::init(){
	if(!CCSprite::init()){
		return false;
	}
	this->setAnchorPoint(CCPointZero);
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();

	m_sprite=CCSprite::create("map/loading.jpg");
	m_sprite->setPosition(winSize/2);
	this->addChild(m_sprite,-1);

	CCLabelTTF* ttf=CCLabelTTF::create("Мгдижа.......","Arial",30);
	ttf->setPosition(CCPoint(winSize.width-70,20));
	this->addChild(ttf);

	if (GAME_SCENE && GAME_SCENE->getCurrBgMap())
	{
		this->setOpacity(0);
		CCFadeIn* fadeIn = CCFadeIn::create(0.5f);
		this->runAction(fadeIn);
	}

	return true;
}

void GameLoading::initGameScene(float delay /* = 0 */){
	CCDirector::sharedDirector()->getRunningScene()->addChild(GameScene::create());
}

void GameLoading::updateBgMap(float delay /* = 0 */){
	CCTextureCache::sharedTextureCache()->removeUnusedTextures();
	GAME_SCENE->replaceBgMap(m_mapID, m_born);
	this->updateFinish();
}

void GameLoading::updateFinish()
{
	CCFadeOut* fadeOut = CCFadeOut::create(0.3f);
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(GameLoading::removeFromParent));
	CCSequence* actions = CCSequence::create(fadeOut, callFunc, NULL);
	this->runAction(actions);
}

bool GameLoading::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{

	return true;
}

void GameLoading::setOpacity(GLubyte opacity)
{
	//    if (this->getChildren())
	//    {
	//        for (int i=0; i<this->getChildren()->count(); i++)
	//        {
	//            CCNode* node=(CCNode*)this->getChildren()->objectAtIndex(i);
	//            
	//            if (CCRGBAProtocol* _children=dynamic_cast<CCRGBAProtocol*>(node))
	//            {
	//                _children->setOpacity(opacity);
	//            }
	//        }
	//    }
}