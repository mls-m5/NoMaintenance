/*
 * Minuteman.cpp
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#include "Minuteman.h"
#include "NukeMissile.h"
#include "common.h"

Minuteman::Minuteman() {
	// TODO Auto-generated constructor stub

}

Minuteman::~Minuteman() {
	// TODO Auto-generated destructor stub
}

void Minuteman::Fire(double X, double Y, double XAim, double YAim, int Turn,
		bool isFire) {
	if (!isFire) return;
    if (MyPlayer->getItem(1) < 200 || MyPlayer->getItem(2) < 200) { return;;}
    MyPlayer->CalcItem(1, -200);
    MyPlayer->CalcItem(2, -200);
    auto nMissile = new NukeMissile;
    Player *Target;
    if (FrmScreen.getPlayer(0) == MyPlayer) {
    	Target = FrmScreen.getPlayer(1);
    }
    else{
    	Target = FrmScreen.getPlayer(0);
    }
    nMissile->Init(Target->XPos);
    FrmScreen.AddObject(nMissile);

}


