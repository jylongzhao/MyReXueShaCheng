//
//  ProgressAutomatic.cpp
//  mir9
//
//  出自九秒社区 http://www.9miao.com
//  Created by 栗元峰 on 14-2-8.
//
//

#include "ProgressAutomatic.h"

ProgressAutomatic* ProgressAutomatic::create(CCSprite* sp)
{
	ProgressAutomatic *pProgressTimer = new ProgressAutomatic();
	if (pProgressTimer->initWithSprite(sp))
	{
		CCSprite* sprite = CCSprite::createWithTexture(sp->getTexture());
		sprite->setColor(ccc3(100, 100, 100));
		sprite->setPosition(pProgressTimer->getContentSize()/2);
		pProgressTimer->addChild(sprite, -1);
		pProgressTimer->autorelease();
	}
	else
	{
		delete pProgressTimer;
		pProgressTimer = NULL;
	}

	return pProgressTimer;
}

void ProgressAutomatic::RunCoolingAction(float delay)
{
	if (this->getPercentage() < 100.0f)
		return;

	this->setPercentage(0);
	m_fInterval = 100 / (delay * 60);
	this->unschedule(schedule_selector(ProgressAutomatic::updateCoolingAction));
	this->schedule(schedule_selector(ProgressAutomatic::updateCoolingAction));
}

void ProgressAutomatic::updateCoolingAction(float dt)
{
	float percentage = m_fPercentage + m_fInterval;
	this->setPercentage(percentage);
	if (percentage >= 100.0f)
		this->unschedule(schedule_selector(ProgressAutomatic::updateCoolingAction));
}

void ProgressAutomatic::RunCoolingNotAction(float delay)
{
	if (this->getPercentage() < 100.0f)
		return;

	this->setPercentage(0);

	CCDelayTime* delayTime = CCDelayTime::create(delay);
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(ProgressAutomatic::setCoolingFalse));
	CCSequence* actions = CCSequence::create(delayTime, callFunc, NULL);
	this->runAction(actions);
}

void ProgressAutomatic::setCoolingFalse()
{
	this->setPercentage(100);
}