/*
 * EldFunkar.cpp
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#include "EldFunkar.h"
#include "aux.h"
#include "EldFunkarProj.h"

EldFunkar::EldFunkar() {
	// TODO Auto-generated constructor stub

}

EldFunkar::~EldFunkar() {
	// TODO Auto-generated destructor stub
}

void EldFunkar::Fire(double X, double Y, double XAim, double YAim, int Turn,
		bool isFire) {
//    FrmScreen.SetWeaponBar( MyPlayer->MyNumber, 100 * Delay \ 15);
    if (Delay > 0) { Delay = Delay - 1;}
    if (! isFire) { return;}
    if (MyPlayer->getItem(1) < 200 || (MyPlayer->getItem(2) < 20 && Delay > 0)) { return;;}
    MyPlayer->CalcItem(1, -200);
    MyPlayer->CalcItem(2, -20);
    Delay = 15;
    auto nMissile = new EldFunkarProj;
    nMissile->Init(X + XAim / 3 * Turn, Y + YAim / 3, XAim / 7 * Turn, YAim / 7);
    FrmScreen.AddObject(nMissile);
    PlaySound(dsFire5);
}


