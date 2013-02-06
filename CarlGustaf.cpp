/*
 * CarlGustaf.cpp
 *
 *  Created on: 6 feb 2013
 *      Author: mattias
 */

#include "CarlGustaf.h"
#include "aux.h"
#include "Missile.h"

CarlGustaf::CarlGustaf() {
	// TODO Auto-generated constructor stub

}

CarlGustaf::~CarlGustaf() {
	// TODO Auto-generated destructor stub
}

void CarlGustaf::Fire(double X, double Y, double XAim, double YAim, int Turn,
		bool isFire) {
    if (!isFire) { return;;}
    if (MyPlayer->getItem(1) < 200 || MyPlayer->getItem(2) < 20) { return;}
    MyPlayer->CalcItem(1, -200);
    MyPlayer->CalcItem(2, -20);
    Player * Target;
    auto nMissile = new Missile;
    if (FrmScreen.getPlayer(0) == MyPlayer) {
    	Target = FrmScreen.getPlayer(1);
    }
    else{
    	Target = FrmScreen.getPlayer(0);
    }
    nMissile->Init(X + XAim / 3 * Turn, Y + YAim / 3, XAim / 7 * Turn, YAim / 7, Target);
    FrmScreen.AddObject(nMissile);
    if (XAim || YAim) {
    	PlaySound(dsFire5);
    }
    else{
    	PlaySound(dsLaunch);
    }

}


