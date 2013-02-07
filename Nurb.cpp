/*
 * Nurb.cpp
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#include "Nurb.h"
#include "aux.h"
#include "Fire.h"

Nurb::Nurb() {
	// TODO Auto-generated constructor stub

}

Nurb::~Nurb() {
	// TODO Auto-generated destructor stub
}

void Nurb::Fire(double X, double Y, double XAim, double YAim, int Turn,
		bool isFire) {
    if (!isFire) { return;;}
    if (MyPlayer->getItem(1) < 10) { return;;}
    MyPlayer->CalcItem(1, -10);
    auto nFire = new class Fire;
    if ( MyPlayer->isGuy()) {
        nFire->Init(X + XAim / 4.5 * Turn, Y + YAim / 4.5, XAim / 10 * Turn + Rnd() * 2 - 1 + MyPlayer->XSpeed, YAim / 10 + Rnd() * 2 - 1 + MyPlayer->XSpeed);
    }else{
        nFire->Init(X + XAim / 3.5 * Turn, Y + YAim / 3.5, XAim / 10 * Turn + Rnd() * 2 - 1 + MyPlayer->XSpeed, YAim / 10 + Rnd() * 2 - 1 + MyPlayer->XSpeed);
    }
    FrmScreen.AddObject(nFire);
}


