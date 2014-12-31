//
//  LMenu.h
//
//  Created by LI YUANFENG on 13-3-14.
//
//

#ifndef __LMenu__
#define __LMenu__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;
using namespace extension;
class LMenu;

typedef enum {
    TouchBegin = 0,
    TouchMoved = 1,
    TouchMovedOutSide = 2,
    TouchUpInSide = 3,
    TouchUpSide = 4,
}LMenuType;

typedef enum {
    LMenuStateNormal = 0,
    LMenuStateHighlighted = 1,
    LMenuStateDisabled = 2,
    LMenuStateSelected = 3
}LMenuTouchState;

typedef bool (CCObject::*SEL_LMenu)(LMenu*, CCPoint);
#define LMenu_selector(_SELECTOR) (SEL_LMenu)(&_SELECTOR)

class LMenu: public CCSprite, public CCTargetedTouchDelegate{
    
public:
    
    LMenu(void);
    
    virtual ~LMenu(void);
    
    /**
     *  ��ť�ޱ��� ���ð�ť������
     */
    
    static LMenu* create(const CCSize &size);
    
    /**
     *  ��ť���� �κλ���CCRGBAProtocol
     */
    
    static LMenu* createWithRGBAProtocol(CCRGBAProtocol* backGround);
    
    /**
     *  ��ť���� CCSprite
     */
    
    static LMenu* createWithSprite(CCSprite* backGround);
    
    /**
     *  ��ť���� CCScale9Sprite
     */
    
    static LMenu* createWithScale9Sprite(CCScale9Sprite* backGround);
    
    /**
     *  ��ť���� CCLayerColor
     */
    
    static LMenu* createWithLayerColor(CCLayerColor* backGround);
    
public:

    /**
     *  ��ť���� CCNode
     *
     *  @param ���� �κλ���CCNode
     *  @param ���� CCSprite��CCScale9Sprite��CCLayerColor��
     */
    
    bool initWithBackGround(CCRGBAProtocol* backGround);
    
    /**
     *  ��ť���� CCSprite
     */
    
    bool initWithSpriteBackGround(CCSprite* backGround);
    
    /**
     *  ��ť���� CCScale9Sprite
     */
    
    bool initWithScale9SpriteBackGround(CCScale9Sprite* backGround);
    
    /**
     *  ��ť���� CCLayerColor
     */
    
    bool initWithLayerColorBackGround(CCLayerColor* backGround);
    
    /**
     *  ��ť�ڸ���״̬���� CCNode
     *
     *  @param ���� �κλ���CCNode
     *  @param ���� CCSprite��CCScale9Sprite��CCLayerColor��
     */
    
    bool setBackGround(LMenuTouchState touchState, CCRGBAProtocol *var);

    /**
     *  ��ť�ڸ���״̬���� CCSprite
     */
    
    bool setSpriteBackGround(LMenuTouchState touchState, CCSprite *var);
    
    /**
     *  ��ť�ڸ���״̬���� CCScale9Sprite
     */
    
    bool setScale9SpriteBackGround(LMenuTouchState touchState, CCScale9Sprite *var);
    
    /**
     *  ��ť�ڸ���״̬���� CCLayerColor
     */
    
    bool setLayerColorBackGround(LMenuTouchState touchState, CCLayerColor *var);
    
    /**
     *  ��ȡ��ť����
     */
    
    CCNode* getBackGround(LMenuTouchState touchState);
    
    /**
     *  ��ť�ϲ� Sprite
     *
     *  @param ���� �κλ���CCNodeRGBA
     *  @param ���� CCSprite��CCScale9Sprite
     *  @param Ĭ������ ����
     */
    
    void setSprite(LMenuTouchState touchState, CCNodeRGBA* var);
    
    /**
     *  ��ť�ϲ� Sprite
     *
     *  @param ���� �κλ���CCNodeRGBA
     *  @param ���� CCSprite��CCScale9Sprite
     *  @param �������꣬����״̬������ֱ�����
     */
    
    void setSprite(LMenuTouchState touchState, CCNodeRGBA* var, CCPoint point);
    
    /**
     *  ��ȡ��ť�ϲ� Sprite
     */
    
    CCNodeRGBA* getSprite(LMenuTouchState touchState);
    
public:
    
    /**
     *  ��ť���ֵ��int��
     */
    
    CC_SYNTHESIZE(int, m_sign, Sign);
    
    /**
     *  ��ť���ֵ���ַ�����
     */
    
    CC_SYNTHESIZE(std::string, m_textTag, TextTag);
    
    /**
     *  ��ť�����Ч�����뿪��״̬��ȡ��bool
     */
    
    CC_SYNTHESIZE(bool, m_specially, TouchSpecially);
    
    /**
     *  ��ť�����Ч�����뿪��״̬��ȡ��bool
     */
    
    CC_SYNTHESIZE(bool, m_closeTapSound, CloseTapSound);
    
    /**
     *  ��ťѡ��״̬�����뿪��״̬��ȡ��bool
     */
    
    CC_SYNTHESIZE(bool, m_stateSelected, StateSelected);
    
    /**
     *  ��ť�����¼������뿪��״̬��ȡ��bool
     */
    
    CC_PROPERTY(bool, m_bIsTouchEnabled, TouchEnabled);
    
    /**
     *  ��ť����״̬�����뿪��״̬��ȡ��bool
     */
    
    CC_PROPERTY(bool, m_touchClick, TouchClick);
    
    /**
     *  ��ť״̬�����뿪��״̬��ȡ��enum
     */
    
    CC_PROPERTY(LMenuTouchState, m_touchState, TouchState);//��ť״̬

    /**
     *  ��ť��С�������ȡ��CCSize
     */
    
    CC_PROPERTY(CCSize, m_preferredSize, PreferredSize);//�������ź��С
    
    /**
     *  ��ȡ��ť״̬����ͨ
     */
    
    bool isNormal();
    
    /**
     *  ��ȡ��ť״̬������
     */
    
    bool isHighlighted();
    
    /**
     *  ��ȡ��ť״̬��ѡ��
     */
    
    bool isSelected();
    
    /**
     *  ��ȡ��ť״̬�����ɵ��
     */
    
    bool isDisabled();

    /**
     *  �жϰ�ť�ַ�������Ƿ��������ַ�����ͬ
     */
    
    bool isTextTagEqual(const char* text);
    
    /**
     *  ��ť���ӳ��ķ������ã�ö�����ָ��ִ���״̬
     */
    
    void addTarget(void* target, SEL_LMenu selector, LMenuType type);
    
    /**
     *  ��ť�����¼�����봥�����ȼ��޸�
     */
    
    void setTouchDispatcher(bool bSwallowsTouches, int nPriority=kCCMenuHandlerPriority);
    
    /**
     *  ��ť͸��������
     */
    
    void setOpacity(GLubyte opacity);
    
    /**
     *  ��ťɫֵ����
     */
    
    void setColor(const ccColor3B &color3);
    
    /**
     *  ��ťɫֵ��ȡ
     */
    
    ccColor3B& getColor();
    
protected:
    
    virtual void onExit();
    
    virtual void onEnter();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void setNormalEffect();
    
    virtual void setHighlightedEffect();
    
    virtual void setDisabledEffect();
    
    virtual void setSelectedEffect();
    
    virtual void setNormalColor();
    
    virtual void setHighlightedColor();

    virtual void setDisabledColor();

    virtual void setSelectedColor();
    
protected:
    
    bool m_nbSwallowsTouches;
    
    int m_nTouchPriority;
    
    ccColor3B m_color;
    
    CCNode* m_bgNormal;
    
    CCNode* m_bgHighlighted;
    
    CCNode* m_bgDisabled;
    
    CCNode* m_bgSelected;
    
    CCNodeRGBA* m_spriteNormal;
    
    CCNodeRGBA* m_spriteHighlighted;
    
    CCNodeRGBA* m_spriteDisabled;
    
    CCNodeRGBA* m_spriteSelected;
    
    CCPoint m_spriteNPoint;
    
    CCPoint m_spriteHPoint;

    CCPoint m_spriteDPoint;
    
    CCPoint m_spriteSPoint;

private:
    
    void updateWithPreferredSize();
    
    void updateWithPoint();
    
    void setTouchMoved(CCPoint point);
    
    void setTouchMovedOutSide(CCPoint point);
    
    void setTouchUpSide(CCPoint point);
    
    void setTouchUpInSide(CCPoint point);
    
    bool setTouchBegin(CCPoint point);
    
    void registerWithTouchDispatcher(void);
    
    void unRegisterWithTouchDispatcher(void);
    
    bool m_IsRehisterTouchDispatcher;
    
    CCRect getRect();
    
private:
    
    void* m_target;
    
    SEL_LMenu m_touchBegin;
    
    SEL_LMenu m_touchMoved;
    
    SEL_LMenu m_touchMovedOutSide;
    
    SEL_LMenu m_touchUpInSide;
    
    SEL_LMenu m_touchUpSide;
    
};

#endif /* defined(__LMenu__) */
