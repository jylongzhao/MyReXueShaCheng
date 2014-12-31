//
//  GameSocket.h
//  mir-mobile
//
//  Created by ÀõÔª·å on 13-12-17.
//
//

#ifndef __mir_mobile__GameSocket__
#define __mir_mobile__GameSocket__

#include <iostream>
#include "Monomer.h"

class GameSocket {

public:

	static void attack(Monomer* one, Monomer* two, int skillNumber);

	static void attackGroup(Monomer* one, vector<Monomer*> two, int skillNumber);

	static void sendRoleCreate(CCNode* node, int roleID, const char* nickName);
};

#endif /* defined(__mir_mobile__GameSocket__) */
