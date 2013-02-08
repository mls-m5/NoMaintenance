/*
 * Jolt.cpp
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#include "Jolt.h"
#include "common.h"
#include "Plasma.h"

Jolt::Jolt() {
	Delay = 0;

}

Jolt::~Jolt() {
	// TODO Auto-generated destructor stub
}

void Jolt::Fire(double X, double Y, double XAim, double YAim, int Turn,
		bool isFire) {
    if (!isFire) { return;;}
    if (Delay > 0) { Delay = Delay - 1;}
    if (MyPlayer->getItem(1) < 150 || (MyPlayer->getItem(2) < 10 && Delay > 0)) { return;;}
    MyPlayer->CalcItem(1, -150);
    MyPlayer->CalcItem(2, -20);
    Delay = 15;
    auto nPlasma = new Plasma;
    nPlasma->Init(X + XAim / 3 * Turn, Y + YAim / 3, XAim / 8 * Turn, YAim / 8);
    FrmScreen.AddObject(nPlasma);
    PlaySound(dsFire2);

}


