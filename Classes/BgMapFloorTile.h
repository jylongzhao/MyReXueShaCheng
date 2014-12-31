#ifndef _BgMapFloorTile_H_
#define _BgMapFloorTile_H_
#include "cocos2d.h"
#define OFF_SIZE CCPoint(128, 128)

USING_NS_CC;
class BgMapFloorTile:public CCNode
{
public:
	BgMapFloorTile();
	virtual ~BgMapFloorTile();
	CREATE_FUNC(BgMapFloorTile);
	CC_SYNTHESIZE_RETAIN(CCString*,m_fileName,FloorTileFileName);
	void IntelligentDisplay(CCRect& showRect,CCRect& hideRect);
protected:
	bool m_nIsDisplay;
	CCSprite* m_sprite;
	void displayImageView();

	void hideImageView();

	void initWithImageView(CCTexture2D* texture);
private:
};
#endif