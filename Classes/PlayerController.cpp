//
//  PlayerController.cpp
//  mir-mobile
//
//  出自九秒社区 http://www.9miao.com
//  Created by 栗元峰 on 13-12-27.
//
//

#include "PlayerController.h"

static PlayerController* _playerController = NULL;

PlayerController* PlayerController::sharePlayerController()
{
	if (_playerController == NULL)
	{
		_playerController = new PlayerController();
		_playerController->init();
	}
	return _playerController;
}

PlayerController::PlayerController()
	:m_playerNumber(11001)
	,m_hairNumber(1100)
	,m_weaponsNumber(0)
{

}

PlayerController::~PlayerController()
{

}

bool PlayerController::init()
{



	return true;
}