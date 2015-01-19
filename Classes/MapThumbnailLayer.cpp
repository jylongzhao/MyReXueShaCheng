#include "MapThumbnailLayer.h"
#include "GameScene.h"
const CCPoint centerPoint=CCPoint(72.5,93);
const int lenght=60;
const int scale=1000;

static CCSprite* createIndicator(unsigned int size)
{
	//int pixels[size][size];
	//int *a=new int[size][size];
	int **pW=new int*[size];
	for (int i=0;i<size;i++)
	{
		pW[i]=new int[size];
	}
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			pW[i][j] = 0xffffffff;
		}
	}

	CCTexture2D* texture=new CCTexture2D();
	texture->initWithData(pW, kCCTexture2DPixelFormat_RGB888, 1, 1,
		CCSize(size, size));
	for (int i=0;i<size;i++)
	{
		delete pW[i];
	}
	delete pW;
	CCSprite* sprite=CCSprite::createWithTexture(texture);
	texture->release();
	return sprite;
}

MapThumbnailMenu::MapThumbnailMenu(){
	m_enemyDic=new CCDictionary();
}

MapThumbnailMenu::~MapThumbnailMenu(){
	CC_SAFE_DELETE(m_enemyDic);
}

MapThumbnailMenu* MapThumbnailMenu::create()
{
	MapThumbnailMenu* sprite = new MapThumbnailMenu();
	if (sprite && sprite->initWithFile("ui/mapThumbnail.png"))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

void MapThumbnailMenu::onEnter(){
	CCSprite::onEnter();
	CCTouchDispatcher* touchDispathcer=CCDirector::sharedDirector()->getTouchDispatcher();
	touchDispathcer->addTargetedDelegate(this,0,true);
	this->schedule(schedule_selector(MapThumbnailMenu::update),0.04);
}

void MapThumbnailMenu::onExit(){
	CCSprite::onExit();
	CCTouchDispatcher* touchDispatcher=CCDirector::sharedDirector()->getTouchDispatcher();
	touchDispatcher->removeDelegate(this);
}

bool MapThumbnailMenu::initWithFile(const char *pszFilename){
	if(!CCSprite::initWithFile(pszFilename)){
		return false;
	}

	CCSprite* bg=CCSprite::create("ui/bg_mapThumbnail.png");
	bg->setAnchorPoint(CCPointZero);
	this->addChild(bg,-2);

	m_playerIndicator=createIndicator(4);
	m_playerIndicator->setPosition(centerPoint);
	this->addChild(m_playerIndicator,-1);

	m_pCoordinateTTF = CCLabelTTF::create("", "Helvetica-Bold", 12);
	m_pCoordinateTTF->setPosition(CCPoint(centerPoint.x, 17));
	this->addChild(m_pCoordinateTTF);

	return true;
}

void MapThumbnailMenu::update(float delta){
	CCArray* enemyKeys=GAME_SCENE->getEnemyDictionary()->allKeys();
	if(enemyKeys==NULL){
		return;
	}

	for (vector<int>::iterator itr = keyVec.begin(); itr!=keyVec.end(); itr++)
	{
		Enemy* enemy = (Enemy*)GAME_SCENE->getEnemyDictionary()->objectForKey(*itr);

		if (!enemy)
		{
			CCSprite* enemyIndicator = (CCSprite*)m_enemyDic->objectForKey(*itr);
			m_enemyDic->removeObjectForKey(*itr);
			enemyIndicator->removeFromParent();
			continue;
		}
		unsigned int distance = ccpDistance(Player::sharePlayer()->getPosition(), enemy->getPosition());
		if (distance > scale)
		{
			CCSprite* enemyIndicator = (CCSprite*)m_enemyDic->objectForKey(*itr);
			m_enemyDic->removeObjectForKey(*itr);
			enemyIndicator->removeFromParent();
		}

	}
	keyVec.clear();
	for (unsigned int i=0; i<enemyKeys->count(); i++)
	{
		int key = ((CCInteger*)enemyKeys->objectAtIndex(i))->getValue();
		Enemy* enemy = (Enemy*)GAME_SCENE->getEnemyDictionary()->objectForKey(key);
		unsigned int distance = ccpDistance(Player::sharePlayer()->getPosition(), enemy->getPosition());
		if (distance <= scale)
		{
			keyVec.push_back(key);
			int distanceX = enemy->getPositionX() - Player::sharePlayer()->getPositionX();
			int distanceY = enemy->getPositionY() - Player::sharePlayer()->getPositionY();
			float x = lenght * distanceX/(float)scale + centerPoint.x;
			float y = lenght * distanceY/(float)scale + centerPoint.y;
			CCSprite* enemyIndicator = (CCSprite*)m_enemyDic->objectForKey(key);
			if (enemyIndicator == NULL)
			{
				enemyIndicator = createIndicator(2);
				enemyIndicator->setColor(ccRED);
				this->addChild(enemyIndicator, -1);
				m_enemyDic->setObject(enemyIndicator, key);
			}
			enemyIndicator->setPosition(CCPoint(x, y));
		}
	}
	CCPoint point = Player::sharePlayer()->getPosition()/10;
	char str[32];
	sprintf(str, "X:%03d     Y:%03d", (int)point.x, (int)point.y);
	m_pCoordinateTTF->setString(str);
}

bool MapThumbnailMenu::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
	CCPoint point=pTouch->getLocation();
	point=this->convertToNodeSpace(point);

	if(ccpDistance(point,centerPoint)<=lenght){
		return true;
	}
	return false;
}

void MapThumbnailMenu::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}

void MapThumbnailMenu::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if (GAME_SCENE->getGameInfoUIController()->getChildByTag(0xff00f))
	{
		return;
	}
	MapThumbnailLayer* map = MapThumbnailLayer::create();
	GAME_SCENE->getGameInfoUIController()->addChild(map, 0 , 0xff00f);
}

void MapThumbnailMenu::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){

}

bool MapThumbnailLayer::init(){
	if(!CCLayer::init()){
		return false;
	}

	CCSize winSize=CCDirector::sharedDirector()->getWinSize();

	CCSprite* bg=CCSprite::create("ui/bg_map_layer.png");
	bg->setPosition(winSize/2);
	this->addChild(bg);

	m_nMap=MapThumbnailScrollView::create();
	m_nMap->setPosition(CCPoint(43,43));
	bg->addChild(m_nMap);

	CCControlButton* button=CCControlButton::create(CCScale9Sprite::create("ui/closed_normal.png"));
	button->setBackgroundSpriteForState(CCScale9Sprite::create("ui/close_selected.png"),CCControlStateHighlighted);
	button->setPreferredSize(CCSize(57,58));
	button->setPosition(ccpSub(ccpAdd(bg->getPosition(),bg->getContentSize()/2),button->getContentSize()/2));
	this->addChild(button);
	button->addTargetWithActionForControlEvents(this, cccontrol_selector(MapThumbnailLayer::removeFromParent), CCControlEventTouchUpInside);
	button->setTouchPriority(0);

	this->setTouchEnabled(true);
	return true;
}


void MapThumbnailLayer::registerWithTouchDispatcher(void)
{
	CCTouchDispatcher* touchDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	touchDispatcher->addTargetedDelegate(this, 0, true);
}

bool MapThumbnailLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{

	return true;
}

MapThumbnailScrollView::MapThumbnailScrollView()
	:m_bIsMoved(false)
	,m_beginPoint(CCPointZero)
{

}

MapThumbnailScrollView::~MapThumbnailScrollView()
{

}

MapThumbnailScrollView* MapThumbnailScrollView::create()
{
	MapThumbnailScrollView* scrollView = new MapThumbnailScrollView();
	if (scrollView && scrollView->initWithViewSize(CCSize(600, 480)))
	{
		scrollView->initWithMap();
		scrollView->autorelease();
		return scrollView;
	}
	CC_SAFE_DELETE(scrollView);
	return NULL;
}


void MapThumbnailScrollView::initWithMap()
{
	this->setAnchorPoint(CCPointZero);
	this->setBounceable(false);

	CCTexture2D* texture = GAME_SCENE->getCurrBgMap()->getSmallMap()->getTexture();
	CCSprite* sprite = CCSprite::createWithTexture(texture);
	sprite->setAnchorPoint(CCPointZero);
	sprite->setPosition(CCPointZero);
	this->addChild(sprite);
	this->setContentSize(sprite->getContentSize());

	m_pEndPoint = createIndicator(8);
	m_pEndPoint->setColor(ccYELLOW);
	m_pContainer->addChild(m_pEndPoint);
	m_pEndPoint->setPosition(CCPoint(-100, -100));

	CCBlink* blink = CCBlink::create(0.5f, 1);
	CCRepeatForever* repeatForever = CCRepeatForever::create(blink);
	m_pEndPoint->runAction(repeatForever);

	m_playerIndicator = CCSprite::create("ui/self_indicator.png");
	m_pContainer->addChild(m_playerIndicator);

	float x = Player::sharePlayer()->getPositionX() * m_pContainer->getContentSize().width / GAME_SCENE->getCurrBgMap()->getBgSize().width;
	float y = Player::sharePlayer()->getPositionY() * m_pContainer->getContentSize().height / GAME_SCENE->getCurrBgMap()->getBgSize().height;
	x -= this->getViewSize().width / 2;
	y -= this->getViewSize().height / 2;
	x = MIN(x, this->getContentSize().width - this->getViewSize().width);
	x = MAX(x, 0);
	y = MIN(y, this->getContentSize().height - this->getViewSize().height);
	y = MAX(y, 0);
	m_pContainer->setPosition(CCPoint(-x, -y));

	this->scheduleUpdate();
}

void MapThumbnailScrollView::update(float delay)
{
	float x = Player::sharePlayer()->getPositionX() * m_pContainer->getContentSize().width / GAME_SCENE->getCurrBgMap()->getBgSize().width;
	float y = Player::sharePlayer()->getPositionY() * m_pContainer->getContentSize().height / GAME_SCENE->getCurrBgMap()->getBgSize().height;
	m_playerIndicator->setPosition(CCPoint(x, y));
}

bool MapThumbnailScrollView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){

	m_beginPoint = pTouch->getLocation();
	return CCScrollView::ccTouchBegan(pTouch, pEvent);
}


void MapThumbnailScrollView::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
	CCScrollView::ccTouchMoved(pTouch, pEvent);

	if (ccpDistance(m_beginPoint, pTouch->getLocation()) < 5)
	{
		m_bIsMoved = true;
	}
}

void MapThumbnailScrollView::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){

	CCScrollView::ccTouchEnded(pTouch, pEvent);

	do
	{
		if (m_bIsMoved)
		{
			m_bIsMoved = false;
			break;
		}

		CCPoint point = pTouch->getLocation();
		point=m_pContainer->convertToNodeSpace(point);
		m_pEndPoint->setPosition(point);
		float x = point.x * GAME_SCENE->getCurrBgMap()->getBgSize().width / m_pContainer->getContentSize().width;
		float y = point.y * GAME_SCENE->getCurrBgMap()->getBgSize().height / m_pContainer->getContentSize().height;

		Player::sharePlayer()->goTo(MapPoint(CCPoint(x, y)));

	}
	while (0);
}