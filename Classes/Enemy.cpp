#include "Enemy.h"
#include "GameScene.h"
#include "GameSocket.h"
//#include "FlutteringFairy.h"
#include "SimpleAudioEngine.h"


Enemy::Enemy()
	:m_enemyID(0)
	,m_denPos(CCPointZero)
	,m_isActive(true)
{

}

Enemy::~Enemy()
{

}

void Enemy::onEnterTransitionDidFinish()
{
	Monomer::onEnterTransitionDidFinish();
	MapPoint position = MapPoint(m_obPosition);
	GAME_SCENE->insterMapPoint(this, position);
}

void Enemy::onExitTransitionDidStart()
{
	Monomer::onExitTransitionDidStart();
	MapPoint position = MapPoint(m_obPosition);
}

Enemy* Enemy::create(int enemyID, unsigned int roleNumber, unsigned int weaponNumber)
{
	Enemy* enemy = new Enemy();
	if (enemy && enemy->initWithEnemy(roleNumber, weaponNumber))
	{
		enemy->m_enemyID = enemyID;
		enemy->autorelease();
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;
}

bool Enemy::initWithEnemy(unsigned int roleNumber, unsigned int weaponNumber)
{
	if (!Monomer::init())
		return false;

	m_fReactionInterval = 1.0f;

	this->setVisualRange(10);

	this->setFigure(TexturePathMonster, roleNumber);

	this->setWeapon(weaponNumber);

	return true;
}

void Enemy::showFigure()
{
	if (!GAME_SCENE->getCurrBgMap()->getShowRect().containsPoint(m_obPosition))
		return;

	Monomer::showFigure();
}

void Enemy::hideFigure()
{
	if (GAME_SCENE->getCurrBgMap()->getHideRect().containsPoint(m_obPosition))
		return;

	Monomer::hideFigure();
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->stopEffect(m_currEffectID);
}

MoveInfo Enemy::runBy(MapPoint point)
{
	MapPoint position = MapPoint(m_obPosition);

	MoveInfo relust = Monomer::runBy(point);

	if (relust.time != 0)
	{
		GAME_SCENE->insterMapPoint(this, relust.point);
	}

	return relust;
}

MoveInfo Enemy::walkBy(MapPoint point)
{
	MapPoint position = MapPoint(m_obPosition);

	MoveInfo relust = Monomer::walkBy(point);

	if (relust.time != 0)
	{
		GAME_SCENE->insterMapPoint(this, relust.point);
	}

	return relust;
}

MoveInfo Enemy::goTo(MapPoint point)
{
	MapPoint position = MapPoint(m_obPosition);
	GAME_SCENE->insterMapPoint(this, point);

	return Monomer::goTo(point);
}

void Enemy::detectionOfEachOther()
{
	Monomer::detectionOfEachOther();
	this->detectionWhetherCounter();
}

void Enemy::detectionWhetherCounter()
{
	if (m_attackMonomerMajor == NULL)
	{
		this->setAttackMonomerMajor(this->getAgainstMeOfFirst());
	}

	if (m_attackMonomerMajor == NULL)
	{
		this->patrol();
	}
	else
	{
		//this->followAttackAndSetAttackMethods(m_attackMonomerMajor, m_attackSkillInfo->getSkillNumber());
	}
}

void Enemy::followAttack()
{
	this->unschedule(schedule_selector(Enemy::patrol));

	Monomer::followAttack();
}

void Enemy::followTheTracks()
{
	//do
	//{
	//	MapPoint point = m_attackMonomerMajor->ownAttackPoint(this, m_attackSkillInfo->getAttackDistance());
	//	CC_BREAK_IF(point.equals(CCPointZero));
	//	point = mapSub(point, MapPoint(m_obPosition));
	//	MoveInfo relust = this->walkBy(point);
	//	float time = m_fReactionInterval + relust.time;
	//	this->delayCallBack(time, callfunc_selector(Enemy::followAttack))->setTag(TAG_FOLLOWATTACK);
	//}
	//while (0);
}

void Enemy::beyondVisualRange()
{
	m_attackMonomerMajor->removeAgainstMe(this);
	this->patrol();

	Monomer::beyondVisualRange();
}

void Enemy::patrol(float delay)
{
	if (m_isCanMoved == false)
		return;

	int symbol = (int)(2 * CCRANDOM_0_1());
	int arcX = (int)(10 * CCRANDOM_0_1());
	int arcY = (int)(10 * CCRANDOM_0_1());
	MapPoint point = MapPoint(m_denPos.x+arcX*symbol, m_denPos.z+arcY*symbol);
	MapPoint dirt = mapSub(point, MapPoint(m_obPosition));
	this->walkBy(dirt);

	int time = (int)(180 * CCRANDOM_0_1()) + 1;

	this->scheduleOnce(schedule_selector(Enemy::patrol), time);
}

void Enemy::moveByEnd()
{
	Monomer::moveByEnd();
}

void Enemy::death()
{
	if (getStateType() == FStateDeath)
		return;

	Monomer::death();

	CCDelayTime* delayTime1 = CCDelayTime::create(0.3);
	CCDelayTime* delayTime2 = CCDelayTime::create(0.3);
	CCDelayTime* delayTime3 = CCDelayTime::create(6);
	CCFadeOut* fadeOut = CCFadeOut::create(0.1f);
	CCCallFunc* callFunc1 = CCCallFunc::create(this, callfunc_selector(Enemy::addExp));
	CCCallFunc* callFunc2 = CCCallFunc::create(this, callfunc_selector(Enemy::removeThis));
	CCCallFunc* callFunc3 = CCCallFunc::create(this, callfunc_selector(Enemy::removeFromParent));
	CCSequence* actions = CCSequence::create(delayTime1, callFunc1, delayTime2, callFunc2, delayTime3, fadeOut, callFunc3, NULL);
	m_nMonomer->runAction(actions);
}

void Enemy::addAgainstMe(Monomer* var, float blood)
{
	Monomer::addAgainstMe(var, blood);
	this->hurt();
}

void Enemy::addExp()
{
	//FlutteringFairy* fairy = FlutteringFairy::addFairy(this, CCPoint(0, this->getContentSize().height*0.6), TypeAddExp, CCRANDOM_0_1()*20+990, this, callfunc_selector(Enemy::flutteringFairyFinish));
	//this->pushFlutteringFairy(fairy);
}

void Enemy::removeThis()
{
	MapPoint position = MapPoint(m_obPosition);
	GAME_SCENE->removeEnemy(this);
	if (bloodBg)
	{
		bloodBg->removeFromParent();
		bloodBg = NULL;
	}
}

unsigned int Enemy::getRoleNumber()
{
	return m_currRoleNumber;
}

void Enemy::attacking()
{
	Monomer::attacking();
	//    switch (m_stateType)
	//    {
	//        case FStateAttack:
	//        {
	//            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/default/800502.wav");
	//        }
	//            break;
	//        case FStateCaster:
	//        {
	//            
	//        }
	//            break;
	//        default:
	//            break;
	//    }

}

void Enemy::underAttack()
{
	Monomer::underAttack();

	do
	{
		CC_BREAK_IF(m_stateType == FStateDeath);
		CC_BREAK_IF(m_attackMonomerMajor);
		this->detectionWhetherCounter();
	}
	while (0);
}

void Enemy::setFigureState(FigureStateType stateType, FigureDirectionType directionType)
{
	Monomer::setFigureState(stateType, directionType);

	if (m_nMonomer == NULL)
		return;

	//    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopEffect(m_currEffectID);
	//    
	//    switch (stateType)
	//    {
	//        case FStateStand:
	//        {
	//            
	//        }
	//            break;
	//        case FStateWalk:
	//        {
	//            m_currEffectID = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/default/800701.wav", true);
	//        }
	//            break;
	//        case FStateRun:
	//        {
	//            m_currEffectID = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/default/800701.wav", true);
	//        }
	//            break;
	//        case FStateDeath:
	//        {
	//            m_currEffectID = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/default/800513.wav", false);
	//        }
	//            break;
	//        default:
	//            break;
	//    }
}