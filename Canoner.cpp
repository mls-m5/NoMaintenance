/*
 * Canoner.cpp
 *
 *  Created on: 30 jan 2013
 *      Author: mattias
 */

#include "Canoner.h"
#include "aux.h"
#include "Player.h"
#include "Bomb.h"
Canoner::~Canoner() {
}


void Canoner::Fire(double X, double Y, double XAim, double YAim, int Turn,
		bool isFire) {

	if (!isFire) { return;}
	if (MyPlayer->getItem(1) < 200 || MyPlayer->getItem(2) < 10) { return;}
	MyPlayer->CalcItem(1, -200);
	MyPlayer->CalcItem(2, -10);
	auto nBomb = new Bomb();
	nBomb->Init(X + XAim / 3 * Turn, Y + YAim / 3, XAim / 5 * Turn, YAim / 5);
	FrmScreen.AddObject(nBomb);
	if (XAim != 0 && YAim != 0) {
		PlaySound(dsFire5);
	}
	else{
		PlaySound(dsLaunch);
	}
}
