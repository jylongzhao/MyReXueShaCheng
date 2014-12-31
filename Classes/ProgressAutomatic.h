//
//  ProgressAutomatic.h
//  mir9
//
//  Created by ÀõÔª·å on 14-2-8.
//
//

#ifndef __mir9__ProgressAutomatic__
#define __mir9__ProgressAutomatic__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class ProgressAutomatic: public CCProgressTimer {

	float m_fInterval;

protected:

	void updateCoolingAction(float dt);

	void setCoolingFalse();

public:

	static ProgressAutomatic* create(CCSprite* sp);

	void RunCoolingAction(float delay);

	void RunCoolingNotAction(float delay);
};

#endif /* defined(__mir9__ProgressAutomatic__) */
