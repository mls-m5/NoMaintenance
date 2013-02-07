/*
 * Zookaba.cpp
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#include "Zookaba.h"
#include "aux.h"
#include "ZookabaProj.h"

Zookaba::Zookaba() {
	Delay = 0;

}

Zookaba::~Zookaba() {
}

void Zookaba::Fire(double X, double Y, double XAim, double YAim, int Turn,
		bool isFire) {
    FrmScreen.SetWeaponBar (MyPlayer->MyNumber, (double)Delay / 15.);
    if (Delay > 0) {
    	Delay = Delay - 1;
    	return;
    }
    if (!isFire) { return;;}
    if (MyPlayer->getItem(1) < 200 || (MyPlayer->getItem(2) < 10 && Delay > 0)) { return;;}
    MyPlayer->CalcItem(1, -200);
    MyPlayer->CalcItem(2, -10);
    Delay = 15;
    auto nMissile = new ZookabaProj;
    nMissile->Init(X + XAim / 3 * Turn, Y + YAim / 3, XAim / 7 * Turn, YAim / 7);
    FrmScreen.AddObject(nMissile);
    PlaySound(dsFire5);
}


