#ifndef __mir_mobile__Player__
#define __mir_mobile__Player__

#include <iostream>
#include "Monomer.h"

class Player: public Monomer {

	bool m_isMoveActions;

	MapPoint m_willGoPoint;

public:

	Player();

	virtual ~Player();

	static Player* sharePlayer();

	void initWithPlayer();

	virtual MoveInfo runBy(MapPoint point);

	virtual MoveInfo walkBy(MapPoint point);

	virtual MoveInfo goTo(MapPoint point);

	void stand();

	virtual void addAgainstMe(Monomer* var, float blood);

	void setBlood(int var);

	void setMagic(int var);

	virtual void clearData();

protected:

	void waitRunBy();

	void waitWalkBy();

	void waitGoTo();

	void setTray();

	virtual void detectionOfEachOther();

	virtual void detectionWhetherCounter();

	void detectionReplaceBgMap(float delay = 0);

	void detectionPropItems(float delay = 0);

	virtual void moveByEnd();

	virtual void goBegin();

	virtual void goEnd();

	virtual bool attackEnemy();

	virtual void followAttack();

	virtual void death();

	virtual void attacking();

	virtual void underAttack();

	virtual void setFigureState(FigureStateType stateType, FigureDirectionType directionType);

};
#endif