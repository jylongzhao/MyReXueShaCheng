#include "BgMapFloorTile.h"

BgMapFloorTile::BgMapFloorTile():m_fileName(NULL),m_sprite(NULL),m_nIsDisplay(false){

}

BgMapFloorTile::~BgMapFloorTile(){
	CC_SAFE_DELETE(m_fileName);
}

void BgMapFloorTile::displayImageView(){
	if(m_nIsDisplay==false){
		m_nIsDisplay=true;
		 CCTextureCache::sharedTextureCache()->addImageAsync(m_fileName->getCString(), this, callfuncO_selector(BgMapFloorTile::initWithImageView));
	}
}

void BgMapFloorTile::hideImageView()
{
	if (m_nIsDisplay)
	{
		m_nIsDisplay = false;
		if (m_sprite)
		{
			m_sprite->removeFromParent();
			m_sprite = NULL;
		}
		CCTextureCache::sharedTextureCache()->removeTextureForKey(m_fileName->getCString());
	}
}

void BgMapFloorTile::initWithImageView(CCTexture2D* texture)
{
	if (m_sprite == NULL)
	{
		m_sprite = CCSprite::createWithTexture(texture);
		m_sprite->setAnchorPoint(CCPointZero);
		this->addChild(m_sprite);
	}
}

void BgMapFloorTile::IntelligentDisplay(CCRect& showRect, CCRect& hideRect)
{
	CCPoint point = ccpAdd(this->getPosition(), OFF_SIZE);

	if (showRect.containsPoint(point))
	{
		this->displayImageView();
	}

	if (!hideRect.containsPoint(point))
	{
		this->hideImageView();
	}

}